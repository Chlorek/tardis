/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   algorithms.hpp
 * Author: chlorek
 *
 * Created on October 23, 2017, 12:52 AM
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <cstdint>

namespace tardis {
    typedef int64_t (*pairing_functor)(const int16_t& x, const int16_t& y);
    pairing_functor cantor_pairing = [](const int16_t& x, const int16_t& y) -> int64_t {
        auto A = (uint64_t)(x >= 0 ? 2 * (int64_t)x : -2 * (int64_t)x - 1);
        auto B = (uint64_t)(y >= 0 ? 2 * (int64_t)y : -2 * (int64_t)y - 1);
        auto C = (int64_t)((A >= B ? A * A + A + B : A + B * B) / 2);
        return (x < 0 && y < 0) || (x >= 0 && y >= 0) ? C : -C - 1;
    };
}

#endif /* ALGORITHMS_HPP */

