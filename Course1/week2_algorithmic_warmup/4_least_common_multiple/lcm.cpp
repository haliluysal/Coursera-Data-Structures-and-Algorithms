#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd(int a, int b) {
    int temp;
    if (a < b) {
        temp = b;
        b = a;
        a = temp;
    }

    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

long long lcm_fast(int a, int b) {
    int comm_div = gcd(a, b);
    long long mlt = (long long)a * b;
    return mlt / comm_div;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << '\t';
  std::cout << lcm_fast(a, b) << '\n';
  return 0;
}
