#include <iostream>

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <tuple>
#include <set>
#include <sstream>

#include "random.hpp"
#include "permutations.hpp"
#include "fraction.hpp"
#include "range.hpp"

typedef struct {
    // info about the presentations
    int r;
    int l_min;
    int l_max;
    int m;
    // temperary storage for the relations
//    std::vector<std::vector<int>> relations;
    // the statictics which have already been generated
    long long small_cancelable = 0;
    long long total_tests = 0;
    // the file to output statistics to
    std::string output_file;
} current_stat;

template <class T>
T power (T x, T p) {
    if (p == 0) {
        return 1;
    }

    if (x == 0) {
        return 0;
    }

    if (x < 0) {
        if ((p % 2) == 0) {
            return power(-x,p);
        } else {
            return -power(-x,p);
        }
    }

    if(p < 0) {
        if (x == 1) {
            return 1;
        } else {
            return 0;
        }
    }

    T total = 1;

    while (p > 0) {
        if ((p%2) == 1) {
            total *= x;
        }

        x *= x;
        p /= 2;
    }

    return total;
}

bool is_not_okay (std::tuple<int,int,int> setting, fraction lambda) {
    unsigned long long r = std::get<0>(setting);
    unsigned long long m = std::get<1>(setting);
    unsigned long long l = std::get<2>(setting);

    unsigned long long l2 = (lambda*fraction(l)).ceil();

    if (r*power((2*r-1),l2-1) < m*l ) {
        return true; // small cancelation is not possible
    }

    return false;

}

int main (int argn, char** argv) {

    // The paramaters of the program

    const fraction lambda(1,6);

    std::vector<current_stat> meta;

    std::set<std::tuple<int,int,int>> settings;

    auto r_range = range(6,20);
    auto m_range = range(2,100);
    auto l_range = range(6,30);

    for (int r : r_range) {
        for (int m : m_range) {
            settings.insert(std::make_tuple(r,m,20));
        }
    }

    for (int l : l_range) {
        for (int m : m_range) {
            settings.insert(std::make_tuple(20,m,l));
        }
    }

    for (int r : r_range) {
        for (int l : l_range) {
            settings.insert(std::make_tuple(r,10,l));
        }
    }

    for (auto& element : settings) {

        if (is_not_okay(element,lambda)) {
            continue;
        }

        current_stat stat;

        stat.r = std::get<0>(element);
        stat.m = std::get<1>(element);
        stat.l_min = std::get<2>(element);
        stat.l_max = std::get<2>(element);

        std::ostringstream fname_stream;
        fname_stream
            << "data"
            <<  "_r-" << stat.r
            <<  "_m-" << stat.m
            << "_l1-" << stat.l_min
            << "_l2-" << stat.l_max
            << ".csv";
        stat.output_file = fname_stream.str();

        meta.push_back(std::move(stat));

    }

    auto rng_engine = init_mersenne_twister();

    while (true) {
        for (auto& stat : meta) {
            std::vector<std::vector<int>> relations;
            relations.resize(stat.m);

            for (int i : range(1,100)) {

                generate_random_relations(relations, stat.r, stat.l_min, stat.l_max, rng_engine);
                if (small_cancelation(relations,lambda)) {
                    ++stat.small_cancelable;
                }

                ++stat.total_tests;

            }

            const double percentage = static_cast<double>(stat.small_cancelable*100) / static_cast<double>(stat.total_tests);

            std::ofstream(stat.output_file, std::ios_base::app) << stat.small_cancelable << ","<< stat.total_tests << "," << percentage << std::endl;

        }
    }


}

