template<typename T>
vector<vector<T>> mat_mul(vector<vector<T>> &A,vector<vector<T>> &B){
  assert(A.size()>0&&A[0].size()>0&&B.size()>0&&B[0].size()>0&&A[0].size()==B.size());
  vector<vector<T>> res(A.size(),vector<T>(B[0].size()));
  for(int i=0;i<A.size();++i)for(int j=0;j<B[0].size();++j)for(int k=0;k<B.size();++k){
    res[i][j]+=A[i][k]*B[k][j];
  }
  return res;
}

template<typename T>
vector<vector<T>> mat_pow(vector<vector<T>> A,long long n){
  assert(A.size()>0&&A.size()==A[0].size());
  vector<vector<T>> base=A,res(A.size(),vector<T>(A.size()));
  for(int i=0;i<A.size();++i){
    res[i][i]=T(1);
  }
  while(n>0){
    if(n&1){
      vector<vector<T>> temp(A.size(),vector<T>(A.size()));
      temp=mat_mul(res,base);
      swap(temp,res);
    }
    n>>=1;
    vector<vector<T>> temp(A.size(),vector<T>(A.size()));
    temp=mat_mul(base,base);
    swap(temp,base);
  }
  return res;
}