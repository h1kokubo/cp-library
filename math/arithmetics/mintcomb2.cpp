#include <bits/stdc++.h>
using namespace std;



//ModInt begin
const int mod=1e9+7;
//const int mod=998244353;

static constexpr uint32_t mul_inv(uint32_t n, int e = 5, uint32_t x = 1) {
  return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
}

template< uint32_t mod,bool friendly, bool fast = false >
struct ModInt {
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 inv_ = mul_inv(mod);
  static constexpr u32 r2 = -uint64_t(mod) % mod;

  uint32_t x;

  ModInt() : x(0) {}

  ModInt(const int64_t &y)
      : x(reduce(u64(fast ? y : (y >= 0 ? y % mod : (mod - (-y) % mod) % mod)) * r2)) {}

  u32 reduce(const u64 &w) const {
    return u32(w >> 32) + mod - u32((u64(u32(w) * inv_) * mod) >> 32);
  }

  ModInt &operator+=(const ModInt &p) {
    if(int(x += p.x - 2 * mod) < 0) x += 2 * mod;
    return *this;
  }

  ModInt &operator-=(const ModInt &p) {
    if(int(x -= p.x) < 0) x += 2 * mod;
    return *this;
  }

  ModInt &operator*=(const ModInt &p) {
    x = reduce(uint64_t(x) * p.x);
    return *this;
  }

  ModInt &operator/=(const ModInt &p) {
    *this *= p.inv();
    return *this;
  }

  ModInt operator-() const { return ModInt() - *this; }

  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

  bool operator==(const ModInt &p) const { return val() == p.val(); }

  bool operator!=(const ModInt &p) const { return val() != p.val(); }

  int val() const { return reduce(x) % mod; }

  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(*this);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  ModInt inv() const {
    return pow(mod - 2);
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
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.val();
  }
  
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod, friendly,fast >(t);
    return (is);
  }

  static int get_mod() { return mod; }
  static bool is_friendly() {return friendly;}
};

using mint = ModInt< mod, true, true >;
//ModInt end

//mintcomb begin
template<typename Mint>
struct Mintcomb{
    private:
        vector<Mint> fact,ifact;
        int sup;
    public:
        Mintcomb(int sup_):sup(sup_),fact(vector<Mint>(sup_)),ifact(vector<Mint>(sup_)){
            fact[0]=Mint(1);
            for(int i=1;i<sup;++i)fact[i]=fact[i-1]*Mint(i);
            ifact[sup-1]=fact[sup-1].inv();
            for(int i=sup-1;i>0;--i)ifact[i-1]=ifact[i]*Mint(i);
        }
        mint f(int n){return fact[n];}
        mint invf(int n){return ifact[n];}
        mint c(int n,int r){
            if(n<0||n<r||r<0)return mint(0);
            else return fact[n]*ifact[n-r]*ifact[r]; 
        }
        mint p(int n,int r){
            if(n<0||n<r||r<0)return Mint(0);
            else return fact[n]*ifact[n-r];
        }
};
//mintcombend
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    //verify ABC178
    Mintcomb<mint> comb(20000);
    int S;
    cin>>S;
    mint ans;
    for(int i=1;i<S;++i){
        ans+=comb.c(S-2*i-1,i-1);
    }
    cout<<ans.val()<<endl;
}