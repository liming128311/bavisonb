/*
Copyright (c) 2015, RISC OS Open Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define _GNU_SOURCE /* enable mempcpy */
#include <string.h>

extern int architecture(void);

#define DISPATCH(ret_type, func, args_full, args) \
                                                  \
typeof(func) func##_arm1176jzfs;                  \
typeof(func) func##_cortexa7;                     \
static typeof(func) func##_initial;               \
static typeof(func) *p##func = func##_initial;    \
                                                  \
ret_type (func) args_full                         \
{                                                 \
    return p##func args;                          \
}                                                 \
                                                  \
static ret_type func##_initial args_full          \
{                                                 \
    if (architecture() == 6)                      \
        p##func = func##_arm1176jzfs;             \
    else                                          \
        p##func = func##_cortexa7;                \
    return p##func args;                          \
}

DISPATCH(void *, memcpy,   (void *__restrict __dest, __const void *__restrict __src, size_t __n), (__dest, __src, __n))
DISPATCH(void *, memmove,  (void *           __dest, __const void *           __src, size_t __n), (__dest, __src, __n))
DISPATCH(void *,__mempcpy, (void *__restrict __dest, __const void *__restrict __src, size_t __n), (__dest, __src, __n))
DISPATCH(void *, mempcpy,  (void *__restrict __dest, __const void *__restrict __src, size_t __n), (__dest, __src, __n))
DISPATCH(void *, memset,   (void *           __s,    int                      __c,   size_t __n), (__s,    __c,   __n))
