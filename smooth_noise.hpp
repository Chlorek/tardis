/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   smooth_noise.hpp
 * Author: chlorek
 *
 * Created on September 2, 2017, 5:01 PM
 */

#ifndef SMOOTH_NOISE_HPP
#define SMOOTH_NOISE_HPP

#include "noise.hpp"

namespace tardis {
    inline static float lerp(float a, float b, float weight) {
        return a*(1-weight) + b*weight;
    }
    
    class smooth_noise : public noise {
        public:
            smooth_noise(int16_t min, int16_t amplitude, float magnification, pairing_functor pair_func = cantor_pairing)
                : noise(min, amplitude, magnification, pair_func) {
                //..
            }
                
            smooth_noise(const smooth_noise& orig) : noise(orig) {};
            
            virtual ~smooth_noise() {
                //..
            }
            
            virtual int32_t at(int16_t x, int16_t y) override  {
                return interpolatedNoise((float)x/magnification, (float)y/magnification) * amplitude + min;
            }
        protected:
            /* Smooths pixels a bit (average from surrounding points) */
            float smoothNoise(int16_t x, int16_t y)  {
                float corners = (randomFloat(x-1, y-1)+randomFloat(x+1, y-1)+randomFloat(x-1, y+1)+randomFloat(x+1, y+1)) / 16;
                float sides   = (randomFloat(x-1, y  )+randomFloat(x+1, y  )+randomFloat(x,   y-1)+randomFloat(x,   y+1)) / 8;
                float center  =  randomFloat(x,   y)                                                                      / 4;

                return corners + sides + center;
            }
            
            /* Adds smooth transitions with floating points */
            float interpolatedNoise(float x, float y)  {
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

#endif /* SMOOTH_NOISE_HPP */

