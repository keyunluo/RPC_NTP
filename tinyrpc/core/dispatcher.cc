#include "dispatcher.h"
#include "detail/log.h"
#include <cassert>

namespace tinyrpc {

void dispatcher::dispatch(msgpack::sbuffer const &msg) {
    msgpack::unpacked unpacked;
    msgpack::unpack(&unpacked, msg.data(), msg.size());
    dispatch(unpacked.get());
}

response dispatcher::dispatch(msgpack::object const &msg,
                              bool suppress_exceptions) {
    switch (msg.via.array.size) {
    case 3:
        return dispatch_notification(msg, suppress_exceptions);
    case 4:
        return dispatch_call(msg, suppress_exceptions);
    default:
        return response::empty();
    }
}

response dispatcher::dispatch_call(msgpack::object const &msg,
                                   bool suppress_exceptions) {
    call_t the_call;
    msg.convert(&the_call);

    auto &&type = std::get<0>(the_call);
    // TODO: proper validation of protocol (and responding to it)
    assert(type == 0);

    auto &&id = std::get<1>(the_call);
    auto &&name = std::get<2>(the_call);
    auto &&args = std::get<3>(the_call);

    auto it_func = funcs_.find(name);

    if (it_func != end(funcs_)) {
        LOG_DEBUG("Dispatching call to '{}'", name);
        try {
            auto result = (it_func->second)(args);
            return response(id, std::string(), std::move(result));
        } catch (std::exception &e) {
            if (!suppress_exceptions) {
                throw;
            }
            return response(id,
                            TINYRPC_FMT::format("callme: function '{0}' (taking {1} "
                                        "arg(s)) "
                                        "threw an exception. The exception "
                                        "contained this information: {2}.",
                                        name, args.via.array.size, e.what()));
        } catch (...) {
            if (!suppress_exceptions) {
                throw;
            }
            return response(
                id, TINYRPC_FMT::format("callme: function '{0}' (taking {1} "
                                "arg(s)) threw an exception. The exception "
                                "is not derived from std::exception. No "
                                "further information available.",
                                name, args.via.array.size));
        }
    }
    return response(id, TINYRPC_FMT::format("callme: server could not find "
                                    "function '{0}' with argument count {1}.",
                                    name, args.via.array.size));
}

response dispatcher::dispatch_notification(msgpack::object const &msg,
                                           bool suppress_exceptions) {
    notification_t the_call;
    msg.convert(&the_call);

    auto &&type = std::get<0>(the_call);
    // TODO: proper validation of protocol (and responding to it)
    assert(type == static_cast<uint8_t>(request_type::notification));

    auto &&name = std::get<1>(the_call);
    auto &&args = std::get<2>(the_call);

    auto it_func = funcs_.find(name);

    if (it_func != end(funcs_)) {
        LOG_DEBUG("Dispatching call to '{}'", name);
        try {
            auto result = (it_func->second)(args);
        } catch (std::exception &e) {
            if (!suppress_exceptions) {
                throw;
            }
        } catch (...) {
            if (!suppress_exceptions) {
                throw;
            }
        }
    }
    return response::empty();
}

void dispatcher::enforce_arg_count(std::string const &func, std::size_t found,
                                   std::size_t expected) {
    if (found != expected) {
        throw std::runtime_error(
            TINYRPC_FMT::format("Function '{0}' was called with an invalid number of "
                        "arguments. Expected: {1}, got: {2}",
                        func, expected, found));
    }
}

} /* callme */
