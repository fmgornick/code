#include <bits/stdc++.h>
using namespace std;

// finding the largest subarray with differing complexities
// O(n^3)
int alg1(int arr[], int len) {
  int best = 0;
  for (int a=0; a<len; a++) {
    for (int b=a; b<len; b++) {
      int sum = 0;
      for (int i=a; i<=b; i++) {
          sum += arr[i];
      }
      best = max(best,sum);
    }
  }
  return best;
}

// O(n^2)
int alg2(int arr[], int len) {
  int best = 0;
  for (int a=0; a<len; a++) {
    int sum = 0;
    for (int b=a; b<len; b++) {
      sum += arr[b];
      best = max(best,sum);
    }
  }
  return best;
}

// O(n)
int alg3(int arr[], int len) {
  int best = 0, sum = 0;
  for (int i=0; i<len; i++) {
    sum = max(arr[i],sum+arr[i]);
    best = max(best,su);
  }
  return best;
}
