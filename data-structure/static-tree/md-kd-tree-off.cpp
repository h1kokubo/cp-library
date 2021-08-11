#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
const int INF=1e9+1e5;

template<typename S,int d,S(*dist)(vector<S>&,vector<S>&)>
struct kd_Tree{
    struct point{
        vector<S> x;int id;
    };
    struct node{
        node *left,*right;
        point p;
        node(node *left,node *right,point p):left(left),right(right),p(p){}
    };

    int axis;
    function<bool(point,point)>comp=[&](const point &p1, const point &p2){return p1.x[axis]<p2.x[axis];};

    vector<point> p;
    node *root;

    kd_Tree(){
        p=vector<point>();
    }
    void add_point(vector<S> x,int index){
        p.push_back(point{x,index});
    }
    void construct(){root=construct(0,p.size(),0);}
    node *construct(int l,int r,int depth){
        if(!(l<r))return nullptr;
        int mid=(l+r)/2;
        axis=depth%d;
        sort(p.begin()+l,p.begin()+r,comp);
        return new node(construct(l,mid,depth+1),construct(mid+1,r,depth+1),p[mid]);
    }
    //入力はクエリ点、与えられた距離（距離公理を満たすもの）で最近傍点を返す。
    S find(node *nd,vector<S> &x,S r,int depth){
        if(nd==nullptr)return r;
        point &p = nd->p;
        S nr=dist(x,p);
        if(r==-1||nr<r)r=nr;
        axis=depth%d;
        if(nd->left!=nullptr&&x[axis]-r<=p.x[axis]){
            r=find(nd->left,x,r,depth+1);
        }
        else if(nd->right!=nullptr&&x[axis]+r>=p.x[axis]){
            r=find(nd->right,x,r,depth+1);
        }

        return r;
    }
    //クエリとして区間直積を与えた時それに含まれる点を列挙
    void find(node *nd,vector<int> &res,vector<pair<S,S>> &interval,int depth){
        point &p=nd->p;
        axis=depth%d;
     
        bool ok=true;
        for(int i=0;i<d;++i){
            if(p.x[i]<interval[i].first||interval[i].second<p.x[i])ok=false;
        }
        if(ok)res.push_back(p.id);
        if(nd->left!=nullptr&&interval[axis].first<=p.x[axis]){
            find(nd->left,res,interval,depth+1);
        }
        if(nd->right!=nullptr&&p.x[axis]<=interval[axis].second){
            find(nd->right,res,interval,depth+1);
        }
    }
    vector<int> enumerate(vector<pair<S,S>>&interval){
        vector<int> res;
        find(root,res,interval,0);
        return res;
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_C

ll dist(vector<ll>&x,vector<ll>&y){
    ll d=0;
    rep(i,2)d+=(x[i]-y[i])*(x[i]-y[i]);
    return d;
}

void Main(){
kd_Tree<ll,2,dist> kd;
int n;cin>>n;
rep(i,n){
    int x,y;
    cin>>x>>y;
    vector<ll> x_={x,y};
    kd.add_point(x_,i);
}
kd.construct();
int q;cin>>q;

vector<vector<int>> ans(q);
rep(i,q){
    int sx,tx,sy,ty;cin>>sx>>tx>>sy>>ty;
    vector<pair<ll,ll>> query={{sx,tx},{sy,ty}};
    vector<int> res=kd.enumerate(query);
    sort(all(res));
    ans[i]=res;
}
rep(i,q){
    rep(j,ans[i].size())cout<<ans[i][j]<<endl;
    cout<<endl;
}
}