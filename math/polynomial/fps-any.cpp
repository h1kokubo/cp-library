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
    void set_mod(int p){mod=p;}
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

  static constexpr int get_mod() { return mod; }
  static constexpr bool is_friendly() {return friendly;}
};


using mint = ModInt< mod,true,false>;//負数を使う際はfastをtrueにしないように注意
//ModInt end

//dynamic modint begin
int dynamic_mod;
bool dynamic_friendly;
struct DynamicModInt {

  using u32 = uint32_t;
  using u64 = uint64_t;

  
    
  uint32_t x;
  
  DynamicModInt() : x(0) {}

  DynamicModInt(const int64_t &y)
      : x(safe_mod(y)){}
    uint32_t safe_mod(int64_t y){y%=dynamic_mod;if(y<0)y+=dynamic_mod;return y;}
   static void set_mod(int p){
       dynamic_mod=p;dynamic_friendly=false;
       }
  

  DynamicModInt &operator+=(const DynamicModInt &p) {
    if(int(x += p.x - 2 * dynamic_mod) < 0) x += 2 * dynamic_mod;
    return *this;
  }

  DynamicModInt &operator-=(const DynamicModInt &p) {
    if(int(x -= p.x) < 0) x += 2 * dynamic_mod;
    return *this;
  }

  DynamicModInt &operator*=(const DynamicModInt &p) {
    x = (uint64_t(x) * p.x)%dynamic_mod;
    return *this;
  }

  DynamicModInt &operator/=(const DynamicModInt &p) {
    *this *= p.inv();
    return *this;
  }

  DynamicModInt operator-() const { return DynamicModInt() - *this; }

  DynamicModInt operator+(const DynamicModInt &p) const { return DynamicModInt(*this) += p; }

  DynamicModInt operator-(const DynamicModInt &p) const { return DynamicModInt(*this) -= p; }

  DynamicModInt operator*(const DynamicModInt &p) const { return DynamicModInt(*this) *= p; }

  DynamicModInt operator/(const DynamicModInt &p) const { return DynamicModInt(*this) /= p; }

  bool operator==(const DynamicModInt &p) const { return val() == p.val(); }

  bool operator!=(const DynamicModInt &p) const { return val() != p.val(); }

  int val() const { return x % dynamic_mod; }

  DynamicModInt pow(int64_t n) const {
    DynamicModInt ret(1), mul(*this);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  DynamicModInt inv() const {
    return pow(dynamic_mod - 2);
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
  friend ostream &operator<<(ostream &os, const DynamicModInt &p) {
    return os << p.val();
  }
  
  friend istream &operator>>(istream &is, DynamicModInt &a) {
    int64_t t;
    is >> t;
    a = DynamicModInt(t);
    return (is);
  }

  static int get_mod() { return dynamic_mod; }
  static bool is_friendly() {return dynamic_friendly;}
};
//dynamic_modint end

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

//any_mod_ntt begin
template< int mod >
vector< int > AnyModNTTMultiply(vector< int > &a, vector< int > &b) {
  using mint = ModInt< mod ,false>;
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
  const int m1 = 1045430273, m2 = 1051721729, m3 = 1053818881;
  const auto m1_inv_m2 = mint2(m1).inv().val();
  const auto m12_inv_m3 = (mint3(m1) * m2).inv().val();
  const auto m12_mod = (mint(m1) * m2).val();
  vector< int > ret(x.size());
  for(int i = 0; i < x.size(); i++) {
    auto v1 = ((mint2(y[i]) + m2 - x[i].val()) * m1_inv_m2).val();
    auto v2 = ((z[i] + m3 - x[i].val() - mint3(m1) * v1) * m12_inv_m3).val();
    ret[i] = (mint(x[i].val()) + mint(m1) * v1 + mint(m12_mod) * v2).val();
  }
  return ret;
}
//any_mod ntt end

//ntt_ll begin

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
  const __int128 m12 = m1 * m2;
  vector< long long > ret(x.size());
  for(int i = 0; i < x.size(); i++) {
    __int128 v1 = ((mint2(y[i]) + m2 - x[i].val()) * m1_inv_m2).val();
    __int128 v2 = ((z[i] + m3 - x[i].val() - mint3(m1) * v1) * m12_inv_m3).val();
    ret[i] = (__int128)(x[i].val()) + m1 * v1 + m12 * v2;
  }
  return ret;
}
//ntt_ll end

template<class T,bool is_ll =false>//is_ll :型がmintでないならtrue ,upper 型がlong long型出ない場合の上限値 multiply(つまり畳み込み時に用いる)
struct fps{
    
