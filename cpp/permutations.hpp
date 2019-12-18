#pragma once
#ifndef b2f9aa55_permutation_checker_hpp
#define b2f9aa55_permutation_checker_hpp

#include <algorithm>
#include <cinttypes>
#include <utility>

#include "cyclic_permutation.hpp"
#include "fraction.hpp"

template <class U, class V>
static fraction small_cancelation_by_prefix (const U& array1, const V& array2) {

    const std::size_t min_word_size = std::min(array1.size(), array2.size());

    std::size_t i;

    for (i = 0; i < min_word_size; ++i) {
        if (array1[i] != array2[i]) {
            break;
        }
    }

    return fraction(i, min_word_size);

}

template <class U, class V>
static bool small_cancelation_with_permutations (const U& array1, const V& array2, const fraction lambda) {

    auto perm_array1 = make_cyclic_permutation(array1);
    auto perm_array2 = make_cyclic_permutation(array2);

    for (std::size_t i = 0; i < perm_array1.size(); ++i, ++perm_array1) {
        for (std::size_t j = 0; j < perm_array2.size(); ++j, ++perm_array2) {
            for (int k = 0; k < 2; ++k, perm_array1.negate()) {
                for (int l = 0; l < 2; ++l, perm_array2.negate()) {

                    const fraction frac = small_cancelation_by_prefix(perm_array1, perm_array2);

                    if (frac >= lambda) {
                        return false;
                    }

                }
            }
        }
    }

    return true;

}

template <class U>
static bool small_cancelation_with_permutations (const U& array, const fraction lambda) {

    auto perm_array1 = make_cyclic_permutation(array);
    auto perm_array2 = make_cyclic_permutation(array);

    for (std::size_t i = 0; i < perm_array1.size(); ++i, ++perm_array1) {
        for (std::size_t j = 0; j < perm_array2.size(); ++j, ++perm_array2) {
            for (int k = 0; k < 2; ++k, perm_array1.negate()) {
                for (int l = 0; l < 2; ++l, perm_array2.negate()) {

                    if ((i == j) && (k == l)) {
                        continue;
                    }

                    const fraction frac = small_cancelation_by_prefix(perm_array1, perm_array2);

                    if (frac >= lambda) {
                        return false;
                    }

                }
            }
        }
    }

    return true;

}

template <class Vector>
bool small_cancelation (const Vector& relations, const fraction lambda) {

    for (std::size_t i = 0; i < relations.size(); ++i) {
        if(!small_cancelation_with_permutations(relations[i], lambda)) {
            return false;
        }
    }

    for (std::size_t i = 0; i < (relations.size() - 1); ++i) {
        for (std::size_t j = (i+1); j < relations.size(); ++j) {
            if (!small_cancelation_with_permutations(relations[i], relations[j], lambda)) {
                return false;
            }
        }
    }

    return true;

}

#endif

