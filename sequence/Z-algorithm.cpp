#include <bits/stdc++.h>
using namespace std;

vector<int> Zalgo(string &s){
    vector<int> prefix(s.size());//lcp(s[0:],s[i:])
    int j=1;//ループ開始時、j+lcp[s[j:]]が最大でかつj<iとなるようにとるしかし、j=0であるとprefix[i-j(=i)]は未計算であるから、ここは例外的に避ける。
    prefix[0]=s.size();//自明 s=s[0:]
    for(int i=1;i<s.size();++i){
        if(j<i&&i-j+prefix[i-j]<prefix[j]){//lcpの定義よりs[0:prefix[j]<s.size()]=s[j:prefix[j]] であり、i-j+prefix[i-j]<prefix[j]ならば、s[i-j:i-j+prefix[i-j]]=s[i:i+prefix[i]]
            prefix[i]=prefix[i-j];
        }
        else{//そうでない場合は求めるが、j+prefix[j]が単調増加であるから(i+prefix[i]<j+prefix[j]が上の分岐と同値であった)償却O(|S|)
            int k=max(0,j+prefix[j]-i);//上の分岐よりprefix[i]>=prefix[j]-i+j
            while(i+k<s.size()&&s[k]==s[i+k])++k;
            prefix[i]=k;
            j=i;
        }
    }
    return prefix;
}


#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;} 

void Main(){

string S;cin>>S;
auto res=Zalgo(S);
print(res);

}