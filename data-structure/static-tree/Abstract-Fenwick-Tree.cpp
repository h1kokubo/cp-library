#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

template<class S,S (*op)(S,S),S(*invop)(S,S),S (*e)()>
class Fenwick_Tree{
    int bsize;
    int N;
    int size;
    vector<S> array;
    public:
        Fenwick_Tree(int n){
            size=n;
            bsize=0;
            N=1;
            while(N<size){
                ++bsize;
                N<<=1;
            }
            array=vector<S>(N,e());
        }
        Fenwick_Tree(vector<S> v){
            size=v.size();
            bsize=0;
            N=1;
            while(N<size){
                ++bsize;
                N<<=1;
            }
            array=vector<S>(N,e());
            for(int i=0;i<size;++i)array[i]=v[i];
            for(int i=0;i<N-1;++i){
                int par=i+((i+1)&-(i+1));
                array[par]=op(array[par],array[i]);
            }
        }
        void apply(int i,S d){
            assert(0<=i&&i<size);
            for(int j=i;j<N;j+=(j+1)&-(j+1))array[j]=op(d,array[j]);
            /*
            while(i<N){
                array[i]=op(d,array[i]);
                i+=(i+1)&-(i+1);
            }
            */
        }
        S acc(int i){
            assert(0<=i&&i<=size);
            --i;
            S ans=e();
            for(int j=i;j>=0;j-=(j+1)&-(j+1))ans=op(ans,array[j]);
            /*
            while(i!=-1){
                ans=op(ans,array[i]);
                i-=(i+1)&-(i+1);
            }
            */
            return ans;
        }
        S prod(int left,int right){
            assert(0<=left&&right<=size&&left<=right);
            S ans=acc(right);
            ans=invop(ans,acc(left));
            return ans;
        }
};      

void Main();

int main(){cout<<fixed<<setprecision(15);Main();}
/*
//ALPC B
ll op(ll n1,ll n2){
    return n1+n2;
}
ll invop(ll n1,ll n2){
    return n1-n2;
}
ll e(){return 0;}
void Main(){
int N,Q;
cin>>N>>Q;
vector<ll> a(N);
rep(i,N)cin>>a[i];
Fenwick_Tree<ll,op,invop,e> ft(a);
vector<ll> ans;
rep(i,Q){
    int t;
    cin>>t;
    if(t==0){
        int p,x;
        cin>>p>>x;
        ft.apply(p,x);
    }
    else{
        int l,r;
        cin>>l>>r;
        ans.push_back(ft.prod(l,r));
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;

}
*/
/*
//ABC185F
int op(int n1,int n2){return n1^n2;}
int invop(int n1,int n2){return n1^n2;}
int e(){return 0;}
void Main(){
    int N,Q;cin>>N>>Q;
    vector<int> A(N);
    rep(i,N)cin>>A[i];
    Fenwick_Tree<int,op,invop,e> ft(A);
    vector<int> ans;
    rep(i,Q){
        int t;
        cin>>t;
        if(t==1){
            int x,y;
            cin>>x>>y;
            x--;
            ft.apply(x,y);
        }
        else{
            int x,y;
            cin>>x>>y;
            x--;
            ans.push_back(ft.prod(x,y));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;

}
*/
/*
//ABC 190F
ll op(ll n1,ll n2){return n1+n2;}
ll invop(ll n1,ll n2){return n1-n2;}
ll e(){return 0;}
void Main(){
    int N;
    cin>>N;
    vector<ll> a(N);
    rep(i,N)cin>>a[i];
    Fenwick_Tree<ll,op,invop,e> ft(N);
    ll ans[N];
    ll cnt=0;
    rep(i,N){
        cnt+=ft.prod(a[i]+1,N);
        ft.apply(a[i],1);
    }
    rep(i,N){
        ans[i]=cnt;
        cnt-=ft.acc(a[i]);
        cnt+=ft.prod(a[i]+1,N);
    }
    rep(i,N)cout<<ans[i]<<endl;
}
*/
/*
// Library-Checker Point Add Range Sum
ll op(ll n1,ll n2){return n1+n2;}
ll invop(ll n1,ll n2){return n1-n2;}
ll e(){return 0;}
void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<ll> a(N);
    rep(i,N)cin>>a[i];
    Fenwick_Tree<ll,op,invop,e> ft(a);
    vector<ll> ans;
    int t,p,l,r;
    ll x;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>p>>x;
            ft.apply(p,x);
        }
        else{
            cin>>l>>r;
            ans.push_back(ft.prod(l,r));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
