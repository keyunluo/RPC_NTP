#pragma once

#ifndef NOT_H_0MEGQWII
#define NOT_H_0MEGQWII

#include "bool.h"

namespace tinyrpc {
namespace detail {

template<typename B>
using not_ = bool_<!B::value>;

}
}

#endif /* end of include guard: NOT_H_0MEGQWII */
