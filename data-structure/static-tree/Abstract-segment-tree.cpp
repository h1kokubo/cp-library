#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
const int INF=1e9+1e5;

template<class S, S (*op)(S,S),S (*e)()>
class Segment_Tree{
    /*
    successor(self,i)  boolfunc(data[index,index2))=Falseとなる最大のindex2を返す。
    predecessor(self,i) boolfunc(data[index2,index))=Falseとなる最小のindex2を返す。
    */
    int N;
    int rank;
    int size;
    vector<S> array;

    S prod(int left,int right,int i,int l,int r){
        if(right<=l||r<=left)return e();
        if(left<=l&&r<=right)return array[i];
        return op(prod(left,right,(i<<1)+1,l,l+(r-l>>1)),prod(left,right,(i<<1)+2,l+(r-l>>1),r));
    }
    public:
    Segment_Tree(int n):size(n){
        N=1;rank=1;
        while(N<size){
            N<<=1;
            rank+=1;
        }
        array=vector<S>((N<<1)-1,e());
    }
    Segment_Tree(vector<S> v){
        size=v.size();N=1;rank=1;
        while(N<size){
            N<<=1;
            rank+=1;
        }
        array=vector<S>((N<<1)-1,e());
        for(int i=0;i<size;++i)array[i+N-1]=v[i];
        for(int i=N-2;i>=0;--i)array[i]=op(array[(i<<1)+1],array[(i<<1)+2]);
    }
    S all_prod(){return array[0];}
    S get(int i){assert(0<=i&&i<size);return array[N-1+i];}
    void set(int i,S data){
        assert(0<=i&&i<size);
        int now=N-1+i;
        array[now]=data;
        while(now!=0){
            now-=1;
            now>>=1;
            array[now]=op(array[(now<<1)+1],array[(now<<1)+2]);
        }
    }
    S prod(int left,int right){
        assert(left>=0&&right<=size&&left<right);
        return prod(left,right,0,0,N);
    }
    template<bool (*bf)(S)>
    int successor(int left){
        assert(0<=left&&left<size);
        int now=N-1+left;
        int res=left;
        int r=left+1;
        S nowprod=e();
        int ra=rank;
        while(1){
            S temp=op(nowprod,array[now]);
            if(!bf(temp)){
                res=r;
                nowprod=temp;
                if(now!=0&&now==(((now-1)>>1)<<1)+1){
                    ++now;
                    r+=1<<rank-ra;
                }
                else if(now+2!=(1<<ra)){
                    now=(now-1>>1)+1;
                    --ra;
                    r+=1<<rank-ra;
                }
                else break;
            }
            else{
                if((now<<1)+1<(N<<1)-1){
                    ++ra;
                    now=(now<<1)+1;
                    r-=1<<rank-ra;
                }
                else break;
            }
        }
        return min(size,res);
    }
    template<bool (*bf)(S)>
    int predecessor(int right){
        assert(0<right&&right<=size);
        int now=N-1+right-1;
        int res=right;
        S nowprod=e();
        int ra=rank;
        int l=right-1;
        while(1){
            S temp=op(array[now],nowprod);
            if(!bf(temp)){
                res=l;
                nowprod=temp;
                if(now!=0&&((now-1<<1)>>1)+2==now){
                    --now;
                    l-=1<<rank-ra;
                }
                else if(now+1!=1<<ra-1){
                    now=((now-1)>>1)-1;
                    --ra;
                    l-=1<<rank-ra;
                }
                else break;
            }
            else{
                if((now<<1)+2<(N<<1)-1){
                    now=(now<<1)+2;
                    ++ra;
                    l+=1<<rank-ra;
                }
                else break;
            }
        }
        return res;
    }


};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

