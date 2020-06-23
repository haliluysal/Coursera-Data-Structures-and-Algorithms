#include <iostream>
#include <cmath>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

int find_period(long long m) {
    int fib_prev_prev = 1;
    int fib_prev = 1;
    int fib_curr;
    int period = 1;
    while (!(fib_prev == 1 && fib_prev_prev == 0)) {
        fib_curr = (fib_prev + fib_prev_prev) % m;
        fib_prev_prev = fib_prev;
        fib_prev = fib_curr;
        period++;
    }
    return period;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    long long period = find_period(m);
    // std::cout << "Period: " << period << '\n';
    int mod = n % period;
    // std::cout << "Remainder: " << mod << '\n';
    if (mod <= 1) {
        return mod;
    }
    else {
        int fib_prev_prev = 0;
        int fib_prev = 1;
        int fib_curr;
        for (int i = 2; i <= mod; ++i) {
            fib_curr = (fib_prev + fib_prev_prev) % m;
            fib_prev_prev = fib_prev;
            fib_prev = fib_curr;
        }
        return fib_curr;
    }
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\t';
    std::cout << get_fibonacci_huge_fast(n ,m) << '\n';
}
