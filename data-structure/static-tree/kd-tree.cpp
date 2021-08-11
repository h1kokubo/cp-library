#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
const int INF=1e9+1e5;

struct kd_Tree{
    struct point{
        long long x,y;int i;
    };
    struct node{
        node *left,*right;
        point p;
        node(node *left,node *right,point p):left(left),right(right),p(p){}
    };
    static bool comp_x(const point &p1, const point &p2){return p1.x<p2.x;}
    static bool comp_y(const point &p1, const point &p2){return p1.y<p2.y;}

    vector<point> p;
    node *root;

    kd_Tree(){
        p=vector<point>();
    }
    void add_point(long long x,long long y,int index){
        p.push_back(point{x,y,index});
    }
    void construct(){root=construct(0,p.size(),0);}
    node *construct(int l,int r,int depth){
        if(!(l<r))return nullptr;
        int mid=(l+r)/2;
        if(depth%2==1){
            sort(p.begin()+l,p.begin()+r,comp_x);
        }
        else{
            sort(p.begin()+l,p.begin()+r,comp_y);
        }
        return new node(construct(l,mid,depth+1),construct(mid+1,r,depth+1),p[mid]);
    }

    long long find(node *nd,long long x,long long y,int depth,long long r){
        if(nd==nullptr)return r;
        point &p = nd->p;
        ll d=(x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
        if(r==-1||d<r)r=d;
        if(depth%2==1){
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
        return r;
    }
    //[sx,tx]×[sy,ty]
    void find(node *nd,vector<int> &res,long long sx,long long tx,long long sy,long long ty,int depth){
        point &p=nd->p;
        if(sx<=p.x&&p.x<=tx&&sy<=p.y&&p.y<=ty)res.push_back(p.i);
        if(depth%2==1){
            if(nd->left!=nullptr&&sx<=p.x){
                find(nd->left,res,sx,tx,sy,ty,depth+1);
            }
            if(nd->right!=nullptr&&p.x<=tx){
                find(nd->right,res,sx,tx,sy,ty,depth+1);
            }

        }
        else{
            if(nd->left!=nullptr&&sy<=p.y){
                find(nd->left,res,sx,tx,sy,ty,depth+1);
            }
            if(nd->right!=nullptr&&p.y<=ty){
                find(nd->right,res,sx,tx,sy,ty,depth+1);
            }
        }

    }
    vector<int> enumerate(long long sx,long long tx,long long sy,long long ty){
        vector<int> res;
        find(root,res,sx,tx,sy,ty,0);
        return res;
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_C
void Main(){
kd_Tree kd;
int n;cin>>n;
rep(i,n){
    int x,y;
    cin>>x>>y;
    kd.add_point(x,y,i);
}
kd.construct();
int q;cin>>q;

vector<vector<int>> ans(q);
rep(i,q){
    int sx,tx,sy,ty;cin>>sx>>tx>>sy>>ty;
    vector<int> res=kd.enumerate(sx,tx,sy,ty);
    sort(all(res));
    ans[i]=res;
}
rep(i,q){
    rep(j,ans[i].size())cout<<ans[i][j]<<endl;
    cout<<endl;
}
}