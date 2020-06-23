#include <iostream>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::max;
using std::vector;

class StackWithMax
{
private:
    vector<int> stack;
    vector<int> max_stack;

public:
    int Size()
    {
        return stack.size();
    }

    void Push(int value)
    {
        stack.push_back(value);
        if (max_stack.empty() || max_stack.back() <= value)
        {
            max_stack.push_back(value);
        }
    }

    void Pop()
    {
        assert(stack.size());
        int popped_value = stack.back();
        stack.pop_back();
        if (max_stack.back() == popped_value)
        {
            max_stack.pop_back();
        }
    }

    int Max() const
    {
        assert(stack.size());
        return max_stack.back();
    }

    int Peek() const
    {
        return stack.back();
    }
};

void print_vector(const std::vector<int> &v)
{
    for (auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void max_sliding_window_naive(vector<int> const &A, int w)
{
    std::vector<int> window_max;
    StackWithMax st1, st2;
    // if (w == 1)
    // {
    //     print_vector(A);
    //     return;
    // }

    for (size_t i = 0; i < w; ++i)
    {
        st1.Push(A[i]);
    }
    // std::cout << "Size: " << st1.Size() << std::endl;
    window_max.push_back(st1.Max());

    for (size_t i = w; i < A.size(); ++i)
    {
        // std::cout << "Size22 : " << st1.Size() << std::endl;
        if (st1.Size() >= w)
        {
            while (st1.Size() > 0)
            {
                st2.Push(st1.Peek());
                st1.Pop();
            }
        }
        st2.Pop();
        st1.Push(A[i]);

        int mx1 = INT32_MIN, mx2 = INT32_MIN;
        if (st1.Size() > 0)
        {
            mx1 = st1.Max();
        }
        if (st2.Size() > 0)
        {
            mx2 = st2.Max();
        }
        window_max.push_back(std::max(mx1, mx2));
    }
    print_vector(window_max);
    return;
}

int main()
{
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);
    // int x;
    // std::cin >> x;
    return 0;
}
