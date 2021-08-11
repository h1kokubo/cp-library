//Rerooting DP
template<typename S,S(*merge)(S,S),typename T, S(*wrap)(S,T), S(*id)()>//
struct Rerooting{
  vector<vector<S>> lacc,racc;//頂点vの初めの根でない部分のうち、graph[v][nv]の左側、右側の累積(merge)和(nv自体は含まない)
  vector<S> chsum;
  vector<T> data;
  vector<vector<int>> graph;
  vector<S> ans;
  int size;
  Rerooting(vector<vector<int>> &_graph,vector<T> _data):graph(_graph),data(_data),size(_graph.size()){
    lacc=vector<vector<S>>(size);
    racc=vector<vector<S>>(size);
    chsum=vector<S>(size,id());
    ans=vector<S>(size,id());
    int root=0;//まず0を根とする。
    //cout<<"initiate"<<endl;
    init(0,-1);
    //cout<<"initiated"<<endl;
    reroot(0,-1,id());
  }
  S init(int v,int pv){//通常の根付き木DPをしながら各部分木を集める
    S lsum=id();
    int cnt=0;
    vector<S> initmemo;
    for(int nv:graph[v]){
      if(nv==pv)continue;
      lacc[v].push_back(lsum);
      initmemo.push_back(init(nv,v));
      lsum=merge(lsum,initmemo.back());
      cnt++;
    }
    S rsum=id();
    racc[v].resize(cnt);
    for(int i=graph[v].size()-1;i>=0;--i){
      int nv=graph[v][i];
      if(nv==pv)continue;
      cnt--;
      racc[v][cnt]=rsum;
      rsum=merge(rsum,initmemo[cnt]);
    }
    chsum[v]=rsum;
    //cout<<v<<" :"<<rsum<<endl;
    //print(initmemo);
    return wrap(rsum,data[v]);
  }
  void reroot(int v,int pv,S parsum){//根からdfsしつつ全ノードについてansを求める。
    ans[v]=merge(chsum[v],parsum);
    //cout<<v<<": "<<chsum[v]<<" "<<parsum<<" "<<ans[v]<<endl;
    int cnt=0;
    for(int nv:graph[v]){
      if(nv==pv)continue;
      reroot(nv,v,wrap(merge(merge(lacc[v][cnt],racc[v][cnt]),parsum),data[v]));
      cnt++;
    }
  }
  S solve(int v){return ans[v];}

};
ll M;

struct S{
  ll b,w;//bw:部分木の根が黒 w:全面白
  friend ostream &operator<<(ostream &os, const S &n) {
    return cout<<"{ "<<n.b<<","<<n.w<<" }";
  }
  
};
S merge(S n1,S n2){
  return S{(n1.b+n1.w)%M*(n2.b+n2.w)%M,0};
}

S wrap(S n,bool dummy){
  return S{n.b,1};
}

S id(){return S{1,0};}

void Main(){

int N;cin>>N>>M;
vector<vector<int>> graph(N);
rep(i,N-1){
  int x,y;cin>>x>>y;x--;y--;
  graph[x].push_back(y);
  graph[y].push_back(x);
}
vector<bool> dummy(N,false);
Rerooting<S,merge,bool,wrap,id> dp(graph,dummy);
rep(i,N){
  cout<<dp.solve(i).b<<endl;
}

}