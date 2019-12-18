#pragma once
#ifndef b2f9aa55_fraction_hpp
#define b2f9aa55_fraction_hpp

#include <iostream>
#include <tuple>
#include <utility>

template <class T>
class basic_fraction {

private:

    T numerator;
    T denominator;

    T gcd (T a, T b) const {

        if (a < 0) {
            a = -a;
        }

        if (b < 0) {
            b = -b;
        }

        if (a < b) {
            std::swap(a,b);
        }

        while (b != 0) {
            std::tie(a,b) = std::make_tuple( b, (a % b) );
        }

        return a;

    }

public:

    basic_fraction (T numerator = 0, T denominator = 1) {

        const T common = gcd(numerator, denominator);

        this->numerator   = numerator   / common;
        this->denominator = denominator / common;

        if (this->denominator < 0) {
            this->numerator   = -this->numerator;
            this->denominator = -this->denominator;
        }

    }

    basic_fraction (const basic_fraction<T>& other) :
        numerator(other.numerator),
        denominator(other.denominator)
    {}

    basic_fraction (const basic_fraction<T>&& other) :
        numerator(other.numerator),
        denominator(other.denominator)
    {}

    basic_fraction<T>& operator = (const basic_fraction<T>& other) {
        this->numerator   = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    basic_fraction<T>& operator = (const basic_fraction<T>&& other) {
        this->numerator   = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    explicit operator T () const {
        return numerator/denominator;
    }

    explicit operator long double () const {
        return static_cast<long double>(numerator) / static_cast<long double>(denominator);
    }

    explicit operator double () const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    explicit operator float () const {
        return static_cast<float>(numerator) / static_cast<float>(denominator);
    }

    T num () const {
        return numerator;
    }

    T den () const {
        return denominator;
    }

    T floor () const {
        return num() / den();
    }

    T ceil() const {
        return (num()+den()-1) / den();
    }

    basic_fraction<T>& operator += (const basic_fraction<T>& other) {

        const T gcd1 = gcd(numerator, other.denominator);
        const T gcd2 = gcd(other.numerator, denominator);

        numerator   =
                ((numerator / gcd1) * other.denominator) +
                ((other.numerator / gcd2) * denominator);
        denominator = (denominator / gcd2) * (other.denominator / gcd1);

        *this = basic_fraction(numerator, denominator);

        return *this;
    }

    basic_fraction<T> operator + (const basic_fraction<T>& other) const {
        basic_fraction<T> answer(*this);
        return (answer += other);
    }

    basic_fraction<T>& operator -= (const basic_fraction<T>& other) {

        const T gcd1 = gcd(numerator, other.denominator);
        const T gcd2 = gcd(other.numerator, denominator);

        numerator   =
                ((numerator / gcd1) * other.denominator) -
                ((other.numerator / gcd2) * denominator);
        denominator = (denominator / gcd2) * (other.denominator / gcd1);

        *this = basic_fraction(numerator, denominator);

        return *this;
    }

    basic_fraction<T> operator - (const basic_fraction<T>& other) const {
        basic_fraction<T> answer(*this);
        return (answer -= other);
    }

    basic_fraction<T>& operator *= (const basic_fraction<T>& other) {

        const T gcd1 = gcd(numerator, other.denominator);
        const T gcd2 = gcd(other.numerator, denominator);

        numerator   = (numerator / gcd1) * (other.numerator / gcd2);
        denominator = (denominator / gcd2) * (other.denominator / gcd1);

        return *this;
    }

    basic_fraction<T> operator * (const basic_fraction<T>& other) const {
        basic_fraction<T> answer(*this);
        return (answer *= other);
    }

    basic_fraction<T>& operator /= (const basic_fraction<T>& other) {

        const T gcd1 = gcd(numerator, other.numerator);
        const T gcd2 = gcd(other.denominator, denominator);

        numerator   = (numerator / gcd1) * (other.denominator / gcd2);
        denominator = (denominator / gcd2) * (other.numerator / gcd1);

        return *this;
    }

    basic_fraction<T> operator / (const basic_fraction<T>& other) const {
        basic_fraction<T> answer(*this);
        return (answer /= other);
    }

    bool operator < (const basic_fraction<T>& other) const {
        return (
            (this->numerator * other.denominator) <
            (other.numerator * this->denominator)
        );
    }

    bool operator == (const basic_fraction<T>& other) const {
        return (
            (this->numerator == other.numerator) &&
            (this->denominator == other.denominator)
        );
    }

    basic_fraction<T> operator + () const {
        return *this;
    }

    basic_fraction<T> operator - () const {
        basic_fraction<T> answer(*this);
        answer.numerator = -answer.numerator;
        return answer;
    }

    bool operator <= (const basic_fraction<T>& other) const {
        return ((*this < other) || (*this == other));
    }

    bool operator > (const basic_fraction<T>& other) const {
        return (other < *this);
    }

    bool operator >= (const basic_fraction<T>& other) const {
        return ((*this > other) || (*this == other));
    }

    bool operator != (const basic_fraction<T>& other) const {
        return !(*this == other);
    }

};

template <class T>
std::ostream& operator << (std::ostream& stream, const basic_fraction<T>& frac) {

    if (frac.den() == 1) {
        stream << frac.num();
    } else {
        stream << frac.num() << "/" << frac.den();
    }

    return stream;
}

using fraction = basic_fraction<long long int>;

#endif

