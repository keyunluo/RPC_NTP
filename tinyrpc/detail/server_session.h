#pragma once

#ifndef SESSION_H_5KG6ZMAB
#define SESSION_H_5KG6ZMAB

#include "asio.hpp"
#include "log.h"
#include "msgpack.hpp"
#include <memory>
#include <vector>
#include <msgpack.hpp>

#include "async_writer.h"
#include "core/dispatcher.h"

namespace tinyrpc {
namespace detail {

class server_session : public async_writer,
                       public std::enable_shared_from_this<server_session> {
public:
    server_session(tiny_rpc_asio::io_service *io, tiny_rpc_asio::ip::tcp::socket socket,
                   std::shared_ptr<dispatcher> disp, bool suppress_exceptions);
    void start();
    void stop();

private:
    void do_read();

private:
    tiny_rpc_asio::io_service *io_;
    tiny_rpc_asio::strand read_strand_;
    std::shared_ptr<dispatcher> disp_;
    msgpack::unpacker pac_;
    msgpack::sbuffer output_buf_;
    const bool suppress_exceptions_;
    static const uint32_t default_buffer_size = 4096;
    TINYRPC_CREATE_LOG_CHANNEL(session)
};
} /* detail */
} /* tinyrpc */

#endif /* end of include guard: SESSION_H_5KG6ZMAB */
