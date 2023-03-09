#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  //the more effective implementation of GenerateSwaps()
  void GenerateSwaps(int i) {
    int smallest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
  
    // If left is smaller
    if (l < data_.size() && data_[l] > data_[smallest])
        smallest = l;
  
    // If right is smaller
    if (r < data_.size() && data_[r] > data_[smallest])
        smallest = r;
  
    // If smallest is not root
    if (smallest != i) {
      
        swap(data_[i], data_[smallest]);
        swaps_.push_back(make_pair(i, smallest));
  
        // Recursively heapify the affected sub-tree
        GenerateSwaps(smallest);
    }
  }
  
  void buildHeap() {

    // Start Index
    int startIdx = (data_.size() / 2) - 1;
  
    // Perform reverse level order traversal
    // from last Start Index
    for (int i = startIdx; i >= 0; i--) {
        GenerateSwaps(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    buildHeap();
    WriteResponse();
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}