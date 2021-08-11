#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template <typename T>bool chmax(T &a, const T& b) {if (a < b) {a = b;return true;}return false;}

bool topological_sort_dfs(int v,vector<vector<int>> &graph,vector<int> &check,vector<int> &res){
  bool judge=true;
  check[v]=0;
  for(int nv:graph[v]){
    if(check[nv]==1)continue;
    if(check[nv]==0){
      return false;
    }
    judge&=topological_sort_dfs(nv,graph,check,res);
  }
  check[v]=1;
  res.push_back(v);
  return judge;
}
pair<bool,vector<int>> topological_sort(vector<vector<int>> &graph){vector<int> check(graph.size(),-1);//-1 未到達 0　途中 1終
vector<int> res;bool judge=true;
for(int v=0;v<graph.size();++v){
  if(check[v]==1)continue;
  judge&=topological_sort_dfs(v,graph,check,res);
}
reverse(res.begin(),res.end());
return {judge,res};
}


void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//verify ABC 139E
int N;
int get(int i,int j){
  if(i<j)return i*N+j;
  else return j*N+i;
}
void Main(){


cin>>N;
int A[N][N-1];
rep(i,N)rep(j,N-1){
  cin>>A[i][j];
  A[i][j]--;
}
vector<vector<int>> graph(N*N);

rep(i,N)rep(j,N-1)if(j){  
  graph[get(i,A[i][j-1])].push_back(get(i,A[i][j]));
}
pair<bool,vector<int>> res=topological_sort(graph);

if(!res.first){
  cout<<-1<<endl;
  return;
}
vector<int> dp(N*N,1);//距離
int ans=0;
rep(i,N*N){
  int v=res.second[i];
  for(int nv:graph[v]){
    if(chmax(dp[nv],dp[v]+1))chmax(ans,dp[nv]);
  }
}
cout<<ans<<endl;
}



