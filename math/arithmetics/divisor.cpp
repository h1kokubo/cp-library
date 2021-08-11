#include <bits/stdc++.h>
using namespace std;

vector<long long> divisor(long long n){
    vector<long long> res;
    long long i = 1;
    while (i*i<=n){
        if(n%i==0){
            res.push_back(i);
        }
        i++;
    }
    if(res.size()==0)return res;
    for(long long i = res.size()-1-(res.back()*res.back()==n);i>=0;--i){
        res.push_back(n/res[i]);
    }

    return res;
}
//verify
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    vector<long long> v=divisor(16);
    for(long long x:v){
        cout<<x<<endl;
    }
}