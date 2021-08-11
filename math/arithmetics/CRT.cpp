#include <bits/stdc++.h>
using namespace std;

//begin
constexpr long long safe_div(long long x,const long long m){if (x<0)return (x+1)/m-1;else return x/m;}
constexpr long long safe_mod(long long x,const long long m){x%=m;if(x<0){x+=m;}return x;}
namespace CRT{
namespace Prime_modinv{
namespace Extend_euclid{
    vector<long long> inner(const long long a,const long long b){
        //b>=0 and abs(a)>=abs(b)
        //b==0
        if(b==0){
            if(a<0){
                return vector<long long>{-a,-1,0};
            }
            else{
                return vector<long long>{a,1,0};
            }
        }
        long long s=a,t=b,sx=1,sy=0,tx=0,ty=1;
        while(t!=0){
            long long temp=safe_div(s,t),u=s-temp*t,ux=sx-temp*tx,uy=sy-temp*ty;
            s=t,t=u,sx=tx,tx=ux,sy=ty,ty=uy;
        }
        return vector<long long>{s,sx,sy};
    }
}

vector<long long> extend_euclid(const long long a,const long long b){
    if(abs(b)>abs(a)){
        if(a<0){
            vector<long long> v=Extend_euclid::inner(-b,-a);
            return vector<long long>{v[0],-v[2],-v[1]};
        }
        else{
            
            vector<long long> v=Extend_euclid::inner(b,a);
            return vector<long long>{v[0],v[2],v[1]};
        }
    }
    else{
        if(b<0){
            vector<long long> v=Extend_euclid::inner(-a,-b);
            return vector<long long>{v[0],-v[1],-v[2]};
        }
        else{
            vector<long long> v=Extend_euclid::inner(a,b);
            return vector<long long>{v[0],v[1],v[2]};
        }
        
    }
} 
}
long long prime_modinv(const long long a,const long long n){
    auto res=Prime_modinv::extend_euclid(a,n);
    //assert(res[0]==1);
    return safe_mod(res[1],n);
}
}
// x=r[i](mod m[i])なるxを返す。 mが全て互いに素であることを想定
// overflowを防ぐために int128を用いる。
long long crt(const vector<long long> r,const vector<long long> m){
    int n=r.size();
    __int128 m_prod=m[0];
    __int128 x=r[0]%m[0];
    for(int i=1;i<n;++i){
        __int128 t=(r[i]-x)*CRT::prime_modinv(m_prod,m[i]);
        x+=t*m_prod;
        m_prod*=m[i];
        x%=m_prod;
    }
    return (long long)x;
}
//end

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

#define endl "\n"
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()
const ll LINF=1e18+1e10;
const int INF=1e9+1e5;
#define Uniq(a) sort(all(a));a.erase(unique(all(a)),end(a))

template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}

//verify ACLC1 B
vector<long long> divisor(long long n){vector<long long> res;long long i = 1;while (i*i<=n){if(n%i==0){res.push_back(i);}i++;}if(res.size()==0)return res;for(long long i = res.size()-1-(res.back()*res.back()==n);i>=0;--i){res.push_back(n/res[i]);}return res;}

namespace Extend_euclid{
    vector<long long> inner(long long a,long long b){
        //b>=0 and abs(a)>=abs(b)
        //b==0
        if(b==0){
            if(a<0){
                return vector<long long>{-a,-1,0};
            }
            else{
                return vector<long long>{a,1,0};
            }
        }
        long long s=a,t=b,sx=1,sy=0,tx=0,ty=1;
        while(t!=0){
            long long temp=safe_div(s,t),u=s-temp*t,ux=sx-temp*tx,uy=sy-temp*ty;
            s=t,t=u,sx=tx,tx=ux,sy=ty,ty=uy;
        }
        return vector<long long>{s,sx,sy};
    }
}

vector<long long> extend_euclid(long long  a,long long b){
    if(abs(b)>abs(a)){
        if(a<0){
            vector<long long> v=Extend_euclid::inner(-b,-a);
            return vector<long long>{v[0],-v[2],-v[1]};
        }
        else{
            
            vector<long long> v=Extend_euclid::inner(b,a);
            return vector<long long>{v[0],v[2],v[1]};
        }
    }
    else{
        if(b<0){
            vector<long long> v=Extend_euclid::inner(-a,-b);
            return vector<long long>{v[0],-v[1],-v[2]};
        }
        else{
            vector<long long> v=Extend_euclid::inner(a,b);
            return vector<long long>{v[0],v[1],v[2]};
        }
        
    }
} 

void Main(){

ll N;
cin>>N;
auto d=divisor(2*N);
ll ans=2*N-1;
for(int i=0;i<d.size();++i){
    if(extend_euclid(d[i],2*N/d[i])[0]!=1)continue;
    ll k=crt(vector<ll>{0,2*N/d[i]-1},vector<ll>{d[i],2*N/d[i]});
    //cout<<k<<endl;
    //assert((k%d[i]==0)&&((k+1)%(2*N/d[i])==0));
    if(k)chmin(ans,k);
}
cout<<ans<<endl;
}
