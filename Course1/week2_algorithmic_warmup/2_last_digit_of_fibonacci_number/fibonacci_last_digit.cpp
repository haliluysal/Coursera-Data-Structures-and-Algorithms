#include <iostream>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int N) {
    if (N <= 1) {
        return N;
    }
    else {
        int fibPrevPrev = 0;
        int fibPrev = 1;
        int fibCurr;
        for (int i = 2; i <= N; ++i) {
            fibCurr = (fibPrev + fibPrevPrev) % 10;
            fibPrevPrev = fibPrev;
            fibPrev = fibCurr;
        }
        return fibCurr;
    }
}

int main() {
    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    // std::cout << c << '\t';
    int cf = get_fibonacci_last_digit_fast(n);
    std::cout << cf << '\n';
}
