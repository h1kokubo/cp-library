#include <bits/stdc++.h>
using namespace std;

struct KMP{
    string p;
    vector<int> prefixArray;
    KMP(string &p):p(p){
        int m=p.size();
        prefixArray=vector<int>{0,0};
        int length=0;
        for(int i=1;i<m;++i){
            while(length>0&&p[length]!=p[i]){
                length=prefixArray[length];
            }
            if(p[length]==p[i])++length;
            prefixArray.push_back(length);
        }
    }
    vector<int> sweep(string &text){
        vector<int> ans;
        int n=text.size();
        int m=p.size();
        int p_i=0;
        for(int i=0;i<n;++i){
            while(p_i>0&&p[p_i]!=text[i]){
                p_i=prefixArray[p_i];
            }
            if(p[p_i]==text[i]){
                p_i+=1;
            }
            if(p_i==m){
                ans.push_back(i);
                p_i=prefixArray[p_i];
            }
        }
        return ans;
    }

};

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 

void Main(){

string p="abcabc",text="abcabcabc";
KMP kmp(p);
auto ans=kmp.sweep(text);
print(ans);

}