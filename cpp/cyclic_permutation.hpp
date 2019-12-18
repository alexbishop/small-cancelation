#pragma once
#ifndef b2f9aa55_cyclic_permutation_hpp
#define b2f9aa55_cyclic_permutation_hpp

#include <functional>
#include <cinttypes>

template <class T>
class cyclic_permutation {

private:

    std::reference_wrapper<const T> word;

    std::size_t size_;
    std::size_t shift;

    bool invert;

public:

    cyclic_permutation(
        const T& word,
        std::size_t shift,
        std::size_t size
    ) :
        word(std::ref(word)),
        shift(shift),
        size_(size),
        invert(false)
    {}

    cyclic_permutation (const cyclic_permutation<T>& other) :
        word(other.word.get()),
        size_(other.size_),
        shift(other.shift),
        invert(other.invert)
    {}

    cyclic_permutation (const cyclic_permutation<T>&& other) :
        word(other.word.get()),
        size_(other.size_),
        shift(other.shift),
        invert(other.invert)
    {}

    const int operator [] (std::size_t offset) const {

        std::size_t index = (shift + offset) % size_;

        if (index < 0) {

            index += size_;
        }

        if (invert) {
            index = size_ - index - 1;

            return -( word.get() [index]);
        }

        return word.get() [index];

    }

    std::size_t offset () const {
        return shift;
    }

    std::size_t size () const {
        return size_;
    }

    bool inverted () const {
        return invert;
    }

    cyclic_permutation<T>& negate () {
        invert = !invert;
        return *this;
    }

    cyclic_permutation<T>& operator ++ () {
        shift = (shift + 1) % size_;
        return *this;
    }

    cyclic_permutation<T>& operator -- () {
        shift = (shift + size_ - 1) % size_;
        return *this;
    }

    cyclic_permutation<T> operator = (const cyclic_permutation<T>& other) {
        word   = other.word;
        size_  = other.size_;
        shift  = other.shift;
        invert = other.invert;

        return *this;
    }

    cyclic_permutation<T> operator = (const cyclic_permutation<T>&& other) {
        word   = other.word;
        size_  = other.size_;
        shift  = other.shift;
        invert = other.invert;

        return *this;
    }

};

template<class T>
cyclic_permutation<T> make_cyclic_permutation (const T& word, std::size_t shift = 0) {
    return cyclic_permutation<T>(
        word, shift, word.size()
    );
}

#endif

