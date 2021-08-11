#include <bits/stdc++.h>
using namespace std;

template<class T>
class Stack{
    struct node{
        T val;
        node *next;
    };
    int sz;
    node *head=NULL;
    public:
        Stack():sz(0){}
        bool empty(){return head==NULL;}
        int size(){return sz;}
        void push(T v){
            ++sz;
            node *q = new node;
            q->val=v;
            q->next=head;
            head=q;
        }
        T top(){
            return head->val;
        }
        T pop(){
            --sz;
            node *q=head;
            T v =q->val;
            head=head->next;
            delete q;
            return v;
        }
};
void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
    Stack<int> st;
    st.push(3);
    st.push(6);
    st.push(2);
    cout<<st.pop()<<endl;
    cout<<st.pop()<<endl;
}