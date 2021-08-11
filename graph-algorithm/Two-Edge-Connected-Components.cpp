#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

struct LowLink{
    vector<bool> used;
    vector<int> ord,low;
    vector<int> articulation;
    vector<pair<int,int>> bridge;
    vector<vector<int>> graph;
    int dfs(int v,int pv,int d){
        used[v]=true;
        ord[v]=d++;
        low[v]=ord[v];
        bool is_articulation=false;
        int cnt=0,pvcnt=0;
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
        used.assign(graph.size(),false);
        ord.assign(graph.size(),0);
        low.assign(graph.size(),0);
        int d=0;
       
        for(int i=0;i<graph.size();++i){

            if(!used[i])d=dfs(i,-1,d);
        }
    }

};

struct TwoEdgeConnectedComponents{
    vector<int> comp;
    vector<vector<int>> comp_groups;
    vector<vector<int>> graph;
    LowLink LL;
    void dfs(int v,int pv,int &num){
        if(pv!=-1&&LL.ord[pv]>=LL.low[v]){//{pv,v}が橋でなければvはpvと同じ成分
            comp[v]=comp[pv];
            comp_groups[comp[v]].push_back(v);
        }
        else{
            comp[v]=num++;
            comp_groups.push_back(vector<int>());
            comp_groups[comp[v]].push_back(v);
        }
        for(int nv:graph[v]){
            if(comp[nv]==-1)dfs(nv,v,num);
        }
    }
    TwoEdgeConnectedComponents(const vector<vector<int>> &graph_):graph(graph_){
       
        LL=LowLink(graph);
        comp.assign(graph.size(),-1);
        int num=0;//二重辺連結成分の数
        for(int i=0;i<comp.size();++i){
            if(comp[i]==-1)dfs(i,-1,num);
        }

    }

};
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
int N,M;cin>>N>>M;
vector<vector<int>> graph(N);
int a,b;
rep(i,M){
    cin>>a>>b;
graph[a].push_back(b);
graph[b].push_back(a);
}
TwoEdgeConnectedComponents tecc(graph);
vector<vector<int>> comp=tecc.comp_groups;
cout<<comp.size()<<endl;
rep(i,comp.size()){
    cout<<comp[i].size();
    rep(j,comp[i].size()){
        cout<<" ";
        cout<<comp[i][j];
    }
    cout<<endl;
}
}