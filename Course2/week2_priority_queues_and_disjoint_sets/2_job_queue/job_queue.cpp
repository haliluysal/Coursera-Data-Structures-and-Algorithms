#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

class JobQueue
{
private:
	int num_workers_;
	vector<int> jobs_;
	struct worker_id_available_time
	{
		int id;
		long long available_time;
	};
	vector<int> assigned_workers_;
	vector<long long> start_times_;
	vector<worker_id_available_time> next_free_time_;

	void WriteResponse() const
	{
		for (int i = 0; i < jobs_.size(); ++i)
		{
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData()
	{
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	int LeftChild(int i)
	{
		return i * 2 + 1;
	}

	int RightChild(int i)
	{
		return i * 2 + 2;
	}

	int Compare(int index_1, int index_2)
	{
		if ((index_1 < num_workers_) && (next_free_time_[index_1].available_time < next_free_time_[index_2].available_time))
		{
			index_2 = index_1;
		}
		else if ((index_1 < num_workers_) && (next_free_time_[index_1].available_time == next_free_time_[index_2].available_time))
		{
			if (next_free_time_[index_1].id < next_free_time_[index_2].id)
			{
				index_2 = index_1;
			}
		}		
		return index_2;
	}

	void SiftDown(int i)
	{
		int min_index = i;

		int l = LeftChild(i);
		min_index = Compare(l, min_index);

		int r = RightChild(i);
		min_index = Compare(r, min_index);

		if (i != min_index)
		{
			std::swap(next_free_time_[i], next_free_time_[min_index]);
			SiftDown(min_index);
		}
	}

	void UpdateNextFreeTime(long long working_time)
	{
		next_free_time_[0].available_time += working_time;
		SiftDown(0);
	}

	void AssignJobs()
	{
		// TODO: replace this code with a faster algorithm.
		assigned_workers_.resize(jobs_.size(), -1);
		start_times_.resize(jobs_.size());
		next_free_time_.resize(num_workers_);
		for (int i = 0; i < num_workers_; ++i)
		{
			next_free_time_[i].id = i;
			next_free_time_[i].available_time = 0;
		}
		

		for (int i = 0; i < jobs_.size(); ++i)
		{
			int duration = jobs_[i];
			// int next_worker = 0;
			// for (int j = 0; j < num_workers_; ++j)
			// {
			// 	if (next_free_time_[j] < next_free_time_[next_worker])
			// 		next_worker = j;
			// }
			assigned_workers_[i] = next_free_time_[0].id;
			start_times_[i] = next_free_time_[0].available_time;
			// std::cout << assigned_workers_[i] << "\t" << start_times_[i] << std::endl;
			UpdateNextFreeTime(duration);
		}
		// std::cout << std::endl << std::endl;
	}

public:
	void Solve()
	{
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	// int x;
	// std::cin >> x;
	return 0;
}
