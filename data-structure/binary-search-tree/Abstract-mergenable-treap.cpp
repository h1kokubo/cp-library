#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template<class T>
class Treap{
    struct node{
        T data;
        node *lch,*rch;
        int pri;
        int cnt;
        node(T d,double p):data(d),pri(p),lch(NULL),rch(NULL),cnt(1){}
    };
    
    //自由実装箇所
    node *update(node *t){
        t->cnt=count(t->lch)+count(t->rch)+1;
        //t->data.sum=sum(t->lch)+sum(t->rch)+t->data.val;
        return t;
    }
    int count(node *t){return t==NULL ? 0:t->cnt;}
    //int sum(node *t){return t==NULL ? 0:t->data.sum;}
    //自由実装箇所終了


    node *merge(node *l,node *r){
        if(l==NULL||r==NULL)return l==NULL ? r:l;
        if(l->pri>r->pri){
            l->rch=merge(l->rch,r);
            return update(l);
        }
        else{
            r->lch=merge(l,r->lch);
            return update(r);
        }
    }
    pair<node*,node*> split(node* t,uint k){
        if (t==NULL) return {NULL,NULL};
        if (k<=count(t->lch)){
            pair<node*,node*> s=split(t->lch,k);
            t->lch=s.second;
            return {s.first,update(t)};
        }
        else{
            pair<node*,node*> s=split(t->rch,k-count(t->lch)-1);
            t->rch=s.first;
            return {update(t),s.second};
        }
    }
    pair<node*,node*> split(node* t,T d){//f(t->data,d)なるノードとそれいがいのノードに分割
        if(t==NULL)return {NULL,NULL};
        if(f(d,t->data)){
            pair<node*,node*> s=split(t->lch,d);
            t->lch=s.second;
            return {s.first,update(t)};
        }
        else{
            pair<node*,node*> s=split(t->rch,d);
            t->rch=s.first;
            return {update(t),s.second};
        }

    }
   pair<node*,node*> erasesplit(node* t,T d){//!f(node->data,d)かつ!f(d,node->data)なるnodeを一つ除外してsplit
        if(t==NULL)return {NULL,NULL};
        if(!f(t->data,d)&&!f(d,t->data)){
            return{t->lch,t->rch};
        }
        if(f(d,t->data)){
            pair<node*,node*> s=erasesplit(t->lch,d);
            t->lch=s.second;
            return {s.first,update(t)};
        }
        else{
            pair<node*,node*> s=erasesplit(t->rch,d);
            t->rch=s.first;
            return {update(t),s.second};
        }
    }
    node* lower_bound(node* t,T d){
        if(t==NULL)return NULL;
        if(!f(t.data,d)){
            node* res=lower_bound(t->lch,d);
            if(res==NULL)return t;
            else return res;
        }
        return lower_bound(t->rch,d);
    }
    int lower_bound_id(node* t,T d){
        if(t==NULL)return 0;
        if(!f(t.data,d))return lower_bound_id(t->lch,d);
        else return count(t->lch)+1+lower_bound_id(t->rch,d);
    }
    bool find(node* t,T d){
        if(t==NULL)return false;
        if(!f(d,t->data)&&!f(t->data,d))return true;
        if(f(d,t->data))return find(t->lch,d);
        else return find(t->rch,d);
    }
    node *find_node(node* t,T d){
        if(t==NULL)return NULL;
        if(!f(d,t->data)&&!f(t->data,d))return t;
        if(f(d,t->data))return find_node(t->lch,d);
        else return find_node(t->rch,d);
    }
    T at(node* t,uint x){
        if(t==NULL)return NULL;
        if(x==count(t->lch))return t->data;
        if(x<count(t->lch))return at(t->lch,x);
        else return at(t->rch,x-count(t->lch));
    }
    int get_id(node* t,T d){
        if(t==NULL)return -1;
        if(!f(d,t->data)&&!f(t->data,d))return count(t->lch);
        if(f(d,t->data))return get_id(t->lch,d);
        else return get_id(t->rch,d);
    }

    public:
    node *root;
    function<bool(T,T)> f;
    Treap(function<bool(T,T)> f_):root(NULL),f(f_){}
    
    
    //自由実装箇所
    int count(){return count(root);}
    int sum(){return sum(root);}
    //自由実装箇所終了
    
    
    friend Treap& merge(Treap& lhs,Treap& rhs){
        Treap tr;
        tr.root=merge(lhs.root,rhs.root);
    }
    pair<Treap&,Treap&> split(Treap& t,int k){//[0,k),[k,n)で切る
        pair<node*,node*> res=split(t.root,k);
        Treap tr1,tr2;
        tr1.root=res.first;tr2.root=res.second;
        return {tr1,tr2};
    }
    node* lower_bound(T d){//!f(node.data,d)が真となる最も左のノードを返す。
        return lower_bound(root,d);   
    }
    uint lower_bound_id(T d){//!f(node.data,d)が真となる最も左のノードのindexを返す。なければ全ノード数(=count(root))になる。
        return lower_bound_id(root,d);
    }
    bool find(T d){
        return find(root,d);
    }

    node *find_node(T d){

        return find_node(root,d);
    }
    int get_id(T d){
        return get_id(root,d);
    }
    void insert(T d){
        node* q=new node(d,rand());
        pair<node*,node*> p=split(root,d);
        root=merge(merge(p.first,q),p.second);
    }
    void unique_insert(T d){
        node* q=find_node(root,d);
        if(q==NULL)insert(d);
        else q->data=d;
    }
    T erase(T d){
        int id=get_id(d);
        return erase((uint)id);
    }
    T erase(uint x){
        pair<node*,node*> p=split(root,x);
        pair<node*,node*> p2=split(p.second,1);
        root=merge(p.first,p2.second);
        return p2.first->data;
    }
    T at(uint x){
        return at(root,x);
    }
    T begin(){
        return at(0);
    }
    T rbegin(){
        return at(count()-1);
    }
};

//データ構造体
struct D{
    //int key;
    int val;
    //int sum;
    D(/***int k,***/int v):/***key(k),***/val(v)/***,sum(v)***/{}
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

bool sort_judge(vector<int> v){
    rep(i,v.size()-1){
        if(v[i]>v[i+1])return false;
    }
    return true;
}

void Main(){
    /***
    Treap<D> tr([](D n1,D n2){return n1.val<n2.val;});
    tr.insert(D(3));
    tr.insert(D(5));
    tr.insert(D(7));
    cout<<tr.find(5)<<endl;
    tr.erase(5);
    cout<<tr.find(5)<<endl;
    ***/
    
    Treap<D> tr([](D n1,D n2){return n1.val<n2.val;});
    random_device rd{};
    int N=1000000;
    vector<int> v(N);
    generate(all(v),ref(rd));
    rep(i,N)tr.insert(D(v[i]));
    rep(i,N)v[i]=tr.erase(0).val;
    cout<<sort_judge(v)<<endl;
    
   /***
   Treap<D> tr([](D n1,D n2){return n1.key<n2.key;});
   tr.unique_insert(D(3,5));
   cout<<tr.count()<<endl;
   tr.unique_insert(D(4,8));
   cout<<tr.count()<<endl;
   tr.unique_insert(D(3,9));
   cout<<tr.count()<<endl;
   cout<<tr.find_node(D(3,0))->data.val<<endl;
   tr.erase(D(3,0));
   cout<<tr.erase(0).val<<endl;
   cout<<tr.count()<<endl;
    ***/
   //cout<<tr.find_node(D(3,0))->data.val<<endl;
}