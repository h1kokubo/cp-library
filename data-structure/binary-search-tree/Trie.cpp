#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define rep2(i,j,n)for(ll i=(j);i<(n);++i)
#define all(v) v.begin(),v.end()

class Trie{
    public:
    struct node{
        bool exist;
        int used;
        node *kids[26];
        node(){for(int i=0;i<26;++i)kids[i]=nullptr;exist=false;used=0;}
    };
    node* root;
    
    Trie():root(nullptr){}
    node* search(string str){
        node* t=root;
        int index=0;
        while(t!=nullptr){
            if(index==str.length())return t;
            t=t->kids[str[index]-'a'];
            ++index;
        }
        return nullptr;
    }
    bool exist(string str){
        node* q=search(str);
        if(q==nullptr||!q->exist)return false;
        else return true;

    }
    void insert(string str){
        if(exist(str))return;
        node* t=root;
        if(t==nullptr)root=t=new node();
        int index=0;
        while(index<str.length()){
            int chrindex=str[index]-'a';
            node* nt=t->kids[chrindex];
            if(nt==nullptr)nt=t->kids[chrindex]=new node();
            t=nt;
            ++t->used;
            ++index;
        }
        t->exist=true;
    }
    void erase(string str){
        node *t=root;
        vector<node*> path;
        int index=-1;
        while(t!=nullptr){
            ++index;
            path.push_back(t);
            if(index==str.length()){
                if(!t->exist)return;
                else break;
            }
            t=t->kids[str[index]-'a'];
            
        }
        if(index!=str.length())return;
        path.back()->exist=false;
        for(int i=str.length();i>0;--i){
            --path[i]->used;
            if(path[i]->used==0)path[i-1]->kids[str[i-1]-'a']=nullptr;
        }

    }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    /*
    Trie tr;
    tr.insert("");
    tr.insert("abc");
    tr.insert("ab");
    cout<<tr.exist("abc")<<endl;
    cout<<tr.exist("ab")<<endl;
    tr.erase("ab");
    cout<<tr.exist("abc")<<endl;
    cout<<tr.exist("ab")<<endl;
    */
   //verify AGC047 B
   int N;
   cin>>N;
   string S[N];
   Trie tr;
   rep(i,N){
       cin>>S[i];
       S[i]=string(S[i].rbegin(),S[i].rend());
        tr.insert(S[i]);
        //cout<<S[i]<<endl;
   }
   /*
   cout<<tr.exist("xyxcba")<<endl;
   cout<<tr.exist("xyc")<<endl;
   cout<<tr.exist("cba")<<endl;
   */
   ll cnt=0;
   rep(i,N){
       vector<Trie::node*> path;
       Trie::node *t=tr.root;
       int index=-1;
       while(t!=nullptr){
           ++index;
           path.push_back(t);
           if(index==S[i].length())break;
           t=t->kids[S[i][index]-'a'];
       }
       //cout<<path.size()<<endl;
       bool chexist[26];
       rep(j,26)chexist[j]=false;
       for(int j=S[i].length();j>=0;--j){
           rep(k,26)if(chexist[k]&&path[j]->kids[k]!=nullptr&&path[j]->kids[k]->exist)cnt++;
           if(j)chexist[S[i][j-1]-'a']=true;
       }
   }
   cout<<cnt-N<<endl;
}