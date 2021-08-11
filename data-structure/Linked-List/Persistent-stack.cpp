#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)

template<typename T>
struct Persistent_Stack{
    struct snode{
        T key;
        snode* next;
        snode(T key_,snode* next_):key(key_),next(next_){}
    };
    snode* head;
    Persistent_Stack():head(nullptr){}
    Persistent_Stack(snode* t):head(t){}
    bool empty(){return head==nullptr;}
    Persistent_Stack* push(T key){
        Persistent_Stack* res=new Persistent_Stack(new snode(key,head));
        return res;
    }
    Persistent_Stack* pop(){
        Persistent_Stack* res=new Persistent_Stack(head->next);
        return res;
    }
    T top(){
        return head->key;
    }
};
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    Persistent_Stack<int>* empty=new Persistent_Stack<int>();
    vector<Persistent_Stack<int>*> lst;
    int n;cin>>n;
    int c,t,x;
    vector<int> ans;
    rep(i,n){
        cin>>c>>t;
        if(c==0){
            cin>>x;
            if(t==-1){
                lst.push_back(empty->push(x));
            }
            else{
                lst.push_back(lst[t]->push(x));
            }
        }
        else{
            
            ans.push_back(lst[t]->top());
            lst.push_back(lst[t]->pop());
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}