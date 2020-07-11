#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Solver
{
	string s_;
	int x_1_, x_2_;
	long long m1_, m2_;
	std::vector<long long> hash_vector1_;
	std::vector<long long> hash_vector2_;
	std::vector<long long> x_pow_l_m1_;
	std::vector<long long> x_pow_l_m2_;

	bool SubstringHashes(int a, int b, int l)
	{
		if (a == b)
			return true;
		long long h1_a = ((hash_vector1_[a + l] + m1_ - hash_vector1_[a]) * x_pow_l_m1_[s_.size() - a - 1]) % m1_;
		long long h1_b = ((hash_vector1_[b + l] + m1_ - hash_vector1_[b]) * x_pow_l_m1_[s_.size() - b - 1]) % m1_;

		if (h1_a != h1_b)
			return false;

		long long h2_a = ((hash_vector2_[a + l] + m2_ - hash_vector2_[a]) * x_pow_l_m2_[s_.size() - a - 1]) % m2_;
		long long h2_b = ((hash_vector2_[b + l] + m2_ - hash_vector2_[b]) * x_pow_l_m2_[s_.size() - b - 1]) % m2_;

		if (h2_a != h2_b)
		{
			return false;
		}

		return true;
	}

public:
	Solver(string s)
	{
		s_ = s;
		srand(time(NULL));
		// initialization, precalculation
		x_pow_l_m1_.resize(s_.size() + 1, 1);
		x_pow_l_m2_.resize(s_.size() + 1, 1);
		hash_vector1_.resize(s_.size() + 1, 0);
		hash_vector2_.resize(s_.size() + 1, 0);

		m1_ = 1000000007;
		m2_ = 1000000009;
		x_1_ = (std::rand() % (m1_ - 1)) + 1;
		x_2_ = (std::rand() % (m2_ - 1)) + 1;

		for (size_t i = 0; i < s_.size(); i++)
		{
			hash_vector1_[i + 1] = (hash_vector1_[i] + s_[i] * x_pow_l_m1_[i]) % m1_;
			hash_vector2_[i + 1] = (hash_vector2_[i] + s_[i] * x_pow_l_m2_[i]) % m2_;
			x_pow_l_m1_[i + 1] = (x_pow_l_m1_[i] * x_1_) % m1_;
			x_pow_l_m2_[i + 1] = (x_pow_l_m2_[i] * x_2_) % m2_;
		}
	}

	bool ask(int a, int b, int l)
	{
		bool out = SubstringHashes(a, b, l);
		return out;
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		// auto start = chrono::steady_clock::now();
		if (solver.ask(a, b, l) == true)
		{
			std::cout << "Yes";
		}
		else
		{
			std::cout << "No";
		}
		std::cout << std::endl;
		// auto end = chrono::steady_clock::now();
		// std::cout << "elapsed time [ns]: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << std::endl;
		// cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
	// int x;
	// std::cin >> x;
	return 0;
}
