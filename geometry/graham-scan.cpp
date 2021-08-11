#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}
vector<long long> divisor(long long n){vector<long long> res;long long i = 1;while (i*i<=n){if(n%i==0){res.push_back(i);}i++;}if(res.size()==0)return res;for(long long i = res.size()-1-(res.back()*res.back()==n);i>=0;--i){res.push_back(n/res[i]);}return res;}
long long safe_mod(long long x,long long m){x%=m;if(x<0){x+=m;}return x;}
long long modpow(long long x,long long n,long long mod){long long ans=1;while(n>0){if(n&1){ans*=x;ans%=mod;}n>>=1;x*=x;x%=mod;}return ans;}
long long intpow(long long x,long long n){long long ans=1;while(n>0){if(n&1){ans*=x;}n>>=1;x*=x;}return ans;}
//template<typename T>T intpow(T x,T n){T ans=1;while(n>0){if(n&1){ans*=x;}n>>=1;x*=x;}return ans;}
vector<pair<long long,long long>> factor_lst(long long n){vector<pair<long long,long long>> factor_lst;long long d=2;while(d*d<=n){if(n%d==0){long long num=0;while(n%d==0){num+=1;n/=d;}factor_lst.push_back({d,num});}d+=1;}if(n!=1){factor_lst.push_back({n,1});}return factor_lst;}
#define Uniq(a) sort(all(a));a.erase(unique(all(a)),end(a))


int msb(int x){return x==0 ? -1:32-__builtin_clz(x);}//1-indexed
int lsb(int x){return x==0 ? 32:__builtin_ctz(x)+1;}//1-indexed
int popcnt(int x){return __builtin_popcount(x);}
int popcnt(long long x){return __builtin_popcount(x);}

bool ingrid(int i,int j,int H,int W){
    return 0<=i&&i<H&&0<=j&&j<W;
}

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 
template<typename T> void print(T* v,int size){for(int i=0;i<size;++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;}
template<typename T,typename S>void print(pair<T,S>&p){cout<<p.first<<" "<<p.second<<endl;}
const ll LINF=4*1e18;
const ll MINF=5*1e15;
const int INF=2*1e9;
const ld PI=acosl(-1);
const ld DINF=INF;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


namespace graham{
    template<typename T>
    struct Point{
        T x,y;
    };
    template<class T>
    class Stack{
        struct node{
            T val;
            node *next;
        };
        int sz;
        node *head=NULL;
        public:
            Stack():sz(0){}
            bool empty(){return head==NULL;}
            int size(){return sz;}
            void push(T v){
                ++sz;
                node *q = new node;
                q->val=v;
                q->next=head;
                head=q;
            }
            T top(){
                return head->val;
            }
            T next_top(){
                return head->next->val;
            }
            T pop(){
                --sz;
                node *q=head;
                T v =q->val;
                head=head->next;
                delete q;
                return v;
            }
    };
    //argment-sort begin
    template<typename T>
    int rotate_direction(Point<T> p1,Point<T> p2,Point<T> p0){
        Point<T> v1=Point<T>{p1.x-p0.x,p1.y-p0.y},v2=Point<T>{p2.x-p0.x,p2.y-p0.y};
        long long det=v1.x*v2.y-v1.y*v2.x;
        if(det>0)return 0;
        else if (det<0) return 1;
        else{
            long long mul_x=v1.x*v2.x,mul_y=v1.y*v2.y;
            if(mul_x>0||mul_y>0)return 2;
            else if(mul_x<0||mul_y<0)return 3;
            else return 4;
        }
    }
    template<typename T>
    bool argument_compare(Point<T> p1,Point<T> p2,Point<T> p0){
        Point<T> v1=Point<T>{p1.x-p0.x,p1.y-p0.y},v2=Point<T>{p2.x-p0.x,p2.y-p0.y};
        int dir=rotate_direction(p1,p2,p0);
        if(dir==0){
            if(v1.y<0&&v2.y>=0)return false;
            else return true;
        }
        else if(dir==1){
            if(v2.y<0&&v1.y>=0)return true;
            else return false;
        }
        else if(dir==2)return false;
        else if(dir==4)return (v1.x==0&&v1.y==0)&&(v2.x!=0||v2.y!=0);
        else return v1.y>0||(v1.y==0&&v1.x>0);
    }

    //argment-sort end
}

template<typename T>
vector<graham::Point<T>> graham_scan(vector<graham::Point<T>> v_lst){
    const int N=v_lst.size();
    assert(N>=3);
    T y_min=v_lst[0].y,x_min=v_lst[0].x;
    int min_id=0;
    for(int i=0;i<N;++i){
        if(v_lst[i].y<y_min){
            y_min=v_lst[i].y;
            x_min=v_lst[i].x;
            min_id=i;
        }
        else if(v_lst[i].y==y_min&&v_lst[i].x<x_min){
            x_min=v_lst[i].x;
            min_id=i;
        }
    }
    swap(v_lst[0],v_lst[min_id]);
    graham::Point<T> p=v_lst[0];
    sort(v_lst.begin(),v_lst.end(),[&](graham::Point<T> p1,graham::Point<T> p2){
        return graham::argument_compare(p1,p2,p);
    });
    graham::Stack<graham::Point<T>> st;
    st.push(v_lst[0]);
    st.push(v_lst[1]);
    for(int i=2;i<N;++i){
        while(true){
            int dir=graham::rotate_direction(v_lst[i],st.next_top(),st.top());
            if(dir==0)break;
            st.pop();
            if(st.size()<2)break;
        }
        st.push(v_lst[i]);
    }
    vector<graham::Point<T>> ans;
    while(!st.empty()){
        ans.push_back(st.pop());
    }
    reverse(ans.begin(),ans.end());
    return ans;
} 


void Main(){

int N;cin>>N;
vector<graham::Point<ll>> lst;
rep(i,N){
    ll X,Y;
    cin>>X>>Y;
    lst.push_back(graham::Point<ll>{X,Y});
} 
auto res=graham_scan(lst);


}
