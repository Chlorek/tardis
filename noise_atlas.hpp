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
#include <cstring>
#include <limits>
#include <cassert>
#include <memory>

namespace tardis {
    template<typename T>
    class noise_atlas : public noise_source {
        public:
            noise_atlas(T atlas_src) {
                this->atlas_src = std::make_shared<T>(atlas_src);
            }
            
            noise_atlas(const noise_atlas& orig) {
                atlas_src = orig.atlas_src;
                sources_size = orig.sources_size;
                highest_src = orig.highest_src;
                delete[] sources;
                sources = new std::shared_ptr<noise_source>[sources_size];
                for(std::size_t i = 0; i < sources_size; ++i)
                    sources[i] = orig.sources[i];
            }
            
            virtual ~noise_atlas() {
                delete[] sources;
            }
            
            /* bind_val must be non-negative value */
            template<typename U>
            void bind(const int32_t bind_val, U gen) {
                assert(bind_val >= 0);
                if(bind_val > highest_src || sources_size == 0) {
                    std::shared_ptr<noise_source>* newSources = new std::shared_ptr<noise_source>[bind_val+1];

                    // copy existing elements
                    for(uint32_t i = 0; i < sources_size; ++i)
                        newSources[i] = sources[i];
                    // fill missing with nullptr
                    for(int32_t i = sources_size; i < bind_val; ++i)
                        newSources[i] = nullptr;
                    // finally add new value
                    newSources[bind_val] = std::make_shared<U>(gen);
                    
                    delete[] sources;
                    sources = newSources;
                    
                    highest_src = bind_val;
                    sources_size = bind_val+1;
                }
                else {
                    sources[bind_val] = std::make_shared<U>(gen);
                }
            }
            
            int32_t at(int16_t x, int16_t y) {
                auto h = atlas_src->at(x, y);
                if(h <= highest_src && sources[h] != nullptr)
                    return sources[h]->at(x, y);
                return 0;
            }
        private:
            std::shared_ptr<T> atlas_src;
            std::shared_ptr<noise_source>* sources = new std::shared_ptr<noise_source>[0];
            std::size_t sources_size = 0;
            int32_t highest_src = 0;
    };
}

#endif /* NOISE_ATLAS_HPP */