        vector<T> coef;
        fps(){coef.resize(1,1);}
        fps(vector<T> v){coef=v;}
        fps operator-()const{
            fps res(coef);
            for(auto &e :res.coef)e*=-1;
            return res;
        }
        fps &operator+=(const T &c){
            for(auto &e :coef)e+=c;
            return *this;
        }
        fps operator+(const T &c){fps f(coef);f+=c;return f;}
        fps &operator-=(const T &c){
            for(auto &e :coef)e-=c;
            return *this;
        }
        fps operator-(const T &c){fps f(coef);f-=c;return f;}
        fps &operator*=(const T &c){
            for(auto &e :coef)e*=c;
            return *this;
        }
        fps operator*(const T &c){fps f(coef);f*=c;return f;}
        //定数割り算 mintでなければ使用不可
        fps &operator/=(const T &c){
            assert(!is_ll);
            assert(c.val()!=0);
            T cinv=c.inv();
            *this*=cinv;
            return *this;
        }
        fps operator/(const T &c){fps f(coef);f/=c;return f;}
        //小さいほうのサイズに合わせる
        fps &operator+=(const fps &g){
            int n=coef.size(),m=g.coef.size();
            for(int i=0;i<min(n,m);++i)coef[i]+=g.coef[i];
            return *this;
        }
        fps operator+(const fps &g){fps f(coef);f+=g;return f;}
        //小さいほうのサイズに合わせる
        fps &operator-=(const fps &g){
            int n=coef.size(),m=g.coef.size();
            for(int i=0;i<min(n,m);++i)coef[i]-=g.coef[i];
            return *this;
        }
        fps operator-(const fps &g){fps f(coef);f-=g;return f;}
        // x^dを掛ける サイズ(残す最大次数)は変えない
        fps &operator<<=(const int d){
            int n=coef.size();
            coef.insert(coef.begin(),d,0);
            coef.resize(n,0);
            return *this;
        }
        fps operator<<(const int d){fps f(coef);f<<=d;return f;}
        // x^dで割る サイズ(残す最大次数)は変えない
        fps &operator>>=(const int d){
            int n=coef.size();
            coef.erase(coef.begin(),coef.begin()+min(n,d));
            coef.resize(n,0);
            return *this;
        }
        fps operator>>(const int d){fps f(coef);f>>=d;return f;}
        //(1+cx^d)を掛ける
        void multiply_inplace(const int d,const T c){
            int n=coef.size();
            for(int i=n-d-1;i>=0;--i)coef[i+d]+=c*coef[i];
        }
        fps multiply(const int d,const T c){fps res=fps(coef);res.multiply_inplace(d,c);return res;}
        //(1+cx^d)で割る
        void divide_inplace(const int d,const T c){
            int n=coef.size();
            for(int i=0;i<n-d;++i)coef[i+d]-=coef[i]*c;
        }
        fps divide(const int d,const T c){fps res=fps(coef);res.divide_inplace(d,c);return res;}
        //スパースな多項式を掛ける (次数、係数)の次数昇順なvectorを渡す。
        void sparse_multiply_inplace(vector<pair<int,T>> g){
            int n=coef.size();
            auto [d,c]=g.front();
            if(d==0)g.erase(g.begin());//定数項は別に扱う
            else c=0;
            for(int i=n-1;i>=0;--i){
                coef[i]*=c;
                for(auto &[j,b]:g){
                    if(j>i)break;//次数昇順
                    coef[i]+=coef[i-j]*b;
                }
            }
        }
        fps sparse_multiply(vector<pair<int,T>> g){fps f=fps(coef);f.sparse_multiply_inplace(g);return f;}
        //T=min限定　スパースな多項式を掛ける、(次数、係数)の次数昇順なvectorを渡す。 ただし、定数項を持たなければならない(持たない場合は分解して右シフトせよ(z^dで割る))
        void sparse_divide_inplace(vector<pair<int,T>> g){
            assert(!is_ll);
            int n=coef.size();
            auto [d,c]=g.front();
            assert(d==0&&c!=T(0));
            T cinv=c.inv();
            g.erase(g.begin());
            for(int i=0;i<n;++i){
                for(auto &[j,b]:g){
                    if(j>i)break;
                    coef[i]-=coef[i-j]*b;
                }
                coef[i]*=cinv;
            }
        }
        fps sparse_divide(vector<pair<int,T>> g){fps f=f(coef);f.sparse_divide_inplace(g);return f;}
        //T=mint 限定不定定数0とした積分 はみ出した項は削除されるので必要ならresizeしておくこと。
        void integral_inplace(){
            int n=coef.size();
            coef.insert(coef.begin(),0);
            coef.pop_back();
            vector<T> inv(n);
            inv[1]=T(1);
            int mod=T::get_mod();
            for(int i=2;i<n;++i)inv[i]=-inv[mod%i]*(mod/i);
            for(int i=2;i<n;++i)coef[i]*=inv[i];
        }
        fps integral() const{fps res=fps(coef);res.integral_inplace();return res;}
        void multiply_inplace(fps &g,int d=-1){//d=-1 であればfの次数と同じだけ残す。 llであればntt_ll,friendlyであればfriendlyntt,そうでなければany_mod_nttを用いる。
            int size;
            if(d==-1)size=coef.size();
            else size=d;
            assert(!fps::get_is_ll());
            if(T::is_friendly()){
                NumberTheoreticTransformFriendlyModInt<T> ntt;
                coef=ntt.multiply(coef,g.coef);
            }
            else{
                vector<int> f_coef(coef.size()),g_coef(g.coef.size());
                for(int i=0;i<coef.size();++i)f_coef[i]=coef[i].val();
                for(int i=0;i<g.coef.size();++i)g_coef[i]=g.coef[i].val();
                vector<int> new_coef=AnyModNTTMultiply<T::get_mod()>(f_coef,g_coef);
                new_coef.resize(size);
                for(int i=0;i<size;++i)coef[i]=T(new_coef[i]);
            }
            coef.resize(size);
        }
        fps multiply(fps &g,int d=-1){fps f(coef);f.multiply_inplace(g,d);return f;}
        
