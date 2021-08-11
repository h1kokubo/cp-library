#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

template<class S,S (*op)(S,S),S(*e)(),class F,S(*mapping)(F,S),F(*composition)(F,F),F(*id)()>
class Lazy_Segment_Tree{
    int size;
    int bsize;
    int N;
    int treesize;
    vector<S> array;
    vector<F> lazy;
    
    void update(int i){
        if(i>=N-1)return;
        int ni=(i<<1)+1;
        eval(ni);
        eval(ni+1);
        array[i]=op(array[ni],array[ni+1]);
    }
    void eval(int i){
            array[i]=mapping(lazy[i],array[i]);
            if(i<N-1){
            int ni=(i<<1)+1;
            lazy[ni]=composition(lazy[i],lazy[ni]);
            ++ni;
            lazy[ni]=composition(lazy[i],lazy[ni]);
            }
            lazy[i]=id();
    }
    S get(int i,int now,int l,int r){
        eval(now);
        int mid=(l+r)>>1;
        if(i+N-1==now)return array[now];
        if(i<mid){
            return get(i,(now<<1)+1,l,mid);
        }
        else{
            return get(i,(now<<1)+2,mid,r);
        }
    }
    void set(int i,S data,int now,int l,int r){
        eval(now);
        int mid=(l+r)>>1;
        if(i+N-1==now){
            array[now]=data;
            return;
        }
        if(i<mid){
            set(i,(now<<1)+1,l,mid);
        }
        else{
            set(i,(now<<1)+2,mid,r);
        }
        update(now);
    }
    
    S prod(int left,int right,int i,int l,int r){
        eval(i);
        if(r<=left||right<=l)return e();
        if(left<=l&&r<=right)return array[i];
        S resl=prod(left,right,(i<<1)+1,l,(l+r)>>1);
        S resr=prod(left,right,(i<<1)+2,(l+r)>>1,r);
        return op(resl,resr);
    }
    void apply(int left,int right,int i,int l,int r,F f){
        
        if(left<=l&&r<=right){
            lazy[i]=composition(f,lazy[i]);
            eval(i);
        }
        else if(left<r&&l<right){
            int mid=(l+r)>>1;
            eval(i);
            apply(left,right,(i<<1)+1,l,mid,f);
            apply(left,right,(i<<1)+2,mid,r,f);
            update(i);
        }
    }
    public:
        Lazy_Segment_Tree(int n){
            size=n;
            N=1;
            bsize=0;
            while(N<size){
                N<<=1;
                ++bsize;
            }
            treesize=(N<<1)-1;
            array=vector<S>(treesize,e());
            lazy=vector<F>(treesize,id());
        }
        Lazy_Segment_Tree(vector<S> v){
            size=v.size();
            N=1;
            bsize=0;
            while(N<size){
                N<<=1;
                ++bsize;
            }
            treesize=(N<<1)-1;
            array=vector<S>(treesize,e());
            for(int i=0;i<size;++i){
                array[N-1+i]=v[i];
            }
            for(int i=N-2;i>=0;--i){
                array[i]=op(array[(i<<1)+1],array[(i<<1)+2]);
            }
            lazy=vector<F>(treesize,id());
        }
        
        S get(int i){
            assert(0<=i&&i<size);
            return get(i,0,0,N);
        }
        void set(int i,S data){
            assert(0<=i&&i<size);
            set(i,data,0,0,N);
        }
        S allprod(){
        //eval(0);
        return array[0];
        }
        S prod(int left,int right){
            assert(left>=0&&right<=size&&left<right);
            return prod(left,right,0,0,N);
        }
        void apply(int left,int right,F f){
            assert(left>=0&&right<=size&&left<right);
            apply(left,right,0,0,N,f);
        }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


namespace Mint{
    const long long mod=998244353;
    //const long long mod=1000000007;
    constexpr long long safe_div(long long x,long long m){if (x<0)return (x+1)/m-1;else return x/m;}
    constexpr long long safe_mod(long long x,long long m){x%=m;if(x<0){x+=m;}return x;}
    namespace Prime_modinv{
        namespace Extend_euclid{
            vector<long long> inner(const long long a,const long long b){
                //b>=0 and abs(a)>=abs(b)
                //b==0
                if(b==0){
                    if(a<0){
                        return vector<long long>{-a,-1,0};
                    }
                    else{
                        return vector<long long>{a,1,0};
                    }
                }
                long long s=a,t=b,sx=1,sy=0,tx=0,ty=1;
                while(t!=0){
                    long long temp=safe_div(s,t),u=s-temp*t,ux=sx-temp*tx,uy=sy-temp*ty;
                    s=t,t=u,sx=tx,tx=ux,sy=ty,ty=uy;
                }
                return vector<long long>{s,sx,sy};
            }
        }

