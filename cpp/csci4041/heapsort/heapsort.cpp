#include <bits/stdc++.h>
using namespace std;

void heapSort(int A[], int size);
void buildHeap(int A[], int size);
void heapify(int A[], int size, int i);
void printArray(int A[], int size);

class Heap {
public:
  int size;
  int *arr;
};

int main() {
  Heap h;
  h.size = 20;

  h.arr = (int *)malloc(h.size * sizeof(int));
  for (int i = 0; i < h.size; i++)
    h.arr[i] = h.size - i;

  printArray(h.arr, h.size);
  heapSort(h.arr, h.size);
  printArray(h.arr, h.size);

  free(h.arr);
  return 0;
}

void heapify(int A[], int size, int i) {
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int largest = i;

  if (l < size && A[l] > A[largest])
    largest = l;
  if (r < size && A[r] > A[largest])
    largest = r;

  if (largest != i) {
    swap(A[i], A[largest]);
    heapify(A, size, largest);
  }
}

void buildHeap(int A[], int size) {
  for (int i = size / 2 - 1; i >= 0; i--)
    heapify(A, size, i);
}

void heapSort(int A[], int size) {
  buildHeap(A, size);
  for (int i = size - 1; i > 0; i--) {
    swap(A[0], A[i]);
    heapify(A, i, 0);
  }
}

void printArray(int A[], int size) {
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << "\n";
}
