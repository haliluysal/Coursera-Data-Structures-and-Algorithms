#include <cmath>
#include <iostream>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum = sum + current * current;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(long long n) {
    int period = 60;

    int mod = n % period;
    if (mod <= 1) {
        return mod;
    }
    else {
        int fib_prev_prev = 0;
        int fib_prev = 1;
        int fib_curr;
        int sum = 1;
        for (int i = 2; i <= mod; ++i) {
            fib_curr = (fib_prev + fib_prev_prev) % 10;
            fib_prev_prev = fib_prev;
            fib_prev = fib_curr;
            sum = (sum + fib_curr*fib_curr) % 10;
        }
        return sum;
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_squares_naive(n) << '\t';
    std::cout << fibonacci_sum_squares_fast(n) << std::endl;
}
