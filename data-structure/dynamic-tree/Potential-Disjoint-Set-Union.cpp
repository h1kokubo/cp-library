#include <bits/stdc++.h>
using namespace std;

template<class Abel,Abel (*add)(Abel,Abel),Abel (*sub)(Abel,Abel),Abel (*e)()> struct Potential_dsu {//
    vector<int> par;
    vector<int> rank;
    vector<Abel> potential_;

    Potential_dsu(int n) {
        init(n);
    }

    void init(int n) {
        par.resize(n); rank.resize(n); potential_.resize(n);
        for (int i = 0; i < n; ++i) par[i] = i, rank[i] = 0, potential_[i] = e();
    }

    int root(int x) {
        if (par[x] == x) {
            return x;
        }
        else {
            int r = root(par[x]);
            potential_[x] =add(potential_[x],potential_[par[x]]);
            return par[x] = r;
        }
    }

    Abel potential(int x) {//根を基準としたポテンシャル
        root(x);
        return potential_[x];
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y, Abel p) {//potential(y)-potential(x)=pとなるようにマージ
        p = add(p,potential(x)); p =sub(p,potential(y));
        x = root(x); y = root(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y), p = sub(e(),p);
        if (rank[x] == rank[y]) ++rank[x];
        par[y] = x;
        potential_[y] = p;
        return true;
    }

    Abel diff(int x, int y) {//xを基準としたときのyのポテンシャル、同じ連結集合でないと未定義
        return sub(potential(y),potential(x));
    }
};

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
const int INF=1e9+1e5;

int add(int n1,int n2){return n1+n2;}
int sub(int n1,int n2){return n1-n2;}
int e(){return 0;}
void Main();

int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
//verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B
int n,q;cin>>n>>q;
Potential_dsu<int,add,sub,e> pdsu(n);
vector<int> ans;
rep(i,q){
    int c;cin>>c;
    if(c==0){
        int x,y,z;
        cin>>x>>y>>z;
        pdsu.unite(x,y,z);
    }
    else{
        int x,y;
        cin>>x>>y;
        if(pdsu.same(x,y)){
            ans.push_back(pdsu.diff(x,y));
        }
        else{
            ans.push_back(INF);
        }
    }
}
rep(i,ans.size()){
    if(ans[i]==INF)cout<<"?"<<endl;
    else cout<<ans[i]<<endl;
}

}