#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 

const ll LINF=4*1e18;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

struct RadixHeapINT64Pair{
    using u64=unsigned long long;
    using u32=unsigned;
    static constexpr int msb(u64 x){//1-indexed
    if(x==0)return 0;
    else return 64-__builtin_clzll(x);
    }
    vector<pair<u64,u32>> v[65];
    u64 last;
    unsigned sz;
    RadixHeapINT64Pair():last(0UL),sz(0U){}
    bool empty(){return sz==0;}
    u32 size(){return sz;}
    void push(pair<ll,int> p){
        assert(last<=p.first);
        ++sz;
        v[msb(p.first^last)].push_back(make_pair(p.first,p.second));
    }
    pair<ll,int> pop(){
        assert(sz>0);
        if(v[0].size()==0){
            int i=1;
            while(v[i].size()==0)++i;
            u64 new_last=ULLONG_MAX;
            pair<u64,u32> res;
            for(auto p:v[i]){
                if(new_last>p.first){
                    new_last=p.first;
                    res=p;
                }
            }
            for(auto p:v[i]){
                v[msb(p.first^new_last)].push_back(p);
            }
            last=new_last;
            v[i].clear();
            v[0].pop_back();
            --sz;
            return make_pair(res.first,res.second);
        }
        else{
            --sz;
            pair<u64,u32> res=v[0].back();
            v[0].pop_back();
            return make_pair(res.first,res.second);
        }
    }
};
/*
void Main(){
    RadixHeapINT64Pair rh;
    rh.push({5,8});
    rh.push({2,21});
    rh.push({7,20});
    rh.push({1,32});
    cout<<rh.pop().first<<endl;
}
*/

void Main(){
int N,M,s,t;cin>>N>>M>>s>>t;
vector<vector<pair<ll,int>>> graph(N);
int a,b;ll c;
rep(i,M){
cin>>a>>b>>c;
graph[a].push_back(make_pair(c,b));
}

vector<ll> dist(N,LINF);

vector<int> par(N,-1);
dist[s]=0;
RadixHeapINT64Pair rh;
rh.push(make_pair(0,s));
while(!rh.empty()){
    auto p=rh.pop();
    if(dist[p.second]!=p.first)continue;
    for(auto np:graph[p.second]){
        if(dist[np.second]>np.first+p.first){
            dist[np.second]=np.first+p.first;
            par[np.second]=p.second;
            rh.push(make_pair(np.first+p.first,np.second));
        }
    }
}



if(dist[t]==LINF){
    cout<<-1<<endl;
    return;
}
ll X=dist[t];
vector<int> path;

while(true){
    
    path.push_back(t);
    if(t==s)break;
    t=par[t];
}
reverse(all(path));
int Y=path.size()-1;
cout<<X<<" "<<Y<<endl;
rep(i,path.size()-1){
    cout<<path[i]<<" "<<path[i+1]<<endl;
}

}
