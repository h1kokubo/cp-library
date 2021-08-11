#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

//fraction begin
template<class T>
struct Fraction{
    using f=Fraction;
    T a,b; // a/b
    Fraction(T x){a=x;b=T(1);}
    void reduce(){
        T g=gcd(a,b);
        a/=g;
        b/=g;
        if(b<0){
            a=-a;
            b=-b;
        }
        }//約分 符号は分子につける
    f& operator+=(const f&rhs){
        T a_=a*rhs.b+b*rhs.a,b_=b*rhs.b;
        a=a_,b=b_;
        reduce();
        return *this;
    }
    f& operator-=(const f&rhs){
        *this+=-rhs;
        reduce();
        return *this;
    }
    f& operator*=(const f&rhs){
        a*=rhs.a;
        b*=rhs.b;
        reduce();
        return *this;
    }
    f& operator/=(const f&rhs){
        assert(rhs!=0);
        a*=rhs.b;
        b*=rhs.a;
        reduce();
        return *this;
    }
    f inv(){
        assert(*this!=f(0));
        return f(1)/(*this);
    }
    f operator+()const{
        return *this;
    }
    f operator-()const{
        f res(*this);
        res.a=-res.a;
        return res;
    }
    friend f operator+(const f&lhs ,const f&rhs){
        return f(lhs)+=rhs;
    }
    friend f operator-(const f&lhs ,const f&rhs){
        return f(lhs)-=rhs;
    }
    friend f operator*(const f&lhs,const f&rhs){
        return f(lhs)*=rhs;
    }
    friend f operator/(const f&lhs,const f&rhs){
        return f(lhs)/=rhs;
    }
    friend bool operator==(const f&lhs,const f&rhs){
        return lhs.a==rhs.a&&lhs.b==rhs.b;
    }
    friend bool operator!=(const f&lhs,const f&rhs){
        return lhs.a!=rhs.a||lhs.b!=rhs.b;
    }
    friend ostream &operator<<(ostream &os,const f& p){
        return os<<p.a<<"/"<<p.b;
    }

};
using frac=Fraction<int>;
//fraction end

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

template<class T>
struct Matrix_Reduction{
    vector<vector<T>> A;
    vector<T> b;
    vector<pair<int,int>> pivlst;
    static constexpr void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 
    
    Matrix_Reduction(vector<vector<T>> A_,vector<T> b_):A(A_),b(b_){
        //pivot の候補を巡回しながら簡約化
        int n=A.size(),m=A[0].size();//A :n×m行列
        
        assert(n==b.size());
        int i=0,j=0;
        while(i<n&&j<m){
            //i行目のpivotを見つける
            while(j<m){
                if(A[i][j]==T(0)){
                    //A[p][j]!=T(0)なる点を探す
                    int p=-1;
                    for(int k=i+1;k<n;++k){
                        if(A[k][j]!=T(0)){
                            p=k;
                            break;
                        }
                    }
                    if(p==-1){//p==-1のままならば、その列にpivotはないのでjをインクリメント
                        ++j;
                        continue;
                    }
                    //i行目とp行目を入れ替える
                    for(int k=j;k<m;++k){
                        swap(A[i][k],A[p][k]);
                    }
                    swap(b[i],b[p]);
                }
                //ここに到達したとき、A[i][j]は非零でピボット
                //A[i][j]=1となるように i行目を変換
                T pivinv=T(1)/A[i][j];
                for(int k=j+1;k<m;++k){
                    A[i][k]*=pivinv;
                }
                b[i]*=pivinv;
                A[i][j]=T(1);
                //j列目のi行目以外が零になるように変換
                for(int k=0;k<n;++k){
                    if(k==i)continue;
                    for(int l=j+1;l<m;++l){
                        A[k][l]-=A[k][j]*A[i][l];
                    }
                    b[k]-=A[k][j]*b[i];
                    A[k][j]=T(0);
                }
                pivlst.push_back(make_pair(i,j));
                ++i;++j;
                break;
            }
        }

    }
    void print_A(){
        for(int i=0;i<A.size();++i)print(A[i]);
    }
    void print_b(){
        print(b);
    }
    vector<vector<T>> col_base(vector<vector<T>> &A_org){
        
        vector<vector<T>> ans; 
        for(auto &piv:pivlst){
            ans.push_back(vector<T>());
            for(int i=0;i<A.size();++i){
                ans.back().emplace_back(A_org[i][piv.second]);
            }
        }
        return ans;
    }
    vector<vector<T>> row_base(){
        //行空間は簡約化しても変化しないのであった(線型同型写像を行ったことに相当)
        vector<vector<T>> ans;
        for(auto &piv:pivlst){
            ans.push_back(A[piv.first]);
        }
        return ans;
    }
    int rank(){return pivlst.size();}
    bool ans_exist(){
        //pivotの数以降の簡約化後のbの要素が全て零であることが解を持つ必要十分条件
        bool judge=true;
        for(int i=pivlst.size();i<A.size();++i)judge&=b[i]==T(0);
        return judge;
    }
    vector<vector<T>> ker_base(){
        //線型方程式が解を持たない時、解空間は空であり、線型空間ですらない。
        assert(ans_exist());
        vector<vector<T>> ans;
        //pivotは行について密で整列済みになるように簡約化したので、pivotの隙間と前後に対応する要素を1にしたそれぞれの場合で、pivotに対応する要素で相殺すればよい。
        //pivotがないような場合は例外的に扱う
        if(pivlst.size()==0){
            //全ての行列要素が0であるから基底は自明なものを選べばよい
            for(int i=0;i<A[0].size();++i){
                ans.push_back(vector<T>(A[0].size(),T(0)));
                ans.back()[i]=T(1);
            }
        }
        else{
            //pivotの前
            for(int i=0;i<pivlst[0].second;++i){
                ans.push_back(vector<T>(A[0].size(),T(0)));
                ans.back()[i]=T(1);
                //Aのi列目を相殺するように pivに対応する要素を求める。
                for(auto &piv:pivlst){
                    ans.back()[piv.second]=-A[piv.first][i];
                }
            }
            //pivotの隙間
            for(int k=0;k<pivlst.size()-1;++k){
                for(int i=pivlst[k].second+1;i<pivlst[k+1].second;++i){
                    ans.push_back(vector<T>(A[0].size(),T(0)));
                    ans.back()[i]=T(1);
                    //Aのi列目を相殺するように pivに対応する要素を求める。
                    for(auto &piv:pivlst){
                        ans.back()[piv.second]=-A[piv.first][i];
                    }
                }
            }
            //pivotの後ろ
            for(int i=pivlst.back().second+1;i<A[0].size();++i){
                ans.push_back(vector<T>(A[0].size(),T(0)));
                    ans.back()[i]=T(1);
                    //Aのi列目を相殺するように pivに対応する要素を求める。
                    for(auto &piv:pivlst){
                        ans.back()[piv.second]=-A[piv.first][i];
                    }
            }
        }
        return ans;
    }
    vector<T> solve(){//Ax=bの解の一つを得る。
        assert(ans_exist());
        //pivの列に対するindex以外は全て0にし、pivの行に対応するbの要素を対応するように決定する
        vector<T> ans(A[0].size(),T(0));
        for(auto &piv:pivlst){
            ans[piv.second]=b[piv.first];
        }
        return ans;
    }
};



