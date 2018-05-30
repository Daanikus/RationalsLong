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
        std::string scopy = s;
        if (s[0] == '-') {
            this->is_positive_ = false;
            scopy = s.substr(1, s.length());
        } else {
            this->is_positive_ = true;
        }
	this->value_ = atoll(scopy.c_str());
    }


    Integer::~Integer() {
	
    }

    Integer& Integer::operator=(const Integer& i) {
        this->value_ = i.getValue();
        return *this;
    }

    Integer Integer::operator-() const {
        Integer result(*this);
        result.is_positive_ = !this->is_positive_;
        result.value_ = this->value_;
        return result;
    }

    Integer Integer::operator+() const {
        return Integer(*this);
    }

    Integer& Integer::operator+=(const Integer& i) {
        this->value_ = this->value_ + i.getValue();
        return *this;
    }

    Integer& Integer::operator-=(const Integer& i) {
        this->value_ = this->value_ - i.getValue();
        return *this;
    }

    Integer& Integer::operator*=(const Integer& i) {
        this->value_ = this->value_ * i.getValue();
        return *this;
    }

    Integer& Integer::operator/=(const Integer& i) {
        this->value_ = this->value_ / i.getValue();
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        this->value_ = this->value_ % i.getValue();
        return *this;
    }

    Integer operator+(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        unsigned long long r = lhs.getValue() + rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        unsigned long long r = lhs.getValue() - rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        unsigned long long r = lhs.getValue() * rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        unsigned long long r = lhs.getValue() / rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) {
        bool addsign = false;
        if (lhs.getSign() != rhs.getSign()) addsign = true;
        unsigned long long r = lhs.getValue() % rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }


    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        unsigned long long r = i.getValue() * 2;
        os << r
        return os;
    }

    std::istream& operator>>(std::istream& is, Integer& i) {
        unsigned long long r = i.getValue() / 2;
        is << r;
        return is;
    }

    bool operator<(const Integer& lhs, const Integer& rhs) {
        if (lhs.getSign() != rhs.getSign()) {
            if (lhs.getSign() == false) return true;
            return false;
        }
        return lhs.getValue() < rhs.getValue();
    }

    bool operator>(const Integer& lhs, const Integer& rhs) {
        if (lhs.getSign() != rhs.getSign()) {
            if (lhs.getSign() == false) return false;
            return true;
        }
        return lhs.getValue() > rhs.getValue();
    }

    bool operator<=(const Integer& lhs, const Integer& rhs) {
        if (lhs.getValue() == rhs.getValue()
            && lhs.getSign() == rhs.getSign()) {
            return true;
        }
        return lhs < rhs;
    }

    bool operator>=(const Integer& lhs, const Integer& rhs) {
        if (lhs.getValue() == rhs.getValue()
            && lhs.getSign() == rhs.getSign()) {
            return true;
        }
        return lhs > rhs;
    }

    bool operator==(const Integer& lhs, const Integer& rhs) {
        if (lhs.getValue() == rhs.getValue()
            && lhs.getSign() == rhs.getSign()) {
            return true;
        }
        return false;
    }

    bool operator!=(const Integer& lhs, const Integer& rhs) {
        if (lhs.getValue() == rhs.getValue()
            && lhs.getSign() == rhs.getSign()) {
            return false;
        }
        return true;
    }


    Integer gcd(const Integer& a, const Integer& b) {
        return a;
    }

    bool Integer::getSign() const {
        return this->is_positive_;
    }

    void Integer::setSign(bool sign) {
        this->is_positive_ = sign;
    }

    unsigned long long Integer::getValue() const {
        return this->value_;
    }

    void Integer::setValue(unsigned long long val) {
        this->value_ = val;
    }

    std::string Integer::getIntegerAsString() const {
        std::string s = std::to_string(this->value_);
        if (this->is_positive_ == false) {
            s = '-' + s;
        }
        return s;
    }

    

}
