#include "Integer.h"
#include <string>

namespace cosc326 {

    Integer::Integer() {
	value_ = 0L;
        this->is_positive_ = true;
    }

    Integer::Integer(const Integer& i) {
	this->value_ = i.getValue();
        this->is_positive_ = i.getSign();
    }

    Integer::Integer(const std::string& s) {
        if (s[0] == '-') {
            this->is_positive_ = false;;
            s.substr(1, s.length());
        } else {
            this->is_positive_ = true;;
        }
	this->value_ = atoll(s.c_str());
    }


    Integer::~Integer() {
	
    }

    Integer& Integer::operator=(const Integer& i) {
        
        return *this;
    }

    Integer Integer::operator-() const {
        return Integer(*this);
    }

    Integer Integer::operator+() const {
        return Integer(*this);
    }

    Integer& Integer::operator+=(const Integer& i) {
        return *this;
    }

    Integer& Integer::operator-=(const Integer& i) {
        return *this;
    }

    Integer& Integer::operator*=(const Integer& i) {
        return *this;
    }

    Integer& Integer::operator/=(const Integer& i) {
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        return *this;
    }

    Integer operator+(const Integer& lhs, const Integer& rhs) {
        Integer result;
        result = lhs + rhs;
        return result;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        return lhs - rhs;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        Integer result;
        result = lhs * rhs;
        result.setSign(addsign);
        return result;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {
        return lhs / rhs;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) {
        return lhs % rhs;
    }


    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        return os;
    }

    std::istream& operator>>(std::istream& is, Integer& i) {
        return is;
    }

    bool operator<(const Integer& lhs, const Integer& rhs) {
        if (lhs.getSign() != rhs.getSign()) {
            if (lhs.getSign() == false) return true;
            return false;
        }
        return lhs < rhs;
    }

    bool operator> (const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator<=(const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator>=(const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator==(const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator!=(const Integer& lhs, const Integer& rhs) {
        return true;
    }


    Integer gcd(const Integer& a, const Integer& b) {
        return a;
    }

    const bool Integer::getSign() const {
        return this->is_positive_;
    }

    void Integer::setSign(bool sign) {
        this->is_positive_ = sign;
    }

    const unsigned long long Integer::getValue() const {
        return this->value_;
    }

    void Integer::setValue(unsigned long long val) {
        this->value_ = val;
    }

    

}
