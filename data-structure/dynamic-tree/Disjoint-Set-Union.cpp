#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}

class Disjoint_Set_Union{
    struct node{
        int leader;
        int rank;
        node(int x){leader=x;rank=0;}
    };
    vector<node*> nodelist;
    public:
    int size;
    int gnum;
        Disjoint_Set_Union(int size_){
            gnum=size=size_;
            nodelist=vector<node*>(size);
            for(int i=0;i<size;++i)nodelist[i]=new node(i);
        }
        int leader(int x){
            node* nx=nodelist[x];
            if(nx->leader!=x)nx->leader=leader(nx->leader);
            return nx->leader;
        }
        bool same(int x,int y){
            return leader(x)==leader(y);
        }
        void unite(int x,int y){
            if(same(x,y))return;
            --gnum;
            node *nx=nodelist[leader(x)],*ny=nodelist[leader(y)];
            if(nx->rank>ny->rank){
                ny->leader=leader(x);
            }
            else if(nx->rank<ny->rank){
                nx->leader=leader(y);
            }
            else{
                ny->leader=leader(x);
                ++nx->rank;
            }
            
        }
        vector<vector<int>> groups(){
            vector<vector<int>> temp(size,vector<int>()),res;
            for(int i=0;i<size;++i)temp[leader(i)].push_back(i);
            for(int i=0;i<size;++i)if(temp[i].size()>0)res.push_back(temp[i]);
            return res;
        }

};
using Dsu = Disjoint_Set_Union;
void Main();

int main(){cout<<fixed<<setprecision(15);Main();}

/*
//verify ABC177D
void Main(){
    int N,M;
    cin>>N>>M;
    Disjoint_Set_Union dsu(N);
    rep(i,M){
        int A,B;
        cin>>A>>B;
        A--;B--;
        dsu.unite(A,B); 
    }
    auto res=dsu.groups();
    int ans=0;
    rep(i,res.size())chmax(ans,(int)res[i].size());
    cout<<ans<<endl;
}
*/
/*
//verify ALPC A
void Main(){
    int N,Q;
    cin>>N>>Q;
    Disjoint_Set_Union dsu(N);
    vector<int> ans;
    rep(i,Q){
        int t;
        cin>>t;
        if(t==0){
            int u,v;
            cin>>u>>v;
            dsu.unite(u,v);
        }
        else{
            int u,v;
            cin>>u>>v;
            ans.push_back(dsu.same(u,v));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify ACLBC C
void Main(){
    int N,M;
    cin>>N>>M;
    Disjoint_Set_Union dsu(N);
    rep(i,M){
        int A,B;
        cin>>A>>B;
        A--;B--;
        dsu.unite(A,B);
    }
    cout<<dsu.gnum-1<<endl;
}
*/
/*
//verify Library-Checker Unionfind
void Main(){
    int N,Q;
    cin>>N>>Q;
    Disjoint_Set_Union dsu(N);
    int t;int u,v;
    vector<int> ans;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>u>>v;
            dsu.unite(u,v);
        }else{
            cin>>u>>v;
            ans.push_back(dsu.same(u,v));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;

}
*/
//verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1
void Main(){
    int n,q;cin>>n>>q;
    Disjoint_Set_Union dsu(n);
    vector<int> ans;
    rep(i,q){
        int c,x,y;cin>>c>>x>>y;
        if(c==0)dsu.unite(x,y);
        else ans.push_back(dsu.same(x,y));
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}