#include <bits/stdc++.h>
using namespace std;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

template<class T>
class Deque{
    struct node{
        T val;
        node *next,*prev;
    };
    node *head=NULL,*tail=NULL;
    public:
        bool empty(){return head==NULL;}
        void push_front(T v){
            node *q=new node;
            q->val=v;
            q->tail=head;
            q->prev=NULL;
            if(head!=NULL)head->prev=q;
            head=q;
            if(tail==NULL)tail=q;
        }
        void push_back(T v){
            node *q=new node;
            q->val=v;
            q->prev=tail;
            q->next=NULL;
            if(tail!=NULL)tail->next=q;
            tail=q;
            if(head==NULL)head=q;
        }
        T pop_front(){
            node *q=head;
            head=q->next;
            if(head!=NULL)head->prev=NULL;
            T v=q->val;
            delete q;
            if(head==NULL)tail=NULL;
            return v;
        }
        T pop_back(){
            node *q=tail;
            tail=q->prev;
            if(tail!=NULL)tail->next=NULL;
            T v=q->val;
            delete q;
            if(tail==NULL)head=NULL;
            return v;
        }
        T front(){
            return head->val;
        }
        T back(){
            return tail->val;
        }
        
};