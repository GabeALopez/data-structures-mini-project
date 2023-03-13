#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    //Old Algorithm vvv
    // TODO: replace this code with a faster algorithm.
    // assigned_workers_.resize(jobs_.size());
    // start_times_.resize(jobs_.size());
    // vector<long long> next_free_time(num_workers_, 0);
    // for (int i = 0; i < jobs_.size(); ++i) {
    //   int duration = jobs_[i];
    //   int next_worker = 0;
    //   for (int j = 0; j < num_workers_; ++j) {
    //     if (next_free_time[j] < next_free_time[next_worker])
    //       next_worker = j;
    //   }
    //   assigned_workers_[i] = next_worker;
    //   start_times_[i] = next_free_time[next_worker];
    //   next_free_time[next_worker] += duration;
    // }
    //New Algorithm vvv
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
  
    for (int i = 0; i < num_workers_; ++i) {
        pq.push(std::make_pair(0, i));
    }

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      std::pair<long long, int> next_worker = pq.top();
      pq.pop();
      assigned_workers_[i] = next_worker.second;
      start_times_[i] = next_worker.first;
      next_worker.first += duration;
      pq.push(next_worker);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
