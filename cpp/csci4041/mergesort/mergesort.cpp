#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void mergeSort(int *A, int size);
void mergeSortHelper(int *A, int p, int r);
void merge(int *A, int p, int q, int r);
void printArray(int *A, int size);

int main() {
  int *arr = new int[20];
  srand((unsigned)time(0));
  for (int i = 0; i < 20; i++) {
    arr[i] = rand() % 50;
  }

  printArray(arr, 20);
  mergeSort(arr, 20);
  printArray(arr, 20);

  return 0;
}

void mergeSort(int *A, int size) { mergeSortHelper(A, 0, size - 1); }

void mergeSortHelper(int *A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    mergeSortHelper(A, p, q);
    mergeSortHelper(A, q + 1, r);
    merge(A, p, q, r);
  }
}

void merge(int *A, int p, int q, int r) {
  int n1 = q - p + 1;
  int *left = new int[n1];
  int n2 = r - q;
  int *right = new int[n2];

  for (int i = 0; i < n1; i++)
    left[i] = A[p + i];
  for (int j = 0; j < n2; j++)
    right[j] = A[q + j + 1];

  int i = 0;
  int j = 0;
  int k = p;
  while (i < n1 && j < n2) {
    if (left[i] < right[j])
      A[k++] = left[i++];
    else
      A[k++] = right[j++];
  }

  if (i < n1) {
    for (; i < n1; i++)
      A[k++] = left[i];
  }
  if (j < n2) {
    for (; j < n2; j++)
      A[k++] = right[j];
  }
}

void printArray(int *A, int size) {
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << "\n";
}
