#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int i, l, r, pivot;

int z = A[0];
A[0] = A[n/2];
A[n/2] = z;

// 先頭の要素をピボットとする
  pivot = A[0];
  i = 1, l = 0, r = n;
  while(i < r){
    if(A[i] < pivot){
      int z = A[l];
      A[l] = A[i];
      A[i] = z;
      i++;
      l++;
    }
    else if(A[i] > pivot){
        r--;
        int z = A[r];
        A[r] = A[i];
        A[i] = z;
    }
    else{
    	i++;
    }
  }

  if(l >= k+1) return quick_select(A, l, k);
  else if(r < k+1) return quick_select(A+r, n-r, k-r);
  else return pivot;
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
