#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

struct LCA{

    vector<vector<int>> par;
    vector<int> depth;
    int sz,bsz;
    LCA(vector<vector<int>> &tree,int r){
        sz=tree.size();
        depth.resize(sz);
        bsz=0;
        while((1<<bsz)<sz)++bsz;
        par.resize(bsz,vector<int>(sz+1));
        dfs(r,sz,0,tree);
        par[0][sz]=sz;
        for(int k=1;k<bsz;++k){
            for(int i=0;i<=sz;++i)par[k][i]=par[k-1][par[k-1][i]];
        }

    }
    int get_LCA(int u,int v){
        if(depth[u]<depth[v]){
            int rem=depth[v]-depth[u];
            for(int k=bsz-1;k>=0;--k){
                if(rem>=1<<k){
                    rem-=1<<k;
                    v=par[k][v];
                }
            }
            
        }
        else if(depth[u]>depth[v]){
            int rem=depth[u]-depth[v];
            for(int k=bsz-1;k>=0;--k){
                if(rem>=1<<k){
                    rem-=1<<k;
                    u=par[k][u];
                }
            }
            
        }
        assert(depth[u]==depth[v]);//u,vが非連結等木でない時にassert failedになるはず。
        if(u==v)return u;
        for(int k=bsz-1;k>=0;--k){
            if(par[k][u]!=par[k][v]){
                u=par[k][u];
                v=par[k][v];
            }
        }
        assert(par[0][u]==par[0][v]&&u!=v);
        return par[0][u];
    }
    void dfs(int v,int pv,int dep,vector<vector<int>>&tree){
        par[0][v]=pv;
        depth[v]=dep;
        for(int nv:tree[v]){
            if(nv==pv)continue;
            dfs(nv,v,dep+1,tree);
        }
    }
    int dist(int u,int v){
      return depth[u]+depth[v]-2*depth[get_LCA(u,v)];
    }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

int N,Q;cin>>N>>Q;
vector<vector<int>> tree(N);
int p;
rep(i,N-1){
    cin>>p;
    tree[p].push_back(i+1);
    tree[i+1].push_back(p);
}
LCA lca(tree,0);
vector<int> ans(Q);
int u,v;
rep(i,Q){
cin>>u>>v;
ans[i]=lca.get_LCA(u,v);
}
rep(i,Q)cout<<ans[i]<<endl;

}