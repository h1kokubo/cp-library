#include <bits/stdc++.h>
using namespace std;




template<typename T>
bool next_perm(vector<T> &p){
    //{0,...,n-1}の順列(uniqueで順序が入っていればよい)で辞書順で次のものに変換、存在すればtrueしなければfalseを返す。
    int n=p.size();
    //p[i]<p[i+1]なる最大のiを探す。
    for(int i=n-2;i>=0;--i){
        if(p[i]<p[i+1]){
            //p[i+1,n)で p[i]より大きい最小の数を探す。(p[i]<p[i+1]の条件より、必ず一つはある。)
            int min_=p[i+1],min_id=i+1;
            for(int j=i+2;j<n;++j){
                if(p[i]<p[j]&&min_>p[j]){
                    min_=p[j];
                    min_id=j;
                }
            }
            //p[i]とp[min_id]をswapしp[i+1,n)をreverse
            swap(p[i],p[min_id]);
            reverse(p.begin()+i+1,p.end());
            return true;
        }
    }
    //逆順sortedな順列は辞書順最後であるから次はない。
    return false;
}

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 
template<typename T,typename S>T intpow(T x,S n){T ans=1;while(n>0){if(n&1){ans*=x;}n>>=1;x*=x;}return ans;}
/*
//使い方
void Main(){
vector<int> v={1,2,3,4,5};
do{
print(v);
}while(next_perm(v));

}
*/
//verify ABC145 C Average Length
void Main(){
    int N;
    cin>>N;
    vector<pair<ll,ll>> xy(N);
    rep(i,N)cin>>xy[i].first>>xy[i].second;
    vector<int> order(N);
    rep(i,N)order[i]=i;
    ld sum=0;
    do{
        ld length=0;
        rep(i,N-1)length+=sqrtl(intpow(xy[order[i]].first-xy[order[i+1]].first,2)+intpow(xy[order[i]].second-xy[order[i+1]].second,2));
        sum+=length;
    }while(next_perm(order));
    for(int i=1;i<=N;++i)sum/=i;
    cout<<sum<<endl;
}