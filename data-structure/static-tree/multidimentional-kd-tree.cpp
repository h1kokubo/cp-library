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
        int axis;
        node(node *left,node *right,point p,int axis_):left(left),right(right),p(p),axis(axis_){}
    };

    int max_axis;
    function<bool(point,point)>comp=[&](const point &p1, const point &p2){return p1.x[max_axis]<p2.x[max_axis];};

    vector<point> p;
    node *root;

    kd_Tree(){
        p=vector<point>();
    }
    void add_point(vector<S> x,int index){
        p.push_back(point{x,index});
    }
    void construct(){root=construct(0,p.size());}
    node *construct(int l,int r){
        if(!(l<r))return nullptr;
        int mid=(l+r)/2;
        max_axis=-1;//射影分散を最大化する軸を探す。
        S max_var=-1;
        for(int i=0;i<d;++i){
            S mu=S(0);
            for(int j=0;j<p.size();++j){
                mu+=p[j].x[i];
            }
            mu/=p.size();
            S var=S(0);
            for(int j=0;j<p.size();++j){
                var+=(p[j].x[i]-mu)*(p[j].x[i]-mu);
            }
            var/=p.size();
            if(max_var<var){
                max_var=var;
                max_axis=i;
            }
        }

        sort(p.begin()+l,p.begin()+r,comp);
        return new node(construct(l,mid),construct(mid+1,r),p[mid],max_axis);
    }
    //入力はクエリ点、与えられた距離（距離公理を満たすもの）で最近傍点を返す。
    S find(node *nd,vector<S> x,S r){
        if(nd==nullptr)return r;
        point &p = nd->p;
        //ll d=(x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
        S nr=dist(x,p);
        if(r==-1||nr<r)r=nr;
        /*if(depth%2==1){
            if(nd->left!=nullptr&&x-r<=p.x){
                r=find(nd->left,x,y,depth+1,r);
            }
            else{
                r=find(nd->right,x,y,depth+1,r);
            }
        }
        else{
            if(nd->left!=nullptr && y-r<=p.y){
                r=find(nd->left,x,y,depth+1,r);
            }
            else{
                r=find(nd->right,x,y,depth+1,r);
            }
        }
        */
        if(nd->left!=nullptr&&x[nd->axis]-r<=p.x[nd->axis]){
            r=find(nd->left,x,r);
        }
        else if(nd->right!=nullptr&&x[nd->axis]+r>=p.x[nd->axis]){
            r=find(nd->right,x,r);
        }

        return r;
    }
    //クエリとして区間直積を与えた時それに含まれる点を列挙
    void find(node *nd,vector<int> &res,vector<pair<S,S>> &interval){
        point &p=nd->p;
        bool ok=true;
        for(int i=0;i<d;++i){
            if(p.x[i]<interval[i].first||interval[i].second<p.x[i])ok=false;
        }
        if(ok)res.push_back(p.id);
        if(nd->left!=nullptr&&interval[nd->axis].first<=p.x[nd->axis]){
            find(nd->left,res,interval);
        }
        if(nd->right!=nullptr&&p.x[nd->axis]<=interval[nd->axis].second){
            find(nd->right,res,interval);
        }
    }
    vector<int> enumerate(vector<pair<S,S>>&interval){
        vector<int> res;
        find(root,res,interval);
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