#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

class bigint {
    private:
        std::string valeu;
        std::string addStrings(const std::string &num1, const std::string &num2) const {
            char *end = NULL;
            long sum = std::strtol(num1.c_str(), &end, 0) + std::strtol(num2.c_str(), &end, 0);
            return std::to_string(sum);
        }

        unsigned long long stringToULL(const std::string &str) const {
            char *end = NULL;
            unsigned long long res = std::strtoul(str.c_str(), &end, 0);
            if (*end != '\0' || str[0] == '-')
                    throw std::invalid_argument("Invalid number format");
            return res;
        }

        void removeLeadingZeros() {
            while (valeu.size() > 1 && valeu[0] == '0')
                valeu.erase(0,1);
        }
    public:
        bigint() : valeu("0") {};
        bigint(unsigned long long num) : valeu(std::to_string(num)) {};
        bigint(const std::string &str) : valeu(str) {
            removeLeadingZeros();
        };
        
        bigint(const bigint &other) : valeu(other.valeu) {}

        bigint &operator=(const bigint &other) {
            if (this != &other)
                this->valeu = other.valeu;
            return *this;
        }

        bigint operator+(const bigint &other) const {
            return  bigint(addStrings(valeu, other.valeu));
        }

        bigint operator+(unsigned long long num) const {
            return  *this + bigint(num);
        }

        bigint& operator+=(const bigint &other) {
            valeu = addStrings(valeu, other.valeu);
            return *this;
        }

        bigint& operator+=(unsigned long long num) {
            return  *this += bigint(num);
        }

        bigint& operator++() {
            *this += 1;
            return *this;
        }

        bigint operator++(int) {
            bigint temp(*this);
            ++(*this);
            return temp;
        }

        bigint operator<<(int shift) const {
            if (shift <= 0)
                return *this;
            return bigint(valeu + std::string(shift, '0'));
        }
        bigint operator>>(int shift) const {
             if (shift <= 0 || shift >= static_cast<int>(valeu.size()))
                return bigint(0);
            return bigint(valeu.substr(0, valeu.size() - shift));
        }
        bigint &operator<<=(int shift) {
            if (shift >= 0)
                valeu = valeu + std::string(shift,'0');
            removeLeadingZeros();
            return *this;
        }
        bigint &operator>>=(int shift) {
            if (shift <= 0 || shift >= static_cast<int>(valeu.size()))
                valeu = "0";
            else
                valeu = valeu.substr(0,valeu.size() - shift);
            removeLeadingZeros();
            return *this;
        }
        bigint operator<<(const bigint &shift) const {
            return *this << stringToULL(shift.valeu);
        }
        bigint operator>>(const bigint &shift) const {
            return *this >> stringToULL(shift.valeu);
        }
        bigint& operator<<=(const bigint &shift) {
            removeLeadingZeros();
            return *this <<= stringToULL(shift.valeu);
        }
        bigint& operator>>=(const bigint &shift) {
            removeLeadingZeros();
            return *this >>= stringToULL(shift.valeu);
        }

        bool operator<(const bigint &shift) const {
            if (valeu.size() != shift.valeu.size())
                return valeu.size() < shift.valeu.size();
            return valeu < shift.valeu;
        }
        bool operator>(const bigint &shift) const {
            if (valeu.size() != shift.valeu.size())
                return valeu.size() > shift.valeu.size();
            return valeu > shift.valeu;
        }
        bool operator<=(const bigint &shift) const {
           return !(*this > shift);
        }
        bool operator>=(const bigint &shift) const {
            return !(*this < shift);
        }
        bool operator==(const bigint &shift) const {
            if (valeu == shift.valeu)
                return true;
            return false;
        }
        bool operator!=(const bigint &shift) const {
            if (valeu != shift.valeu)
                return true;
            return false;
        }
        friend std::ostream &operator<<(std::ostream &os, const bigint &other) {
            os << other.valeu;
            return os;
        }
};