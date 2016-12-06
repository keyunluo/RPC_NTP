#pragma once

#ifndef PIMPL_H_TV7E3C9K
#define PIMPL_H_TV7E3C9K

#include "pimpl_ptr.hh"

#ifdef _MSC_VER
#define TINYRPC_DEF_ALIGN 8
#else
#define TINYRPC_DEF_ALIGN 8
#endif

#define TINYRPC_DECL_PIMPL(Size)                                                \
    struct impl;                                                               \
    pimpl_ptr<impl, Size, TINYRPC_DEF_ALIGN> pimpl;

#endif /* end of include guard: PIMPL_H_TV7E3C9K */
