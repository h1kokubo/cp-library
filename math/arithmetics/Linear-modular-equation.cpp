#include <bits/stdc++.h>
using namespace std;
constexpr long long safe_div(long long x,long long m){if (x<0)return (x+1)/m-1;else return x/m;}
long long safe_mod(long long x,long long m){x%=m;if(x<0){x+=m;}return x;}
namespace Lme{
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
}
vector<long long> lme(long long a,long long b,long long n){
    vector<long long> v=Lme::extend_euclid(a,n);
    long long g=v[0],x_=v[1],y_=v[2];
    vector<long long> ans;
    if(b%g==0){
        long long width=n/g,x=safe_mod(x_*(b/g),width);
        for(long long i=0;i<g;++i){
            ans.push_back(x+i*width);
        }
    }
    return ans;
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
 auto res=lme(35,10,50);
 for(auto x : res){
     cout<<x<<endl;
 } 
}