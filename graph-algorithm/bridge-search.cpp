#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

namespace Bridge_Search{
    int dfs(int v,int pv,int d,vector<int> &dist,vector<pair<int,int>>&ans,vector<vector<int>>&graph){
        dist[v]=d;
        int nd=d;
        for(int nv:graph[v]){
            if(nv==pv)continue;
            if(dist[nv]!=-1){
                nd=min(nd,dist[nv]);
                continue;
            }
            nd=min(nd,dfs(nv,v,d+1,dist,ans,graph));
        }
        if(pv!=-1&&nd==d){
            ans.push_back(make_pair(pv,v));
        }
        return nd;
    }
}
vector<pair<int,int>> bridge_search(vector<vector<int>>&graph){
    const int N=graph.size();
    vector<int> dist(N,-1);
    vector<pair<int,int>> ans;
    for(int v=0;v<N;++v){
        if(dist[v]!=-1)continue;
        dfs(v,-1,0,dist,ans,graph);
    }
    return ans;
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

}