        vector<long long> extend_euclid(const long long a,const long long b){
            if(abs(b)>abs(a)){
                if(a<0){
                    vector<long long> v=Extend_euclid::inner(-b,-a);
                    return vector<long long>{v[0],-v[2],-v[1]};
                }
                else{
            
                    vector<long long> v=Extend_euclid::inner(b,a);
                    return vector<long long>{v[0],v[2],v[1]};
                }
            }
            else{
                if(b<0){
                    vector<long long> v=Extend_euclid::inner(-a,-b);
                    return vector<long long>{v[0],-v[1],-v[2]};
                }
                else{
                    vector<long long> v=Extend_euclid::inner(a,b);
                    return vector<long long>{v[0],v[1],v[2]};
                }
        
            }
        } 
    }
    long long prime_modinv(const long long a,const long long n){
        return safe_mod(Prime_modinv::extend_euclid(a,n)[1],n);
    }
}
struct mint{
    private:
        unsigned int x;
    public:
        mint(const long long x_):x((unsigned int)(x_%Mint::mod)){}
        mint(){}
        mint rawset(const long long x_){
            x=(unsigned int)x_;
            return *this;
        }
        long long val()const{return x;}
        mint& operator++(){
            x++;
            if(x==Mint::mod)x=0;
            return *this;
        }
        mint& operator--(){
            if(x==0)x=Mint::mod;
            x--;
            return *this;
        }
        mint& operator+=(const mint& rhs){
            x+=rhs.val();
            if(x>=Mint::mod)x-=Mint::mod;
            return *this;
        }
        mint& operator-=(const mint& rhs){
            
            if(x<rhs.val())x+=Mint::mod;
            x-=rhs.val();
            return *this;
        }
        mint& operator*=(const mint& rhs){
            unsigned long long y=x;
            y*=rhs.val();
            x=(unsigned int)(y%Mint::mod);
            return *this;
        }
        mint& operator/=(const mint& rhs){return *this=*this * rhs.inv();}
        mint operator+() const { return *this;}
        mint operator-() const { return mint().rawset(Mint::mod)-*this;}
        mint pow(long long n) const{
            mint x = *this,ans=mint(1);
            while(n>0){
                if(n&1)ans*=x;
                x*=x;
                n>>=1;
            }
            return ans;
        }
        mint inv() const{
            return mint(Mint::prime_modinv(x,Mint::mod));
        }

