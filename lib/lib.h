#pragma once

#include "version.h"

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

namespace hw {
int version();

template<typename ItType>
void radix_sort(ItType begin, ItType end, int entries, int length, int position = 0)
{
    std::vector<std::pair<ItType, ItType>> buckets(11);
    
    if (std::distance(begin, end) <= 1) return;
    if (position >= length) return;

    int size = length / entries;
    int step = position / size;
    int sub_position = position % size;
    
    //auto to_real_pos = [size, step, sub_position](auto str_len){ return sub_position - ( size - str_len); };
    auto comparator = [size, step, sub_position](auto &lhs, auto &rhs) {
        
        int real_lhs_pos = sub_position - ( size - lhs.at(step).length() );
        int real_rhs_pos = sub_position - ( size - rhs.at(step).length() );

        if (real_lhs_pos != real_rhs_pos) {
            return real_lhs_pos > real_rhs_pos;
        }

        if (real_lhs_pos < 0 || real_rhs_pos < 0) return false;

        return lhs.at(step).at(real_lhs_pos) > rhs.at(step).at(real_rhs_pos);
    };

    std::sort(begin, end, comparator);

    auto sub_begin = begin;
    auto sub_end = sub_begin;

    for (int i = 9; i >= 0; --i) {
        sub_begin = sub_end;
        for ( ; sub_end != end; ++sub_end) {
            int str_len = sub_end->at(step).length();
            int real_pos = sub_position - ( size - str_len);
            if (real_pos < 0) break;
            auto val = sub_end->at(step).at(real_pos);
            if (val != '0' + i) break;
        }
        buckets[i] = std::move(std::make_pair(sub_begin, sub_end));
    }

    buckets[10] = std::move(std::make_pair(sub_begin, end));

    for (const auto &bucket: buckets) {
        if (std::distance(begin, end) > 1)  {
            radix_sort(bucket.first, bucket.second, entries, length, position + 1);
        }
    }
}

template<typename ItType>
void print_ip(ItType begin, ItType end)
{
    for(auto ip_part = begin; ip_part != end; ++ip_part)
    {
        if (ip_part != begin)
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

template<typename ItType>
void print_all(ItType begin, ItType end)
{
    for(auto ip = begin; ip != end; ++ip)
    {
        print_ip(ip->cbegin(), ip->cend());
    }
}

template<typename ItType>
void print_filtered_single(ItType begin, ItType end, int position, int value)
{
    std::string value_str = std::to_string(value);
    auto predicate = [position, value_str](auto val) { return val.at(position) == value_str; };
    for (auto it = begin; it != end; ++it) {
        it = std::find_if(it, end, predicate);
        if (it == end) break;
        print_ip(it->cbegin(), it->cend());
    }
}

template<typename ItType>
void print_filtered_first2(ItType begin, ItType end, int first, int second)
{
    std::string first_str = std::to_string(first);
    std::string second_str = std::to_string(second);
    auto predicate = [&first_str, &second_str](auto val) { return val.at(0) == first_str && val.at(1) == second_str; };
    for (auto it = begin; it != end; ++it) {
        it = std::find_if(it, end, predicate);
        if (it == end) break;
        print_ip(it->cbegin(), it->cend());
    }
}

template<typename ItType>
void print_filtered_any(ItType begin, ItType end, int value)
{
    std::string value_str = std::to_string(value);
    auto predicate = [&value_str](auto val) { return std::find(val.cbegin(), val.cend(), value_str) != val.cend(); };
    for (auto it = begin; it != end; ++it) {
        it = std::find_if(it, end, predicate);
        if (it == end) break;
        print_ip(it->cbegin(), it->cend());
    }
}
};