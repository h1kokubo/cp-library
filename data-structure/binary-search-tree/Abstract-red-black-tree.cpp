#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

template<class T,bool(*f)(T,T),T (*op)(T,T),T (*e)()>
class RBT{
    struct node{
        T data;
        //追加
        T datasum;
        //追加終了
        node *par,*lch,*rch;
        int col;
        int cnt;
        node():cnt(1){}
    };
    node *root,*dummy;
    //function<bool(T,T)> f;
    int black=0,red=1;
    int count(node* t){return t==dummy? 0:t->cnt;}
    T sum(node *t){return t==dummy? e():t->datasum;}
    void update(node* t){
        if(t!=dummy)t->cnt=count(t->lch)+count(t->rch)+1;
        //追加したいものを追加。(これは和)
        if(t!=dummy)t->datasum=op(op(sum(t->lch),t->data),sum(t->rch));
        
    }

    int lower_bound_id(node*t,T data){
        if(t==dummy)return 0;
        if(f(t->data,data))return count(t->lch)+1+lower_bound_id(t->rch,data);
        //if(!f(t->data,data)&&!f(data,t->data))return count(t->lch);
        return lower_bound_id(t->lch,data);
    }
    node *lower_bound(node*t,T data){
        if(t==dummy)return NULL;
        if(f(t->data,data))return lower_bound(t->rch,data);
        node *q=lower_bound(t->lch,data);
        if(q==NULL)return t;
        return q;
    }
    node *begin(node* t){
        if(t==dummy)return NULL;
        while(t->lch!=dummy)t=t->lch;
        return t;
    }
    node *rbegin(node* t){
        if(t==dummy)return NULL;
        while(t->rch!=dummy)t=t->rch;
        return t;
    }
    void left_rotate(node* t){
            node* tr=t->rch;
            t->rch=tr->lch;
            if(tr->lch!=dummy)tr->lch->par=t;
            tr->lch=t;
            tr->par=t->par;
            if(t->par==dummy)root=tr;
            else if(t->par->lch==t)t->par->lch=tr;
            else t->par->rch=tr;
            t->par=tr;
            update(t);update(tr);
        }
        void right_rotate(node* t){
            node* tl=t->lch;
            t->lch=tl->rch;
            if(tl->rch!=dummy)tl->rch->par=t;
            tl->rch=t;
            tl->par=t->par;
            if(t->par==dummy)root=tl;
            else if(t->par->rch==t)t->par->rch=tl;
            else t->par->lch=tl;
            t->par=tl;
            update(t);update(tl);
        }
    void insert_fixup(node* t){
        
        while(t->par->col==red){
            if(t->par==t->par->par->lch){
                node* tpr=t->par->par->rch;
                if(tpr->col==red){
                    t->par->col=black;
                    tpr->col=black;
                    t->par->par->col=red;
                    update(t);update(t->par);
                    t=t->par->par;
                }
                else{
                    if(t->par->rch==t){
                        t=t->par;
                        left_rotate(t);
                    }
                    t->par->par->col=red;
                    t->par->col=black;
                    right_rotate(t->par->par);
                    
                }
            }
            else{
                node* tpl=t->par->par->lch;
                if(tpl->col==red){
                    t->par->col=black;
                    tpl->col=black;
                    t->par->par->col=red;
                    update(t);update(t->par);
                    t=t->par->par;
                }
                else{
                    if(t->par->lch==t){
                        t=t->par;
                        right_rotate(t);
                    }
                    t->par->par->col=red;
                    t->par->col=black;
                    left_rotate(t->par->par);

                }
            }
        }
        
        root->col=black;
        update_fixup(t);
    }
    void transplant(node* t1,node* t2){
        if(t1->par==dummy)root=t2;
        else if(t1==t1->par->lch)t1->par->lch=t2;
        else t1->par->rch=t2;
        //if(t1->par!=t2)t2->par=t1->par;
        t2->par=t1->par;
    }
    void erase_fixup(node* t){
        update(t);
        while(t!=root&&t->col==black){
            if(t==t->par->lch){
                node* bro=t->par->rch;
                if(bro->col==red){
                    bro->col=black;
                    t->par->col=red;
                    left_rotate(t->par);
                    bro=t->par->rch;
                }
                if(bro->lch->col==black&&bro->rch->col==black){
                    bro->col=red;
                    t=t->par;
                    update(t);
                }
                else{
                    if(bro->rch->col==black){
                        bro->lch->col=black;bro->col=red;
                        right_rotate(bro);
                        bro=t->par->rch;
                    }
                    bro->col=t->par->col;
                    t->par->col=black;
                    bro->rch->col=black;
                    left_rotate(t->par);
                    update_fixup(t);
                    t=root;
                    
                }
            }
            else{
                node* bro=t->par->lch;
                if(bro->col==red){
                    bro->col=black;
                    t->par->col=red;
                    right_rotate(t->par);
                    bro=t->par->lch;
                }
                if(bro->lch->col==black && bro->rch->col==black){
                    bro->col=red;
                    t=t->par;
                    update(t);
                    
                }
                else{
                    if(bro->lch->col==black){
                        bro->rch->col=black;bro->col=red;
                        left_rotate(bro);
                        bro=t->par->lch;

                    }
                    bro->col=t->par->col;
                    t->par->col=black;
                    bro->lch->col=black;
                    right_rotate(t->par);
                    update_fixup(t);
                    t=root;
                    
                }
            }
        }
        t->col=black;
        update_fixup(t);
    }
    void update_fixup(node*t){//dummyを渡さない
        update(t);
        while(t->par!=dummy){
            t=t->par;
            update(t);
    }
    }

