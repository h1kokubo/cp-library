#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template<typename S,S(*op)(S,S),S(*e)()>
struct Persistent_Segment_Tree{
    struct snode{
        S sum;
        snode *lch,*rch;
        snode():sum(e()){}
        snode(S sum_,snode* lch,snode* rch):sum(sum_),lch(lch),rch(rch){}
    };
    snode* root;
    int sz,bsize;
    Persistent_Segment_Tree(snode* r,int size,int bsize):root(r),sz(size),bsize(bsize){}
    Persistent_Segment_Tree(vector<S> v){
        sz=v.size();
        bsize=0;
        while((1<<bsize)<sz+31)++bsize;
        int lsize=1<<bsize;
        vector<snode*> table(2*lsize-1,new snode());
        for(int i=0;i<sz;++i)table[lsize-1+i]=new snode(v[i],nullptr,nullptr);
        for(int i=lsize-2;i>=0;--i){
            //cout<<"No"<<endl;
            table[i]=new snode(op(table[2*i+1]->sum,table[2*i+2]->sum),table[2*i+1],table[2*i+2]);
        }
        root=table[0];
    }   
    S get(int index){
        assert(0<=index&&index<sz);
        return get(root,index,bsize-1);
    }
    Persistent_Segment_Tree* set(int index,S key){
        assert(0<=index&&index<sz);
        return new Persistent_Segment_Tree(set(root,index,bsize-1,key),sz,bsize);
    }
    S prod(int left,int right){
        if(left==right)return e();
        assert(0<=left&&left<right&&right<=sz);
        return prod(root,left,right,0,1<<bsize);
    }
    private:
    S get(snode* t,int index,int bi){
        if(bi==-1)return t->sum;
        else if((index>>bi)&1){
            return get(t->rch,index,bi-1);
        }
        else{
            return get(t->lch,index,bi-1);
        }
    }
    snode* set(snode* t,int index,int bi,S key){
        if(bi==-1){
            return new snode(key,nullptr,nullptr);
        }
        else if((index>>bi)&1){
            snode* resr=set(t->rch,index,bi-1,key);
            return new snode(op(t->lch->sum,resr->sum),t->lch,resr);
        }
        else{
            snode* resl=set(t->lch,index,bi-1,key);
            return new snode(op(resl->sum,t->rch->sum),resl,t->rch);
        }
    }
    S prod(snode* t,int left,int right,int l,int r){
        if(right<=l||left>=r)return e();
        else if(left<=l&&r<=right)return t->sum;
        else{
            return op(prod(t->lch,left,right,l,(l+r)/2),prod(t->rch,left,right,(l+r)/2,r));
        }
    }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


//verify Library-Checker Rectangle Sum
#define Uniq(a) sort(all(a));a.erase(unique(all(a)),end(a))

ll op(ll n1,ll n2){return n1+n2;}
ll e(){return 0;}

struct Point{
    int x,y;ll w;
};

void Main(){
    int N,Q;
    cin>>N>>Q;
    int x,y;ll w;
    vector<Point> lst;
    vector<int> xlst,ylst;
    rep(i,N){
        cin>>x>>y>>w;
        lst.push_back(Point{x,y,w});
        xlst.push_back(x);
        ylst.push_back(y);
    }
    Uniq(xlst);
    map<int,int> mx;
    rep(i,xlst.size())mx[xlst[i]]=i;
    sort(all(ylst));
    sort(all(lst),[](Point p1,Point p2){return p1.y<p2.y;});
    vector<Persistent_Segment_Tree<ll,op,e>*> seglst;
   
    vector<ll> v(xlst.size());
    
    Persistent_Segment_Tree<ll,op,e>* seg=new Persistent_Segment_Tree<ll,op,e>(v);
    rep(i,N){
        if(i)seglst.push_back(seglst.back()->set(mx[lst[i].x],seglst.back()->get(mx[lst[i].x])+lst[i].w));
        else seglst.push_back(seg->set(mx[lst[i].x],lst[i].w));
    }
    vector<ll> ans(Q);
    int l,r,d,u;
    rep(i,Q){
        cin>>l>>d>>r>>u;
        int itl=lower_bound(all(xlst),l)-xlst.begin(),itr=lower_bound(all(xlst),r)-xlst.begin(),itd=lower_bound(all(ylst),d)-ylst.begin(),itu=lower_bound(all(ylst),u)-ylst.begin();
        if(itu==0)ans[i]=0;
        else{
            --itu;
            if(itd>0){
                ans[i]=seglst[itu]->prod(itl,itr)-seglst[itd-1]->prod(itl,itr);
            }
            else{
                ans[i]=seglst[itu]->prod(itl,itr);
            }
        }
    }
    rep(i,Q)cout<<ans[i]<<endl;
}