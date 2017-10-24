# Tardis
## Introduction
C++ library for generating complex worlds height-maps. Named after Dr. Who's Tardis, and like his Tardis, this one will take you to countless places as well!

The generator is based on pure noise generator wrapped in simple yet powerful modern API.
This program originally began as my scholarship project, formerly *"Little Bang"*. The whole concept is still the same, but it was rewritten
to make it modular and extend its possibilities by allowing end user to use internal, basic functions, but without stripping ready-to-use features too,
these are built on top of those basic functions now. Everything is object-oriented so you can extend functionality to fit your wild needs.

Keep in mind it's not just noise generator like perlin noise (however basic output pretty much resembles it). Tardis lets you design
complicated sets of noises in easy to read and logical manner, with enough tinkering there is possibility to achieve *(I hope)* pretty much anything you want.

## Readme todo...

## How to use
It is not full coverage of API, just simple overview of how work with this library looks like:
'''
    auto combined = smooth_noise(0, 20, 100) + smooth_noise(0, 20, 35) + smooth_noise(0, 5, 15);
    for(/* loop over x */) {
        for(/* loop over y */) {
            heightmap[x][y] = combined.at(x, y);
        }
    }
'''
Variable heightmap is just pseudo-code. This example just adds 3 smooth noises output together.
You can also subtract, multiply and divide.

There is also class named *noise_atlas*, it is essential for generating biomes, islands, rivers etc.
To put it simple: it just takes noise source to determine noises to be used at given location.
'''
    noise_atlas<smooth_noise> atlas(smooth_noise(0, 3, 2));
    atlas.bind(0, noise_const(100));
    atlas.bind(1, noise_const(50));
    atlas.bind(2, noise_const(200));
    for(/* loop over x */) {
        for(/* loop over y */) {
            heightmap[x][y] = atlas.at(x, y);
        }
    }
'''

You can also perform changes to X and Y value and internal pairing algorithm. For details contact wiki (To-Do).

## Requirements
It is pure C++, all you need is compiler supporting C++14.

## Performance
It was designed with performance in mind, but there are little trade-offs introduced by easy to use C++ API. While it is not optimized yet, I think current performance is just enough though.
On my CPU (i5-3570, boost to 3,89GHz) algorithm works decently (generating square kilometers in few seconds). Of course performance heavily depends on what you want to achieve and how you do it,
this tool is not for instant effect - you design the desired outcome yourself.

Let's not forget about compiler - the very thing that determines how programs really perform, personally I develop it with GCC 7.1.1 and highest optimizations level.
Also that's why entire code is in headers, this way compiler knows what is inside that library and may apply best optimizations possible based on your case.

Also you can expect "set-up" functions to be slow - they are not optimized, as by design they will be called mostly during startup/loading. By "set-up" functions I mean anything you
use in your noise design process, look at it this way: everything but *at()* methods is not important for high-map generation time.
Still, it does not mean these functions have to be slow, most likely you will be able to make billions of calls in no time, but simply more work was moved there to make 
generator faster in the end.

When it comes to multi-threading, designing noises is not thread-safe, but generation is totally fine to be run in parallel and I bet you can greatly benefit from that.

## Stability
Stability leads to three different aspects - stability of the API, the runtime and output consistency.
* API is generally designed in its final form, however some updates requiring you to apply *little* changes to your code may and probably
will happen (shall take no more but a few minutes of your time)
* runtime stability was tested many times but so far in 64-bit only and on Linux (which has true, non-limited word sizes, compared to Windows) and is supposed to work fine
for extended periods of time and without memory-leaks.
* output is guaranteed to be consistent across future updates, but only when it comes to basic functions, anything that is made to be easy-to-use wrapper, for example
*noise_layered* class may change anytime. However if some algorithm that changes behavior is replaced, old one will stay available, but moved to tardis::compat namespace
and/or renamed.

## Licensing
Tardis is licensed under custom license. Read LICENSE for details.

In short: it is pretty much open-source, free for non-commercial use.
If you like this piece of software and would like to use it in your own commercial project, consider buying rights (for symbolic value)
for commercial use and possibility to make your product closed source. Details of course in LICENSE file.