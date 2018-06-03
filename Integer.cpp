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
        Integer result;
        Integer lhsc = lhs;
        Integer rhsc = rhs;
        if (!lhsc.getSign() && rhsc.getSign()) {
            std::cout << "lhs" << rhs.getValue() << rhs.getSign() << "\n";
            lhsc.setSign(true);
            Integer r = lhsc - rhsc;
            r.setSign(false);
            result = r;
        } else if (lhsc.getSign() && !rhsc.getSign()) {
            std::cout << "here2\n";
            lhsc.setSign(true);
            Integer rh(std::to_string(rhsc.getValue()));
            rh.setSign(true);
            
            result = lhs - rhs;
        } else if ((lhsc.getSign() && rhsc.getSign())
                   || (!lhsc.getSign() && !rhsc.getSign())) {
            std::cout << "here3\n";
            unsigned long long r;
            r = lhsc.getValue() + rhsc.getValue();
            Integer res(std::to_string(r));
            res.setSign(rhsc.getSign());
            result = res;
        }
        return result;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        Integer result;
        Integer big, small;
        bool switched = false;
        if (lhs.getValue() > rhs.getValue()) {
            big = lhs;
            small = rhs;
        } else {
            switched = true;
            big = rhs;
            small = lhs;
        }
        if (!big.getSign() && small.getSign()) {
            unsigned long long r = big.getValue() + small.getValue();
            Integer res(std::to_string(r));
            res.setSign(false);
            result = res;    
        } else if (big.getSign() && !small.getSign()) {
            /*unsigned long long r = big.getValue() + small.getValue();
            Integer res(std::to_string(r));
            res.setSign(false);
            result = res;*/
            result = big + small;
        } else if(!big.getSign() && !small.getSign()) {
            unsigned long long res = big.getValue() - small.getValue();
            Integer r(std::to_string(res));
            r.setSign(false);
            result = r;
        } else {
            unsigned long long res = big.getValue() - small.getValue();
            Integer r(std::to_string(res));
            if (switched) {
                r.setSign(false);
            }
            result = r;
        }
        
        return result;
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
       
        os << i.getIntegerAsString();
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
