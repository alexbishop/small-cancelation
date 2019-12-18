#pragma once
#ifndef b2f9aa55_random_hpp
#define b2f9aa55_random_hpp

#include <random>
#include <array>
#include <cinttypes>
#include <functional>
#include <algorithm>

#include "permutations.hpp"
#include "cyclic_permutation.hpp"

std::mt19937 init_mersenne_twister () {

    std::array<std::uint32_t, 624> entropy;

    std::random_device real_random;
    std::generate(entropy.begin(), entropy.end(), std::ref(real_random));

    std::seed_seq seed_bits(entropy.begin(), entropy.end());

    return std::mt19937(seed_bits);

}

template <class E, class Word>
void generate_random_word (Word& word, int r, int length, E& engine) {

    word.resize(length);

    std::uniform_int_distribution<int> first_letter( 0, ((2*r)-1) );
    std::uniform_int_distribution<int> other_letter( 0, ((2*r)-2) );

    // randomly generate a freely reduced word until a cyclically reduced one is generated
    //  this is somewhat inefficient but it ensures uniform probability as is required
    while (true) {

        for (size_t i = 0; i < length; ++i) {
            if (i == 0) {
                word[i] = first_letter(engine);
            } else {

                const int prev = word[i-1];

                if ((prev % 2) == 0) {
                    word[i] = ( 2*r + prev - other_letter(engine) ) % (2*r);
                } else {
                    word[i] = ( prev + other_letter(engine) ) % (2*r);
                }

            }
        }

        for (size_t i = 0; i < length; ++i) {
            if (word[i] % 2 == 0) {
                word[i] = (word[i] / 2) + 1;
            } else {
                word[i] = - ( ((word[i] - 1) / 2) + 1);
            }
        }

        // check if the word is cyclically reduced
        if (word.front() != -word.back()) {
            break;
        }

    }

}

template <class E, class Words>
void generate_random_relations (Words& word, int r, int length, E& engine) {
	for (size_t i = 0; i < word.size(); ++i) {
        generate_random_word(word[i], r, length, engine);
    }
}

template <class E, class Words>
void generate_random_relations (Words& word, int r, int min_length, int max_length, E& engine) {

    if (min_length == max_length) {
        generate_random_relations(word, r, min_length, engine);
        return;
    }

    std::vector<double> weights;

    for (int l = min_length; l <= max_length; ++l) {
        if ((l % 2) == 0) {
            weights.push_back(pow(static_cast<double>(2*r-1), static_cast<double>(l)) + 1.0);
        } else {
            weights.push_back(pow(static_cast<double>(2*r-1), static_cast<double>(l)) + static_cast<double>(2*r-1));
        }
    }

    std::discrete_distribution<int> distribution(weights.begin(), weights.end());

    for (size_t i = 0; i < word.size(); ++i) {
        int length = min_length + distribution(engine);
        generate_random_word(word[i], r, length, engine);
    }

}

#endif

