#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

struct LowLink{
    vector<int> used,ord,low;
    vector<int> articulation;
    vector<pair<int,int>> bridge;
    vector<vector<int>> graph;
    int dfs(int v,int pv,int d){
        used[v]=true;
        ord[v]=d++;
        low[v]=ord[v];
        bool is_articulation=false;
        int cnt=0;
        for(int nv:graph[v]){
            if(!used[nv]){
                ++cnt;
                d=dfs(nv,v,d);
                low[v]=min(low[v],low[nv]);
                is_articulation|=pv!=-1&&low[nv]>=ord[v];
                if(ord[v]<low[nv])bridge.push_back(make_pair(v,nv));
            }
            else if(nv!=pv){
                low[v]=min(low[v],ord[nv]);
            }
        }
        is_articulation|=pv==-1&&cnt>1;
        if(is_articulation)articulation.push_back(v);
        return d;
    }

    LowLink(){}
    LowLink(const vector<vector<int>> &graph):graph(graph){
        used.assign(graph.size(),0);
        ord.assign(graph.size(),0);
        low.assign(graph.size(),0);
        int d=0;
        for(int i=0;i<graph.size();++i){
            if(!used[i])d=dfs(i,-1,d);
        }
    }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){



}