    T index_prod(int l,int r,node *t){
        assert(0<=l&&l<r&&r<=count(t));//何もないところで呼び出せない。
        //全範囲を含む場合
        if(l==0&&r==count(t))return t->datasum;
        
        //o.w.
        T res=e();
        int lcnt=count(t->lch);
        if(l<lcnt)res=op(res,index_prod(l,min(r,lcnt),t->lch));
        if(r>lcnt&&l<=lcnt)res=op(res,t->data);
        if(r>lcnt+1)res=op(res,index_prod(max(0,l-lcnt-1),r-lcnt-1,t->rch));
        return res;
    }
    public:
        int count(){return count(root);}
        RBT(/*function<bool(T,T)> f_*/)/*:f(f_)*/{
            dummy=new node();
            root=dummy;
            dummy->col=black;dummy->par=nullptr;dummy->lch=nullptr;dummy->rch=nullptr;}
        bool empty(){return root==dummy;}
        int size(){return count(root);}
        node* access(int index){
            assert(0<=index&&index<size());
            node *t=root;
            int nowindex;
            while(1){
                nowindex=count(t->lch);
                if(index==nowindex)return t;
                if(nowindex>index)t=t->lch;
                else{
                    index-=nowindex;
                    t=t->rch;
                }
            }
        }
        int get_node_index(node* t){
            assert(t!=dummy);
            int nowindex=count(t->lch);
            while(t->par!=dummy){
                if(t==t->par->rch)nowindex+=count(t->par->lch);
                t=t->par;
            }
            return nowindex;
        }
        int lower_bound_id(T data){
            return lower_bound_id(root,data);
        }
        node *lower_bound(T data){
            return lower_bound(root,data);
        }
        node *search(T data){
            node *t=root;
            while(t!=dummy){
                if(!f(t->data,data)&&!f(data,t->data)){ return t;}
                if(f(data,t->data))t=t->lch;
                else t=t->rch;
            }
            
            return NULL;
        }
        node *begin(){
            return begin(root);
        } 
        node *rbegin(){
            return rbegin(root);
        }
        node *successor(node *t){
            if(t->rch!=dummy)return begin(t->rch);
            while(t->par!=dummy&&t->par->rch==t)t=t->par;
            if(t->par!=dummy)return t->par;
            return NULL;
        }
        node *predecessor(node *t){
            if(t->lch!=dummy)return rbegin(t->lch);
            while(t->par!=dummy&&t->par->lch==t)t=t->par;
            if(t->par!=dummy)return t->par;
            return NULL;
        }
        
