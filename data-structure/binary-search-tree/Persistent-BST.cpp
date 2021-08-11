#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)

template<typename T>
struct Persistent_BST{
    struct bnode{
        T key;
        bnode *lch,*rch;
        bnode(T key_,bnode* lch_,bnode* rch_):key(key_),lch(lch_),rch(rch_){}
    };
    bnode *root;
    Persistent_BST():root(nullptr){}
    Persistent_BST(bnode* t):root(t){}
    bool empty(){return root==nullptr;}
    Persistent_BST* insert(T key){
        Persistent_BST* res=new Persistent_BST(insert(root,key));
        return res;
    }
    Persistent_BST* erase(T key){
        pair<bool,bnode*> eres=erase(root,key); 
        if(eres.first){
            Persistent_BST* res=new Persistent_BST(eres.second);
            return res;
        }
        else{
            return this;
        }
    }
    bool search(T key){
        return search(root,key);
    }
    void print_lst(){
        print_lst(root);
        cout<<endl;
    }
    private:
    bnode* insert(bnode* t,T key){
        if(t==nullptr)return new bnode(key,nullptr,nullptr);
        else if(key<t->key)return new bnode(t->key,insert(t->lch,key),t->rch);
        else return new bnode(t->key,t->lch,insert(t->rch,key));
    }
    pair<bool,bnode*> erase(bnode* t,T key){
        if(t==nullptr){return make_pair(false,nullptr);}
        else if(t->key==key){
            if(t->rch==nullptr)return make_pair(true,t->lch);
            else{
                pair<bool,pair<T,bnode*>> eres=erasemin(t->rch);
                return make_pair(true,new bnode(eres.second.first,t->lch,eres.second.second));
            }
        }
        else if(key<t->key){
            pair<bool,bnode*> eres=erase(t->lch,key);
            if(eres.first){
                return make_pair(true,new bnode(t->key,eres.second,t->rch));
            }
            else{
                return make_pair(false,t);
            }
        }
        else{
            pair<bool,bnode*> eres=erase(t->rch,key);
            if(eres.first){
                return make_pair(true,new bnode(t->key,t->lch,eres.second));
            }
            else{
                return make_pair(false,t);
            }
        }
    }
    pair<bool,pair<T,bnode*>> erasemin(bnode* t){
        if(t==nullptr)return make_pair(false,make_pair(T(0),nullptr));
        else{
            pair<bool,pair<T,bnode*>> eres=erasemin(t->lch);
            if(eres.first){
                return make_pair(true,make_pair(eres.second.first,new bnode(t->key,eres.second.second,t->rch)));
            }
            else{
                return make_pair(true,make_pair(t->key,nullptr));
            }
        }
    }
    bool search(bnode* t,T key){
        if(t==nullptr)return false;
        else if(key==t->key)return true;
        else if(key<t->key)return search(t->lch,key);
        else return search(t->rch,key);
    }
    void print_lst(bnode* t){
        if(t==nullptr)return;
        print_lst(t->lch);
        cout<<t->key<<" ";
        print_lst(t->rch);
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    Persistent_BST<int>* empty=new Persistent_BST<int>();
    vector<Persistent_BST<int>*> lst;
    int n;cin>>n;
    int c,t,x;
    vector<int> ans;
    rep(i,n){
        cin>>c>>t;
        if(c==0){
            cin>>x;
            if(t==-1){
                lst.push_back(empty->insert(x));
            }
            else{
                lst.push_back(lst[t]->insert(x));
            }
        }
        else if(c==1){
            if(t==-1){
                cin>>x;
                lst.push_back(empty);
                ans.push_back(empty->search(x));
            }
            else{
                cin>>x;
                lst.push_back(lst[t]);
                ans.push_back(lst[t]->search(x));
            }
        }
        else{
            cin>>x;
            lst.push_back(lst[t]->erase(x));
        }
        lst.back()->print_lst();
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}