        void multiply_inplace_ll(fps &g,int d=-1){
            int size;
            if(d==-1)size=coef.size();
            else size=d;
            assert(fps::get_is_ll());
            coef=Multiply_ll(coef,g.coef);
            coef.resize(size,T(0));
        }
        
        fps multiply_ll(fps &g,int d=-1){fps f(coef);f.multiply_inplace_ll(g,d);return f;}
        
        
        // 微分、最大次は2で埋められる
        void derivative_inplace(){
            int n=coef.size();
            coef.push_back(0);
            coef.erase(coef.begin());
            for(int i=1;i<n;++i)coef[i]*=i+1;
        }
        fps derivative() const{fps res=fps(coef);res.derivative_inplace();return res;}

        void fzt_inplace(){//g(S)=∑(T⊆S)f(T) に変換
            int n=coef.size();
            int N=1,bsize=0;
            while(N<n){
                N<<=1;
                ++bsize;
            }
            coef.resize(N,T(0));
            for(int j=0;j<bsize;++j){
                int bit=1<<j;
                for(int i=0;i<N;++i){
                    if(i&bit)coef[i]+=coef[i^bit];
                }
            }
            coef.resize(n);
        }
        fps fzt(){fps f(coef);f.fzt_inplace();return f;}
        void fmt_inplace(){//g(S)=∑(T⊆S)f(T)なる fを求める。
            int n=coef.size();
            int N=1,bsize=0;
            while(N<n){
                N<<=1;
                ++bsize;
            }
            coef.resize(N,T(0));
            for(int j=0;j<bsize;++j){
                int bit=1<<j;
                for(int i=0;i<N;++i){
                    if(i&bit)coef[i]-=coef[i^bit];
                }
            }
            coef.resize(n);
        }
        fps fmt(){fps f(coef);f.fmt_inplace();return f;}
        mint eval(const T &a){
            mint x=T(1),res=T(0);
            for(auto e:coef)res+=e*x,x*=a;
            return res;
        }
        static bool get_is_ll(){return is_ll;}

};

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i) 
#define all(v) v.begin(),v.end()
long long intpow(long long x,long long n){long long ans=1;while(n>0){if(n&1){ans*=x;}n>>=1;x*=x;}return ans;}