        void insert(T data){
            node *nowpar=dummy,*now=root;
            while(now!=dummy){
                nowpar=now;
                if(f(data,now->data))now=now->lch;
                else now=now->rch;
            }
            
            node* q=new node();
            q->data=data;
            q->col=red;
            q->lch=q->rch=dummy;
            q->par=nowpar;
            if(nowpar==dummy)root=q;
            else if(f(data,nowpar->data))nowpar->lch=q;
            else nowpar->rch=q;
            update(q);
            
            insert_fixup(q);
        }
        void unique_insert(T data){
            node *nowpar=dummy,*now=root;
            while(now!=dummy){
                nowpar=now;
                if(!f(data,now->data)&&!f(now->data,data)){
                    now->data=data;
                    update(now);
                    return;
                }
                else if(f(data,now->data))now=now->lch;
                else now=now->rch;
            }
            node* q=new node();
            q->data=data;
            q->col=red;
            q->lch=q->rch=dummy;
            q->par=nowpar;
            if(nowpar==dummy)root=q;
            else if(f(data,nowpar->data))nowpar->lch=q;
            else nowpar->rch=q;
            update(q);
            insert_fixup(q);
        }
        void erase(T data){
            node* q=search(data);
            if(q!=NULL)erase(q);
        }
        void erase(node* t){
            node* alt1=t,*alt2;
            int origin_col=alt1->col;
            if(t->lch==dummy){
                /***if(t->rch==dummy){
                    
                    if(t->par==dummy){root=dummy;delete t;return;}
                    else if(t->par->lch==t)t->par->lch=dummy;
                    else t->par->rch=dummy;
                    //alt2=t->par;
                    p=t->par;
                }
                else{
                    ***/
                alt2=t->rch;
                transplant(t,alt2);
                /***}***/
                //if(t->rch!=dummy)update(t->rch);
                //if(alt2==dummy&&alt1->par!=dummy)alt2=alt2->par;
            }
            else if(t->rch==dummy){
                alt2=t->lch;
                transplant(t,alt2);
            }
            else{
                alt1=begin(t->rch);
                origin_col=alt1->col;
                alt2=alt1->rch;
                if(alt1->par==t){
                    /***if(alt2!=dummy)***/alt2->par=alt1;
                    /***else p=t;***/
                }
                else{
                    transplant(alt1,alt2);
                    alt1->rch=t->rch;
                    alt1->rch->par=alt1;

                }
                transplant(t,alt1);
                alt1->lch=t->lch;
                alt1->lch->par=alt1;
                alt1->col=t->col;
            }
            delete t;
            if(origin_col==black)erase_fixup(alt2);
            else{
                update_fixup(alt2);
            }
            
            


        }
        T index_prod(int l,int r){//昇順ソートされた状態で、[l,r)番目の範囲
        //何もないときはeを返す。
        if(root==nullptr||root->cnt<=l||r<=0)return e();
        assert(l>=0&&l<r&&r<=root->cnt);
        
        return index_prod(l,r,root);
        }
        T val_prod(T lv,T rv){//fの意味での順序があるとき、[lv,rv)の範囲でop演算
            //li=min{i|lv<=data[i]},ri={min{i|rv+eps<=data[i]},空の時 root->cnt}
            assert(f(lv,rv));
            int li=lower_bound_id(lv),ri=lower_bound_id(rv);
            return index_prod(li,ri);
        }
        int range_cnt(T lv,T rv){//[lv,rv)に属する数
            assert(f(lv,rv));
            int li=lower_bound_id(lv),ri=lower_bound_id(rv);
            return ri-li;
        }

        
};



