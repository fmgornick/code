class Aggregator : monitor {
private:
  int sum = 0;
  int numProcs = 0;
  condition X;

public:
  int Add(int n) {
    sum += n;
    numProcs++;

    if (numProcs == 3) {
      X.signal();
      X.signal();
    } else
      X.wait();

    return sum;
  }
};
