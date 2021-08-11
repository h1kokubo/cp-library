#include <bits/stdc++.h>
using namespace std;
struct Eratosthenes{
    private:
        int n;
        vector<bool> sieve;
    public:
        Eratosthenes(int n_):n(n_+1),sieve(vector<bool>(n,true)){
            sieve[0]=sieve[1]=false;
            int i=2;
            while(i*i<n){
                if(!sieve[i]){
                    ++i;
                    continue;
                }
                for(int j=2*i;j<n;j+=i){
                    sieve[j]=false;
                }
                ++i;
            }
        }
        bool is_prime(int x){
            return sieve[x];
        }
        };

void Main();
int main(){cout<<fixed<<setprecision(15);Main();}

void Main(){
Eratosthenes er=Eratosthenes(1000000);
cout<<er.is_prime(200003)<<endl;
}      
