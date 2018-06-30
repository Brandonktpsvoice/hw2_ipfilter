#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template<typename ItType>
void radix_sort(ItType begin, ItType end, int entries, int length, int position = 0) {
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

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
         radix_sort(ip_pool.begin(), ip_pool.end(), 4, 12);
        
        print_all(ip_pool.cbegin(), ip_pool.cend());
        //std::cout << "==========================================================\n";
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        print_filtered_single(ip_pool.cbegin(), ip_pool.cend(), 0, 1);
        //std::cout << "==========================================================\n";
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        print_filtered_first2(ip_pool.cbegin(), ip_pool.cend(), 46, 70);
        //std::cout << "==========================================================\n";
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        print_filtered_any(ip_pool.cbegin(), ip_pool.cend(), 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
