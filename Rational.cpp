#include "Rational.h"
#include <ctype.h>

namespace cosc326 {

    Rational::Rational() {
        Integer one("1");
        Integer zero("0");
        this->is_positive_ = true;
        this->denom_ = one;
        this->num_ = zero;
        reduce();
    }

    Rational::Rational(const std::string& str) {
        bool fraction = false;
        bool denominator = false;
        Integer n;
        Integer d("1");
        this->num_ = n;
        this->denom_ = d;
        std::string whole, num, denom;
        this->is_positive_ = true;
        for (int i = 0; i < str.length(); i++) {
            if (i == 0 && str[i] == '-') {
                this->is_positive_ = false;
                this->num_.setSign(false);
                std::cout << "neg as bro\n";
            } else if (isdigit(str[i])) {
                if (!fraction) {
                    whole += str[i];
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
        if (!denom.empty() && !num.empty()) {
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
        this->is_positive_ = a.getSign() == b.getSign();
        this->reduce();
        printStatus();

    }

    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        Integer r = (a * c) + b;
        this->num_ = r;
        this->denom_ = c;
        this->is_positive_ = r.getSign();
        this->reduce();
    }

    Rational::~Rational() {

    }

    Rational& Rational::operator=(const Rational& r) {
        
        this->num_ = r.getNum();
        this->denom_ = r.getDenom();
        reduce();
        return *this;
    }
    
    Rational Rational::operator-() const {
        Rational result(*this);
        result.is_positive_ = !this->is_positive_;
          /*result.num_ = this->num_;
            result.denom_ = this->denom_;*/
        result.reduce();
        
        return result;
    }
    
    Rational Rational::operator+() const {
        Rational result(*this);
        result.setSign(true);
        return result;
    }
    
    Rational& Rational::operator+=(const Rational& r) {
        *this = *this + r;
        reduce();
        return *this;
    }
    
    
    Rational& Rational::operator-=(const Rational& r) {
        *this = *this - r;
        this->reduce();
        return *this;
    }
    
    Rational& Rational::operator*=(const Rational& r) {
        *this = *this * r;
        return *this;
    }
    
    Rational& Rational::operator/=(const Rational& r) {
        *this = *this / r;
        this->reduce();
        return *this;
    }
    
    Rational operator+(const Rational& lhs, const Rational& rhs) {
        //lhs.printStatus();
        //rhs.printStatus();
        Rational result;
        std::cout << lhs.getNum() << "*" << rhs.getDenom() << " + " << rhs.getNum() << "*" << lhs.getDenom() <<'\n';
        result.setNum((-lhs.getNum() * rhs.getDenom()) + (rhs.getNum() * lhs.getDenom()));
        result.setDenom(lhs.getDenom() * rhs.getDenom());
        //if (!lhs.getSign() || !rhs.getSign()) result.setSign(false);
        result.setSign(result.getNum().getSign());
        result.reduce();
        std::cout << "result is " << result << '\n';
        return result;
    }
    
    Rational operator-(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum((lhs.getNum() * rhs.getDenom()) - (lhs.getDenom() * rhs.getNum()));
        result.setDenom(lhs.getDenom() * rhs.getDenom());
        result.setSign(result.getNum().getSign());
        result.reduce();
        return result;
    }
    
    Rational operator*(const Rational& lhs, const Rational& rhs) {
        //lhs.reduce();
        //rhs.reduce();
        Rational result;
        Integer num(lhs.getNum() * rhs.getNum());
        Integer denom(lhs.getDenom() * rhs.getDenom());
        result.setNum(num);
        result.setDenom(denom);
        if (num.getSign() != denom.getSign()) result.setSign(false);
        result.reduce();
        return result;
    }
    
    Rational operator/(const Rational& lhs, const Rational& rhs) {
        Rational result;
        Integer num = (lhs.getNum() * rhs.getDenom());
        Integer denom = lhs.getDenom() * rhs.getNum();
        result.setNum(num);
        result.setDenom(denom);
        if (num.getSign() != denom.getSign()) result.setSign(false);
        result.reduce();
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
        result.reduce();
        return is;
    }
    
    bool operator<(const Rational& lhs, const Rational& rhs) {
        Integer l = lhs.getNum() / lhs.getDenom();
        Integer r = rhs.getNum() / rhs.getDenom();
        return l < r;
    }
    
    bool operator> (const Rational& lhs, const Rational& rhs) {
        Integer l = lhs.getNum() / lhs.getDenom();
        Integer r = rhs.getNum() / rhs.getDenom();
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
        reduce();
    }

    Integer Rational::getDenom() const {
        
        return this->denom_;
    }

    void Rational::setDenom(Integer a) {
        this->denom_ = a;
        a.setSign(false);
        this->reduce();
    }

    Integer Rational::getNum() const {
        
        return this->num_;
    }

    void Rational::setNum(Integer a) {
        this->num_ = a;
        this->is_positive_ = a.getSign();
    }
            
    std::string Rational::getRationalAsString() const {
        std::string s;
        Integer zero;
        if (this->denom_ == zero) return "0";
        Integer whole = this->num_ / this->denom_;
        
        s.append(std::to_string(whole.getValue()));
        Integer num, denom;
        if (this->num_ % this->denom_ != zero) {
            s.append(".");
            num = this->num_ % this->denom_;
            denom = this->denom_;
            if (!num.getSign()) s.append(num.getIntegerAsString().substr(1) + "/");
            else s.append(num.getIntegerAsString() + "/");
            if (!denom.getSign()) s.append(denom.getIntegerAsString().substr(1));
            else s.append(denom.getIntegerAsString());
            if (s.at(0) == '0') s = s.substr(2);
        }
        if (!this->is_positive_ && !this->num_.getSign()) {
            std::cout << *this << " is negative" << '\n';
            s.insert(0, "-");
        }
        return s;
    }

    void Rational::reduce() {
        Integer zero;
        if (this->num_.getSign() != this->denom_.getSign()) {
            this->num_.setSign(false);
            this->denom_.setSign(true);
            this->is_positive_ = false;
        } else {
            this->num_.setSign(true);
            this->denom_.setSign(true);
            this->is_positive_ = true;
        }
        //this->num_.setSign(this->is_positive_);
        //this->denom_.setSign(this->is_positive_);
        if (this->denom_ == zero || this->num_ == zero) return;
        Integer divisor = gcd(this->num_, this->denom_);
        this->num_ = this->num_ / divisor;
        this->denom_ = this->denom_ / divisor;
    }

    void Rational::printStatus() const {
        std::cout << "Stream Output    : " << *this << '\n';
        std::cout << "Numerator   Value: " << this->num_ << '\n';
        std::cout << "Denominator Value: " << this->denom_ << '\n';
        std::cout << "Numerator   Sign : " << this->num_.getSign() << '\n';
        std::cout << "Denominator Sign : " << this->denom_.getSign() << '\n';
                                                                     
    }
}
    

