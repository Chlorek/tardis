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
                return raw_at(x/magnification, y/magnification);
            }
            
            virtual int32_t raw_at(float x, float y) override {
                return smoothNoise(x, y) * amplitude + min;
            }
        protected:
            /* Smooths pixels a bit (average from surrounding points) */
            float smoothNoise(int16_t x, int16_t y) {
                float corners = (randomFloat(x-1, y-1)+randomFloat(x+1, y-1)+randomFloat(x-1, y+1)+randomFloat(x+1, y+1)) / 16;
                float sides   = (randomFloat(x-1, y  )+randomFloat(x+1, y  )+randomFloat(x,   y-1)+randomFloat(x,   y+1)) / 8;
                float center  =  randomFloat(x,   y)                                                                      / 4;

                return corners + sides + center;
            }
    };
}

#endif /* SMOOTH_NOISE_HPP */

