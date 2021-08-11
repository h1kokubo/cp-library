#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template<typename T,T INF,int initiate_height=-1> //T:流量、容量の型 ,INF:flow,capの上界, initiate_height: 始点に盛る高さデフォルトはノード数、特殊なグラフでは変更することによってO(V+E)まで計算量が減少
class Relabel_To_Front_Max_Flow{
    class Queue{
        struct node{
            int val;
            node *next,*prev;
        };
        node *head=NULL,*tail=NULL;
        vector<bool> check;
        int sz;
        public:
            Queue(int size):sz(size){
                check=vector<bool>(sz,false);
            }
            bool empty(){return head==NULL;}
            void push(int v){
                if(check[v])return;
                node *q=new node;
                q->val=v;
                q->prev=tail;
                q->next=NULL;
                if(tail!=NULL)tail->next=q;
                tail=q;
                if(head==NULL)head=q;
                check[v]=true;
            }
            int pop(){
                node *q=head;
                head=q->next;
                if(head!=NULL)head->prev=NULL;
                int v=q->val;
                delete q;
                if(head==NULL)tail=NULL;
                check[v]=false;
                return v;
            }
            int front(){
                return head->val;
            }
            void push_front(int v){
                if(check[v])return;
                check[v]=true;
                node *q=new node;
                q->val=v;
                q->next=head;
                q->prev=NULL;
                if(head!=NULL)head->prev=q;
                head=q;
                if(tail==NULL)tail=q;
            }
            
    };
    struct node{
        int index,h;
        T e;
        node(){}
        node(int index):index(index),e(T(0)),h(0){};
        void relabel(){++h;}
        bool is_overflow(){return e>0;}
    };
    struct edge{
        node *v,*nv;
        T flow,cap;
        edge(){}
        edge(node* v,node* nv,T flow,T cap):v(v),nv(nv),flow(flow),cap(cap){}
        bool is_reverse(){return flow==-1;}

        T augument_num(){
            if(is_reverse())return cap;
            else return cap-flow;
        }
        void add_flow(T flow_num){
            if(is_reverse())cap-=flow_num;
            else flow+=flow_num;
        }
        void sub_flow(T flow_num){
            if(is_reverse())cap+=flow_num;
            else flow-=flow_num;
        }
        bool relabelable(){
            if(augument_num()>0&&v->h==1+nv->h)return false;
            else return true;
            
        }
        
        bool pushable(bool is_source=false){return augument_num()>0&&(v->h==1+nv->h||is_source);}
        T push(edge *rev_edge){
            T flow_num=min(augument_num(),v->e);
            add_flow(flow_num);
            rev_edge->sub_flow(flow_num);
            v->e-=flow_num;
            nv->e+=flow_num;
            return flow_num;
        }
    };
    int sz,s,t;
    vector<vector<edge*>> graph;
    vector<node*> nodelst;
    vector<edge*> edgelst;

