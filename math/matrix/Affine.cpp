#include <bits/stdc++.h>
using namespace std;
namespace AFFINE{
    struct point{
        public:
            long long x,y;
            point(){}
            point(long long x_,long long y_):x(x_),y(y_){}
    };
}
struct Affine{
    private:
        vector<vector<long long>> mt;
    public:
        Affine():mt(vector<vector<long long>>{{1,0,0},{0,1,0},{0,0,1}}){}
        AFFINE::point apply(AFFINE::point p){
            auto res=AFFINE::point(mt[0][0]*p.x+mt[0][1]*p.y+mt[0][2],mt[1][0]*p.x+mt[1][1]*p.y+mt[1][2]);
            return res;
        }
        Affine& rot_left_90(){
            for(int i = 0;i<3;++i){
                long long temp=mt[0][i];
                mt[0][i]=-mt[1][i];
                mt[1][i]=temp;
            }
            return *this;
        }
        Affine& rot_right_90(){
            for(int i=0;i<3;++i){
                long long temp=mt[0][i];
                mt[0][i]=mt[1][i];
                mt[1][i]=-temp;
            }
            return *this;
        }
        Affine& origin_reflec(){
            for(int i=0;i<3;++i){
                mt[0][i]*=-1;
                mt[1][i]*=-1;
            }
            return *this;
        }
        Affine& x_reflec(){
            for(int i=0;i<3;++i){
                mt[1][i]*=-1;
            }
            return *this;
        }
        Affine& y_reflec(){
            for(int i=0;i<3;++i){
                mt[0][i]*=-1;
            }
            return *this;
        }
        Affine& x_b_reflec(long long b){
            mt[0][0]*=-1;
            mt[0][1]*=-1;
            mt[0][2]=-mt[0][2]+2*b;
            return *this;
        }
        Affine& y_b_reflec(long long b){
            mt[1][0]*=-1;
            mt[1][1]*=-1;
            mt[1][2]=-mt[1][2]+2*b;
            return *this;
        }      

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}
//verify ABC189E

#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()
#define elif else if

struct query{
    int index,order;
    query(){}
    query(int index_,int order_):index(index_),order(order_){}
};
struct Op_{
    int code;
    ll p;
    Op_(){}
    Op_(int code_,ll p_):code(code_),p(p_){}
};

void Main(){
  Affine af;
  int N;
  cin>>N;
    vector<AFFINE::point> pv(N);
    rep(i,N){
        ll X,Y;
        cin>>X>>Y;
        pv[i].x=X;pv[i].y=Y;
    }
    int M;
    cin>>M;
    vector<Op_> opv(M);
    rep(i,M){
        int code,p;
        cin>>code;
        if(code==1||code==2){
            p=0;
        }
        else{
            cin>>p;
        }
        opv[i]=Op_(code,p);
    }
    vector<vector<query>> qlst=vector<vector<query>> (M+1);//M番目は操作前
    int Q;
    cin>>Q;
    rep(i,Q){
        int A, B;
        cin>>A>>B;
        A--;B--;
        if(A==-1){
            qlst[M].push_back(query(B,i));
        }
        else{
            qlst[A].push_back(query(B,i));
        }
    }
    vector<AFFINE::point> ans(Q);
    rep(j,qlst[M].size()){
        ans[qlst[M][j].order]=af.apply(pv[qlst[M][j].index]);
    }
    rep(i,M){
        Op_ op=opv[i];
        if(op.code==1){
            af.rot_right_90();
        }
        elif(op.code==2){
            af.rot_left_90();
        }
        elif(op.code==3){
            af.x_b_reflec(op.p);
        }
        else{
            af.y_b_reflec(op.p);
        }
        rep(j,qlst[i].size()){
            ans[qlst[i][j].order]=af.apply(pv[qlst[i][j].index]);
        }
    }
    rep(i,Q){
        cout<<ans[i].x<<" "<<ans[i].y<<endl;
    }

}