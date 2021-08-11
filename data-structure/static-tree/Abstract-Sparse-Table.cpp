#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
int msb(int x){return x==0 ? -1:31-__builtin_clz(x);}//0-indexed
int lsb(int x){return x==0 ? 32:__builtin_ctz(x);}//0-indexed
int popcnt(int x){return __builtin_popcount(x);}

template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}

template<class S,S (*op)(S,S),S (*e)()>
class Sparse_Table{
    int size,N,bsize;
    vector<vector<S>> array;
    public:
    static constexpr int msb(int x){return x==0 ? -1:31-__builtin_clz(x);}//0-index
        Sparse_Table(vector<S> v){
            size=v.size();
            N=1,bsize=0;
            while(N<size){
                N<<=1;
                ++bsize;
            }
            array=vector<vector<S>>(bsize+(int)(bsize==0),vector<S>(N,e()));
            for(int i=0;i<size;++i)array[0][i]=v[i];

            for(int k=1;k<bsize;++k){
                for(int i=0;i<(N>>(k+1));++i){
                    int offset=i*(1<<(k+1))+(1<<k);
                    for(int j=0;j<(1<<k);++j){
                        if(j==0)array[k][offset]=array[0][offset];
                        else array[k][j+offset]=op(array[k][j-1+offset],array[0][j+offset]);
                    }
                    --offset;
                    for(int j=0;j>-(1<<k);--j){
                        if(j==0)array[k][offset]=array[0][offset];
                        else array[k][j+offset]=op(array[0][j+offset],array[k][j+1+offset]);
                    }
                }
            }
        }
        S query(int left,int right){
            assert(0<=left&&right<=size&&left<right);
            --right;
            if(left==right)return array[0][left];
            return op(array[msb(left^right)][left],array[msb(left^right)][right]);
        }



};

void Main();

int main(){cout<<fixed<<setprecision(15);Main();}

/*
//verify ABC182D
ll op(ll n1,ll n2){return max(n1,n2);}
ll e(){return 0;}

void Main(){
int N;
cin>>N;
vector<ll> A(N);
rep(i,N)cin>>A[i];
rep(i,N)if(i)A[i]+=A[i-1];
Sparse_Table<ll,op,e> st(A);
ll sum=0;
ll ans=0;
rep(i,N){
    chmax(ans,sum+st.query(0,i+1));
    sum+=A[i];
}
cout<<ans<<endl;

}
*/
//verify ABC175D
ll op(ll n1,ll n2){return max(n1,n2);}
ll e(){return 0;}
void Main(){
    int N;ll K;
    cin>>N>>K;
    int P[N];
    rep(i,N){
        cin>>P[i];P[i]--;
    }
    ll C[N];
    rep(i,N)cin>>C[i];
    bool check[N];
    rep(i,N)check[i]=false;
    ll ans=0;
    bool pos=false;
    ll ngmax=-1e9-5;
    rep(i,N){
        if(C[i]>0)pos=true;
        chmax(ngmax,C[i]);
    }
    if(!pos){
        cout<<ngmax<<endl;
        return;
    }
    rep(i,N){
        if(check[i])continue;
        int j=i;
        vector<int> cycle;
        ll cyclenum=0;
        int cyclesize=0;
        for(;!check[j];j=P[j]){
            cycle.push_back(j);
            ++cyclesize;
            cyclenum+=C[j];
            check[j]=true;
        }

        /*
        cout<<cyclenum<<endl;
        rep(j,cyclesize)cout<<cycle[j]<<" ";
        cout<<endl;
        */
        vector<ll> sum(cyclesize*2);
        rep(j,cyclesize*2){
            if(j)sum[j]=sum[j-1]+C[cycle[j%cyclesize]];
            else sum[j]=C[cycle[j]];
        }
        Sparse_Table<ll,op,e> st(sum);
        if(cyclenum<=0||K<cyclesize){
            rep(j,cyclesize){
                if(j)chmax(ans,st.query(j,j+min(K,(ll)cyclesize))-sum[j-1]);
                else chmax(ans,st.query(0,min(K,(ll)cyclesize)));
            }
        }
        else if(cyclenum>0){
            rep(j,cyclesize){
                if(j){
                chmax(ans,(K/cyclesize-1)*cyclenum+st.query(j,j+cyclesize)-sum[j-1]);
                if(K%cyclesize)chmax(ans,(K/cyclesize)*cyclenum+st.query(j,j+K%cyclesize)-sum[j-1]);
                else chmax(ans,K/cyclesize*cyclenum);
                }
                else{
                    chmax(ans,(K/cyclesize-1)*cyclenum+st.query(0,cyclesize));
                if(K%cyclesize)chmax(ans,(K/cyclesize)*cyclenum+st.query(0,K%cyclesize));
                else chmax(ans,K/cyclesize*cyclenum);
                }
            }
        }

    }
    cout<<ans<<endl;
}