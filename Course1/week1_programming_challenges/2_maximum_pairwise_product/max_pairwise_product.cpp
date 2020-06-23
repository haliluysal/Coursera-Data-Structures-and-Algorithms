
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

/* int MaxPairwiseProduct(const std::vector<int>& numbers) {
	int max_product = 0;
	int n = numbers.size();

	for (int first = 0; first < n; ++first) {
		for (int second = first + 1; second < n; ++second) {
			max_product = std::max(max_product,
				numbers[first] * numbers[second]);
		}
	}

	return max_product;
}
*/

long long MaxPairwiseProductFast(const std::vector<int> &numbers)
{
	long long max_product = 0;
	int n = numbers.size();

	long long maxNum1 = numbers[0];
	long long maxNum2 = -1;

	for (size_t i = 1; i < n; i++)
	{
		if (numbers[i] >= maxNum1)
		{
			maxNum2 = maxNum1;
			maxNum1 = numbers[i];
		}
		else if (numbers[i] >= maxNum2)
		{
			maxNum2 = numbers[i];
		}
	}

	max_product = maxNum1 * maxNum2;
	return max_product;
}

int main()
{
	// keep seed constant
	/* srand(1);

	while (true) {
		int n = rand() % 4 + 2;
		std::vector<int> numbers(n, 0);
		for (size_t i = 0; i < n; i++) {
			numbers[i] = rand() % 100000;
		}
		long long mpp = MaxPairwiseProduct(numbers);
		long long mppf = MaxPairwiseProductFast(numbers);
		if (mpp == mppf) {
			std::cout << "OK" << '\n';
		} else {
			for (size_t i = 0; i < n; i++) {
				std::cout << numbers[i] << ' ';
			}
			std::cout << '\n';
			std::cout << mpp << ' ' << mppf << '\n';
			break;
		}
	} */

	int n = 100;
	vector<int> numbers(n);
	for (int i = 0; i < n; ++i)
	{
		numbers[i] = rand() % 10;
	}

	cout << MaxPairwiseProductFast(numbers) << "\n";
	return 0;
}