void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 
/*
void Main(){
    vector<vector<frac>> A={
        {frac(2),frac(-1),frac(0)},
        {frac(1),frac(1),frac(1)},
        {frac(0),frac(-2),frac(-1)}
    };
    vector<frac> b={frac(1),frac(-2),frac(3)};
    Matrix_Reduction<frac> mr(A,b);
    mr.print_A();
    mr.print_b();
    auto col_base_lst=mr.col_base(A);
    for(auto &base:col_base_lst){
        print(base);
    }
    auto row_base_lst=mr.row_base();
    for(auto &base:row_base_lst){
        print(base);
    }
    
}
*/
/*
void Main(){
    vector<vector<frac>> A={
        {frac(2),frac(-1),frac(0),frac(7)},
        {frac(1),frac(1),frac(1),frac(3)},
        {frac(0),frac(-2),frac(-1),frac(4)}
    };
    vector<frac> b={frac(1),frac(-2),frac(3),frac(0)};
    Matrix_Reduction<frac> mr(A,b);
    cout<<"A:"<<endl;
    mr.print_A();
    cout<<"b:"<<endl;
    mr.print_b();
    cout<<"col_base:"<<endl;
    auto col_base_lst=mr.col_base(A);
    for(auto &base:col_base_lst){
        print(base);
    }
    cout<<"row_base:"<<endl;
    auto row_base_lst=mr.row_base();
    for(auto &base:row_base_lst){
        print(base);
    }
    cout<<"ker_base:"<<endl;
    auto ker_base_lst=mr.ker_base();
    for(auto &base:ker_base_lst){
        print(base);
    }
    cout<<"ans:"<<endl;
    auto ans=mr.solve();
    print(ans);
}
*/
//verify Library-Checker System of Linear Equations 
void Main(){
int N,M;
cin>>N>>M;
vector<vector<mint>> A(N,vector<mint>(M));
rep(i,N)rep(j,M)cin>>A[i][j];
vector<mint> b(N);rep(i,N)cin>>b[i];
Matrix_Reduction<mint> mr(A,b);
if(!mr.ans_exist()){
    cout<<-1<<endl;
}
else{
    auto ker_base_lst=mr.ker_base();
    cout<<ker_base_lst.size()<<endl;
    auto ans=mr.solve();
    rep(i,M){
        if(i)cout<<" ";
        cout<<ans[i];
    }
    cout<<endl;
    for(auto &base:ker_base_lst){
        rep(i,M){
            if(i)cout<<" ";
            cout<<base[i];
        }
        cout<<endl;
    }
}
}