        friend mint operator+(const mint& lhs,const mint& rhs){
            return mint(lhs)+=rhs;
        }
        friend mint operator-(const mint& lhs,const mint& rhs){
            return mint(lhs)-=rhs;
        }
        friend mint operator*(const mint& lhs,const mint& rhs){
            return mint(lhs)*=rhs;
        }
        friend mint operator/(const mint& lhs,const mint& rhs){
            return mint(lhs)/=rhs;
        }
        friend bool operator==(const mint& lhs,const mint& rhs){
            return lhs.val()==rhs.val();
        }
        friend bool operator!=(const mint& lhs,const mint& rhs){
            return lhs.val()!=rhs.val();
        }




};
/*
//verify ALPC K
struct S{
    mint x;
    int size;
};
S op(S n1,S n2){
    return S{n1.x+n2.x,n1.size+n2.size};
}
S e(){return S{0,0};}
struct F{
    mint a,b;
};
S mapping(F f,S n){
    return S{f.a*n.x+f.b*n.size,n.size};
}
F composition(F f,F g){
    return F{f.a*g.a,f.a*g.b+f.b};
}
F id(){return F{1,0};}
void Main(){
int N,Q;
cin>>N>>Q;
vector<S> v(N);
rep(i,N){
    int a;cin>>a;
    v[i]=S{mint(a),1};
}
Lazy_Segment_Tree<S,op,e,F,mapping,composition,id> lz(v);
vector<int> ans;
rep(i,Q){
    int T;
    cin>>T;
    if(T==0){
        int l,r,b,c;
        cin>>l>>r>>b>>c;
        lz.apply(l,r,F{mint(b),mint(c)});
    }
    else{
        int l,r;
        cin>>l>>r;
        ans.push_back(lz.prod(l,r).x.val());
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//ACLBC E
struct S{
    mint x;
    mint pow_10_size;
};
S op(S n1,S n2){
    return S{n1.x*n2.pow_10_size+n2.x,n1.pow_10_size*n2.pow_10_size};
}
S e(){return S{0,1};}
int ID=1000000000;
using F=int;
mint inv9;
S mapping(F f,S n){
    if(f==ID)return n;
    else return S{mint(f)*(n.pow_10_size-1)*inv9,n.pow_10_size};
}
F composition(F f,F g){
    if(f==ID)return g;
    else return f;
}
F id(){return ID;}
void Main(){
inv9=(mint(9)).inv();
int N,Q;
cin>>N>>Q;
vector<S> v(N,S{1,10});
Lazy_Segment_Tree<S,op,e,F,mapping,composition,id> lz(v);
vector<int> ans(Q);
rep(i,Q){
    int L,R,D;
    cin>>L>>R>>D;
    L--;
    lz.apply(L,R,D);
    ans[i]=lz.allprod().x.val();
}
rep(i,Q)cout<<ans[i]<<endl;
}
*/
/*
// Library-Checker Range Affine Range Sum
struct S{
    mint x;
    int size;
};

S op(S n1,S n2){return S{n1.x+n2.x,n1.size+n2.size};}
S e(){return S{mint(0),0};}
struct F{
    mint b,c;
};
S mapping(F f,S x){
    return S{f.b*x.x+f.c*x.size,x.size};
}
F composition(F f,F g){
    return F{f.b*g.b,f.b*g.c+f.c};
}
F id(){return F{mint(1),mint(0)};}

void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<S> a(N);
    int a_;
    rep(i,N){
        cin>>a_;
        a[i]=S{a_,1}; 
    }
    Lazy_Segment_Tree<S,op,e,F,mapping,composition,id> lz(a);
    int t,l,r,b,c;
    vector<int> ans;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>l>>r>>b>>c;
            lz.apply(l,r,F{b,c});
        }
        else{
            cin>>l>>r;
            ans.push_back(lz.prod(l,r).x.val());
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RUQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D
struct S{
    ll x;int size;
};
S op(S n1,S n2){return S{n1.x+n2.x,n1.size+n2.size};}
S e(){return S{0,0};}
const ll ID=-1;
S mapping(ll f,S n){
    if(f==ID){
        return S{n.x,n.size};
    }
    else{
        return S{f*n.size,n.size};
    }
}
ll composition(ll f,ll g){
    if(f==ID)return g;
    else return f;
}
ll id(){return ID;}
void Main(){
    int n,q;cin>>n>>q;
    vector<S> a(n,S{(1LL<<31)-1,1});
    Lazy_Segment_Tree<S,op,e,ll,mapping,composition,id> lz(a);
    vector<ll> ans;
    rep(i,q){
        int c;
        cin>>c;
        if(c==0){
            int s,t;ll x;
            cin>>s>>t>>x;
            lz.apply(s,t+1,x);
        }
        else{
            int j;cin>>j;
            ans.push_back(lz.get(j).x);
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RAQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_E
struct S{
    ll x;int size;
};
S op(S n1,S n2){return S{n1.x+n2.x,n1.size+n2.size};}
S e(){return S{0,0};}
S mapping(ll f,S n){return S{n.x+f*n.size,n.size};}
ll composition(ll f,ll g){return f+g;}
ll id(){return 0;}

void Main(){
    int n,q;cin>>n>>q;
    vector<S> v(n,S{0,1});
    Lazy_Segment_Tree<S,op,e,ll,mapping,composition,id> lz(v);
    vector<ll> ans;
    rep(i,q){
        int c;cin>>c;
        if(c==0){
            int s,t;ll x;
            cin>>s>>t>>x;
            s--;
            lz.apply(s,t,x);
        }
        else{
            int j;cin>>j;
            --j;
            ans.push_back(lz.get(j).x);
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RMQ and RUQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F
int op(int n1,int n2){return min(n1,n2);}
int e(){return INT_MAX;}
const int ID=-1;
int mapping(int f,int n){return f==ID ? n:f;}
int composition(int f,int g){return f==ID ? g:f;}
int id(){return ID;}
void Main(){
    int n,q;cin>>n>>q;
    vector<int> v(n,(1LL<<31)-1);
    Lazy_Segment_Tree<int,op,e,int,mapping,composition,id> lz(v);
    vector<int> ans;
    rep(i,q){
        int c;cin>>c;
        if(c==0){
            int s,t,x;cin>>s>>t>>x;
            lz.apply(s,t+1,x);
        }
        else{
            int s,t;cin>>s>>t;
            ans.push_back(lz.prod(s,t+1));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RSQ and RAQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G
struct S{
    ll x;int size;
};
S op(S n1,S n2){return S{n1.x+n2.x,n1.size+n2.size};}
S e(){return S{0,0};}
S mapping(ll f,S n){return S{n.x+f*n.size,n.size};}
ll composition(ll f,ll g){return f+g;}
ll id(){return 0;}

void Main(){
    int n,q;cin>>n>>q;
    vector<S> v(n,S{0,1});
    Lazy_Segment_Tree<S,op,e,ll,mapping,composition,id> lz(v);
    vector<ll> ans;
    rep(i,q){
        int c;
        cin>>c;
        if(c==0){
            int s,t; ll x;
            cin>>s>>t>>x;
            s--;
            lz.apply(s,t,x);        
        }
        else{
            int s,t;cin>>s>>t;
            s--;
            ans.push_back(lz.prod(s,t).x);
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
// verify RMQ and RAQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H

int op(int n1,int n2){return min(n1,n2);}
int e(){return INT_MAX;}
int mapping(int f,int n){return f+n;}
int composition(int f,int g){return f+g;}
int id(){return 0;}
void Main(){
    int n,q;cin>>n>>q;
    vector<int> v(n);
    Lazy_Segment_Tree<int,op,e,int,mapping,composition,id> lz(v);
    vector<int> ans;
    rep(i,q){
        int c;cin>>c;
        if(c==0){
            int s,t,x;cin>>s>>t>>x;
            lz.apply(s,t+1,x);
        }
        else{
            int s,t;cin>>s>>t;
            ans.push_back(lz.prod(s,t+1));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
//verify RSQ and RUQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I
struct S{
    int x,size;
};
S op(S n1,S n2){return S{n1.x+n2.x,n1.size+n2.size};}
S e(){return S{0,0};}
const int ID=10000;
S mapping(int f,S n){return f==ID? n:S{f*n.size,n.size};}
int composition(int f,int g){return f==ID? g:f;}
int id(){return ID;}

void Main(){
    int n,q;
    cin>>n>>q;
    vector<S> v(n,S{0,1});
    Lazy_Segment_Tree<S,op,e,int,mapping,composition,id> lz(v);
    vector<int> ans;
    rep(i,q){
        int c;cin>>c;
        if(c==0){
            int s,t,x;cin>>s>>t>>x;
            lz.apply(s,t+1,x);
        }   
        else{
            int s,t;cin>>s>>t;
            ans.push_back(lz.prod(s,t+1).x);
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}