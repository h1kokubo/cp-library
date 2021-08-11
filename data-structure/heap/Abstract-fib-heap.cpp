#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template<typename T,bool (*comp)(T,T),T INF>
class Fib_Heap{
    struct node{
        int id;
        T key;
        node* par,*left,*right,*child;
        bool mark;
        int degree;
        node(int id_,T key_){
            id=id_,key=key_,par=nullptr,left=nullptr,right=nullptr,child=nullptr,mark=false,degree=0;
        }
    };
    
    node *min_;
    int sz;
    
    void insert_root_lst(node* t){
        node *head=min_;
        //assert(t!=nullptr&&head!=nullptr);
        t->right=head;
        t->left=head->left;
        head->left->right=t;
        head->left=t;
        t->par=nullptr;
    }
    void delete_root_lst(node* t){
        //assert(t!=nullptr);
        if(t->right!=t){
            t->left->right=t->right;
            t->right->left=t->left;
        }
    }
    void delete_child(node* par,node* t){
        //assert(par!=nullptr);
        //assert(t!=nullptr);
        if(t->right!=t){
            t->left->right=t->right;
            t->right->left=t->left;
            par->child=t->right;
        }
        else{
            par->child=nullptr;
        }
        t->mark=false;
        --par->degree;
    }
    void insert_child(node* par,node* t){
        //assert(par!=nullptr&&t!=nullptr);
        if(par->child==nullptr){
            par->child=t;
            t->left=t;
            t->right=t;
            t->par=par;
        }
        else{
            t->left=par->child;
            t->right=par->child->right;
            par->child->right->left=t;
            par->child->right=t;
            t->par=par;
        }
        ++par->degree;
    }
    vector<node*> node_gen(node* t){
        vector<node*> res;
        if(t==nullptr)return res;
        node* now=t;
        while(now){
            res.push_back(now);
            now=now->right;
            if(now==t)break;
        }
        return res;
    }
    void merge_lst(node* h1,node* h2){
        h1->left->right=h2;
        h2->left->right=h1;
        node* t1=h1->left;
        h1->left=h2->left;
        h2->left=t1;
    }
    void consolidate(){
        vector<node*> rootlst=node_gen(min_);
        vector<node*> table;
        for(node* &root : rootlst){
            if(root->par!=nullptr){
                continue;
            }
            int d=root->degree;
            if(table.size()<=d)table.resize(d+1,nullptr);
            while(table[d]!=nullptr&&table[d]!=root){
                node* root2=table[d];
                if(comp(root2->key,root->key)){
                    swap(root,root2);
                }
                delete_root_lst(root2);
                insert_child(root,root2);
                table[d]=nullptr;
                ++d;
                if(table.size()<=d)table.resize(d+1,nullptr);
            }
            table[d]=root;
        }
         
        min_=nullptr;
        for(node* &root:table){
            if(root==nullptr){
                continue;
            }
            if(min_==nullptr){
                min_=root;
            }
            else if(comp(root->key,min_->key)){
                min_=root;
            }
        }
    }
    
    void cascading_cut(node* t){
        node* tp=t->par;
        if(tp!=nullptr){
            if(!t->mark){
                t->mark=true;
            }
            else{
                delete_child(tp,t);
                cascading_cut(tp);
            }
        }
    }

    public:
    Fib_Heap():min_(nullptr),sz(0){}
    bool empty(){return sz==0;}
    int size(){return sz;}
    void push(node* t){
        if(min_==nullptr){
            min_=t;
            t->left=t;
            t->right=t;
        }
        else{
            insert_root_lst(t);
            if(comp(t->key,min_->key)){
                min_=t;
            }
        }
        ++sz;
    }
    vector<node*> make_nodelst(int size){
        vector<node*> res;
        for(int i=0;i<size;++i){
            res.push_back(new node(i,INF));
            
        }
        return res;
    }
    node* top(){assert(min_!=nullptr);return min_;}
    node* pop(){
        assert(min_!=nullptr);
        node* t=min_;
        if(t!=nullptr){
            vector<node*> chlst=node_gen(t->child);
           
            for(node* r:chlst){
                r->par=nullptr;
            }
            if(chlst.size()>0){
                merge_lst(min_,chlst[0]);
            }
            
            delete_root_lst(t);
           
            if(t->right==t){
                min_=nullptr;
            }
            
            else{
                min_=t->right;
                consolidate();
            }
            
            --sz;
        }
        return t;
    }
    void decrease(node* t,T newkey){
        assert(!comp(t->key,newkey));
        t->key=newkey;
        node* tp=t->par;
        if(tp!=nullptr&&comp(t->key,tp->key)){
            delete_child(tp,t);
            insert_root_lst(t);
            cascading_cut(tp);
        }
        if(comp(t->key,min_->key)){
            min_=t;
        }

    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

const ll MINF=5*1e15;
struct Edge{
    int to;
    ll cost;
};
bool comp(ll n1,ll n2){return n1<n2;}

//verify Dijkstra法
void Main(){
    int N,M,s,t;
    cin>>N>>M>>s>>t;
    vector<vector<Edge>> graph(N);
    int a,b;ll c;
    rep(i,M){
        cin>>a>>b>>c;
        graph[a].push_back(Edge{b,c});
    }
    Fib_Heap<ll,comp,MINF> q;
    auto nodelst=q.make_nodelst(N);
    for(auto &t:nodelst)q.push(t);
    vector<int> par(N,-1);
    
    q.decrease(nodelst[s],0);
    while(!q.empty()){
        auto n=q.pop();
       
        for(Edge &e:graph[n->id]){
            if(nodelst[e.to]->key>n->key+e.cost){
                q.decrease(nodelst[e.to],n->key+e.cost);
                par[e.to]=n->id;
            }
        }
    }
    
    if(nodelst[t]->key==MINF){
        cout<<-1<<endl;
        return;
    }
    ll X=nodelst[t]->key;
    vector<int> pathcomp;
    while(par[t]!=-1){
        pathcomp.push_back(t);
        t=par[t];
    }
    pathcomp.push_back(t);
    int Y=pathcomp.size()-1;
    reverse(all(pathcomp));
    cout<<X<<" "<<Y<<endl;
    rep(i,Y)cout<<pathcomp[i]<<" "<<pathcomp[i+1]<<endl;
}
/*
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;}
void Main(){
    int N,M,s,t;
    cin>>N>>M>>s>>t;
    vector<vector<Edge>> graph(N);
    int a,b;ll c;
    rep(i,M){
        cin>>a>>b>>c;
        graph[a].push_back(Edge{b,c});
    }
    Fib_Heap<ll,comp,MINF> q;
    auto nodelst=q.make_nodelst(N);
    for(auto &t:nodelst)q.push(t);
    
    q.decrease(nodelst[s],0);
    while(!q.empty()){
        auto n=q.pop();
       
        for(Edge &e:graph[n->id]){
            if(nodelst[e.to]->key>n->key+e.cost){
                q.decrease(nodelst[e.to],n->key+e.cost);
            
            }
        }
    }
    vector<ll> dist(N);
    rep(i,N)dist[i]=nodelst[i]->key;
    print(dist);
}
*/