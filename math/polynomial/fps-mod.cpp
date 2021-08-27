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

//fps_mod begin
template<typename T>
struct FormalPowerSeries{
    NTT<T> ntt;
    FormalPowerSeries(){
        ntt=NTT<T>();
    }
    vector<T> sliced(const vector<T> &v,const int l,const int r){return vector<T>(v.begin()+l,v.begin()+r);}//f(x)%x^r/x^l
    vector<T> reversed(const vector<T> &v,const int l,const int r){//(f(x)%x^r/x^l)(1/x)x^(r-l)
      vector<T> ret=vector<T>(v.begin()+l,v.begin()+r);
      reverse(ret.begin(),ret.end());
      return ret;
    }
    void add(vector<T> &v,const vector<T> &w){//f=v[x],g=w[x] f+=g
      if(w.size()>v.size())v.resize(w.size());
      for(int i=0;i<w.size();++i)v[i]+=w[i];
    } 
    vector<T> added(const vector<T> &v,const vector<T> &w){
      vector<T> ret(v);
      add(ret,w);
      return ret;
    }
    void sub(vector<T> &v,const vector<T> &w){//f=v[x],g=w[x] f-=g
      if(w.size()>v.size())v.resize(w.size());
      for(int i=0;i<w.size();++i)v[i]-=w[i];
    }
    vector<T> subbed(const vector<T> &v,const vector<T> &w){
      vector<T> ret(v);
      sub(ret,w);
      return ret;
    }
    void multiply(vector<T> &v,const vector<T> &w){//f=v[x],g=w[x] f*=g
      auto ret= ntt.multiply(v,w);
      v.resize(ret.size());
      for(int i=0;i<ret.size();++i)v[i]=ret[i];
    }
    vector<T> multiplied(const vector<T> &v,const vector<T> &w){
      return ntt.multiply(v,w);
    }
    void divide(vector<T> &v,const vector<T> &w){//f=v[x],g=w[x] f/=g
      if(v.size()<w.size()){
        v.clear();
        return;
      }
      int n=v.size()-w.size()+1;
      auto ret=reversed(multiplied(reversed(v,v.size()-n,v.size()),sliced(inversed(reversed(w,0,w.size())),0,n)),0,n);
      v.resize(n);
      for(int i=0;i<n;++i)v[i]=ret[i];
    
    }
    vector<T> divided(const vector<T> &v,const vector<T> &w){
      if(v.size()<w.size()){
        return {};
      }
      int n=v.size()-w.size()+1;
      return reversed(multiplied(reversed(v,v.size()-n,v.size()),inversed(reversed(w,0,w.size()),n)),0,n);
    }
    void extract(vector<T> &v,const vector<T> &w){//f=v[x],g=w[x] f%=g
      int n=v.size()-w.size()+1;
      sub(v,multiplied(divided(v,w),w));
      v.resize(w.size());
    }
    vector<T> extracted(const vector<T> &v,const vector<T> &w){
      int n=v.size()-w.size()+1;
      return slice(subbed(v,multiplied(divided(v,w),w)),0,w.size());
    }
    pair<vector<T>,vector<T>> div_mod(const vector<T> &v,const vector<T> &w){
      vector<T> q=divided(v,w);
      return make_pair(q,subbed(v,multiplied(q,w)));
    }
    void add(vector<T> &v,const T r){// f=v[x] v[x]+r
      if(v.size()==0)v.resize(1);
      v[0]+=r;
    }
    vector<T> added(const vector<T> &v,const T r){
      vector<T> ret(v);
      if(ret.size()==0)ret.resize(1);
      ret[0]+=r;
      return ret;
    }
    void sub(vector<T> &v,const T r){// f=v[x] v[x]-r
      if(v.size()==0)v.resize(1);
      v[0]-=r;
    }
    vector<T> subbed(const vector<T> &v,const T r){
      vector<T> ret(v);
      sub(ret,r);
      return ret;
    }
    void multiply(vector<T> &v,const T r){// f=v[x] r*v[x]
      for(int i=0;i<v.size();++i)v[i]*=r;
    }
    vector<T> multiplied(const vector<T> &v,const T r){
      vector<T> ret(v);
      multiply(ret,r);
      return ret;
    }
    void divide(vector<T> &v,const T r){// f=v[x] v[x]/r
      T invr=r.inv();
      for(int i=0;i<v.size();++i)v[i]*=invr;
    }
    vector<T> divided(const vector<T> &v,const T r){
      vector<T> ret(v);
      divide(ret,r);
      return ret;
    }
    void shiftl(vector<T> &v,const int d){// f=v[x] f*x^d
      v.insert(v.begin(),d,T(0));
      v.erase(v.begin()+v.size()-d,v.begin()+v.size());
    }
    vector<T> shiftedl(const vector<T> &v,const int d){
      vector<T> ret(v);
      shiftl(ret,d);
      return ret;
    }
    void shiftr(vector<T> &v,const int d){// f=v[x] f/x^d
      v.insert(v.end(),d,T(0));
      v.erase(v.begin(),v.begin()+d);
    }
    vector<T> shiftedr(const vector<T> &v,const int d){
      vector<T> ret(v);
      shiftedr(ret,d);
      return ret;
    }
    T eval(const vector<T> &v,const T x){// f=v[x] f(x)
      T r=T(0),w=T(1);
      for(auto &vi:v){
        r+=w*vi;
        w*=x;
      }
      return r;
    }
    void differentiate(vector<T> &v){
      for(int i=v.size()-1;i>=0;--i){
        v[i]*=T(i);
      }
      v.push_back(T(0));
      v.erase(v.begin());
      v.resize(max(0,(int)v.size()-1));
    }
    vector<T> differentiated(const vector<T> &v){
      vector<T> ret(v);
      differentiate(ret);
      return ret;
    }
    void integrate(vector<T> &v){
      v.insert(v.begin(),T(0));
      if(v.size()<=2)return;
      vector<T>  inv(v.size());
      inv[1]=T(1);
      int p=T::get_mod();
      for(int i=2;i<v.size();++i){
        inv[i]=-inv[p%i]*(p/i);
        v[i]*=inv[i];
      }
    }
    vector<T> integrated(vector<T> &v){
      vector<T> ret(v);
      integrate(ret);
      return ret;
    }
    void sparse_multiply(vector<T> &v,const vector<pair<int,T>> &w){// f=v[x],(d[i],c[i])=w[i] f[x]*{∑c[i]x^d[i]}
      assert(w.size()>0);
      //wに定数項が存在すれば別途処理
      auto [d,c] = w.front();
      if(d==0) w.erase(w.begin());
      else c=0;
      for(int i=v.size()-1;i>=0;--i){
        v[i]*=c;
        for(auto &[j,b]:w){
          if(j>i)break;
          v[i]+=v[i-j]*b;
        }
      }
    }
    vector<T> sparse_multiplied(const vector<T> &v,const vector<pair<int,T>> &w){
      vector<T> ret(v);
      sparse_multiply(ret,w);
      return ret;
    }
    void sparse_divide(vector<T> &v,const vector<pair<int,T>> &w){// f=v[x],(d[i],c[i])=w[i] f[x]/{∑c[i]x^d[i]}
      assert(w.size()>0);
      //wに定数項が存在しなければならない(なければvをシフトすることで同様)
      auto [d,c] = w.front();
      assert(d==0&&c!=T(0));
      T cinv=c.inv();
      w.erase(w.begin());
      for(int i=0;i<v.size();++i){
        for(auto &[j,b]:w){
          if(j>i)break;
          v[i]-=v[i-j]*b;
        }
        v[i]*=cinv;
      }
    }
    vector<T> sparse_divided(const vector<T> &v,const vector<pair<int,T>> &w){
      vector<T> ret(v);
      sparser_divide(ret,w);
      return ret;
    }
    vector<T> dot(const vector<T> &v,const vector<T> &w){// v・w (内積)
      vector<T> res(min(v.size(),w.size()));
      for(int i=0;i<res.size();++i)res[i]=v[i]*w[i];
      return res;
    }
    void inverse(vector<T> &v,int deg=-1){// f=v[x] ,1/f[x] mod x^max(deg,v.size())
      assert(v[0]!=T(0));//定数項が0でない
      vector<T> ret(v);
      if(deg==-1)deg=v.size();
      v.resize(deg);
      v[0]=T(1)/ret[0];
      for(int d=1;d<deg;d<<=1){
        vector<T> f(2*d),g(2*d);
        for(int j=0;j<min(2*d,(int)ret.size());++j)f[j]=ret[j];
        for(int j=0;j<d;++j)g[j]=v[j];
        ntt.ntt(f);
        ntt.ntt(g);
        f=dot(f,g);
        ntt.intt(f);
        for(int j=0;j<d;++j)f[j]=T(0);
        ntt.ntt(f);
        f=dot(f,g);
        ntt.intt(f);
        for(int j=d;j<min(2*d,deg);++j)v[j]=-f[j];
      }
    }
    vector<T> inversed(const vector<T> &v,const int deg=-1){
      vector<T> ret(v);
      inverse(ret,deg);
      return ret;
    }
    void logtake(vector<T> &v,int deg=-1){ // f=v[x] f(x)=∑g(x)^k/k! (mod x^v.size())なる g
      assert(v[0]==T(1));
      if(deg==-1)deg=v.size();
      vector<mint> vdiff=differentiated(v);
      inverse(v);
      multiply(vdiff,v);
      vector<mint> ret=sliced(vdiff,0,deg-1);
      integrate(ret);
      for(int i=0;i<deg;++i)v[i]=ret[i];
    }
    vector<T> logtaken(const vector<T> &v,const int deg=-1){
      assert(v[0]==T(1));
      if(deg==-1)deg=v.size();
      vector<mint> vdiff=differentiated(v);
      inverse(v);
      multiply(vdiff,v);
      vector<mint> ret=sliced(vdiff,0,deg-1);
      integrate(ret);
      return ret;
    }
    vector<T> taylor_shifted(const vector<T> &v,T c){ //f=v[x+c]　を返す
      vector<T> fact(v.size()),ifact(v.size());
      fact[0]=T(1);
      ifact[0]=T(1);
      for(int i=1;i<v.size();++i)fact[i]=fact[i-1]*T(i);
      ifact[v.size()-1]=fact[v.size()-1].inv();
      for(int i=v.size()-1;i>1;--i)ifact[i-1]=ifact[i]*T(i);
      vector<T> p(v);
      for(int i=0;i<v.size();++i){
        p[i]*=fact[i];
      }
      reverse(p.begin(),p.end());
      vector<T> bs(v.size(),T(1));
      for(int i=1;i<v.size();++i)bs[i]=bs[i-1]*c*ifact[i]*fact[i-1];
      multiply(p,bs);
      p=sliced(p,0,v.size());
      reverse(p.begin(),p.end());
      for(int i=0;i<v.size();++i)p[i]*=ifact[i];
      return p;
    }
    void taylor_shift(vector<T> &v,T c){
      auto p=taylor_shifted(v,c);
      for(int i=0;i<p.size();++i)v[i]=p[i];
    }
};
using FPS=FormalPowerSeries<mint>;
//fps_mod end

