#include <bits/stdc++.h>
using namespace std;

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

template<typename T>
pair<bool,vector<T>>SLE_solver(vector<vector<T>> A,vector<T> b){
    /*
    行列方程式Ax=bを解く。Tに順序があることは仮定しないため、ピボット選択は行わない。
    Aが正則ならば {true,解ベクトル} 特異ならば {false,空ベクトル} を返す。
    */
    
    assert(A[0].size()==b.size());
    int n=A.size(),m=b.size();//A: n×m
    for(int i=0;i<n;++i){
        if(A[i][i]==T(0)){
            //0の場合はi列目が非零の行を探す
            int p=-1;
            for(int j=i+1;j<n;++j){
                if(A[j][i]!=T(0)){
                    p=j;
                    break;
                }
            }
            //pが-1のままであれば特異
            if(p==-1){
                return make_pair(false,vector<T>());
            }
            //そうでなければi行目とp行目を交換
            for(int j=i;j<m;++j){
                swap(A[i][j],A[p][j]);
            }
            swap(b[i],b[p]);
        }
        //ピボットが1になるように行を変換
        T pivinv=T(1)/A[i][i];
        for(int j=i;j<m;++j){
            A[i][j]*=pivinv;
        }
        b[i]*=pivinv;
        //i列目のi+1行目以降が0になるように変換
        for(int k=i+1;k<n;++k){
            //A[k][i]は最後に0に
            for(int j=i+1;j<m;++j){
                A[k][j]-=A[k][i]*A[i][j];
            }
            b[k]-=A[k][i]*b[i];
            A[k][i]=T(0);
        }

    }
    //後退代入(Aは残さないので変えなくてよい)
    for(int i=n-1;i>0;--i){
        assert(A[i][i]==T(1));
        for(int j=i-1;j>=0;--j){
            b[j]-=A[j][i]*b[i];
        }
    }
    return make_pair(true,b);
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 

void Main(){
    vector<frac> res=SLE_solver(vector<vector<frac>>{{frac(2),frac(-1),frac(0)},{frac(1),frac(1),frac(1)},{frac(0),frac(-2),frac(-1)}},vector<frac>{frac(1),frac(-2),frac(3)}).second;
    print(res);

}