#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int pivot(int *A, int p, int q);
int partition(int *A, int p, int r);
void quicksortHelper(int *A, int p, int r);
void quicksort(int *A, int size);
void printArray(int *A, int size);

int main() {
  int *arr = new int[20];
  srand((unsigned)time(0));
  for (int i = 0; i < 20; i++) {
    arr[i] = rand() % 50;
  }

  printArray(arr, 20);
  quicksort(arr, 20);
  printArray(arr, 20);

  return 0;
}

void quicksort(int *A, int size) { quicksortHelper(A, 0, size - 1); }

void quicksortHelper(int *A, int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quicksortHelper(A, p, q - 1);
    quicksortHelper(A, q + 1, r);
  }
}

int partition(int *A, int p, int r) {
  int x = pivot(A, p, r);
  if (x != r)
    swap(A[x], A[r]);

  int q = p - 1;
  for (int i = p; i < r; i++) {
    if (A[i] <= A[r])
      swap(A[i], A[++q]);
  }
  swap(A[++q], A[r]);
  return q;
}

int pivot(int *A, int p, int r) {
  int x = A[p];
  int y = A[(p + r) / 2];
  int z = A[r];

  if (x > y) {
    if (x > z) {
      if (y > z) {
        return (p + r) / 2;
      }
      return r;
    }
    return p;
  }

  if (y > z) {
    if (x > z) {
      return p;
    }
    return r;
  }
  return (p + r) / 2;
}

void printArray(int *A, int size) {
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << "\n";
}
