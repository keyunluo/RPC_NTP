#pragma once

#ifndef DEV_UTILS_H_JQSWE2OS
#define DEV_UTILS_H_JQSWE2OS

#ifdef __GNUC__
#include "pthread.h"
#endif

namespace tinyrpc {
namespace detail {
inline void name_thread(std::string const &name) {
#ifdef __GNUC__
    pthread_setname_np(pthread_self(), name.c_str());
#endif
}
} /* detail */
} /* tinyrpc */

#endif /* end of include guard: DEV_UTILS_H_JQSWE2OS */