void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void verify1(){
    //TDPC-A
    int N;
    cin>>N;
    vector<int> p(N);
    rep(i,N)cin>>p[i];
    vector<int> coef(10001,0);
    fps<int,true> fps(coef);
    fps.coef[0]=1;
    rep(i,N)fps.multiply_inplace(p[i],1);
    int ans=0;
    rep(i,10001)if(fps.coef[i])ans++;
    cout<<ans<<endl; 
}

void verify2(){
    //EDPC-M
    int N,K;
    cin>>N>>K;
    vector<int> a(N);
    rep(i,N)cin>>a[i];
    vector<mint> v(K+5,0);
    v[0]=mint(1);
    fps<mint> f(v);
    rep(i,N){
        f.multiply_inplace(a[i]+1,-1);
        f.divide_inplace(1,-1);
    }
    cout<<f.coef[K].val()<<endl;
}
void verify3(){
    //TDPC-F
    int N,K;
    cin>>N>>K;
    vector<mint> v(N+1,0);
    v[0]=mint(1);
    fps<mint> f(v);
    f<<=1;
    f.multiply_inplace(K-1,mint(-1));
    f.multiply_inplace(1,mint(-1));
    f.sparse_divide_inplace(vector<pair<int,mint>>{{0,mint(1)},{1,mint(-2)},{K+1,mint(1)}});
    cout<<f.coef[N].val()<<endl;
}

