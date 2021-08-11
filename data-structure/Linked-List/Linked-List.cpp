#include <bits/stdc++.h>
using namespace std;

template<class T>
class Linked_List{
    struct node{
        T val;
        node *next;
    };
    node *head=NULL;
    int _size=0;
    node *find(node *x,T v){
        if(x==NULL||x->val==v)return x;
        return find(x->next,v);
        
    }
    node *erase(node *x,T v){
        if(x==NULL)return x;
        if(x->val==v){
            _size-=1;
            node *q=x->next;
            delete x;
            return q;
        }
        x->next=erase(x->next,v);
        return x;
    }
    public:
    int size(){return _size;}
    bool empty(){return _size==0;}
    node *find(T v){
        return find(head,v);
    }
    void insert(T v){
        _size+=1;
        node *q=new node;
        q->val=v;
        q->next=head;
        head=q;
    }
    void erase(T v){
        head = erase(head,v);
    }

};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    Linked_List<int> linklst;
    linklst.insert(3);
    linklst.insert(4);
    linklst.insert(2);
    cout<<linklst.find(4)->val<<endl;
    linklst.erase(4);
    cout<<linklst.find(4)<<endl;
}