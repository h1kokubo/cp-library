#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

const ll inf=1e18*2;

class RCH_Segment_Tree{
    int N,size;
    vector<ll> max_v,smax_v,max_c;
    vector<ll> min_v,smin_v,min_c;
    vector<ll> sum;
    vector<ll> len,ladd,lval;

    void update_node_max(int k, ll x) {
    sum[k] += (x - max_v[k]) * max_c[k];

    if(max_v[k] == min_v[k]) {
      max_v[k] = min_v[k] = x;
    } else if(max_v[k] == smin_v[k]) {
      max_v[k] = smin_v[k] = x;
    } else {
      max_v[k] = x;
    }

    if(lval[k] != inf && x < lval[k]) {
      lval[k] = x;
    }
  }
  void update_node_min(int k, ll x) {
    sum[k] += (x - min_v[k]) * min_c[k];

    if(max_v[k] == min_v[k]) {
      max_v[k] = min_v[k] = x;
    } else if(smax_v[k] == min_v[k]) {
      min_v[k] = smax_v[k] = x;
    } else {
      min_v[k] = x;
    }

    if(lval[k] != inf && lval[k] < x) {
      lval[k] = x;
    }
  }

  void push(int k) {

    if(N-1 <= k) return;

    if(lval[k] != inf) {
      updateall(2*k+1, lval[k]);
      updateall(2*k+2, lval[k]);
      lval[k] = inf;
      return;
    }

    if(ladd[k] != 0) {
      addall(2*k+1, ladd[k]);
      addall(2*k+2, ladd[k]);
      ladd[k] = 0;
    }

    if(max_v[k] < max_v[2*k+1]) {
      update_node_max(2*k+1, max_v[k]);
    }
    if(min_v[2*k+1] < min_v[k]) {
      update_node_min(2*k+1, min_v[k]);
    }

    if(max_v[k] < max_v[2*k+2]) {
      update_node_max(2*k+2, max_v[k]);
    }
    if(min_v[2*k+2] < min_v[k]) {
      update_node_min(2*k+2, min_v[k]);
    }
  }

  void update(int k) {
    sum[k] = sum[2*k+1] + sum[2*k+2];

    if(max_v[2*k+1] < max_v[2*k+2]) {
      max_v[k] = max_v[2*k+2];
      max_c[k] = max_c[2*k+2];
      smax_v[k] = max(max_v[2*k+1], smax_v[2*k+2]);
    } else if(max_v[2*k+1] > max_v[2*k+2]) {
      max_v[k] = max_v[2*k+1];
      max_c[k] = max_c[2*k+1];
      smax_v[k] = max(smax_v[2*k+1], max_v[2*k+2]);
    } else {
      max_v[k] = max_v[2*k+1];
      max_c[k] = max_c[2*k+1] + max_c[2*k+2];
      smax_v[k] = max(smax_v[2*k+1], smax_v[2*k+2]);
    }

    if(min_v[2*k+1] < min_v[2*k+2]) {
      min_v[k] = min_v[2*k+1];
      min_c[k] = min_c[2*k+1];
      smin_v[k] = min(smin_v[2*k+1], min_v[2*k+2]);
    } else if(min_v[2*k+1] > min_v[2*k+2]) {
      min_v[k] = min_v[2*k+2];
      min_c[k] = min_c[2*k+2];
      smin_v[k] = min(min_v[2*k+1], smin_v[2*k+2]);
    } else {
      min_v[k] = min_v[2*k+1];
      min_c[k] = min_c[2*k+1] + min_c[2*k+2];
      smin_v[k] = min(smin_v[2*k+1], smin_v[2*k+2]);
    }
  }

  void _update_min(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a || max_v[k] <= x) {
      return;
    }
    if(a <= l && r <= b && smax_v[k] < x) {
      update_node_max(k, x);
      return;
    }

