#pragma once

#ifndef ALL_H_H8MAAYCG
#define ALL_H_H8MAAYCG

#include "invoke.h"
#include "if.h"
#include "bool.h"

namespace tinyrpc {
namespace detail {

//! \brief This type can be used to check multiple conditions.
//! It will be true_type if all its arguments are true.
template <typename... T> struct all : true_ {};

template <typename H, typename... T>
struct all<H, T...>
    : if_<H, all<T...>, false_> {};

}
}



#endif /* end of include guard: ALL_H_H8MAAYCG */