void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
/*
void Main(){
    
    RBT<int> rbt([](int n1,int n2){return n1<n2;});
    rbt.insert(3);
    rbt.insert(9);
    rbt.insert(7);
    rbt.insert(21);
    rbt.insert(12);
    rbt.insert(20);
    rbt.insert(11);    
    rbt.insert(123);
    
    rbt.erase(7);
    rbt.erase(12);
    rbt.erase(123);
    rbt.erase(11);
    cout<<rbt.count()<<endl;
    ***/
   /**
   //verify ABC195 D
   int N,M,Q;
   cin>>N>>M>>Q;
   pair<int,int> WV[N];
   rep(i,N)cin>>WV[i].first>>WV[i].second;
   sort(WV,WV+N,[&](pair<int,int> p1,pair<int,int> p2){return p1.second>p2.second;});
   int X[M];rep(i,M)cin>>X[i];
   int ans[Q];
   rep(i,Q){
       ans[i]=0;
       int L,R;
       cin>>L>>R;
       L--;
       RBT<int> rbt([](int n1,int n2){return n1<n2;});
        rep(j,L)rbt.insert(X[j]);
        rep2(j,R,M)rbt.insert(X[j]);
        rep(j,N){
            //cout<<i<<" "<<j<<endl;
            auto res=rbt.lower_bound(WV[j].first);
            if(res!=NULL){
                rbt.erase(res);
                ans[i]+=WV[j].second;
            }
        }
        
   }
   rep(i,Q)cout<<ans[i]<<endl;
   */
   /*
  //Library-Checker Associate Array
  int Q;
  cin>>Q;
  RBT<pair<ll,ll>> rbt([](pair<ll,ll> n1,pair<ll,ll> n2){return n1.first<n2.first;});
  vector<ll> ans;
  int t;
  ll k,v;
  rep(i,Q){
      cin>>t;
      if(t==0){
          cin>>k>>v;
        rbt.unique_insert({k,v});
      }
      else{
          cin>>k;
            auto res=rbt.search({k,0});
            if(res==NULL){
                ans.push_back(0);
            }
            else{
                ans.push_back(res->data.second);
            }

      }
  }
  rep(i,ans.size())cout<<ans[i]<<endl;
  
  
  //verify HHKB2020 C
  int N;
  cin>>N;
  int ans[N];
  RBT<int> rbt([](int n1,int n2){return n1<n2;});
    for(int i=0;i<=200000;++i)rbt.insert(i);
    int p;
    rep(i,N){
        cin>>p;
        rbt.erase(p);
        ans[i]=rbt.begin()->data;
    }
    rep(i,N)cout<<ans[i]<<endl;
    
}
*/
/*
//verify Sliding Minimum https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_D
bool comp(int n1,int n2){return n1<n2;}
int op(int n1,int n2){return n1+n2;}
int e(){return 0;}
void Main(){
    int N,L;cin>>N>>L;
    vector<int> a(N);rep(i,N)cin>>a[i];
    vector<int> ans;
    RBT<int,comp,op,e> rb;
    rep(i,L)rb.insert(a[i]);
    ans.push_back(rb.begin()->data);
    rep(i,N-L){
        rb.erase(a[i]);
        rb.insert(a[i+L]);
        ans.push_back(rb.begin()->data);
    }
    rep(i,N-L+1){
        if(i)cout<<" ";
        cout<<ans[i];
    }
    cout<<endl;
}
*/
/*
const int INF=1e9+1e5;
// 第二回日本最強プログラマー学生選手権 F
bool comp(ll n1,ll n2){return n1<n2;}
ll op(ll n1,ll n2){return n1+n2;}
ll e(){return 0;}
void Main(){
     
    int N,M,Q;cin>>N>>M>>Q;
    RBT<ll,comp,op,e> ra,rb;
    vector<ll> a(N),b(M); 
    rep(i,N){
        ra.insert(0);
    }
    rep(i,M){
        rb.insert(0);
    }
    vector<ll> ans(Q);
    ll now=0;
    rep(i,Q){
        int T,X;cin>>T>>X;X--;
        ll Y;cin>>Y;
        if(T==1){
            ra.erase(a[X]);
            now-=rb.lower_bound_id(a[X])*a[X]+rb.val_prod(a[X],INF);
            a[X]=Y;
            ra.insert(Y);
            now+=rb.lower_bound_id(a[X])*a[X]+rb.val_prod(a[X],INF);
        }
        else{
            rb.erase(b[X]);
            now-=ra.lower_bound_id(b[X])*b[X]+ra.val_prod(b[X],INF);
            
            b[X]=Y;
            rb.insert(Y);
            now+=ra.lower_bound_id(b[X])*b[X]+ra.val_prod(b[X],INF);
            
        }
        ans[i]=now;
    }
    rep(i,Q)cout<<ans[i]<<endl;
    
    
}
*/
// range_cnt verify https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/4/DPL_4_B
int popcnt(int x){return __builtin_popcount(x);}

bool comp(ll n1,ll n2){return n1<n2;}
ll op(ll n1,ll n2){return n1+n2;}
ll e(){return 0;}
void Main(){
    int N,K;cin>>N>>K;
    ll L,R;cin>>L>>R;
    vector<ll> a(N);rep(i,N)cin>>a[i];
    int N2=N/2;
    map<pair<int,ll>,ll> m1;
    vector<RBT<ll,comp,op,e>> rbv(N+1);
    rep(bit,1<<N2){
        ll sum=0;
        for(int i=0;i<N2;++i)if((bit>>i)&1)sum+=a[i];
        m1[make_pair(popcnt(bit),sum)]++;
    }
    rep(bit,1<<N-N2){
        ll sum=0;
        for(int i=0;i<N-N2;++i)if((bit>>i)&1)sum+=a[N2+i];
        rbv[popcnt(bit)].insert(sum);
    }
    ll ans=0;
    for(auto &p:m1){
        if(p.first.first<=K)ans+=p.second*rbv[K-p.first.first].range_cnt(L-p.first.second,R+1-p.first.second);
    }
    cout<<ans<<endl;
}