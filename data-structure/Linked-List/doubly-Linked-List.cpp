#include <bits/stdc++.h>
using namespace std;

template<class T>
class Doubly_Linked_List{
    struct node{
        T val;
        node *next,*prev;
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
            node *y=x->next;
            delete x;
            return y;
        }
        node *z=erase(x->next,v);
        x->next=z;
        z->prev=x;
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
            q->prev=NULL;
            head=q;
        }
        void erase(T v){
            head=erase(head,v);
        }
};

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    Doubly_Linked_List<int> dlink;
    dlink.insert(3);
    dlink.insert(4);
    dlink.insert(2);
    cout<<dlink.find(4)->val<<endl;
    dlink.erase(4);
    cout<<dlink.find(4)<<endl;
}