/*verify ABC185F
int op(int x,int y){return x^y;}
int e(){return 0;}
void Main(){
int N,Q;
cin>>N>>Q;
vector<int> A(N);
rep(i,N)cin>>A[i];
Segment_Tree<int,op,e> seg(A);
vector<int> ans;
rep(i,Q){
    int T,X,Y;
    cin>>T>>X>>Y;
    if(T==1){
        X--;
        seg.set(X,seg.get(X)^Y);
    }
    else{
        X--;
        ans.push_back(seg.prod(X,Y));
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
int op(int x,int y){return max(x,y);}
int e(){return 0;}
int v;
bool bf(int x){return x>=v;}

void Main(){
int N,Q;
cin>>N>>Q;
vector<int> A(N);
rep(i,N)cin>>A[i];
Segment_Tree<int,op,e> seg(A);
vector<int> ans;
rep(i,Q){
    int T;
    cin>>T;
    if(T==1){
        int X,V;
        cin>>X>>V;
        X--;seg.set(X,V);
    }
    else if(T==2){
        int L,R;
        cin>>L>>R;
        L--;
        ans.push_back(seg.prod(L,R));
    }
    else{
        int X;
        cin>>X>>v;
        X--;
        ans.push_back(seg.successor<bf>(X)+1);
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
// Library-Checker static RMQ
int op(int n1,int n2){return min(n1,n2);}
int e(){return 1000000000;}
void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<int> a(N);
    rep(i,N)cin>>a[i];
    Segment_Tree<int,op,e> st(a);
    vector<int> ans(Q);
    int l,r;
    rep(i,Q){
        cin>>l>>r;
        ans[i]=st.prod(l,r);
    }
    rep(i,Q)cout<<ans[i]<<endl;
}
*/

//Library-Checker Point Set Range Composite
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
struct S{
    mint a,b;
};
S op(S n1,S n2){
    return S{n1.a*n2.a,n2.a*n1.b+n2.b};
}
S e(){return S{1,0};}

void Main(){
    int N,Q;cin>>N>>Q;
    vector<S> ab(N);
    int a,b;
    rep(i,N){
        cin>>a>>b;
        ab[i]=S{a,b};
    }
    Segment_Tree<S,op,e> st(ab);
    int t,p,c,d,l,r,x;
    vector<int> ans;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>p>>c>>d;
            st.set(p,S{c,d});
        }
        else{
            cin>>l>>r>>x;
            S res=st.prod(l,r);
            ans.push_back((res.a*x+res.b).val());
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RMQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
int op(int n1,int n2){return min(n1,n2);}
int e(){return INT_MAX;}

void Main(){
    int n,q;cin>>n>>q;
    vector<int> v(n,(1LL<<31)-1);
    Segment_Tree<int,op,e> seg(v);
    vector<int> ans;
    rep(i,q){
        int c;
        cin>>c;
        if(c==0){
            int x,y;
            cin>>x>>y;
            seg.set(x,y);
        }
        else{
            int x,y;
            cin>>x>>y;
            ans.push_back(seg.prod(x,y+1));
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
/*
//verify RSQ https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B

int op(int n1,int n2){return n1+n2;}
int e(){return 0;}

void Main(){

int n,q;cin>>n>>q;
vector<int> v(n,0),ans;
Segment_Tree<int,op,e> seg(v);
rep(i,q){
    int c;cin>>c;
    int x,y;cin>>x>>y;
    if(c==0){
        x--;
        seg.set(x,seg.get(x)+y);
    }
    else{
        x--;
        ans.push_back(seg.prod(x,y));
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;

}
*/
//verify Sliding Minimum https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_D
int op(int n1,int n2){return min(n1,n2);}
int e(){return INT_MAX;}
void Main(){
    int N,L;cin>>N>>L;
    vector<int> a(N);
    rep(i,N)cin>>a[i];
    Segment_Tree<int,op,e> seg(a);
    vector<int> ans(N-L+1);
    rep(i,N-L+1)ans[i]=seg.prod(i,i+L);
    rep(i,N-L+1){
        if(i)cout<<" ";
        cout<<ans[i];
    }
    cout<<endl;
}