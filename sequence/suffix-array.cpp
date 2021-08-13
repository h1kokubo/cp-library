#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {//O(NlogN)
  vector<int> SA;
  const string s;

  SuffixArray(const string &str) : s(str) {
    SA.resize(s.size());
    //0~n-1までUniqueで埋め、一文字ソート
    iota(begin(SA), end(SA), 0);
    sort(begin(SA), end(SA), [&](int a, int b) {
      return s[a] == s[b] ? a > b : s[a] < s[b];
    });
    //classes: s[i:i+2^k]の識別番号 c,cnt:カウントソート用の外部記憶領域
    vector<int> classes(s.size()), c(s.begin(), s.end()), cnt(s.size());
    //ダブリングで構成 
    for(int len = 1; len < s.size(); len <<= 1) {
      for(int i = 0; i < s.size(); i++) {
        if(i > 0 && c[SA[i - 1]] == c[SA[i]] && SA[i - 1] + len < s.size() && c[SA[i - 1] + len / 2] == c[SA[i] + len / 2]) {
          classes[SA[i]] = classes[SA[i - 1]];
        } else {
          classes[SA[i]] = i;
        }
      }
      iota(begin(cnt), end(cnt), 0);
      copy(begin(SA), end(SA), begin(c));
      for(int i = 0; i < s.size(); i++) {
        int s1 = c[i] - len;
        if(s1 >= 0) SA[cnt[classes[s1]]++] = s1;
      }
      classes.swap(c);
    }
  }

  int operator[](int k) const {
    return SA[k];
  }

  size_t size() const {
    return s.size();
  }
};

struct LCPArray{//O(N) indexが通常に戻っている点に注意
    vector<int> LA;
    const string s;
    LCPArray(const SuffixArray &sa) : s(sa.s){
        const int n=s.size();
        vector<int> rsa(n);
        for(int i=0;i<n;++i)rsa[sa[i]]=i;
        int h=0;
        for(int i=0;i<n;++i){
            int sa_i=rsa[i];
            if(sa_i==n-1){
                h=0;
                LA.push_back(h);
            }
            else if(h==0){
                h=calcLcp(i,sa[sa_i+1]);
                LA.push_back(h);
            }
            else{
                h=h-1+calcLcp(i+h-1,sa[sa_i+1]+h-1);
                LA.push_back(h);
            }
        }
    }
    int calcLcp(const int i,const int j){
        int length=0;
        while(i+length<s.size()&&j+length<s.size()){
            if(s[i+length]==s[j+length]){
                ++length;
            }
            else break;
        }
        return length;
    }
    int operator[](int k) const {
        return LA[k];
    }

    size_t size() const {
        return s.size();
    }
};

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 

void Main(){

string s;
cin>>s;
SuffixArray sa(s);
LCPArray la(sa);
ll ans=(ll)s.size()*(s.size()+1)/2;
rep(i,s.size()){
    ans-=la[i];
}
cout<<ans<<endl;

}