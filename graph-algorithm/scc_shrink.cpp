#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

namespace scc{
    namespace topo{
    void dfs(int v,vector<vector<int>> &graph,vector<int> &state,vector<int> &res){
        state[v]=1;
        for(int nv:graph[v]){
            if(state[nv]>0){
                continue;
            }
            dfs(nv,graph,state,res);
        }
        state[v]=2;
        res.push_back(v);
    }
    }
    vector<int> topological_sort(vector<vector<int>> &graph){
        int N=graph.size();
        vector<int> state(N);
        vector<int> res;
        for(int v=0;v<N;++v){
            if(state[v]>0)continue;
            topo::dfs(v,graph,state,res);
        }
        reverse(res.begin(),res.end());
        return res;
    }
    void dfs(int v,vector<vector<int>> &graph_T,vector<int> &component,vector<bool> &check){
        check[v]=true;
        component.push_back(v);
        for(int nv:graph_T[v]){
            if(check[nv])continue;
            dfs(nv,graph_T,component,check);
        }
    }
}
vector<vector<int>> scc_graph(vector<vector<int>> &graph){
    vector<int> topord=scc::topological_sort(graph);
    int N=graph.size();
    vector<vector<int>> graph_T(N);
    for(int v=0;v<N;++v){
        for(int nv:graph[v]){
            graph_T[nv].push_back(v);
        }
    }
    vector<vector<int>> res;
    vector<bool> check(N,false);
    for(int v:topord){
        if(check[v])continue;
        vector<int> component;
        scc::dfs(v,graph_T,component,check);
        res.push_back(component);
    }
    return res;
}

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

pair<vector<int>,vector<vector<int>>> scc_shrink(vector<vector<int>> &scc_comp,vector<vector<int>> &graph){
    int N=graph.size();
    vector<int> table(N);
    for(int i=0;i<scc_comp.size();++i){
        for(int &v:scc_comp[i]){
            table[v]=i;
        }
    }
    vector<vector<int>> scc_graph(scc_comp.size())
    for(int v=0;v<N;++v){
        for(int nv:graph[v]){
        if(table[v]!=table[nv])scc_graph[table[v]].push_back(table[nv]);
        }
    }
    //uniqueにする
    erase_parallel_edges(scc_graph);
    return make_pair(table,scc_graph);
}
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//verify ALPC G
void Main(){
    int N,M;cin>>N>>M;
    vector<vector<int>> g(N);
    rep(i,M){
        int a,b;cin>>a>>b;
        g[a].push_back(b);
    }
    vector<vector<int>> res=scc_graph(g);
    cout<<res.size()<<endl;
    for(vector<int> &g:res){
        cout<<g.size()<<" ";
        rep(i,g.size()){
            if(i)cout<<" ";
            cout<<g[i];
        }
        cout<<endl;
    }
}