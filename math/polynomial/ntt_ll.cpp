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

//ntt begin
template< typename Mint >
struct NumberTheoreticTransformFriendlyModInt {

  vector< Mint > dw, idw;
  int max_base;
  Mint root;

  NumberTheoreticTransformFriendlyModInt() {
    const unsigned mod = Mint::get_mod();
    assert(Mint::is_friendly());
    assert(mod >= 3 && mod % 2 == 1);
    auto tmp = mod - 1;
    max_base = 0;
    while(tmp % 2 == 0) tmp >>= 1, max_base++;
    root = 2;
    while(root.pow((mod - 1) >> 1) == 1) root += 1;
    assert(root.pow(mod - 1) == 1);
    dw.resize(max_base);
    idw.resize(max_base);
    for(int i = 0; i < max_base; i++) {
      dw[i] = -root.pow((mod - 1) >> (i + 2));
      idw[i] = Mint(1) / dw[i];
    }
  }

  void ntt(vector< Mint > &a) {
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    assert(__builtin_ctz(n) <= max_base);
    for(int m = n; m >>= 1;) {
      Mint w = 1;
      for(int s = 0, k = 0; s < n; s += 2 * m) {
        for(int i = s, j = s + m; i < s + m; ++i, ++j) {
          auto x = a[i], y = a[j] * w;
          a[i] = x + y, a[j] = x - y;
        }
        w *= dw[__builtin_ctz(++k)];
      }
    }
  }

  void intt(vector< Mint > &a, bool f = true) {
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    assert(__builtin_ctz(n) <= max_base);
    for(int m = 1; m < n; m *= 2) {
      Mint w = 1;
      for(int s = 0, k = 0; s < n; s += 2 * m) {
        for(int i = s, j = s + m; i < s + m; ++i, ++j) {
          auto x = a[i], y = a[j];
          a[i] = x + y, a[j] = (x - y) * w;
        }
        w *= idw[__builtin_ctz(++k)];
      }
    }
    if(f) {
      Mint inv_sz = Mint(1) / n;
      for(int i = 0; i < n; i++) a[i] *= inv_sz;
    }
  }

  vector< Mint > multiply(vector< Mint > a, vector< Mint > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    Mint inv_sz = Mint(1) / sz;
    for(int i = 0; i < sz; i++) a[i] *= b[i] * inv_sz;
    intt(a, false);
    a.resize(need);
    return a;
  }
};
#define NTT NumberTheoreticTransformFriendlyModInt
//ntt end

//ntt_ll begin
template< long long upper >//あり得る上限値
vector< long long > Multiply_ll(vector< long long > &a, vector< long long > &b) {
  //using mint = ModInt< mod ,false>;
  using mint1 = ModInt< 1045430273 ,true>;
  using mint2 = ModInt< 1051721729 ,true>;
  using mint3 = ModInt< 1053818881 ,true>;
  NumberTheoreticTransformFriendlyModInt< mint1 > ntt1;
  NumberTheoreticTransformFriendlyModInt< mint2 > ntt2;
  NumberTheoreticTransformFriendlyModInt< mint3 > ntt3;
  vector< mint1 > a1(begin(a), end(a)), b1(begin(b), end(b));
  vector< mint2 > a2(begin(a), end(a)), b2(begin(b), end(b));
  vector< mint3 > a3(begin(a), end(a)), b3(begin(b), end(b));
  auto x = ntt1.multiply(a1, b1);
  auto y = ntt2.multiply(a2, b2);
  auto z = ntt3.multiply(a3, b3);
  const __int128 m1 = 1045430273, m2 = 1051721729, m3 = 1053818881;
  const __int128 m1_inv_m2 = mint2(m1).inv().val();
  const __int128 m12_inv_m3 = (mint3(m1) * m2).inv().val();
  const __int128 m12_mod = m1 * m2%mod;
  vector< long long > ret(x.size());
  for(int i = 0; i < x.size(); i++) {
    __int128 v1 = ((mint2(y[i]) + m2 - x[i].val()) * m1_inv_m2).val();
    __int128 v2 = ((z[i] + m3 - x[i].val() - mint3(m1) * v1) * m12_inv_m3).val();
    ret[i] = ((__int128)(x[i].val()) + m1 * v1 + m12_mod * v2)%mod;
  }
  return ret;
}
//ntt_ll end

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
/*
void Main(){
//verify Library-Checker Convolution(1e+7)
int N,M;
cin>>N>>M;
vector<ll> a(N),b(M);
rep(i,N)cin>>a[i];
rep(i,M)cin>>b[i];
vector<ll> c=AnyModNTTMultiply<mod>(a,b);
rep(i,N+M-1)cout<<c[i]<<endl;
}
*/
const int P=200003;
void Main(){
    int N;
    cin>>N;
    vector<ll> a(N);
    vector<ll> table(P);
    rep(i,N){
        cin>>a[i];table[a[i]]++;
    }
    vector<ll> logtable(P-1);
    ll now=1;
    rep(i,P-1){
        logtable[i]+=table[now];
        now*=2;
        now%=P;
    }
    vector<ll> c=Multiply_ll<100000000000>(logtable,logtable);
    ll ans=0;
    now=1;
    rep(i,c.size()){
        ans+=now*c[i];
        now*=2;
        now%=P;
    }
    rep(i,N)ans-=a[i]*a[i]%P;
    cout<<ans/2<<endl;
}