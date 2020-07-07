#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using std::string;
typedef unsigned long long ull;

struct Data
{
    string pattern, text;
};

int AreEqual(const string &s, const string &p)
{
    return s.compare(p);
}

long long PolyHash(string s, long long p, long long x)
{
    long long h = 0;
    for (int i = static_cast<int>(s.size() - 1); i >= 0; i--)
    {
        h = (h * x + s[i]) % p;
    }
    // std::cout << "Poly hash function, string: " << s << " Hash value: " << h << std::endl;
    return h;
}

std::vector<long long> PrecomputeHashes(string t, int length_of_substring, long long p, long long x)
{
    std::vector<long long> H(t.size() - length_of_substring + 1);
    string sub = t.substr(t.size() - length_of_substring, length_of_substring);
    H[H.size() - 1] = PolyHash(sub, p, x);
    long long y = 1;
    for (size_t i = 1; i <= length_of_substring; ++i)
    {
        long long dummy = y * x;
        // std::cout << "Precompute Hashes function, dummy value: " << dummy << std::endl;
        y = dummy % p;
    }
    // std::cout << "Precompute Hashes function, y: " << y << std::endl;
    for (int i = t.size() - length_of_substring - 1; i >= 0; i--)
    {
        long long val1 = x * H[i + 1];
        long long val2 = t[i];
        long long val3 = y * t[i + length_of_substring];
        // std::cout << "Precompute Hashes function, value check: " << val1 << " " << val2 << " " << val3 << " Expected Hash value: "
        //           << (val1 + val2 - val3) % p << std::endl;
        H[i] = (x * H[i + 1] + t[i] - y * t[i + length_of_substring] + p);
        while (H[i] < 0)
        {
            H[i] += p;
        }
        H[i] %= p;
        // std::cout << "Precompute Hashes function, substring: " << t.substr(i, length_of_substring) << " Hash Value: " << H[i] << std::endl;
    }
    return H;
}

std::vector<int> RubinKarpAlg(string P, string T)
{
    long long p = 100000007; // 10000139;
    long long x = (std::rand() % (p - 1) + 1);
    std::vector<int> result;
    long long pHash = PolyHash(P, p, x);
    std::vector<long long> H = PrecomputeHashes(T, (int)P.size(), p, x);
    for (size_t i = 0; i < (T.size() - P.size()) + 1; i++)
    {
        // std::cout << "Rubin Karp, for loop - substring: " << T.substr(i, P.size()) << " hash value: " << H[i] << std::endl;
        if (pHash == H[i])
        {
            // std::cout << "Rubin Karp, if check - substring: " << T.substr(i, P.size()) << " pattern: " << P << std::endl;
            if (AreEqual(T.substr(i, P.size()), P) == 0)
            {
                result.push_back(i);
            }
        }
    }
    return result;
}

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int> &output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data &input)
{
    const string &s = input.pattern, t = input.text;
    std::vector<int> ans;
    // for (size_t i = 0; i + s.size() <= t.size(); ++i)
    //     if (t.substr(i, s.size()) == s)
    //         ans.push_back(i);
    ans = RubinKarpAlg(s, t);
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    // int x;
    // std::cin >> x;
    return 0;
}
