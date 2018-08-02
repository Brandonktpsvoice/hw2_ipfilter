#pragma once

#include "version.h"

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <array>

namespace hw {
int version();

enum class Type : int {
    IPv4 = 4,
    IPv6 = 6
};

template<int IpSize = static_cast<int>(Type::IPv4)>
struct IpAddr {
    explicit IpAddr(std::string ip_str) {
        std::stringstream ip_str_stream(ip_str);
        std::string entry;
        for (int index = 0; getline(ip_str_stream, entry, '.'); ++index) {
            addr_[index] = std::stoi(entry);
        }
    }
    
    IpAddr(const IpAddr<IpSize> &) = default;
    IpAddr(IpAddr<IpSize>&&) = default;
    IpAddr & operator=(const IpAddr<IpSize>&) = default;
    IpAddr & operator=(IpAddr<IpSize> &&) = default;
    
    bool operator<(const IpAddr<IpSize> & rhs) const {
        for (int i = 0; i < IpSize; ++i) {
            if (addr_[i] == rhs.addr_[i]) {
                continue;
            }
            else if (addr_[i] > rhs.addr_[i]) {
                return false;
            }
            else {
                return addr_[i] < rhs.addr_[i];
            }
        }
        return false;
    }

    bool operator>(const IpAddr<IpSize> & rhs) const { return !operator<(rhs); }
    
    friend std::ostream & operator<<(std::ostream &os, const IpAddr<IpSize> &ip) {
        for(std::size_t i = 0; i < ip.addr_.size(); ++i) {
            if (i != 0) {
                os << ".";
            }
            os << static_cast<int>(ip.addr_[i]);
        }
        return os;  
    }

    std::array<uint8_t, IpSize> addr_;
};

};