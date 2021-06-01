#include <bits/stdc++.h>
using namespace std;

// function to print a set
void print_set(vector<int> set, int len) {
  cout << "{ ";
  for (int i=0; i<len; i++) {
    if (i+1 == len) cout << set[i] << " ";
    else cout << set[i] << ", ";
  }
  cout << "}\n";
}

// create every possible subarray of elemenst 0 to n-1
void search(int k, vector<int> subset, int n) {
  if (k == n) print_set(subset, (int) subset.size());
  else {
    search(k+1, subset, n);
    subset.push_back(k);
    search(k+1, subset, n);
    subset.pop_back();
  }
}

// creates subarray using bit representations (non recursively)
void bits(int n) {
  for (int b=0; b<(1<<n); b++) {
    vector<int> subset;
    for (int i=0; i<n; i++) if (b & (1<<i)) subset.push_back(i);
    print_set(subset, (int) subset.size());
  }
}

void permute(int n, vector<int> perm, bool *chosen) {
  if (perm.size() == n) print_set(perm, n);
  else {
    for (int i=0; i<n; i++) {
      if (chosen[i]) continue;
      chosen[i] = true;
      perm.push_back(i);
      permute(n, perm, chosen);
      chosen[i] = false;
      perm.pop_back();
    }
  }
}

int main (int argc, char *argv[]) {
  int n;
  vector<int> arr;

  cout << "select number of elements in array: ";
  cin >> n;
  bool *chosen = (bool *) malloc(sizeof(bool) * n);
  for (int i=0; i<n; i++) chosen[i] = false;

  cout << "\nall possible permutations: \n";

  permute(n, arr, chosen);
  /* bits(n); */
  /* search(0, arr, n); */
  return 0;
}
