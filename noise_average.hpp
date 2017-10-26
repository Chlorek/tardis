/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_average.hpp
 * Author: chlorek
 *
 * Created on October 26, 2017, 6:06 PM
 */

#ifndef NOISE_AVERAGE_HPP
#define NOISE_AVERAGE_HPP

#include "noise_layered.hpp"

namespace tardis {
    template<typename T>
    class noise_average : public noise_layered<T> {
        public:
            noise_average(T src, std::vector<float> magnification) : noise_layered<T>(src, magnification) {
                //..
            }
            
            int32_t at(int16_t x, int16_t y) override {
                int32_t result = 0;
                // wont overflow, size is checked in constructor
                for(uint8_t i = 0; i < this->magnification.size(); ++i)
                    result += this->src_ptr->raw_at((float)x/this->magnification[i], (float)y/this->magnification[i]);
                return result / this->magnification.size();
            }
    };
}

#endif /* NOISE_AVERAGE_HPP */

