#include "Rational.h"
#include <ctype.h>

namespace cosc326 {

    Rational::Rational() {
        Integer one("1");
        this->is_positive_ = true;
        this->denom_ = one;
        reduce();
    }

    Rational::Rational(const std::string& str) {
        bool fraction = false;
        bool denominator = false;
        std::string whole, num, denom;
        this->is_positive_ = true;
        for (int i = 0; i < str.length(); i++) {
            if (i == 0 && str[i] == '-') {
                this->is_positive_ = false;
                std::cout << "neg as bro\n";
            }
            if (isdigit(str[i])) {
                if (!fraction) {
                    whole =+ str[i];
                } else {
                    if(!denominator) {
                        num += str[i];
                    } else {
                        denom += str[i];
                    }
                }
            } else if (str[i] == '.') {
                fraction = true;
            } else if (str[i] == '/') {
                denominator = true;
            }
        }
        //std::cout << whole + " " + num + " " + denom + '\n';
        if (!denom.empty()) {
            this->num_.setValue(atoll(whole.c_str())
                            * atoll(denom.c_str()) + atoll(num.c_str()));
            this->denom_.setValue(atoll(denom.c_str()));
        } else {
            this->num_.setValue(atoll(whole.c_str()));
            this->denom_.setValue(1);
        }
        reduce();
    }

    Rational::Rational(const Rational& r) {
        *this = r;
        reduce();
    }

    Rational::Rational(const Integer& a) {
        this->num_ = a;
        this->denom_ = Integer("1");
        this->is_positive_ = a.getSign();
        this->reduce();
    }

    Rational::Rational(const Integer& a, const Integer& b) {
        this->num_ = a;
        this->denom_ = b;
        this->is_positive_ = (a.getSign() && b.getSign());
        this->reduce();

    }

    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        Integer r = a + b;
        this->num_ = r;
        this->denom_ = c;
        this->is_positive_ = (r.getSign() && c.getSign());
        this->reduce();
    }

    Rational::~Rational() {

    }

    Rational& Rational::operator=(const Rational& r) {
        
        this->num_ = r.getNum();
        this->denom_ = r.getDenom();
        this->is_positive_ = r.getSign();
        reduce();
        return *this;
    }
    
    Rational Rational::operator-() const {
        Rational result(*this);
        result.is_positive_ = !this->is_positive_;
        result.num_ = this->num_;
        result.denom_ = this->denom_;
        return result;
    }
    
    Rational Rational::operator+() const {
        Rational result(*this);
        result.setSign(true);
        return result;
    }
    
    Rational& Rational::operator+=(const Rational& r) {
        
        this->num_ += r.getNum();
        this->denom_ += r.getDenom();
        this->reduce();
        return *this;
    }
    
    
    Rational& Rational::operator-=(const Rational& r) {
        this->reduce();
        return *this;
    }
    
    Rational& Rational::operator*=(const Rational& r) {
        this->num_ = this->num_ * r.getNum();
        this->denom_ = this->denom_ * r.getNum();
        if (this->is_positive_ != r.getSign()) this->is_positive_ = false;
        else this->is_positive_ = true;
        this->reduce();
        return *this;
    }
    
    Rational& Rational::operator/=(const Rational& r) {
        
        this->num_ = this->num_ / r.getNum();
        this->denom_ = this->denom_ / r.getNum();
        if (this->is_positive_ != r.getSign()) this->is_positive_ = false;
        else this->is_positive_ = true;
        this->reduce();
        return *this;
    }
    
    Rational operator+(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum((lhs.getNum() * rhs.getDenom()) + (rhs.getNum() * lhs.getDenom()));
        result.setDenom(lhs.getDenom() * rhs.getDenom());
        if (!lhs.getSign() || !rhs.getSign()) result.setSign(false);
        return result;
    }
    
    Rational operator-(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() - rhs.getNum());
        result.setDenom(lhs.getDenom() - rhs.getDenom());
        if (!lhs.getSign() || !rhs.getSign()) result.setSign(false);
        return result;
    }
    
    Rational operator*(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() * rhs.getNum());
        result.setDenom(lhs.getDenom() * rhs.getDenom());
        if (lhs.getSign() != rhs.getSign()) result.setSign(false);
        return result;
    }
    
    Rational operator/(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() / rhs.getNum());
        result.setDenom(lhs.getDenom() / rhs.getDenom());
        if (lhs.getSign() != rhs.getSign()) result.setSign(false);
        return result;
    }
    
    std::ostream& operator<<(std::ostream& os, const Rational& i) {
        os << i.getRationalAsString();
        return os;
    }
    std::istream& operator>>(std::istream& is, Rational& i) {
        std::string s;
        is >> s;
        Rational result(s);
        return is;
    }
    
    bool operator<(const Rational& lhs, const Rational& rhs) {
        Integer l = lhs.getNum() / lhs.getDenom();
        Integer r = rhs.getNum() / lhs.getDenom();
        return l < r;
    }
    
    bool operator> (const Rational& lhs, const Rational& rhs) {
        Integer l = lhs.getNum() / lhs.getDenom();
        Integer r = rhs.getNum() / lhs.getDenom();
        return l > r;
    }
    
    bool operator<=(const Rational& lhs, const Rational& rhs) {
        return lhs < rhs || lhs == rhs;
    }
    
    bool operator>=(const Rational& lhs, const Rational& rhs) {
        return lhs > rhs || lhs == rhs;
    }
    
    bool operator==(const Rational& lhs, const Rational& rhs) {
        if (lhs.getNum() == rhs.getNum()
            && lhs.getDenom() == rhs.getDenom()
            && lhs.getSign() == rhs.getSign()) return true;
        return false;
    }
    
    bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs == rhs);
    }

    bool Rational::getSign() const {
        return this->is_positive_;
    }

    void Rational::setSign(bool sign) {
        this->is_positive_ = sign;
    }

    Integer Rational::getDenom() const {
        return this->denom_;
    }

    void Rational::setDenom(Integer a) {
        this->denom_ = a;
        this->reduce();
    }

    Integer Rational::getNum() const {
        return this->num_;
    }

    void Rational::setNum(Integer a) {
        this->num_ = a;
        this->reduce();
    }
            
    std::string Rational::getRationalAsString() const {
        std::string s;
        Integer zero;
        if (this->denom_ == zero) return "0";
        Integer whole = this->num_ / this->denom_;
        
        s.append(std::to_string(whole.getValue()));
        Integer num, denom;
        if (this->num_ % this->denom_ != Integer()) {
            s.append(".");
            num = this->num_ % this->denom_;
            denom = this->denom_;
            if (!num.getSign()) s.append(num.getIntegerAsString().substr(1) + "/");
            else s.append(num.getIntegerAsString() + "/");
            if (!denom.getSign()) s.append(denom.getIntegerAsString().substr(1));
            else s.append(denom.getIntegerAsString());
            if (s.at(0) == '0') s = s.substr(2);
        }
        if (!this->is_positive_ || (this->denom_.getSign() != this->num_.getSign()))
            s.insert(0, "-");
        return s;
    }

    void Rational::reduce() {
        Integer zero;
        this->num_.setSign(this->is_positive_);
        this->denom_.setSign(this->is_positive_);
        if (this->denom_ == zero || this->num_ == zero) return;
        Integer divisor = gcd(this->num_, this->denom_);
        this->num_ = this->num_ / divisor;
        this->denom_ = this->denom_ / divisor;
    }
}
    

