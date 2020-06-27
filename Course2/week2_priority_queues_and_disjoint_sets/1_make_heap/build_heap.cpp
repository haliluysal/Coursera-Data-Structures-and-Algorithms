#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder
{
private:
	int size_;
	vector<int> data_;
	vector<pair<int, int>> swaps_;

	void WriteResponse() const
	{
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i)
		{
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
		// cout << std::endl;
		// for (auto d : data_)
		// {
		// 	cout << d << "\t";
		// }
		// cout << std::endl;
	}

	void ReadData()
	{
		int n;
		cin >> n;
		size_ = n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> data_[i];
	}

	void GenerateSwaps()
	{
		swaps_.clear();
		// The following naive implementation just sorts
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap,
		// but in the worst case gives a quadratic number of swaps.
		//
		// TODO: replace by a more efficient implementation
		// for (int i = 0; i < data_.size(); ++i)
		// {
		// 	for (int j = i + 1; j < data_.size(); ++j)
		// 	{
		// 		if (data_[i] > data_[j])
		// 		{
		// 			swap(data_[i], data_[j]);
		// 			swaps_.push_back(make_pair(i, j));
		// 		}
		// 	}
		// }
		for (int i = floor(size_ / 2); i >= 0; --i)
		{
			sift_down(i);
		}
	}

	int left_child(int i)
	{
		return i * 2 + 1;
	}

	int right_child(int i)
	{
		return i * 2 + 2;
	}

	int compare(int index_1, int index_2)
	{
		if ((index_1 < size_) && (data_[index_1] < data_[index_2]))
		{
			index_2 = index_1;
		}
		return index_2;
	}

	void sift_down(int i)
	{
		int min_index = i;

		int l = left_child(i);
		min_index = compare(l, min_index);

		int r = right_child(i);
		min_index = compare(r, min_index);

		if (i != min_index)
		{
			swap(data_[i], data_[min_index]);
			swaps_.push_back(make_pair(i, min_index));
			sift_down(min_index);
		}
	}

public:
	void Solve()
	{
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	// int x;
	// cin >> x;
	return 0;
}
