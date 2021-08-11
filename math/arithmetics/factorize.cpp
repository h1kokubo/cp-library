#include <bits/stdc++.h>
using namespace std;
long long intpow(long long x,long long n){long long ans=1;while(n>0){if(n&1){ans*=x;}n>>=1;x*=x;}return ans;}
vector<pair<long long,long long>> factor_lst(long long n){
    vector<pair<long long,long long>> factor_lst;
    long long d=2;
    while(d*d<=n){
        if(n%d==0){
            long long num=0;
            while(n%d==0){
                num+=1;
                n/=d;
            }
            factor_lst.push_back({d,num});
        }
        d+=1;
    }
    if(n!=1){
        factor_lst.push_back({n,1});
    }
    return factor_lst;
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
 auto res=factor_lst(intpow(2,23)*7*17);
 for(auto p: res){
     cout<<p.first<<" "<<p.second<<endl;
 }   
}