#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}
const ll LINF=1e18+1e10;
const int INF=1e9+1e5;
#define Uniq(a) sort(all(a));a.erase(unique(all(a)),end(a))

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

 
class Li_Chao_Tree{
    const ll INF=1e9+1e5;
    const ll LINF=1e18+1e10;
    long long safe_div(long long x,long long m){if (x<0)return (x+1)/m-1;else return x/m;}
    struct Line{
        ll a,b;
    };
    map<int,int> x2i;
    vector<Line*> data;
    vector<ll> X;
    int size,N;
    ll apply(Line *line,ll x){
        return line->a*x+line->b;
    }
    void add_line(Line *line,int k,int l,int r){
        int m=(l+r)/2;
        if(data[k]->a==INF){
            data[k]=line;
            return;
        }
        ll lx=X[l],mx=X[m],rx=X[r-1];
        bool left=apply(line,lx)<apply(data[k],lx),mid=apply(line,mx)<apply(data[k],mx),right=apply(line,rx)<apply(data[k],rx);

        if(left&&right){
            data[k]=line;
            return;
        }
        if(!left&&!right)return;
        if(mid){
            Line *temp=data[k];
            data[k]=line;
            line=temp;
        }
        if(left!=mid){
            add_line(line,2*k+1,l,m);
        }
        else{
            add_line(line,2*k+2,m,r);
        }
    }
    void add_segment(Line *line,int left,int right,int k,int l,int r){
        if(r<=left||right<=l)return;
        int m=(l+r)/2;
        if (!(left<=l&&r<=right)){
            add_segment(line,left,right,2*k+1,l,m);
            add_segment(line,left,right,2*k+2,m,r);
            return;
        }
        if(data[k]->a==INF){
            data[k]=line;
            return;
        }
        int lx=X[l],mx=X[m],rx=X[r-1];
        bool lb=apply(line,lx)<apply(data[k],lx),mb=apply(line,mx)<apply(data[k],mx),rb=apply(line,rx)<apply(data[k],rx);
        if(lb&&rb){
            data[k]=line;
            return;
        }
        if(!lb&&!rb)return;
        if(mb){
            Line* temp=data[k];
            data[k]=line;
            line=temp;
        }
        if(lb!=mb){
            add_segment(line,left,right,2*k+1,l,m);
        }
        else{
            add_segment(line,left,right,2*k+2,m,r);
        }
    }

    public:
    Li_Chao_Tree(vector<ll> dot_lst){//dot_lstはソート済みとする。
        size=dot_lst.size();
        rep(i,size)x2i[dot_lst[i]]=i;
        N=1;
        while(N<size)N<<=1;
        data=vector<Line*>(2*N-1,new Line{INF,LINF});
        X=dot_lst;
        while(X.size()<N)X.push_back(INF);
    }
    void add_line(ll a,ll b){ // add line ax+b (x in all)
        add_line(new Line{a,b},0,0,N);
    }
    void add_segment(ll a,ll b,ll lx,ll rx){// add line ax+b (lx<=x<rx)
        int pl=lower_bound(X.begin(),X.end(),lx)-X.begin(),pr=lower_bound(X.begin(),X.end(),rx)-X.begin();
        if(pl==pr)return;
        add_segment(new Line{a,b},pl,pr,0,0,N);
    }
    ll get_min(int x){
            int k=x2i[x];
            k+=N-1;
            ll s=LINF;
            while(k>=0){
                if(data[k]->a!=INF){
                    chmin(s,apply(data[k],x));
                }
                k=safe_div((k-1),2);
                
            }
            return s;
    }
    
};

/*
//verify Library-Checker Line Add Get Min
void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<pair<ll,ll>> ab(N);
    rep(i,N)cin>>ab[i].first>>ab[i].second;
    int t[Q];vector<ll> qx;
    int a_;ll b_;ll p; 
    rep(i,Q){
        cin>>t[i];
        if(t[i]==0){
            cin>>a_>>b_;
            ab.push_back({a_,b_});
        }
        else{
            cin>>p;
            qx.push_back(p);
        }
    }
    vector<ll> x;
    rep(i,qx.size())x.push_back(qx[i]);
    Uniq(x);
    
    Li_Chao_Tree lct(x);
    
    vector<ll> ans;
    rep(i,N){
        lct.add_line(ab[i].first,ab[i].second);
    }
    
    int cnt0=-1,cnt1=-1;
    rep(i,Q){
        if(t[i]==0){
            cnt0++;
            lct.add_line(ab[cnt0+N].first,ab[cnt0+N].second);
        }
        else{
            cnt1++;
            ans.push_back(lct.get_min(qx[cnt1]));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
//verify Segment Add Get Min
void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<ll> l(N),r(N),a(N),b(N);
    rep(i,N){
        cin>>l[i]>>r[i]>>a[i]>>b[i];
    }
    int t[Q];
    vector<ll> p;
    ll l_,r_,a_,b_,p_;
    rep(i,Q){
        cin>>t[i];
        if(t[i]==0){
            cin>>l_>>r_>>a_>>b_;
            l.push_back(l_);r.push_back(r_);a.push_back(a_);b.push_back(b_);
        }
        else{
            cin>>p_;
            p.push_back(p_);
        }
    }
    vector<ll> x;
    rep(i,p.size())x.push_back(p[i]);
    Uniq(x);
    Li_Chao_Tree lct(x);
    rep(i,N){
        lct.add_segment(a[i],b[i],l[i],r[i]);
    }
    int cnt0=-1,cnt1=-1;
    vector<ll> ans;
    rep(i,Q){
        if(t[i]==0){
            cnt0++;
            lct.add_segment(a[N+cnt0],b[N+cnt0],l[N+cnt0],r[N+cnt0]);
        }
        else{
            cnt1++;
            ans.push_back(lct.get_min(p[cnt1]));
        }
    }
    rep(i,ans.size()){
        if(ans[i]==LINF)cout<<"INFINITY"<<endl;
        else cout<<ans[i]<<endl;
    }
}