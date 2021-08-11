#include <bits/stdc++.h>
using namespace std;


template<typename S,bool(*comp)(S,S)>//compの意味で昇順となる
struct CartesianTree{
    struct node{
        int par,lch,rch;
        S x;
    };
    vector<node*> nodelst;
    CartesianTree(vector<S>&data){
        int min_id=-1;
        for(int i=0;i<data.size();++i){
           
            nodelst.push_back(new node{-1,-1,-1,data[i]});
            int p=i-1;
            int l=-1;
            while(p!=-1&&comp(data[i],data[p])){
                int pp=nodelst[p]->par;
                if(l!=-1){
                    nodelst[l]->par=p;
                    nodelst[p]->rch=l;
                }
                nodelst[p]->par=i;
                nodelst[i]->rch=p;
                l=p;
                p=pp;
            }
            nodelst[i]->par=p;
            if(p!=-1)nodelst[p]->rch=i;
            nodelst[i]->lch=min_id;
            if(min_id==-1||comp(data[i],data[min_id]))min_id=i;
        }
    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

bool comp(int n1,int n2){return n1<n2;}

void Main(){
    int N;cin>>N;
    vector<int> a(N);
    for(int i=0;i<N;++i){
        cin>>a[i];
    }
    CartesianTree<int,comp> ct(a);
    for(int i=0;i<N;++i){
        if(i)cout<<" ";
        if(ct.nodelst[i]->par==-1){
            cout<<i;
        }
        else cout<<ct.nodelst[i]->par;
    }
    cout<<endl;
}