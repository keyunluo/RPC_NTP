#pragma once

#ifndef RESPONSE_H_MVRZEKPX
#define RESPONSE_H_MVRZEKPX

#include "detail/log.h"
#include "detail/object.h"
#include "msgpack.hpp"

namespace tinyrpc {

//! \brief Represents a response and creates a msgpack to be sent back
//! as per the msgpack-rpc spec.
class response {
public:
    //! \brief Constructs a msgpack::response with the given values.
    response(uint32_t id, std::string const &error,
             std::unique_ptr<msgpack::object_handle> result =
                 std::unique_ptr<msgpack::object_handle>());

    //! \brief Constructs a response from msgpack::object (useful when
    //! reading a response from a stream).
    response(msgpack::object_handle o);

    //! \brief Gets the response data as a msgpack::sbuffer.
    msgpack::sbuffer get_data() const;

    //! \brief Returns the call id/index used to identify which call
    //! this response corresponds to.
    int get_id() const;

    //! \brief Returns the error message stored in the response. Can
    //! be empty.
    std::string const &get_error() const;

    //! \brief Returns the result stored in the response. Can be empty.
    msgpack::object_handle get_result() const;

    //! \brief Gets an empty response which means "no response" (not to be
    //! confused with void return, i.e. this means literally
    //! "don't write the response to the socket")
    static response &empty();

    //! \brief If true, this response is empty (\see empty())
    bool is_empty() const;

    //! \brief The type of a response, according to the msgpack-rpc spec
    using response_type =
        std::tuple<uint32_t, uint32_t, msgpack::object, msgpack::object>;

private:
    response();

private:
    uint32_t id_;
    std::string error_;
    // I really wish to avoid shared_ptr here but at this point asio does not
    // work with move-only handlers in post() and I need to capture responses
    // in lambdas.
    std::shared_ptr<msgpack::object_handle> result_;
    bool empty_;
    TINYRPC_CREATE_LOG_CHANNEL(response)
};

} /* callme  */

#endif /* end of include guard: RESPONSE_H_MVRZEKPX */
