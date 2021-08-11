#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

class Two_CNF_SAT{

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
    void rdfs(int v,vector<vector<int>> &graph,int cnt,vector<int>&id){
        id[v]=cnt;
        for(int nv:graph[v]){
            if(id[nv]!=-1)continue;
            rdfs(nv,graph,cnt,id);
        }
    }
    vector<int> topological_sort(vector<vector<int>> &graph){
        const int N=graph.size();
        vector<int> state(N,0);
        vector<int> res; 
        for(int v=0;v<N;++v){
            if(state[v]>0)continue;
            dfs(v,graph,state,res);
        }
        reverse(res.begin(),res.end());
        return res;
    }

    vector<int> scc(vector<vector<int>> &graph){
        const int N=graph.size();
        vector<int> ord=topological_sort(graph);
        vector<vector<int>> graph_T(N);
        for(int v=0;v<N;++v){
            for(int nv:graph[v]){
                graph_T[nv].push_back(v);
            }
        }
        vector<int> id(N,-1);
        int cnt=0;
        for(int v:ord){
            if(id[v]!=-1)continue;
            rdfs(v,graph_T,cnt,id);
            ++cnt;

        }
        return id;
    }
    int sz;
    vector<vector<int>> graph;
    vector<bool> ans;
    public:
    Two_CNF_SAT(int size):sz(size){
        graph=vector<vector<int>>(2*sz);
        ans=vector<bool>(sz,false);
    }
    void add_closure(int i,bool type_i,int j,bool type_j){
        graph[i+type_i*sz].push_back(j+(!type_j)*sz);
        graph[j+type_j*sz].push_back(i+(!type_i)*sz);
    }
    pair<bool,vector<bool>> satisfy(){
        vector<int> id=scc(graph);
        for(int i=0;i<sz;++i){
            if(id[i]==id[i+sz])return make_pair(false,ans);
            if(id[i]>id[i+sz])ans[i]=true;
        }
        return make_pair(true,ans);
    }
};

void Main(){
    int N,D;cin>>N>>D;
    vector<int> X(N),Y(N);
    rep(i,N)cin>>X[i]>>Y[i];
    Two_CNF_SAT sat(N);
    rep(i,N){
        for(int j=i+1;j<N;++j){
            if(abs(X[i]-X[j])<D)sat.add_closure(i,false,j,false);
            if(abs(X[i]-Y[j])<D)sat.add_closure(i,false,j,true);
            if(abs(Y[i]-X[j])<D)sat.add_closure(i,true,j,false);
            if(abs(Y[i]-Y[j])<D)sat.add_closure(i,true,j,true);
        }
    }
    auto res=sat.satisfy();
    if(res.first){
        cout<<"Yes"<<endl;
        rep(i,N){
            if(res.second[i])cout<<X[i]<<endl;
            else cout<<Y[i]<<endl;
        }
    }
    else{
        cout<<"No"<<endl;
    }
}