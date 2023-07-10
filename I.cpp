#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <unordered_map>

class Graph {
 public:
  explicit Graph(int n) : size_(n), vertex_list_(n) {
  }

  void AddWeightedEdge(int from, int to, int weight) {
    int cur_weight = vertex_list_[from][to];
    if (cur_weight == 0 || cur_weight > weight) {
      vertex_list_[from][to] = weight;
      vertex_list_[to][from] = weight;
    }
  }

  std::vector<int64_t> Dijkstra(int begin) {
    std::vector<int64_t> distance(size_, inf_);
    distance[begin] = 0;
    std::vector<int> prev(size_, -1);
    std::set<std::pair<int64_t, int>> heap;
    std::vector<bool> in_heap(size_, true);
    heap.insert(std::make_pair(0, begin));
    while (!heap.empty()) {
      std::pair<int64_t, int> v = *heap.begin();
      heap.erase(heap.begin());
      int vertex = v.second;
      if (!in_heap[vertex]) {
        continue;
      }
      in_heap[vertex] = false;
      for (auto& [i, weight] : vertex_list_[vertex]) {
        if (in_heap[i] && distance[i] > distance[vertex] + weight) {
          prev[i] = vertex;
          distance[i] = distance[vertex] + weight;
          heap.insert(std::make_pair(distance[i], i));
        }
      }
    }
    return distance;
  }

 private:
  int size_;
  std::vector<std::unordered_map<int, int>> vertex_list_;
  const int64_t inf_ = 2'009'000'999;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m = 0;
  int n = 0;
  int begin = 0;
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
      int vertex1 = 0;
      int vertex2 = 0;
      int weight = 0;
      std::cin >> vertex1 >> vertex2 >> weight;
      graph.AddWeightedEdge(vertex1, vertex2, weight);
    }
    std::cin >> begin;
    std::vector<int64_t> paths = graph.Dijkstra(begin);
    for (auto& length : paths) {
      std::cout << length << " ";
    }
    std::cout << "\n";
  }
}