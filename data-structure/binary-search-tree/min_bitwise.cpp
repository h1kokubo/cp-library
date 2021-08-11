#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

class Bit_Trie{
    public:
    struct node{
        bool exist=false;
        int used=0;
        node *zero=nullptr,*one=nullptr;
        node(){}
    };
    node* root;
    int upper;
    Bit_Trie(int upper_):upper(upper_),root(nullptr){}//upper 入力しうるmsb(1-indexed)
    node* search(int x){
        node* t=root;
        int index=0;
        while(t!=nullptr){
            if(index==upper)return t;
            if((x>>(upper-1-index))&1)t=t->one;
            else t=t->zero;
            ++index;
        }
        return nullptr;
    }
    bool exist(int x){
        node* q=search(x);
        if(q==nullptr||!q->exist)return false;
        else return true;

    }
    void insert(int x){
        if(exist(x))return;
        node* t=root;
        if(t==nullptr)root=t=new node();
        int index=0;
        while(index<upper){
            /*
            int chrindex=str[index]-'a';
            node* nt=t->kids[chrindex];
            if(nt==nullptr)nt=t->kids[chrindex]=new node();
            t=nt;
            */
            node* nt;
            if((x>>(upper-1-index))&1)nt=t->one;
            else nt=t->zero;
            if(nt==nullptr){
            if((x>>(upper-1-index))&1)nt=t->one=new node();
            else nt=t->zero=new node();
            }
            t=nt;
            ++t->used;
            ++index;
        }
        t->exist=true;
    }
    void erase(int x){
        node *t=root;
        vector<node*> path;
        int index=-1;
        while(t!=nullptr){
            ++index;
            path.push_back(t);
            if(index==upper){
                if(!t->exist)return;
                else break;
            }
            if((x>>(upper-1-index))&1)t=t->one;
            else t=t->zero;
            
        }
        if(index!=upper)return;
        path.back()->exist=false;
        for(int i=upper;i>0;--i){
            --path[i]->used;
            if(path[i]->used==0){
                if((x>>(upper-i))&1)path[i-1]->one=nullptr;
                else path[i-1]->zero=nullptr;
            }
        }

    }
    int max_xor(int x){
        node *t=root;
        int index=0;
        int ans=0;
        while(index<upper){
            if((x>>(upper-1-index))&1){
                if(t->zero!=nullptr){
                    t=t->zero;
                    ans+=1<<(upper-1-index);
                }
                else t=t->one;

            }
            else{
                if(t->one!=nullptr){
                    t=t->one;
                    ans+=1<<(upper-1-index);
                }
                else t=t->zero;
            }
            index++;
        }
        return ans;
    }
    int min_xor(int x){
        node *t=root;
        int index=0;
        int ans=0;
        while(index<upper){
            if((x>>(upper-1-index))&1){
                if(t->one!=nullptr)t=t->one;
                else{
                    t=t->zero;
                    ans+=1<<(upper-1-index);
                }
            }
            else{
                if(t->zero!=nullptr)t=t->zero;
                else{
                    t=t->one;
                    ans+=1<<(upper-1-index);
                }
            }
            ++index;
        }
        return ans;
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    int Q;
    cin>>Q;
    Bit_Trie bt(31);
    int t,x;
    vector<int> ans;
    rep(i,Q){
        cin>>t>>x;
        if(t==0)bt.insert(x);
        else if(t==1)bt.erase(x);
        else ans.push_back(bt.min_xor(x));
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}