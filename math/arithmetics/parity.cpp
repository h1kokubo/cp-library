
struct Parity {
  
  bool x;

  Parity() : x(0) {}

  Parity(const bool &y)
      : x(y) {}

  Parity &operator+=(const Parity &p) {
    x^=p.x;
    return *this;
  }

  Parity &operator-=(const Parity &p) {
    x^=p.x;
    return *this;
  }

  Parity &operator*=(const Parity &p) {
    x&=p.x;
    return *this;
  }

  Parity &operator/=(const Parity &p) {//非零項がそもそも1しかないためそのまま
    assert(p.x!=0);
    return *this;
  }

  Parity operator-() const { return *this; }//そのまま

  Parity operator+(const Parity &p) const { return Parity(*this) += p; }

  Parity operator-(const Parity &p) const { return Parity(*this) -= p; }

  Parity operator*(const Parity &p) const { return Parity(*this) *= p; }

  Parity operator/(const Parity &p) const { return Parity(*this) /= p; }

  bool operator==(const Parity &p) const { return val() == p.val(); }

  bool operator!=(const Parity &p) const { return val() != p.val(); }

  int val() const { return x; }

  Parity pow(int64_t n) const {//そのまま
    return Parity(*this);
  }

  /*
  friend ModInt operator+(const ModInt& lhs,const ModInt& rhs){
            return ModInt(lhs)+=rhs;
    }
    friend ModInt operator-(const ModInt& lhs,const ModInt& rhs){
            return ModInt<>(lhs)-=rhs;
    }
    friend ModInt operator*(const ModInt& lhs,const ModInt& rhs){
            return ModInt<friendly,fast>(lhs)*=rhs;
    }
    friend ModInt operator/(const ModInt& lhs,const ModInt& rhs){
            return ModInt<friendly,fast>(lhs)/=rhs;
    }
    friend bool operator==(const ModInt& lhs,const ModInt& rhs){
            return lhs.val()==rhs.val();
    }
    friend bool operator!=(const ModInt& lhs,const ModInt& rhs){
            return lhs.val()!=rhs.val();
    }
  */
  friend ostream &operator<<(ostream &os, const Parity &p) {
    return os << p.val();
  }
  
  friend istream &operator>>(istream &is, Parity &a) {
    bool t;
    is >> t;
    a = Parity(t);
    return (is);
  }

};

using pa = Parity;