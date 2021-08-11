#include <bits/stdc++.h>
using namespace std;
#define endl "\n"


//int memberlist[262144];//二のべき乗が入るように
int memberlist[16777216];
class van_Emde_Boas_Tree{
    using vEB=van_Emde_Boas_Tree;
    int size,bsize,INF,Max,Min;
    int hsize,lsize,lmask;
    vector<van_Emde_Boas_Tree> summary;
    vector<van_Emde_Boas_Tree> cluster;
    
    void empty_insert(int x){
            Max=x;
            Min=x;
        }
    void insert(int x){
        if(Min==INF){
            empty_insert(x);
        }
        else{
            if(x<Min){
                int temp=x;
                x=Min;
                Min=temp;
            }
            if(size>2){
                if(cluster[high(x)].minimum()==INF){
                    cluster[high(x)].empty_insert(low(x));
                    summary[0].insert(high(x));
                }
                else{
                    cluster[high(x)].insert(low(x));
                }
            }
            if(x>Max){
                Max=x;
            }
        }

    }
    void erase(int x){
        if(Min==Max){
            Max=-INF;
            Min=INF;
        }
        else if(size==2){
            if(x==0)Min=1;
            else Max=0;
            Max=Min;
        }
        else{
            if(x==Min){
                int first_cluster=summary[0].minimum();
                x=mergebit(first_cluster,cluster[first_cluster].minimum());
                Min=x;
            }
            cluster[high(x)].erase(low(x));
            if(cluster[high(x)].minimum()==INF){
                summary[0].erase(high(x));
                if(x==Max){
                    int summary_max=summary[0].maximum();
                    if(summary_max==-INF)Max=Min;
                    else Max=mergebit(summary_max,cluster[summary_max].maximum());
                }
            }
            else if(x==Max)Max=mergebit(high(x),cluster[high(x)].maximum());
        }
    }
    public:
        van_Emde_Boas_Tree(){}
        van_Emde_Boas_Tree(int _size,int _INF,int _bsize=-1){//普遍集合 [0,_size)
            if(_bsize==-1){
                _bsize=0;
                int newsize=1;
                while(newsize<_size){
                    newsize<<=1;
                    _bsize++;
                }
                _size=newsize;
                //cout<<_size<<endl;
                //
                for(int i=0;i<_size;++i)memberlist[i]=0;
            }
            size=_size;
            bsize=_bsize;
            
            hsize=bsize/2;
            lsize=bsize-hsize;
            lmask=(1<<lsize)-1;
            
            INF=_INF;
            Max=-INF;
            Min=INF;
            //cout<<size<<" "<<bsize<<" "<<hsize<<" "<<lsize<<" "<<lmask<<" "<<INF<<" "<<Max<<" "<<Min<<endl;
            if(bsize>1){
                summary=vector<van_Emde_Boas_Tree>(1);
                summary[0]=van_Emde_Boas_Tree(1<<hsize,INF,hsize);
                cluster=vector<van_Emde_Boas_Tree>(1<<hsize);
                for(int i=0;i<(1<<hsize);++i)cluster[i]=van_Emde_Boas_Tree(1<<lsize,INF,lsize);
            }
        }
        
        int high(int x){return x>>lsize;}
        int low(int x){return x&lmask;}
        int mergebit(int high,int low){return (high<<lsize)+low;}
        bool member(int x){return memberlist[x]>0;}
        int num(int x){return memberlist[x];}
        void increment(int x,int _num=1){memberlist[x]+=_num;}
        void decrement(int x,int _num=1){assert(num(x)>=_num);memberlist[x]-=_num;}
        int maximum(){return Max;}
        int minimum(){return Min;}
        int successor(int x){
            if(size==2){
                if(x==0&&Max==1)return 1;
                else return -INF;
            }
            else if(Min!=INF&&x<Min)return Min;
            else{
                int max_low=cluster[high(x)].maximum();
                if(max_low!=-INF&&low(x)<max_low){
                    int offset=cluster[high(x)].successor(low(x));
                    return mergebit(high(x),offset);
                }
                else{
                    int succ_cluster=summary[0].successor(high(x));
                    if(succ_cluster==-INF)return -INF;
                    else{
                        int offset=cluster[succ_cluster].minimum();
                        return mergebit(succ_cluster,offset);
                    }
                }
            }
        }
        int predecessor(int x){
            if(size==2){
                if(x==1&&Min==0)return 0;
                else return INF;
            }
            else if(Max!=-INF&&Max<x)return Max;
            else{
                int min_low=cluster[high(x)].minimum();
                if(min_low!=INF&&low(x)>min_low){
                    int offset=cluster[high(x)].predecessor(low(x));
                    return mergebit(high(x),offset);
                }
                else{
                    int pred_cluster=summary[0].predecessor(high(x));
                    if(pred_cluster==INF){
                        if(Min!=INF&&Min<x){
                            return Min;
                        }
                        else return INF;
                    }
                    else{
                        int offset=cluster[pred_cluster].maximum();
                        return mergebit(pred_cluster,offset);
                    }
                }
            }
        }
        
        void insert(int x,int num){
            if(member(x))increment(x,num);
            else{
                increment(x,num);
                insert(x);
            }
        }
        void erase(int x,int num){
            if(!member(x))return;
            decrement(x,min(num,memberlist[x]));
            if(member(x))return;
            else erase(x);
        }
};

const int INF=1e9+1e5;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}


#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)

/*
//verify HHKB2020 C
void Main(){
van_Emde_Boas_Tree v(200001,INF);
rep(x,200001)v.insert(x,1);
int N;cin>>N;
int p;
vector<int> ans(N);
rep(i,N){
    cin>>p;
    v.erase(p,1);
    ans[i]=v.minimum();
}
rep(i,N)cout<<ans[i]<<endl;
}
*/
//verify Library-Checker PredecessorProblem
void Main(){
    int N,Q;cin>>N>>Q;
    string T;
    cin>>T;
    van_Emde_Boas_Tree v(N,INF);
    rep(i,N){
        if(T[i]=='1')v.insert(i,1);
    }
    int c,k;
    vector<int> ans;
    rep(i,Q){
        cin>>c>>k;
        if(c==0){
            if(!v.member(k))v.insert(k,1);
        }
        else if(c==1){
            if(v.member(k))v.erase(k,1);
        }
        else if(c==2){
            ans.push_back(v.member(k));
        }
        else if(c==3){
            if(v.member(k))ans.push_back(k);
            else{
                int x=v.successor(k);
                if(x!=-INF)ans.push_back(x);
                else ans.push_back(-1);
            }

        }
        else{
            if(v.member(k))ans.push_back(k);
            else{
                int x=v.predecessor(k);
                if(x!=INF)ans.push_back(x);
                else ans.push_back(-1);
            }
        }
    }
    rep(i,ans.size())cout<<ans[i]<<endl;

}