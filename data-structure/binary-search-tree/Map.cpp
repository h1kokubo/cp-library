#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

template<class S,class T>
class Map{
    struct node{
        S key;
        T val;
        node *par,*lch,*rch;
        int col;
        int cnt;
        node(S k,T v):cnt(1){
            key=k;val=v;
        }
    };
    node *root,*dummy;
    function<bool(S,S)> f;
    int black=0,red=1;
    int count(node* t){return t==dummy? 0:t->cnt;}
    void update(node* t){
        if(t!=dummy)t->cnt=count(t->lch)+count(t->rch)+1;
    }   

    int lower_bound_id(node*t,S key){
        if(t==dummy)return 0;
        if(f(t->key,key))return count(t->lch)+lower_bound_id(t->rch,key);
        else return lower_bound_id(t->lch,key);
    }
    node *lower_bound(node*t,S key){
        if(t==dummy)return NULL;
        if(f(t->key,key))return lower_bound(t->rch,key);
        node *q=lower_bound(t->lch,key);
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
    node *ersearch(S key){
            node *t=root;
            while(t!=dummy){
                if(!f(t->key,key)&&!f(key,t->key)){ return t;}
                if(f(key,t->key))t=t->lch;
                else t=t->rch;
            }
            
            return NULL;
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
    public:
        int count(){return count(root);}
        Map(function<bool(S,S)> f_,S def_S,T def_T):f(f_){
            dummy=new node(def_S,def_T);
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
        int lower_bound_id(S key){
            return lower_bound_id(root,key);
        }
        node *lower_bound(S key){
            return lower_bound(root,key);
        }
        node *search(S key){
            node *t=root;
            while(t!=dummy){
                if(!f(t->key,key)&&!f(key,t->key)){ return t;}
                if(f(key,t->key))t=t->lch;
                else t=t->rch;
            }
            
            return new node(dummy->key,dummy->val);
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
        /*
        void insert(S key){
            node *nowpar=dummy,*now=root;
            while(now!=dummy){
                nowpar=now;
                if(f(data,now->key))now=now->lch;
                else now=now->rch;
            }
            
            node* q=new node();
            q->key=key;
            q->col=red;
            q->lch=q->rch=dummy;
            q->par=nowpar;
            if(nowpar==dummy)root=q;
            else if(f(data,nowpar->data))nowpar->lch=q;
            else nowpar->rch=q;
            
            insert_fixup(q);
        }
        */
        void unique_insert(S key,T val){
            node *nowpar=dummy,*now=root;
            while(now!=dummy){
                nowpar=now;
                if(!f(key,now->key)&&!f(now->key,key)){
                    now->val=val;
                    return;
                }
                else if(f(key,now->key))now=now->lch;
                else now=now->rch;
            }
            node* q=new node(key,val);
            q->col=red;
            q->lch=q->rch=dummy;
            q->par=nowpar;
            if(nowpar==dummy)root=q;
            else if(f(key,nowpar->key))nowpar->lch=q;
            else nowpar->rch=q;
            insert_fixup(q);
        }
        
        void erase(S key){
            node* q=ersearch(key);
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

        
};


void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

/*
void Main(){
    //verify ABC177F
    int H,W;
    cin>>H>>W;
    pair<int,int>AB[H];
    rep(i,H){
        cin>>AB[i].first>>AB[i].second;
        AB[i].first--;
    }
    Map<int,int> m([](int n1,int n2){return n1<n2;},0,0);
    rep(i,W)m.unique_insert(i,i);
    multiset<int> ms;
    rep(i,W)ms.insert(0);
    int ans[H];
    
    rep(i,H){
        
        auto p=m.lower_bound(AB[i].first);
        int max_=-1;
        while(p!=NULL&&p->key<=AB[i].second){
            auto np=m.successor(p);
            max_=max(max_,p->val);
            ms.erase(ms.find(p->key-p->val));
            m.erase(p);
            p=np;
        }
        if(max_!=-1){
            if(AB[i].second!=W){
            m.unique_insert(AB[i].second,max_);
            ms.insert(AB[i].second-max_);
            }
            
        }
        if(m.size()==0)ans[i]=-1;
        else ans[i]=*ms.begin()+i+1;
    }
    rep(i,H)cout<<ans[i]<<endl;
}
*/
void Main(){
    //verify Library-Checker Associate-Array
    
    Map<ll,ll> m([](ll n1,ll n2){return n1<n2;},0,0);
    int Q;
    cin>>Q;
    int t;
    ll k,v;
    vector<ll> ans;
    rep(i,Q){
        cin>>t;
        if(t==0){
            cin>>k>>v;
            m.unique_insert(k,v);
        }
        else{
            cin>>k;
            ans.push_back(m.search(k)->val);

        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}