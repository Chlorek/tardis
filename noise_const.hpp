/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_const.hpp
 * Author: chlorek
 *
 * Created on October 13, 2017, 5:34 PM
 */

#ifndef NOISE_CONST_HPP
#define NOISE_CONST_HPP

#include "noise_source.hpp"

namespace tardis {
    class noise_const : public noise_source {
        public:
            noise_const(int32_t val)
                : val(val) {
                //..
            }
            
            noise_const(const noise_const& orig) {
                val = orig.val;
            }
            
            virtual ~noise_const() {
                //..
            }
            
            int32_t at(int16_t x, int16_t y) override {
                return val;
            }
        private:
            int32_t val;
    };
}

#endif /* NOISE_CONST_HPP */

