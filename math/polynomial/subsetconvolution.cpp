#include <bits/stdc++.h>
using namespace std;


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

//ntt end
int popcnt(int x){return __builtin_popcount(x);}
//subsetconvolution begin
template<typename T>
vector<T> subsetconvolution(vector<T> a,vector<T> b){
    int n=max(a.size(),b.size());
    int bn=0;
    while((1<<bn)<n)bn++;
    n=1<<bn;
    a.resize(n,T(0));b.resize(n,T(0));
    vector<vector<T>> A(bn+1,vector<T>(n)),B(bn+1,vector<T>(n));
    for(int i=0;i<a.size();++i)A[popcnt(i)][i]=a[i];
    for(int i=0;i<b.size();++i)B[popcnt(i)][i]=b[i];
    //集合元数ごとで包含zeta変換
    for(int k=0;k<=bn;++k){
        for(int i=0;i<bn;++i){
            for(int j=0;j<n;++j){
                if(!((j>>i)&1)){
                    A[k][j|(1<<i)]+=A[k][j];
                    B[k][j|(1<<i)]+=B[k][j];
                }
            }
        }
    }
    //非公和＝元数の和 を踏まえて積
    vector<vector<T>> C(bn+1,vector<T>(n));
    for(int i=0;i<=bn;++i)for(int j=0;j<=bn;++j){
        if(i+j>bn)continue;
        for(int k=0;k<n;++k){
            C[i+j][k]+=A[i][k]*B[j][k];
        }
    }
    //集合元数ごとで包含mobius変換
    for(int k=0;k<=bn;++k){
        for(int i=0;i<bn;++i){
            for(int j=0;j<n;++j){
                if(!((j>>i)&1)){
                    C[k][j|(1<<i)]-=C[k][j];
                }
            }
        }
    }
    vector<T> res(1<<bn);
    for(int j=0;j<n;++j)res[j]=C[popcnt(j)][j];
    return res;
}
//subsetconvolution end

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}



void Main(){
int N;cin>>N;
vector<mint> a(1<<N),b(1<<N);
rep(i,1<<N)cin>>a[i];
rep(i,1<<N)cin>>b[i];
vector<mint> ans=subsetconvolution(a,b);
rep(i,1<<N){
    if(i)cout<<" ";
    cout<<ans[i];
}
cout<<endl;
}