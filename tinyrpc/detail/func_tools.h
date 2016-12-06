#pragma once

#ifndef FUNC_TOOLS_H_9FNRD4G2
#define FUNC_TOOLS_H_9FNRD4G2

#include "invoke.h"
#include "all.h"
#include "any.h"

namespace tinyrpc {
namespace detail {


enum class enabled {};

template <typename... C>
using enable_if = invoke<std::enable_if<all<C...>::value, enabled>>;

template <typename... C>
using disable_if = invoke<std::enable_if<!any<C...>::value, enabled>>;


}
}

#endif /* end of include guard: FUNC_TOOLS_H_9FNRD4G2 */
