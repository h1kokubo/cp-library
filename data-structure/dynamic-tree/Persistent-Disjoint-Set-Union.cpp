#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)

struct Persistent_DSU{
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
        Persistent_Array(){}
        Persistent_Array(anode* t,int bsize,int sz):root(t),bsize(bsize),sz(sz){}
        Persistent_Array(vector<T> A){
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

    Persistent_Array<int> *par,*rank;

        int size;
        int gnum;
        Persistent_DSU(Persistent_Array<int>* par_,Persistent_Array<int>* rank_,int size_,int gnum_):par(par_),rank(rank_),size(size_),gnum(gnum_){}
        Persistent_DSU(int size_){
            gnum=size=size_;
            vector<int> v(size),r(size);
            for(int i=0;i<size;++i)v[i]=i;
            par=new Persistent_Array<int>(v);
            rank=new Persistent_Array<int>(r);
        }
        int leader(int x){
            int xp=par->get(x);
            if(xp!=x)return leader(xp);
            else return xp;
        }
        bool same(int x,int y){
            return leader(x)==leader(y);
        }
        Persistent_DSU* unite(int x,int y){
            //if(same(x,y))return this;
            //--gnum;
            //node *nx=nodelist[leader(x)],*ny=nodelist[leader(y)];
            int lx=leader(x),ly=leader(y);
            if(lx==ly)return this;
            int rx=rank->get(lx),ry=rank->get(ly);
            if(rx>ry){
                return new Persistent_DSU(par->set(ly,lx),rank,size,gnum-1);
                //ny->leader=leader(x);
            }
            else if(rx<ry){
                return new Persistent_DSU(par->set(lx,ly),rank,size,gnum-1);
                //nx->leader=leader(y);
            }
            else{
                return new Persistent_DSU(par->set(ly,lx),rank->set(x,rx+1),size,gnum-1);
                //ny->leader=leader(x);
                //++nx->rank;
            }
            
        }
        vector<vector<int>> groups(){
            vector<vector<int>> temp(size,vector<int>()),res;
            for(int i=0;i<size;++i)temp[leader(i)].push_back(i);
            for(int i=0;i<size;++i)if(temp[i].size()>0)res.push_back(temp[i]);
            return res;
        }


};
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

//verify Library-Checker Persistent-UnionFind
void Main(){
    int N,Q;cin>>N>>Q;
    Persistent_DSU* pd=new Persistent_DSU(N);
    vector<int> ans;
    vector<Persistent_DSU*> lst;
    int c,k,u,v;
    rep(i,Q){
        cin>>c>>k>>u>>v;
        if(c==0){
            if(k==-1){
                lst.push_back(pd->unite(u,v));
            }
            else{
                lst.push_back(lst[k]->unite(u,v));
            }
        }
        else{
            if(k==-1){
                lst.push_back(pd);
                ans.push_back(lst.back()->same(u,v));
            }
            else{
                lst.push_back(lst[k]);
                ans.push_back(lst.back()->same(u,v));
            }
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
}