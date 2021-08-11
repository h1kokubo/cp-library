#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)

template<typename T>//INF: 取りえない値、葉でないことの判定
struct Persistent_Array{
    struct anode{
        T key;
        anode *lch,*rch;
        anode():lch(nullptr),rch(nullptr){}
        anode(T key_):key(key_),lch(nullptr),rch(nullptr){};
        anode(anode* lch_,anode* rch_):lch(lch_),rch(rch_){}
        
    };
    anode* root;
    int bsize,sz;
    Persistent_Array(anode* t,int bsize,int sz):root(t),bsize(bsize),sz(sz){}
    Persistent_Array(vector<T> &A){
        sz=A.size();bsize=0;
        while((1<<bsize)<sz+31)++bsize;
        int lsize=1<<bsize;
        vector<anode*> lst(2*lsize-1);
        for(int i=0;i<sz;++i)lst[lsize-1+i]=new anode(A[i]);
        for(int i=lsize-2;i>=0;--i)lst[i]=new anode(lst[2*i+1],lst[2*i+2]);
        root=lst[0];
    }
    T get(int index){
        return get(root,index,bsize-1);
    }
    Persistent_Array* set(int index,T key){
        Persistent_Array* res=new Persistent_Array(set(root,index,bsize-1,key),bsize,sz);
        return res;
    }
    void print_array(){
        int cnt=0;
        print_array(root,bsize-1,cnt);
        cout<<endl;
    }
    private:
    T get(anode* t,int index,int bi){
        if(bi==-1){
            return t->key;
        }
        else if((index>>bi)&1){
            return get(t->rch,index,bi-1);
        }
        else{
            return get(t->lch,index,bi-1);
        }
    }
    anode* set(anode* t,int index,int bi,T key){
        if(bi==-1){
            return new anode(key);
        }
        else if((index>>bi)&1){
            return new anode(t->lch,set(t->rch,index,bi-1,key));
        }
        else{
            return new anode(set(t->lch,index,bi-1,key),t->rch);
        }
    }
    void print_array(anode* t,int bi,int& cnt){
        if(bi==-1){
            ++cnt;
            cout<<t->key<<" ";
        }
        else{
            print_array(t->lch,bi-1,cnt);
            if(cnt>=sz)return;
            print_array(t->rch,bi-1,cnt);
        }
    }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


/*
void Main(){
    int n,q;cin>>n>>q;
    vector<int> ans;
    vector<int> array(n);
    rep(i,n)cin>>array[i];
    
    Persistent_Array<int>* pa=new Persistent_Array<int>(array);
    pa->print_array();
    int c,t,x,y;
    vector<Persistent_Array<int>*> lst;
    
    
    rep(i,q){
        cin>>c>>t>>x;
        if(c==0){
            cin>>y;
            if(t==-1){
                lst.push_back(pa->set(x,y));
            }
            else{
                lst.push_back(lst[t]->set(x,y));
            }
        }
        else{
            if(t==-1){
                lst.push_back(pa);
            }
            else{
                lst.push_back(lst[t]);
            }
            ans.push_back(lst.back()->get(x));
        }
        
        lst.back()->print_array();
        
    }
    rep(i,ans.size())cout<<ans[i]<<endl;

}
*/
//verify Library-Checker Persistent Queue
void Main(){

int Q;cin>>Q;
vector<int> array(2*Q);
vector<int> head(Q),tail(Q);
Persistent_Array<int>* pa=new Persistent_Array<int>(array);
vector<Persistent_Array<int>*> lst;
int c,t,x;
vector<int> ans;
rep(i,Q){
    cin>>c>>t;
    if(c==0){
        cin>>x;
        if(t==-1){
            lst.push_back(pa->set(0,x));
            head[i]=tail[i]=0;
        }
        else{
            lst.push_back(lst[t]->set(tail[t]+1,x));
            head[i]=head[t];
            tail[i]=tail[t]+1;
        }
    }
    else{
        lst.push_back(lst[t]);
        ans.push_back(lst[t]->get(head[t]));
        head[i]=head[t]+1;
        tail[i]=tail[t];
    }
}
rep(i,ans.size())cout<<ans[i]<<endl;
}