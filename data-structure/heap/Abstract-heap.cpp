#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()

template<class T,bool (*f)(T,T)>
class Heap{
    vector<T> v;
    int _size;
    int par(int x){return (x-1)>>1;}
    int lch(int x){return (x<<1)+1;}
    int rch(int x){return (x<<1)+2;}
    void downheapify(int i){
        while(1){
        int lchid=lch(i),rchid=rch(i);
        int smallest=i;
        if(lchid<_size&&f(v[lchid],v[smallest]))smallest=lchid;
        if(rchid<_size&&f(v[rchid],v[smallest]))smallest=rchid;
        if(smallest!=i){
            T temp=v[smallest];
            v[smallest]=v[i];
            v[i]=temp;
            i=smallest;
        }
        else break;
        }
    }
    void upheapify(int i){
        T x =v[i];
        while(1){
        if(i==0)break;
        int parid=par(i);
        if(f(x,v[parid])){v[i]=v[parid];}
        else break;
        i=parid;
        }
        v[i]=x;
    }
    public:
    Heap():v(vector<T>()),_size(0){}
    bool empty(){return _size==0;}
    T top(){return v[0];}
    T pop(){
        T res=v[0];
        --_size;
        v[0]=v[_size];
        v.pop_back();
        downheapify(0);
        return res;
    }
    void push(T x){
        v.push_back(x);
        upheapify(_size);
        ++_size;
    }
    vector<T>& get_heap(){return v;}

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

bool sort_judge(vector<int> v){
    rep(i,v.size()-1){
        if(v[i]>v[i+1])return false;
    }
    return true;
}

void Main(){
Heap<int> heap([](int n1,int n2){return n1<n2;});
/***
heap.push(7);
heap.push(3);
heap.push(13);
//cout<<[](int n1,int n2){return n1<n2;}(3,5)<<endl;
cout<<heap.pop()<<endl;
cout<<heap.pop()<<endl;
cout<<heap.pop()<<endl;
***/
random_device rd{};
int N=1000000;
vector<int> v(N);
generate(all(v),ref(rd));
rep(i,N)heap.push(v[i]);
rep(i,N)v[i]=heap.pop();
cout<<v[0]<<" "<<v[1]<<" "<<v[5]<<endl;
cout<<sort_judge(v)<<endl;
}