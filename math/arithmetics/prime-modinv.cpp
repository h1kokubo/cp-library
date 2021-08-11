#include <bits/stdc++.h>
using namespace std;
constexpr long long safe_div(long long x,long long m){if (x<0)return (x+1)/m-1;else return x/m;}
long long safe_mod(long long x,long long m){x%=m;if(x<0){x+=m;}return x;}
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
    return safe_mod(Prime_modinv::extend_euclid(a,n)[1],n);
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
const long long mod=988244353; 
void Main(){
  cout<<353*prime_modinv(353,mod)%mod<<endl;   
}