#include <bits/stdc++.h>
using namespace std;

//eratosthenes begin
struct Eratosthenes{
    private:
        int n;
        vector<bool> sieve;
    public:
        Eratosthenes(int n_):n(n_+1),sieve(vector<bool>(n,true)){
            sieve[0]=sieve[1]=false;
            int i=2;
            while(i*i<n){
                if(!sieve[i]){
                    ++i;
                    continue;
                }
                for(int j=2*i;j<n;j+=i){
                    sieve[j]=false;
                }
                ++i;
            }
        }
        bool is_prime(int x){
            return sieve[x];
        }
};
//eratosthenes end

//multiple-zeta begin
template<typename T> void multiplezetainline(vector<T> &v,Eratosthenes &er){
    for(int p=2;p<v.size();++p){
        if(!er.is_prime(p))continue;
        for(int i=(v.size()-1)/p;i>=1;--i){
            v[i]+=v[i*p];
        }
    }
}
template<typename T> vector<T> multiplezeta(const vector<T> &v,Eratosthenes &er){
    vector<T> vcopy(v);
    multiplezetainline(vcopy,er);
    return vcopy;
}
//multiple-zeta end

//multiple-mobius begin
template<typename T> void multiplemobiusinline(vector<T> &v,Eratosthenes &er){
    for(int p=2;p<v.size();++p){
        if(!er.is_prime(p))continue;
        for(int i=1;i*p<v.size();++i){
            v[i]-=v[i*p];
        }
    }
}
template<typename T> vector<T> multiplemobius(const vector<T> &v,Eratosthenes &er){
    vector<T> vcopy(v);
    multiplemobiusinline(vcopy,er);
    return vcopy;
}
//multiple-mobius end

//gcd-convolution begin
template<typename T>
vector<T> gcdconvolution(vector<T> a,vector<T> b,Eratosthenes &er){
    int n=max(a.size(),b.size());
    a.resize(n,T(0));b.resize(n,T(0));
    vector<T> res(n,T(0));
    multiplezetainline(a,er);
    multiplezetainline(b,er);
    for(int i=1;i<n;++i)res[i]=a[i]*b[i];
    multiplemobiusinline(res,er);
    return res;
}
//gcd-convolution end

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//ModInt begin
//const int mod=1e9+7;
const int mod=998244353;

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

void Main(){
    const int MAX=1000001;
    int N;cin>>N;
    vector<int> A(N);rep(i,N)cin>>A[i];
    vector<mint> F(MAX,mint(0));//Aの分布
    rep(i,N)F[A[i]]+=mint(1);
    for(int i=1;i<MAX;++i)F[i]*=mint(i);
    Eratosthenes er(MAX);
    vector<mint> res=gcdconvolution(F,F,er);
    mint ans;
    for(int i=1;i<MAX;++i)ans+=res[i]/mint(i);
    for(int i=0;i<N;++i)ans-=A[i];
    cout<<ans/2<<endl;
}