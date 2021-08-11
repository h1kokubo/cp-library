#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Fraction{
    using f=Fraction;
    T a,b; // a/b
    static constexpr T safe_mod(T x,T m){T res=x%m;if(res<0)res+=m;return res;}
    static constexpr T euclid_gcd_inner(T a,T b){
        if(b==0)return a;
        else return euclid_gcd_inner(b,a%b);
    }
    static constexpr T euclid_gcd(T a,T b){
        if(abs(a)<abs(b)){
            if(a<0)return euclid_gcd_inner(-b,-a);
            else return euclid_gcd_inner(b,a);
        }
        else{
            if(b<0)return euclid_gcd_inner(-a,-b);
            else return euclid_gcd_inner(a,b);
        }
    }
    Fraction(){a=T(0);b=T(1);}
    Fraction(T x){a=x;b=T(1);}
    Fraction(T a_,T b_):a(a_),b(b_){}
    void reduce(){
        T g=euclid_gcd(a,b);
        a/=g;
        b/=g;
        if(b<0){
            a=-a;
            b=-b;
        }
        }//約分 符号は分子につける
    f& operator=(const f&rhs){
        a=rhs.a;b=rhs.b;
        return *this;
    }
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
        assert(rhs.a!=0);
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
    
    friend istream &operator>>(istream &is,f&a) {
    string s;
    is >> s;
    int i=0;
    for(;i<s.size();++i){
        if(s[i]=='/')break;
    }
    try{
    a.a=stoi(s.substr(0,i));
    a.b=stoi(s.substr(i+1));
    }
    catch(const invalid_argument& e){
    cout << "invalid argument" << endl;
    }
    catch(const out_of_range& e){
    cout << "Out of range" <<endl;
    }
    return (is);
    }
    friend ostream &operator<<(ostream &os,const f& p){
        return os<<p.a<<"/"<<p.b;
    }

};
using frac=Fraction<int>;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


void Main(){
    
    cout<<+(-frac(6)/frac(9)*frac(12)).inv()+frac(7)/frac(3)<<endl;
    cout<<frac(3).inv()<<endl;
    frac a(3),b(2);
    a-=b;
    cout<<(a<b)<<endl;
}