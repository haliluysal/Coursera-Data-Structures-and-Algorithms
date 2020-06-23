#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int get_fibonacci_partial_sum_fast(long long from, long long to) {
    int period = 60;
    int mod = to % period;
    int mod_sum = from % period;
    if (mod <= 1) {
        return mod;
    }
    else {
        int fib_prev_prev = 0;
        int fib_prev = 1;
        int fib_curr;
        int sum = 0;
        for (int i = 2; i <= mod; ++i) {
            fib_curr = (fib_prev + fib_prev_prev) % 10;
            fib_prev_prev = fib_prev;
            fib_prev = fib_curr;
            if (i >= mod_sum) {
                sum = (sum + fib_curr) % 10;
            }
        }
        return sum;
    }
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
