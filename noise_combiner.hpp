/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_combiner.hpp
 * Author: chlorek
 *
 * Created on September 2, 2017, 8:05 PM
 */

#ifndef NOISE_COMBINER_HPP
#define NOISE_COMBINER_HPP

#include "noise_source.hpp"
#include "combine_operation.hpp"
#include "noise.hpp"
#include <vector>
#include <utility>
#include <exception>

namespace tardis {
    class noise_combiner : public noise_source {
        public:
            noise_combiner(std::shared_ptr<noise_source> src_t, std::shared_ptr<noise_source> src_u, combine_operation operation)
                : src_t(src_t), src_u(src_u), operation(operation) {
                //..
            }
                
            noise_combiner(const noise_combiner& orig) {
                src_t = orig.src_t;
                src_u = orig.src_u;
                operation = orig.operation;
            }
            
            virtual ~noise_combiner() {
                //..
            }

            int32_t at(int16_t x, int16_t y) override {
                switch(operation) {
                    case combine_operation::ADD :
                        return src_t->at(x, y) + src_u->at(x, y);
                        break;
                    case combine_operation::SUB :
                        return src_t->at(x, y) - src_u->at(x, y);
                        break;
                    case combine_operation::DIV :
                        return src_t->at(x, y) / src_u->at(x, y);
                        break;
                    case combine_operation::MUL :
                        return src_t->at(x, y) * src_u->at(x, y);
                        break;
                    default:
                        throw std::runtime_error("noise_combiner: unknown operation");
                }
            }
        private:
            std::shared_ptr<noise_source> src_t, src_u;
            combine_operation operation;
    };
}

#endif /* NOISE_COMBINER_HPP */

