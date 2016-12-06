#pragma once

#ifndef SERVER_H_S0HB5KXY
#define SERVER_H_S0HB5KXY

#include "msgpack.hpp"

#include "core/dispatcher.h"
#include "detail/pimpl.h"
#include "core/config.h"

namespace tinyrpc {

//! \brief Implements a msgpack-rpc server. This is the main interfacing
//! point with the library for creating servers.
class server {
public:
    explicit server(std::string const &address, uint16_t port);
    ~server();

    //! \brief Starts the server loop. This is a blocking call.
    void run();

    //! \brief Starts the server loop on a separate thread. This is a
    //! non-blocking call.
    //! \param worker_threads The number of worker threads to start.
    void async_run(std::size_t worker_threads = 1);

    //! \brief Binds a functor to a name so it becomes callable via RPC.
    //! \param name The name of the functor.
    //! \param func The functor to bind.
    //! \tparam F The type of the functor.
    template <typename F> void bind(std::string const &name, F func) {
        disp_->bind(name, func);
    }

    //! \brief Sets the exception behavior in handlers. By default,
    //! handlers throwing will crash the server. If suppressing is on,
    //! the server will try to gather textual data and return it to
    //! the client as an error response.
    //! \note Setting this flag only affects subsequent connections.
    void suppress_exceptions(bool suppress);

private:
	//TINYRPC_DECL_PIMPL(172)
	TINYRPC_DECL_PIMPL(768)
    std::shared_ptr<dispatcher> disp_;
};

}

#endif /* end of include guard: SERVER_H_S0HB5KXY */
