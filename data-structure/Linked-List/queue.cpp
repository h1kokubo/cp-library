#include <bits/stdc++.h>
using namespace std;

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

template<class T>
class Queue{
    struct node{
        T val;
        node *next,*prev;
    };
    node *head=NULL,*tail=NULL;
    public:
        bool empty(){return head==NULL;}
        void push(T v){
            node *q=new node;
            q->val=v;
            q->prev=tail;
            q->next=NULL;
            if(tail!=NULL)tail->next=q;
            tail=q;
            if(head==NULL)head=q;
        }
        T pop(){
            node *q=head;
            head=q->next;
            if(head!=NULL)head->prev=NULL;
            T v=q->val;
            delete q;
            if(head==NULL)tail=NULL;
            return v;
        }
        T front(){
            return head->val;
        }

        
};
void Main(){
    Queue<int> q;
    q.push(3);
    q.push(6);
    q.push(2);
    cout<<q.pop()<<endl;
    cout<<q.pop()<<endl;
}