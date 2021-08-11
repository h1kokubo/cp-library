#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

struct RadixHeapINT32Pair{
    static constexpr msb(unsigned x){//1-indexed
    if(x==0)return 0;
    else return 32-__builtin_clz(x);
    }
    vector<pair<unsigned,unsigned>> v[33];
    unsigned last,sz;
    RadixHeapINT32Pair():last(0U),sz(0U){}
    bool empty(){return sz==0;}
    unsigned size(){return sz;}
    void push(pair<unsigned,unsigned> p){
        assert(last<=p.first);
        ++sz;
        v[msb(p.first^last)].push_back(p);
    }
    pair<unsigned,unsigned> pop(){
        assert(sz);
        if(v[0].size()==0){
            int i=1;
            while(v[i].size()==0)++i;
            unsigned new_last=UINT_MAX;
            pair<unsigned,unsigned> res;
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
            return res;
        }
        else{
            --sz;
            pair<unsigned,unsigned> res=v[0].back();
            v[0].pop_back();
            return res;
        }
    }
};

void Main(){



}