#define endl "\n"
#define ll long long
#define ld long double
#define ul unsigned long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()
#define mp(a,b) make_pair(a,b)


void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


//div_mod
void verify1(){
   int N,M;
  cin>>N>>M;
  vector<mint> f(N),g(M);
  rep(i,N)cin>>f[i];
  rep(i,M)cin>>g[i];
  FPS fps;
  auto [q,r]=fps.div_mod(f,g);
  int qd=-1;
  for(int i=q.size()-1;i>=0;--i)if(q[i]!=mint(0)){
    qd=i;
    break;
  }
  int rd=-1;
  for(int i=r.size()-1;i>=0;--i)if(r[i]!=mint(0)){
    rd=i;
    break;
  }
  cout<<qd+1<<" "<<rd+1<<endl;
  rep(i,qd+1){
    if(i)cout<<" ";
    cout<<q[i];
  }
  cout<<endl;
  rep(i,rd+1){
    if(i)cout<<" ";
    cout<<r[i];
  }
  cout<<endl;
}
//inverse
void verify2(){
  int N;cin>>N;
  vector<mint> a(N);
  rep(i,N)cin>>a[i];
  FPS fps;
  fps.inverse(a);
  rep(i,N){
    if(i)cout<<" ";
    cout<<a[i];
  }
  cout<<endl;
}
//log
void verify3(){
  int N;cin>>N;
  vector<mint> a(N);
  rep(i,N)cin>>a[i];
  FPS fps;
  fps.logtake(a);
  rep(i,N){
    if(i)cout<<" ";
    cout<<a[i];
  }
  cout<<endl;
}
//taylorshift
void verify4(){
  int N,c;cin>>N>>c;
  vector<mint> a(N);
  rep(i,N)cin>>a[i];
  FPS fps;
  fps.taylor_shift(a,c);
  rep(i,N){
    if(i)cout<<" ";
    cout<<a[i];
  }
  cout<<endl;
}
void Main(){
verify4();
}