#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long
#define ld long double
#define rep(i,n) for (ll i = 0;i<(n);++i)
#define all(v) v.begin(),v.end()


template<typename T>
class Mergenable_Linked_List{
    struct node{
        T key;
        node* next;
        node(T key_,node* next_=nullptr):key(key_),next(next_){}
    }
    node *head,*tail;
    int sz;
    public:
        Mergenable_Linked_List():sz(0),head(nullptr),tail(nullptr){}
        int size(){return sz;}
        bool empty(){return sz==0;}
        void insert(T key){
            ++sz;
            if(head==nullptr){
                head=node(key);
                tail=head;
            }
            else{
                node *newnode=new node(key,head);
                head=newnode;
            }
        }
        void erase(T key){
            node* now=head;
            if(now==nullptr){
                return;
            }
            else if(now->key==key){
                --sz;
                if(now->next==nullptr){
                    head=nullptr;
                    tail=nullptr;
                }
                else{
                    head=now->next;
                }
            }
            else{
                if(now->next==nullptr){
                    return;
                }
                while(now->next!=nullptr){
                    if(now->next->key==key){
                        --sz;
                        node* deleted_node=now->next;
                        if(now->next->next==nullptr){
                            tail=now;
                        }
                        now->next=now->next->next;
                        return deleted_node;
                    }
                    now=now->next;
                }
            }
        }
        void merge(Mergenable_Linked_List<T> &other){
            if(other.empty())return;
            else if(empty()){
                head=other.head;
                tail=other.tail;
                sz=other.size();
            }
            else{
                tail->next=other->head;
                tail=other->tail;

            }
        }
        vector<T> to_array(){
            vector<T> res;
            node* now=head;
            while(now!=nullptr){
                res.push_back(now->key);
                now=now->next;
            }
            return res;
        }
    
};


void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){

}