#include <bits/stdc++.h>
using namespace std;

//argment-sort begin
int rotate_direction(pair<long long,long long> p1,pair<long long,long long> p2,pair<long long,long long> p0){
    pair<long long,long long> v1=make_pair(p1.first-p0.first,p1.second-p0.second),v2=make_pair(p2.first-p0.first,p2.second-p0.second);
    long long det=v1.first*v2.second-v1.second*v2.first;
    if(det>0)return 0;
    else if (det<0) return 1;
    else{
        long long mul_x=v1.first*v2.first,mul_y=v1.second*v2.second;
        if(mul_x>0||mul_y>0)return 2;
        else if(mul_x<0||mul_y<0)return 3;
        else return 4;
    }
}
bool argument_compare(pair<long long,long long> p1,pair<long long,long long> p2,pair<long long,long long> p0){
    pair<long long,long long> v1=make_pair(p1.first-p0.first,p1.second-p0.second),v2=make_pair(p2.first-p0.first,p2.second-p0.second);
    int dir=rotate_direction(p1,p2,p0);
    if(dir==0){
        if(v1.second<0&&v2.second>=0)return false;
        else return true;
    }
    else if(dir==1){
        if(v2.second<0&&v1.second>=0)return true;
        else return false;
    }
    else if(dir==2)return false;
    else if(dir==4)return (v1.first==0&&v1.second==0)&&(v2.first!=0||v2.second!=0);
    else return v1.second>0||(v1.second==0&&v1.first>0);
}

//argment-sort end

void Main();

int main(){cout<<fixed<<setprecision(15);Main();}

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()
template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}
template <typename T>bool chmin(T &a, const T& b) {if (a > b) {a = b;return true;}return false;}
#define mp make_pair

void Main(){

//verify Library-Checker Sort Points by Argument
int N;
cin>>N;
vector<pair<ll,ll> > xy(N);
rep(i,N)cin>>xy[i].first>>xy[i].second;
pair<ll,ll> base=mp(0,0);
sort(all(xy),[&](pair<ll,ll> n1,pair<ll,ll> n2){return argument_compare(n1,n2,base);});
vector<pair<ll,ll> > yneg,zeros,ypos;
rep(i,N){
      if(xy[i].second<0)yneg.push_back(xy[i]);
      else if(xy[i].first==0&&xy[i].second==0)zeros.push_back(xy[i]);
        else ypos.push_back(xy[i]);
}
vector<pair<ll,ll> >nxy;
rep(i,yneg.size())nxy.push_back(yneg[i]);
rep(i,zeros.size())nxy.push_back(zeros[i]);
rep(i,ypos.size())nxy.push_back(ypos[i]);
rep(i,N)cout<<nxy[i].first<<" "<<nxy[i].second<<endl;
}