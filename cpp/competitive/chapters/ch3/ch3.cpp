#include <bits/stdc++.h>
using namespace std;

// defining comparison operator for structs
struct P {
  int x, y;
  bool operator<(const P &p) {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
};

// creating external comparison operator for strings
// checks length first, then letters (true if a < b)
bool comp(string a, string b) {
  if (a.size() != b.size()) return a.size() < b.size();
  return a < b;
}
/* now you can sort a vector of strings like this... */
/*     sort(v.begin(), v.end(), comp); */

// methods for binary search
// changing size of region
int method1(int arr[], int len, int target) {
  int a=0, b=len-1;
  while (a <= b) {
    int idx = (a+b)/2;
    if (arr[idx] == target) return idx;
    else if (arr[idx] > target) b = idx-1;
    else a = idx+1;
  }
  return -1;
}

// jumping from start
int method2(int arr[], int len, int target) {
  int idx = 0;
  for (int jmp = len/2; jmp >= 1; jmp /= 2) {
    while (idx+jmp < len && arr[idx+jmp] < target) idx += jmp;
  }
  if (arr[idx] == target) return idx;
  else return -1;
}