    vector<int> call_num;
    public:
        Relabel_To_Front_Max_Flow(int size):sz(size){
            graph=vector<vector<edge*>>(sz);
            for(int i=0;i<sz;++i){
                nodelst.push_back(new node(i));
            }
            call_num.assign(sz,0);
        }
        void add_edge(int i,int j,T cap){
            edge* ed=new edge(nodelst[i],nodelst[j],0,cap),*red=new edge(nodelst[j],nodelst[i],-1,0);
            graph[i].push_back(ed);
            graph[i].push_back(red);
            graph[j].push_back(red);
            graph[j].push_back(ed);
            edgelst.push_back(ed);
        }
        T calc_max_flow(int s_,int t_){
            s=s_,t=t_;
            Queue q(sz);
            nodelst[s]->h=sz;
            if(initiate_height!=-1)nodelst[s]->h=initiate_height;
            nodelst[s]->e=INF;
            T s_e=T(0);
            for(int i =0;i<graph[s].size()/2;++i){
                edge *ed=graph[s][2*i],*red=graph[s][2*i+1];
                if(ed->pushable(true)){
                    s_e-=ed->push(red);
                    int nv_index=ed->nv->index;
                    if(nv_index!=t)q.push(nv_index);
                }
            }
            nodelst[s]->e=s_e;
            while(!q.empty()){
                int v_index=q.pop();
                call_num[v_index]++;
                bool judgerelabel=true;
                for(int i=0;i<graph[v_index].size()/2;++i){
                    edge *ed=graph[v_index][2*i];
                    edge *red=graph[v_index][2*i+1];
                    
                    if(ed->pushable()){
                        ed->push(red);
                        int nv_index=ed->nv->index;
                        if(nv_index!=s&&nv_index!=t)q.push(nv_index);
                        
                    }
                    if(!ed->v->is_overflow())break;
                     judgerelabel&=ed->relabelable();                   
                }
                if(judgerelabel&&nodelst[v_index]->is_overflow()){
                    nodelst[v_index]->relabel();
                    q.push_front(v_index);
                }
            }
            return nodelst[t]->e;
        }
        edge* get_edge(int index){return edgelst[index];}
        /*
        vector<int> get_call_num(){return call_num;}
        vector<int> get_height(){
            vector<int> res(sz);
            for(int i=0;i<sz;++i)res[i]=nodelst[i]->h;
            return res;
        }
        */
        vector<edge*> min_cut_edge(){
            vector<bool> is_connected(sz,false);// connected with s ?
            is_connected[s]=true;
            queue<int> q;
            q.push(s);
            while(!q.empty()){
                int v=q.front();
                q.pop();
                for(int i=0;i<graph[v].size()/2;++i){
                    edge *ed=graph[v][2*i];
                    if(ed->augument_num()>0){
                        int nv_index=ed->nv->index;
                        if(!is_connected[nv_index]){
                            is_connected[nv_index]=true;
                            q.push(nv_index);
                        }
                    }
                }
            }
            vector<edge*> res;
            for(int v=0;v<sz;++v){
                if(is_connected[v]){
                    for(int j=0;j<graph[v].size()/2;++j){
                        edge *ed=graph[v][2*j];
                        if(!ed->is_reverse()&&ed->augument_num()==0&&!is_connected[ed->nv->index]){
                            res.push_back(ed);
                        }
                    }
                }
            }
            return res;

        }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
const int INF=2*1e9;
template<typename T> void print(vector<T> &v){for(int i=0;i<v.size();++i){if(i)cout<<" ";cout<<v[i];}cout<<endl;}


void Main(){


int N,M,s,t;cin>>N>>M>>s>>t;
Relabel_To_Front_Max_Flow<int,INF> mf_graph(N);

rep(i,M){
    int a,b,c;cin>>a>>b>>c;
    mf_graph.add_edge(a,b,c);
}
cout<<"max_flow:"<<endl;
cout<<mf_graph.calc_max_flow(s,t)<<endl;
cout<<"max_flow_detail:"<<endl;
rep(i,M){
    auto ed=mf_graph.get_edge(i);
    cout<<ed->v->index<<" -> "<<ed->nv->index<<" flow:"<<ed->flow<<endl;
}
cout<<"min_cut_edge_details"<<endl;
auto cut_edge=mf_graph.min_cut_edge();
for(auto &e:cut_edge){
    cout<<e->v->index<<" -> "<<e->nv->index<<" cap:"<<e->flow<<endl;
}
/*
auto res=mf_graph.get_call_num();
    print(res);
auto res2=mf_graph.get_height();
print(res2);
*/
}

/***
void Main(){
    int L,R,M;cin>>L>>R>>M;
    Relabel_Push_Front_Max_Flow<int,INF,14> mf_graph(L+R+2);
    rep(i,M){
        int a,b;
        cin>>a>>b;
        mf_graph.add_edge(a,b+L,1);
    }
    rep(i,L)mf_graph.add_edge(L+R,i,1);
    rep(i,R)mf_graph.add_edge(i+L,L+R+1,1);
    int K=mf_graph.calc_max_flow(L+R,L+R+1);
    vector<pair<int,int>> ans;
    rep(i,M){
        auto ed=mf_graph.get_edge(i);
        if(ed->flow>0)ans.push_back(make_pair(ed->v->index,ed->nv->index-L));
    }
    cout<<K<<endl;
    rep(i,ans.size()){
        cout<<ans[i].first<<" "<<ans[i].second<<endl;
    }
    /*
    auto res=mf_graph.get_call_num();
    print(res);
    auto res2=mf_graph.get_height();
    print(res2);
    
}
*/
