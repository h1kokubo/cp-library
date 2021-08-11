#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

namespace Articulation{
    int dfs(int v,int pv,int d,vector<int>&ans,vector<int> &dist,vector<vector<int>> &graph){
        int cnt1=0,cnt2=0,nd=d;
        dist[v]=d;
        for(int nv:graph[v]){
            if(nv==pv)continue;
            if(dist[nv]!=-1){
                nd=min(nd,dist[nv]);
                continue;
            }
            int res=dfs(nv,v,d+1,ans,dist,graph);
            nd=min(nd,res);
            if(res==d+1){
                ++cnt2;
            }
            ++cnt1;
        }
        if(d==0){
            if(cnt1>=2)ans.push_back(v);
        }
        else if(cnt2>0)ans.push_back(v);
        return nd;
    }
}

vector<int> articulation_point(vector<vector<int>> &graph){
    const int N=graph.size();
    vector<int> dist(N,-1);
    vector<int> ans;
    for(int v=0;v<N;++v){
        if(dist[v]!=-1)continue;
        Articulation::dfs(v,-1,0,ans,dist,graph);
    }
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

}