void verify4(){
    //verify HHKB2020 F
    int N;
    cin>>N;
    int L[N],R[N];
    rep(i,N)cin>>L[i]>>R[i];
    vector<pair<int,pair<int,int>>> lst(2*N);
    mint all_prod=1;
    rep(i,N){
        all_prod*=R[i]-L[i];
        lst[2*i]={0,{L[i],R[i]}};
        lst[2*i+1]={1,{R[i],L[i]}};
    }
    sort(all(lst),[](pair<int,pair<int,int>> n1,pair<int,pair<int,int>> n2){return n1.second.first<n2.second.first||(n1.second.first==n2.second.first&&n1.first<n2.first);});
    mint ans=mint(intpow(10,9))*all_prod;
    vector<mint> v(N+2,0);
    v[0]=1;
    fps<mint> f(v);
    int pred=0;
    int cnt=0;//Lを通過した数
    rep(i,2*N){
        if(lst[i].first==0){
            ++cnt;
            f*=-lst[i].second.first;
            f.multiply_inplace(1,mint(-lst[i].second.first).inv());
        }
        else{
            if(cnt==N){
                fps<mint> integral=f.integral();
                ans+=integral.eval(pred);
                ans-=integral.eval(lst[i].second.first);
            }
            f/=-lst[i].second.second;
            f.divide_inplace(1,mint(-lst[i].second.second).inv());
            f*=lst[i].second.first-lst[i].second.second;
            
        }
        pred=lst[i].second.first;
    }
    ans-=mint(intpow(10,9)-pred)*all_prod;
    mint fact=1;
    rep(i,N)fact*=i+2;
    ans*=fact;
    cout<<ans.val()<<endl;
}
void verify5(){
    //ABC179D
    int N,K;
    cin>>N>>K;
    vector<int> lst(N+1);
    lst[0]++;
    lst[1]--;
    int L,R;
    rep(i,K){
        cin>>L>>R;
        lst[L]--;
        lst[R+1]++;
    }
    vector<pair<int,mint>> divlst;
    rep(i,N+1)if(lst[i]!=0)divlst.push_back({i,mint(lst[i])});
    vector<mint> v(N+6);
    v[0]=1;
    fps<mint> f(v); 
    f.multiply_inplace(1,mint(-1));
    f.sparse_divide_inplace(divlst);
    cout<<f.coef[N-1].val()<<endl;
}
void verify6(){
    //ABC178D
    int S;
    cin>>S;
    vector<mint> v(S+1);
    v[0]=1;
    fps<mint> f(v);
    mint ans=0;
    for(int i=0;i<S/3;++i){
        f<<=3;
        f.divide_inplace(1,mint(-1));
        ans+=f.coef[S];
    }
    cout<<ans.val()<<endl;
}
void verify7(){
    //ABC171 F
    int K;cin>>K;
    string S;cin>>S;
    int N=S.size();
    vector<mint> v(K+1);
    mint now=1;
    Mintcomb<mint> comb(2000005);
    rep(i,K+1){
        v[i]=comb.c(i+N-1,N-1)*now;
        now*=25;
    }
    fps<mint> f(v);
    f.divide_inplace(1,mint(-26));
    cout<<f.coef[K]<<endl;
}
void verify8(){
    //ABC169F
    mint inv2=mint(2).inv();
    int N,S;cin>>N>>S;
    vector<int> A(N);rep(i,N)cin>>A[i];
    vector<mint> v(S+1);
    v[0]=1;
    fps<mint> f(v);
    rep(i,N){
        f*=mint(2);
        f.multiply_inplace(A[i],inv2);
    }
    cout<<f.coef[S]<<endl;
}
void verify9(){
    //ABC149 F
    int N;ll M;cin>>N>>M;
    vector<ll> A(N);
    vector<ll> v(100005);
    rep(i,N){
        cin>>A[i];
        ++v[A[i]];
    }
    fps<ll,true> f(v);
    auto g=f.multiply_ll(f,200005);
    ll ans=0;
    for(ll i=200000;i>=0;--i){
        if(g.coef[i]<=M){
            ans+=i*g.coef[i];
            M-=g.coef[i];
        }
        else{
            ans+=i*M;
            M=0;
            break;
        }
    }
    cout<<ans<<endl;
}
const int P=200003;
void verify10(){
    //AGC047 C
    int N;
    cin>>N;
    vector<ll> A(N);
    vector<ll> table(P);
    rep(i,N){
        cin>>A[i];
        ++table[A[i]];
    }
    vector<ll> logtable(P-1);
    ll now=1;
    rep(i,P-1){
        logtable[i]+=table[now];
        now*=2;
        now%=P;
    }
    fps<ll,true> f(logtable);
    f.multiply_inplace_ll(f,2*P-3);
    ll ans=0;
    now=1;
    rep(i,2*P-3){
        ans+=f.coef[i]*now;
        now*=2;
        now%=P;
    }
    rep(i,N)ans-=A[i]*A[i]%P;
    cout<<ans/2<<endl;
}
void verify11(){
    //yukicoder 2つの数の和 https://yukicoder.me/problems/no/723
    int N,X;
    cin>>N>>X;
    vector<ll> a(N),v(100001);
    rep(i,N){
        cin>>a[i];
        ++v[a[i]];
    }
    fps<ll,true> f(v);
    f.multiply_inplace_ll(f,2*v.size()-1);
    ll ans;
    if(X>f.coef.size()-1)ans=0;
    else ans=f.coef[X];
    cout<<ans<<endl;
}
void verify12(){
    //yukicoder 場合の数 https://yukicoder.me/problems/no/287
    int N;
    cin>>N;
    vector<ll> v(6*N+1);
    v[0]=1;
    fps<ll,true> f(v);
    rep(i,8){
        f.multiply_inplace(N+1,-1);
        f.divide_inplace(1,-1);
    }
    cout<<f.coef[6*N]<<endl;
}
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
void verify13(){
    //yukicoder 3PrimeCounting https://yukicoder.me/problems/no/732
    int N;
    cin>>N;
    Eratosthenes ers(3*N);
    vector<ll> v(N+1);
    rep(i,N+1)if(ers.is_prime(i))v[i]=1;
    fps<ll,true> f(v);
    auto f2=f.multiply_ll(f,2*N+1);
    auto f3=f2.multiply_ll(f,3*N+1);
    ll ans=0;
    rep(i,3*N+1)if(ers.is_prime(i))ans+=f3.coef[i];
    vector<ll> v_ev(2*N+1);
    rep(i,N+1)if(ers.is_prime(i))v_ev[2*i]=1;
    fps<ll,true> f_ev(v_ev);
    f_ev.multiply_inplace_ll(f,3*N+1);
    rep(i,3*N+1)if(ers.is_prime(i))ans-=f_ev.coef[i]*3;
    cout<<ans/6<<endl;
}
void verify14(){
    //ARC028 注文の多い高橋商店
    int N,M,Q;
    cin>>N>>M>>Q;
    vector<mint> v(2*M+1);
    v[0]=mint(1);
    fps<mint> f(v);
    vector<int> a(N);
    rep(i,N){
        cin>>a[i];
        f.multiply_inplace(a[i]+1,mint(-1));
        f.divide_inplace(1,mint(-1));
    }
    vector<vector<mint>> kx(N,vector<mint>(M+1));
    rep(i,N){
        f.divide_inplace(a[i]+1,mint(-1));
        f.multiply_inplace(1,mint(-1));
        rep(j,M+1)kx[i][j]=f.coef[M-j];
        f.multiply_inplace(a[i]+1,mint(-1));
        f.divide_inplace(1,mint(-1));
    }
    int k,x;
    vector<mint> ans(Q);
    rep(i,Q){
        cin>>k>>x;
        k--;
        ans[i]=kx[k][x];
    }
    rep(i,Q)cout<<ans[i]<<endl;
}
void verify15(){
    //ABC159-F
    int N,S;cin>>N>>S;
    vector<int> A(N);rep(i,N)cin>>A[i];
    vector<mint> v(S+2);
    fps<mint> f(v);
    mint ans=0;
    rep(i,N){
        f.coef[0]+=1;
        f.multiply_inplace(A[i],mint(1));
        ans+=f.coef[S];
    }
    cout<<ans<<endl;
}
/*
void verify16(){
    //ABC137-F
    //ラグランジュ補間
    int p;
    cin>>p;
    using mint=DynamicModInt;
    mint::set_mod(p);
    vector<mint> a(p);
    rep(i,p)cin>>a[i];
    vector<mint> v(p+1);
    v[0]=mint(1);
    fps<mint> f(v);
    rep(i,p){
        
        if(i){
        f*=mint(-i);
        f.multiply_inplace(1,mint(-i).inv());
        }
        else{
            f<<=1;
        }
    }
    vector<mint> v_(p+1);
    fps<mint> ans(v_);
    rep(i,p){
        
        if(i){
            mint prod=mint(1);
            rep(j,p)if(i!=j)prod*=mint(i-j);
            fps<mint> g=f.divide(1,mint(-i).inv());
            g/=mint(-i);
            g*=mint(a[i])/prod;
            ans+=g;
        }
        else{
            mint prod=mint(1);
            rep(j,p)if(j!=0)prod*=mint(-j);
            fps<mint> g=f>>1;
            g*=mint(a[i])/prod;
            ans+=g;
        }
    }
    rep(i,p){
        if(i)cout<<" ";
        cout<<ans.coef[i];
    }
    cout<<endl;
}
*/  

void Main(){
    //verify1();
    //verify2();
    //verify3();
    //verify4();
    //verify5();
    //verify6();
    //verify7();
    //verify8();
    //verify9();
    //verify10();
    //verify11();
    //verify12();
    //verify13();
    //verify14();
    //verify15();
    //verify16();
    verify17();
}