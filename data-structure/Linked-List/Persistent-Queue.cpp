#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)


template<class T>
struct Persistent_Queue{
    struct qnode{
        T key;
        qnode* next;
        qnode(T key_,qnode* next_):key(key_),next(next_){}
    };
    pair<qnode*,qnode*> q;
    int lsize,rsize;
    Persistent_Queue ():q(make_pair(nullptr,nullptr)),lsize(0),rsize(0){}
    Persistent_Queue (pair<qnode*,qnode*> p):q(p){}
    Persistent_Queue* push(T key){
        Persistent_Queue* nq;
        if(lsize==0){
        nq=new Persistent_Queue(make_pair(new qnode(key,q.first),q.second));
        nq->lsize=1;
        nq->rsize=rsize;
        }
        else{
        nq=new Persistent_Queue(make_pair(q.first,new qnode(key,q.second)));
        nq->lsize=lsize;
        nq->rsize=rsize+1;
        }
        return nq;
    }
    Persistent_Queue* pop(){
        Persistent_Queue* nq=new Persistent_Queue(*this);
        if(lsize==1){
            nq->q=make_pair(reverse(q.second),nullptr);
            nq->lsize=rsize;
            nq->rsize=0;
        }
        else{
            nq->q=make_pair(q.first->next,q.second);
            nq->lsize=lsize-1;
            nq->rsize=rsize;
            //nq->q.first=q.first->next;
            //nq->q.second=q.second;
        }
        return nq;
    }
    T top(){
        return q.first->key;
    }

    private:
    qnode* reverse(qnode *q_){
        qnode *res=nullptr;
        while(q_!=nullptr){
            res=new qnode(q_->key,res);
            q_=q_->next;
        }
        return res; 
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

Persistent_Queue<int>* emp=new Persistent_Queue<int>();
vector<Persistent_Queue<int>*> lst;
int Q;cin>>Q;
int c,t,x;
vector<int> ans;
rep(i,Q){
cin>>c>>t;

if(c==0){
    cin>>x;
    if(t==-1){

        lst.push_back(emp->push(x));
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