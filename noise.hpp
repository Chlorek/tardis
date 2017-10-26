/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise.hpp
 * Author: chlorek
 *
 * Created on September 2, 2017, 12:36 AM
 */

#ifndef NOISE_HPP
#define NOISE_HPP

#include <cstdint>
#include <vector>
#include <stdexcept>
#include "noise_source.hpp"
#include "algorithms.hpp"

namespace tardis {
    class noise : public noise_source {
        template<typename T> friend class noise_layered;
        public:
            noise() = delete;
            
            noise(int16_t min, int16_t amplitude, float magnification, pairing_functor pair_func = cantor_pairing) : 
                min(min), amplitude(amplitude), magnification(magnification), pair_func(pair_func) {
                //..
            }
            
            noise(const noise& orig) {
                min = orig.min;
                amplitude = orig.amplitude;
                magnification = orig.magnification;
                pair_func = orig.pair_func;
            }
            
            virtual ~noise() {
                //..
            }
            
            virtual int32_t at(int16_t x, int16_t y) override {
                return raw_at(x/magnification, y/magnification);
            }
            
            /* Used by compositing classes with custom magnification (noise_layered for example) */
            virtual int32_t raw_at(float x, float y) {
                return randomFloat(x, y) * amplitude + min;
            }

            /* Returns float in range <0,1>.
             * Alters seed.
             */
            virtual float randomFloat(int64_t seed) {
                seed = (seed >> 13) ^ seed;
                int32_t nn = (seed * (seed * seed * 60493 + 19990303) + 1376312589) & 0x7fffffff;

                return ((double)nn / 1073741824.0) / 2;
            }
            
            virtual float randomFloat(int16_t x, int16_t y) {
                return randomFloat(pair_func(x, y));
            }
        protected:
            int16_t min, amplitude;
            float magnification;
            pairing_functor pair_func = nullptr;
    };
}
#endif /* NOISE_HPP */

