/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_source.hpp
 * Author: chlorek
 *
 * Created on September 5, 2017, 4:30 PM
 */

#ifndef NOISE_SOURCE_HPP
#define NOISE_SOURCE_HPP

#include "combine_operation.hpp"
#include <cstdint>
#include <memory>

namespace tardis {
    class noise_combiner;
    
    /* Anything to be used in combiner must derive from this class */
    class noise_source {
        public:
            noise_source() {};
            noise_source(const noise_source& orig) {};
            virtual ~noise_source() {};
            
            virtual int32_t at(int16_t x, int16_t y) = 0;
            
            template<typename T, typename U>
            friend noise_combiner& operator+ (T src, U src2) {
                std::shared_ptr<T> src_ptr = std::make_shared<T>(src);
                std::shared_ptr<U> src2_ptr = std::make_shared<U>(src2);
                noise_combiner* combiner = new noise_combiner(src_ptr, src2_ptr, combine_operation::ADD);
                return *combiner;
            }
            
            template<typename T, typename U>
            friend noise_combiner& operator- (T src, U src2) {
                std::shared_ptr<T> src_ptr = std::make_shared(src);
                std::shared_ptr<U> src2_ptr = std::make_shared(src2);
                noise_combiner* combiner = new noise_combiner(src_ptr, src2_ptr, combine_operation::SUB);
                return *combiner;
            }
            
            template<typename T, typename U>
            friend noise_combiner& operator* (T src, U src2) {
                std::shared_ptr<T> src_ptr = std::make_shared(src);
                std::shared_ptr<U> src2_ptr = std::make_shared(src2);
                noise_combiner* combiner = new noise_combiner(src_ptr, src2_ptr, combine_operation::MUL);
                return *combiner;
            }
            
            template<typename T, typename U>
            friend noise_combiner& operator/ (T src, U src2) {
                std::shared_ptr<T> src_ptr = std::make_shared(src);
                std::shared_ptr<U> src2_ptr = std::make_shared(src2);
                noise_combiner* combiner = new noise_combiner(src_ptr, src2_ptr, combine_operation::DIV);
                return *combiner;
            }
        protected:
    };
}

#endif /* NOISE_SOURCE_HPP */

