#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int B[N], i, j, l, r, pivot;
 if(n <= 5){
  for(i = 0; i < n; i++){
    int min = i;
    for(j = i+1; j < n; j++){
      if(A[j] < A[min]){
        min = j;
      }
    }
    int z = A[i];
    A[i] = A[min];
    A[min] = z;
   }
   return A[k];
 }
 else{
	 for(i = 0; i < n/5; i++){
		B[i] = quick_select(A+5*i, 5, 2);
	}
	if(n-5*i != 0){
	B[i] = quick_select(A+5*i, n-5*i, (n-5*i)/2 );
	}

  pivot = quick_select(B,(n+4)/5,(n+4)/5/2);
  i = l = 0, r = n;
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
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
