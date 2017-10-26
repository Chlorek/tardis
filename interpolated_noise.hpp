/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   interpolated_noise.hpp
 * Author: chlorek
 *
 * Created on October 25, 2017, 6:26 PM
 */

#ifndef INTERPOLATED_NOISE_HPP
#define INTERPOLATED_NOISE_HPP

#include "smooth_noise.hpp"
#include "algorithms.hpp"

namespace tardis {
    class intrpl_noise : public smooth_noise {
        public:
            intrpl_noise(int16_t min, int16_t amplitude, float magnification, pairing_functor pair_func = cantor_pairing)
                : smooth_noise(min, amplitude, magnification, pair_func) {
                //..
            }
                
            intrpl_noise(const intrpl_noise& orig) : smooth_noise(orig) {};
            
            virtual ~intrpl_noise() {
                //..
            }
            
            virtual int32_t at(int16_t x, int16_t y) override {
                return raw_at(x/magnification, y/magnification);
            }
            
            virtual int32_t raw_at(float x, float y) override {
                return interpolatedNoise(x, y) * amplitude + min;
            }
            
        protected:           
            /* Adds smooth transitions with floating points */
            float interpolatedNoise(float x, float y) {
                uint16_t intX = (uint16_t)x;
                float fractionalX = x - (float)intX;

                uint16_t intY = (uint16_t)y;
                float fractionalY = y - (float)intY;

                float v1 = smoothNoise(intX,     intY);
                float v2 = smoothNoise(intX + 1, intY);
                float v3 = smoothNoise(intX,     intY + 1);
                float v4 = smoothNoise(intX + 1, intY + 1);

                float i1 = lerp(v1, v2, fractionalX);
                float i2 = lerp(v3, v4, fractionalX);

                return lerp(i1, i2, fractionalY);
            }
    };
}

#endif /* INTERPOLATED_NOISE_HPP */

