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
        this->is_positive_ = i.getSign();
        return *this;
    }

    Integer Integer::operator-() const {
        Integer result(*this);
        result.is_positive_ = !this->is_positive_;
        result.value_ = this->value_;
        return result;
    }

    Integer Integer::operator+() const {
        Integer result(*this);
        if (!result.is_positive_) result.is_positive_ = true;
        return result;
    }

    Integer& Integer::operator+=(const Integer& i) {
        *this = *this + i;
        return *this;
    }

    Integer& Integer::operator-=(const Integer& i) {
        *this = *this - i;
        return *this;
    }

    Integer& Integer::operator*=(const Integer& i) {

        *this = *this * i;
        return *this;
    }

    Integer& Integer::operator/=(const Integer& i) {
        *this = *this / i;
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        this->value_ %= i.getValue();
        return *this;

    }

    Integer operator+(const Integer& lhs, const Integer& rhs) {
        Integer finalres;
        Integer big = lhs.getValue() > rhs.getValue() ? lhs : rhs;
        Integer small = lhs.getValue() <= rhs.getValue() ? lhs : rhs;

        // Both the same
        if (big.getSign() == small.getSign()) {
            //     std::cout << "Signes the same in add\n";
            unsigned long long r = big.getValue() + small.getValue();
            Integer result(std::to_string(r));
            result.setSign(big.getSign());
            finalres = result;
        } else {

            unsigned long long r = big.getValue() - small.getValue();
            Integer result(std::to_string(r));
            result.setSign(big.getSign());
            finalres = result;
        }
        return finalres;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        Integer finalres;
        Integer big = lhs.getValue() > rhs.getValue() ? lhs : rhs;
        Integer small = lhs.getValue() <= rhs.getValue() ? lhs : rhs;
        if (big.getSign() == small.getSign()) {
            //       std::cout << "signs the same in subtraction\n";
            unsigned long long r = big.getValue() - small.getValue();
            //         std::cout << "Unsigned result is " << r << '\n';
            Integer result(std::to_string(r));
            if (big == lhs) result.setSign(big.getSign());
            else result.setSign(!big.getSign());
            finalres = result;
        } else {
            unsigned long long r = big.getValue() + small.getValue();
            Integer result(std::to_string(r));
            result.setSign(!rhs.getSign());
            finalres = result;
        }

        return finalres;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        bool addsign = true;
        if (lhs.getSign() != rhs.getSign()) addsign = false;
        unsigned long long r = lhs.getValue() * rhs.getValue();
        Integer result(std::to_string(r));
        result.setSign(addsign);
        return result;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {

        unsigned long long r = lhs.getValue() / rhs.getValue();
        Integer result(std::to_string(r));
        if (lhs.getSign() != rhs.getSign()) result.setSign(false);
        return result;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) { 
        Integer result = lhs;

        return result%=rhs;
    }


    std::ostream& operator<<(std::ostream& os, const Integer& i) {

        os << i.getIntegerAsString();
        return os;
    }

    std::istream& operator>>(std::istream& is, Integer& i) {
        std::string s;
        is >> s;
        i.setValue(atoll(s.c_str()));
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
        unsigned long long v = a.getValue();
        unsigned long long u = b.getValue();
        while ( v != 0) {
            unsigned long long r = u % v;
            u = v;
            v = r;
        }
        Integer result(std::to_string(u));
        return result;
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
        if (this->is_positive_ == false && this->value_ != 0) {
            s = '-' + s;
        }
        return s;
    }

}