    push(k);
    _update_min(x, a, b, 2*k+1, l, (l+r)/2);
    _update_min(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void _update_max(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a || x <= min_v[k]) {
      return;
    }
    if(a <= l && r <= b && x < smin_v[k]) {
      update_node_min(k, x);
      return;
    }

    push(k);
    _update_max(x, a, b, 2*k+1, l, (l+r)/2);
    _update_max(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void addall(int k, ll x) {
    max_v[k] += x;
    if(smax_v[k] != -inf) smax_v[k] += x;
    min_v[k] += x;
    if(smin_v[k] != inf) smin_v[k] += x;

    sum[k] += len[k] * x;
    if(lval[k] != inf) {
      lval[k] += x;
    } else {
      ladd[k] += x;
    }
  }

  void updateall(int k, ll x) {
    max_v[k] = x; smax_v[k] = -inf;
    min_v[k] = x; smin_v[k] = inf;
    max_c[k] = min_c[k] = len[k];

    sum[k] = x * len[k];
    lval[k] = x; ladd[k] = 0;
  }

  void _add_val(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return;
    }
    if(a <= l && r <= b) {
      addall(k, x);
      return;
    }

    push(k);
    _add_val(x, a, b, 2*k+1, l, (l+r)/2);
    _add_val(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void _update_val(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return;
    }
    if(a <= l && r <= b) {
      updateall(k, x);
      return;
    }

    push(k);
    _update_val(x, a, b, 2*k+1, l, (l+r)/2);
    _update_val(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  ll _query_max(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return -inf;
    }
    if(a <= l && r <= b) {
      return max_v[k];
    }
    push(k);
    ll lv = _query_max(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_max(a, b, 2*k+2, (l+r)/2, r);
    return max(lv, rv);
  }

  ll _query_min(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return inf;
    }
    if(a <= l && r <= b) {
      return min_v[k];
    }
    push(k);
    ll lv = _query_min(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_min(a, b, 2*k+2, (l+r)/2, r);
    return min(lv, rv);
  }

  ll _query_sum(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return 0;
    }
    if(a <= l && r <= b) {
      return sum[k];
    }
    push(k);
    ll lv = _query_sum(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_sum(a, b, 2*k+2, (l+r)/2, r);
    return lv + rv;
  }

    public:
        RCH_Segment_Tree(vector<ll> v){
            size=v.size();
            N=1;
            while(N<size)N<<=1;
            ladd=vector<ll>(2*N-1,0);
            lval=vector<ll>(2*N-1,inf);
            
            len=vector<ll>(2*N-1,0);
            for(int i=N-1;i<2*N-1;++i)len[i]=1;
            for(int i=N-2;i>=0;--i)len[i]=len[2*i+1]+len[2*i+2];
            max_v=vector<ll>(2*N-1,-inf);min_v=vector<ll>(2*N-1,inf);sum=vector<ll>(2*N-1,0);
            smax_v=vector<ll>(2*N-1,-inf);smin_v=vector<ll>(2*N-1,inf);
            max_c=vector<ll>(2*N-1,0);min_c=vector<ll>(2*N-1,0);
            for(int i=0;i<size;++i){
                max_v[i+N-1]=min_v[i+N-1]=sum[i+N-1]=v[i];
                max_c[i+N-1]=min_c[i+N-1]=1;
            }
            for(int i=N-2;i>=0;--i)update(i);
        }
        // range minimize query
  void update_min(int a, int b, ll x) {
    _update_min(x, a, b, 0, 0, N);
  }

  // range maximize query
  void update_max(int a, int b, ll x) {
    _update_max(x, a, b, 0, 0, N);
  }

  // range add query
  void add_val(int a, int b, ll x) {
    _add_val(x, a, b, 0, 0, N);
  }

  // range update query
  void update_val(int a, int b, ll x) {
    _update_val(x, a, b, 0, 0, N);
  }

  // range minimum query
  ll query_max(int a, int b) {
    return _query_max(a, b, 0, 0, N);
  }

  // range maximum query
  ll query_min(int a, int b) {
    return _query_min(a, b, 0, 0, N);
  }

  // range sum query
  ll query_sum(int a, int b) {
    return _query_sum(a, b, 0, 0, N);
  }
};

void Main();

int main(){cout<<fixed<<setprecision(15);Main();}

/*
//verify Library-Checker Range Chmin Chmax Add Range Sum
void Main(){
    int N,Q;
    cin>>N>>Q;
    vector<ll> a(N);
    rep(i,N)cin>>a[i];
    RCH_Segment_Tree rch(a);
    int t,l,r;ll b;
    vector<ll> ans;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>l>>r>>b;
            rch.update_min(l,r,b);
        }
        else if(t==1){
            cin>>l>>r>>b;
            rch.update_max(l,r,b);
        }
        else if(t==2){
            cin>>l>>r>>b;
            rch.add_val(l,r,b);
        }
        else{
            cin>>l>>r;
            ans.push_back(rch.query_sum(l,r));
        }

    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}
*/
//verify ABC196 E
void Main(){
  int N;
  cin>>N;
  pair<ll,int> p[N];
  rep(i,N)cin>>p[i].first>>p[i].second;
  int Q;
  cin>>Q;
  vector<ll> x(Q);
  rep(i,Q)cin>>x[i];
  RCH_Segment_Tree rch(x);
  rep(i,N){
    if(p[i].second==1){
      rch.add_val(0,Q,p[i].first);
    }
    else if(p[i].second==2){
      rch.update_max(0,Q,p[i].first);
    }
    else{
      rch.update_min(0,Q,p[i].first);
    }  
  }
  rep(i,Q)cout<<rch.query_sum(i,i+1)<<endl;
}