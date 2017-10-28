/*
 * This file is part of Tardis project,
 * licensed under conditions described in LICENSE file
 * included along. Every copy of this file
 * shall require distributing it with LICENSE file.
 */

/* 
 * File:   noise_atlas.hpp
 * Author: chlorek
 *
 * Created on October 21, 2017, 6:30 PM
 */

#ifndef NOISE_ATLAS_HPP
#define NOISE_ATLAS_HPP

#include "noise_source.hpp"
#include <utility>
#include <cstddef>
#include <memory>
#include <vector>
#include <functional>

namespace tardis {  
    template<typename T>
    class noise_atlas : public noise_source {
        private:
            struct dict {
                dict(const std::function<bool(int32_t)>& check_func, std::shared_ptr<noise_source> gen) :
                check_func(check_func), gen(gen) {};
                
                const std::function<bool(int32_t)> check_func;
                std::shared_ptr<noise_source> gen;
            };
        public:
            noise_atlas(T atlas_src) {
                this->atlas_src = std::make_shared<T>(atlas_src);
            }
            
            noise_atlas(const noise_atlas& orig) {
                atlas_src = orig.atlas_src;
                atlas_dict = orig.atlas_dict;
            }
            
            virtual ~noise_atlas() {
                //..
            }
            
            template<typename NS>
            void bind(const std::function<bool(int32_t)>& cf, NS gen) {
                atlas_dict.push_back(dict(cf, std::make_shared<NS>(gen)));
            }
            
            template<typename NS>
            void bind(int32_t val, NS gen) {
                atlas_dict.push_back(dict([val](int32_t v) {return v==val;}, std::make_shared<NS>(gen)));
            }
            
            int32_t at(int16_t x, int16_t y) {
                auto v = atlas_src->at(x, y);
                for(dict check : atlas_dict) {
                    if(check.check_func(v))
                        return check.gen->at(x, y);
                }
                return 0;
            }
        private:
            std::shared_ptr<T> atlas_src;
            std::vector<dict> atlas_dict;
    };
}

#endif /* NOISE_ATLAS_HPP */

