/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_layered.hpp
 * Author: chlorek
 *
 * Created on October 13, 2017, 6:36 PM
 */

#ifndef NOISE_LAYERED_HPP
#define NOISE_LAYERED_HPP

#include "noise_source.hpp"
#include "noise.hpp"
#include <vector>
#include <stdexcept>
#include <memory>

namespace tardis {
    template<typename T>
    class noise_layered : public noise_source {
        public:
            noise_layered(T src, std::vector<float> magnification) : magnification(magnification) {
                if(magnification.size() > 256) 
                    throw std::runtime_error("noise_layered: too many layers");
                for(auto mag : magnification)
                    if(mag == 0)
                        throw std::runtime_error("noise_layered: magnification equal 0");
                src_ptr = std::make_shared<T>(src);
            }
            
            noise_layered(const noise_layered& orig) {
                src_ptr = orig.src_ptr;
                magnification = orig.magnification;
            }
            
            ~noise_layered() {
                //..
            }
            
            virtual int32_t at(int16_t x, int16_t y) override {
                int32_t result = 0;
                // wont overflow, size is checked in constructor
                for(uint8_t i = 0; i < magnification.size(); ++i) {
                    auto height = src_ptr->raw_at((float)x/magnification[i], (float)y/magnification[i]);
                    switch(i) {
                        case 0 :
                            result += height;
                            break;
                        default:
                            result += (src_ptr->amplitude - result) * ((float)height/src_ptr->amplitude) / (i*2);
                    }
                }
                return result;
            }
        protected:
            std::shared_ptr<T> src_ptr = nullptr;
            std::vector<float> magnification; 
    };
}
#endif /* NOISE_LAYERED_HPP */

