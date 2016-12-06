#include "server_session.h"
#include "log.h"

namespace tinyrpc {
namespace detail {

server_session::server_session(tiny_rpc_asio::io_service *io,
                               tiny_rpc_asio::ip::tcp::socket socket,
                               std::shared_ptr<dispatcher> disp,
                               bool suppress_exceptions)
    : async_writer(io, std::move(socket)),
      io_(io),
      read_strand_(*io),
      disp_(disp),
      pac_(),
      suppress_exceptions_(suppress_exceptions) {
    pac_.reserve_buffer(default_buffer_size); // TODO: make this configurable
                                              // [sztomi 2016-01-13]
}

void server_session::start() { do_read(); }

void server_session::stop() { socket_.close(); }

void server_session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        tiny_rpc_asio::buffer(pac_.buffer(), default_buffer_size),
        read_strand_.wrap([this, self](std::error_code ec, std::size_t length) {
            if (!ec) {
                pac_.buffer_consumed(length);
                msgpack::unpacked result;
                while (pac_.next(&result)) {
                    auto msg = result.get();
                    output_buf_.clear();

                    // any worker thread can take this call
                    io_->post([this, msg, z = std::shared_ptr<msgpack::zone>(result.zone().release())]() {
                        auto resp = disp_->dispatch(msg, suppress_exceptions_);
                        if (!resp.is_empty()) {
#ifdef _MSC_VER
                            // doesn't compile otherwise.
                            write_strand_.post(
                                [=]() { write(resp.get_data()); });
#else
                            write_strand_.post(
                                [this, resp, z]() { write(resp.get_data()); });
#endif
                        }
                    });
                }

                do_read();
            }
        }));
}

} /* detail */
} /* tinyrpc */
