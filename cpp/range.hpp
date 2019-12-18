#pragma once
#ifndef b2f9aa55_range_hpp
#define b2f9aa55_range_hpp

template <class T>
class range_object {
private:
    T first;
    T last;

public:

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using reference = T;
        using pointer = T*;
        using difference_type = void;

        iterator(T value): value(value) {}

        bool operator == (const iterator& other) const {
            return (value == other.value);
        }

        bool operator != (const iterator& other) const {
            return (value != other.value);
        }

        iterator& operator ++ () {
            ++value;
            return *this;
        }

        iterator operator ++ (int) {
            iterator cpy(*this);
            ++(*this);
            return cpy;
        }

        value_type operator * () const {
            return value;
        }

    private:
        T value;
    };

    range_object(T first, T last): first(first), last(last) {}

    iterator begin() const {
        return iterator(first);
    }

    iterator end() const {
        return iterator(last+1);
    }

};

template <class T>
range_object<T> range(T first, T last) {
    return range_object<T>(first, last);
}

template <class T>
range_object<T> range(T len) {
    return range_object<T>(0, len-1);
}

#endif
