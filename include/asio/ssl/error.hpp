//
// ssl/error.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_SSL_ERROR_HPP
#define ASIO_SSL_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/error_code.hpp"

#include "asio/detail/push_options.hpp"

namespace tiny_rpc_asio {
namespace error {

enum ssl_errors
{
};

extern ASIO_DECL
const tiny_rpc_asio::error_category& get_ssl_category();

static const tiny_rpc_asio::error_category& ssl_category
  = tiny_rpc_asio::error::get_ssl_category();

} // namespace error
} // namespace tiny_rpc_asio

#if defined(ASIO_HAS_STD_SYSTEM_ERROR)
namespace std {

template<> struct is_error_code_enum<tiny_rpc_asio::error::ssl_errors>
{
  static const bool value = true;
};

} // namespace std
#endif // defined(ASIO_HAS_STD_SYSTEM_ERROR)

namespace tiny_rpc_asio {
namespace error {

inline tiny_rpc_asio::error_code make_error_code(ssl_errors e)
{
  return tiny_rpc_asio::error_code(
      static_cast<int>(e), get_ssl_category());
}

} // namespace error
} // namespace tiny_rpc_asio

#include "asio/detail/pop_options.hpp"

#if defined(ASIO_HEADER_ONLY)
# include "asio/ssl/impl/error.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_SSL_ERROR_HPP
