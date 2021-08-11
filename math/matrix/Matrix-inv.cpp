#include <bits/stdc++.h>
using namespace std;


template<typename T>
vector<vector<T>> mat_inv(vector<vector<T>> A){
  vector<vector<T>> res(A.size(),vector<T>(A.size()));
  for(int j=0;j<A.size();++j){
    vector<T> id(A.size());
    id[j]=T(1);
    Matrix_Reduction<T> mr(A,id);
    assert(mr.ans_exist());
    auto s=mr.solve();
    for(int i=0;i<A.size();++i){
      res[i][j]=s[i];
    }
  }
  return res;
}
