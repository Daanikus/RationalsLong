#include "Rational.h"

namespace cosc326 {

    Rational::Rational() {
        this->is_positive_ = true;
    }

    Rational::Rational(const std::string& str) {

    }

    Rational::Rational(const Rational& r) {
        *this = r;
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
        this->is_positive_ = a.getSign();
        this->reduce();

    }

    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        Integer r = a + b;
        this->num_ = r;
        this->denom_ = c;
        this->is_positive_ = r.getSign();
        this->reduce();
    }

    Rational::~Rational() {

    }

    Rational& Rational::operator=(const Rational& r) {
        reduce();
        this->num_ = r.getNum();
        this->denom_ = r.getDenom();
        this->is_positive_ = r.getSign();
        return *this;
    }
    
    Rational Rational::operator-() const {
        Rational result(*this);
        result.is_positive_ = !this->is_positive_;
        result.num_ = this->num_;
        result.denom_ = this->denom_;
        return Rational(*this);
    }
    
    Rational Rational::operator+() const {
        return Rational(*this);
    }
    
    Rational& Rational::operator+=(const Rational& r) {
        this->reduce();
        this->num_ += r.getNum();
        this->denom_ += r.getDenom();
        return *this;
    }
    
    
    Rational& Rational::operator-=(const Rational& r) {
        this->reduce();
        return *this;
    }
    
    Rational& Rational::operator*=(const Rational& r) {
        this->reduce();
        this->num_ = this->num_ * r.getNum();
        this->denom_ = this->denom_ * r.getNum();
        if (this->is_positive_ != r.getSign()) this->is_positive_ = false;
        else this->is_positive_ = true;
        return *this;
    }
    
    Rational& Rational::operator/=(const Rational& r) {
        this->reduce();
        this->num_ = this->num_ / r.getNum();
        this->denom_ = this->denom_ / r.getNum();
        if (this->is_positive_ != r.getSign()) this->is_positive_ = false;
        else this->is_positive_ = true;
        return *this;
    }
    
    Rational operator+(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() + rhs.getNum());
        result.setDenom(lhs.getDenom() + rhs.getDenom());
        if (!lhs.getSign() || !rhs.getSign()) result.setSign(false);
        return result;
    }
    
    Rational operator-(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() - rhs.getNum());
        result.setDenom(lhs.getDenom() - rhs.getDenom());
        if (!lhs.getSign() || !rhs.getSign()) result.setSign(false);
        return lhs;
    }
    
    Rational operator*(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() * rhs.getNum());
        result.setDenom(lhs.getDenom() * rhs.getDenom());
        if (lhs.getSign() != rhs.getSign()) result.setSign(false);
        return lhs;
    }
    
    Rational operator/(const Rational& lhs, const Rational& rhs) {
        Rational result;
        result.setNum(lhs.getNum() / rhs.getNum());
        result.setDenom(lhs.getDenom() / rhs.getDenom());
        if (lhs.getSign() != rhs.getSign()) result.setSign(false);
        return lhs;
    }
    
    std::ostream& operator<<(std::ostream& os, const Rational& i) {
        os << i.getRationalAsString();
        return os;
    }
    std::istream& operator>>(std::istream& is, Rational& i) {
        return is;
    }
    
    bool operator<(const Rational& lhs, const Rational& rhs) {
        return true;
    }
    
    bool operator> (const Rational& lhs, const Rational& rhs) {
        return true;
    }
    
    bool operator<=(const Rational& lhs, const Rational& rhs) {
        return true;
    }
    
    bool operator>=(const Rational& lhs, const Rational& rhs) {
        return true;
    }
    
    bool operator==(const Rational& lhs, const Rational& rhs) {
        if (lhs.getNum() == rhs.getNum()
            && lhs.getDenom() == rhs.getDenom()
            && lhs.getSign() == rhs.getSign()) return true;
        return false;;
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
        Integer whole = this->num_ / this->denom_;
        
        s.append(std::to_string(whole.getValue()));
        Integer num, denom;
        if (this->num_ % this->denom_ != Integer()) {
            s.append(".");
            num = this->num_ % this->denom_;
            denom = this->denom_;
            if (!num.getSign()) s.append(num.getIntegerAsString().substr(1) + "/");
            else s.append(num.getIntegerAsString() + "/");
            s.append(denom.getIntegerAsString());
            if (s.at(0) == '0') s = s.substr(2);
        }
        if (!whole.getSign()) s.insert(0, "-");
        return s;
    }

    void Rational::reduce() {
        Integer divisor = gcd(this->num_, this->denom_);
        std::cout << this->num_ << " " << this->denom_ << '\n';
        this->num_ = this->num_ / divisor;
        this->denom_ = this->denom_ / divisor;
        std::cout << this->num_ << " " << this->denom_ << '\n';
    }
}
    

