#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <lib.h>


int main()
{
    try {
        std::vector<hw::IpAddr<static_cast<int>(hw::Type::IPv4)>> ip_pool;

        while (!std::cin.eof()) {
            std::string ip;
            std::cin >> ip;
            std::cin.ignore(50, '\n');
            if (ip.length())
                ip_pool.push_back(hw::IpAddr<static_cast<int>(hw::Type::IPv4)>(ip));
        }
        
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<hw::IpAddr<static_cast<int>(hw::Type::IPv4)>>());

        for (auto const & ip: ip_pool) {
            std::cout << ip << '\n';
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // std::cout << "==========================================================\n";
        // TODO filter by first byte and output
        // ip = filter(1)
        
        int value = 1;
        auto filter_first = [value](auto val) { return val.addr_[0] == value; };
        for (auto it = ip_pool.begin(); it != ip_pool.end(); ++it) {
            it = std::find_if(it, ip_pool.end(), filter_first);
            if (it == ip_pool.end()) break;
            std::cout << *it << '\n';
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // std::cout << "==========================================================\n";
        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        int value1 = 46, value2 = 70;
        auto filter_two = [value1, value2](auto val) { return val.addr_[0] == value1 && val.addr_[1] == value2; };
        for (auto it = ip_pool.begin(); it != ip_pool.end(); ++it) {
            it = std::find_if(it, ip_pool.end(), filter_two);
            if (it == ip_pool.end()) break;
            std::cout << *it << '\n';
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // std::cout << "==========================================================\n";
        // TODO filter by any byte and output
        // ip = filter_any(46)

        value = 46;
        auto filter_any = [value](auto val) { 
            bool res = false;
            for (const auto ip: val.addr_) {
                res |= (ip == value);
            }
            return res; };
                
        for (auto it = ip_pool.begin(); it != ip_pool.end(); ++it) {
            it = std::find_if(it, ip_pool.end(), filter_any);
            if (it == ip_pool.end()) break;
            std::cout << *it << '\n';
        }

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
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
