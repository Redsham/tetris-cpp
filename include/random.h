#pragma once

#include <random>
#include <type_traits>

class Random {
public:
    // Returns a random integer in the range [min, max)
    template<typename IntType>
    static IntType int_in_range(const IntType min, const IntType max) {
        static_assert(std::is_integral_v<IntType>, "IntType must be integral");
        std::uniform_int_distribution<IntType> dist(min, max);
        return dist(engine());
    }

    // Returns a random real number in the range [min, max)
    template<typename RealType>
    static RealType real_in_range(const RealType min, const RealType max) {
        static_assert(std::is_floating_point_v<RealType>, "RealType must be floating point");
        std::uniform_real_distribution<RealType> dist(min, max);
        return dist(engine());
    }

    // Returns true with a probability of prob (0.0 to 1.0)
    static bool chance(const double prob) {
        std::bernoulli_distribution dist(prob);
        return dist(engine());
    }

    // Returns a random element from the container
    template<typename Container>
    static auto &choice(const Container &c) { return c[int_in_range<size_t>(0, c.size() - 1)]; }

    // Shuffles the elements in the range [first, last)
    template<typename RandomIt>
    static void shuffle(RandomIt first, RandomIt last) { std::shuffle(first, last, engine()); }

private:
    // Returns a reference to a thread-local random number generator
    static std::mt19937 &engine() {
        thread_local static std::mt19937 rng{std::random_device{}()};
        return rng;
    }
};
