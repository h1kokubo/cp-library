#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

void erase_parallel_edges(vector<vector<int>>& graph){
    const int N=graph.size();
    vector<bool> check(N);
    for(vector<int>& v:graph){
        for(int i=0;i<v.size();){
            if(check[v[i]]){
                swap(v[i],v.back());
                v.pop_back();
            }
            else{
                check[v[i]]=true;
                ++i;
            }
        }
        for(int i: v)check[i]=false;
    }
    
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

}