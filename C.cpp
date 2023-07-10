#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <unordered_map>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : size_(n + 1), vertex_list_(n + 1) {
  }

  void AddWeightedEdge(int from, int to, int weight) {
    int cur_weight = vertex_list_[from][to];
    if (cur_weight == 0 || cur_weight > weight) {
      vertex_list_[from][to] = weight;
      vertex_list_[to][from] = weight;
    }
  }

  int Prim() {
    int weight = 0;
    std::vector<int> dist(size_, inf_);
    dist[1] = 0;
    std::vector<int> prev(size_, -1);
    std::vector<bool> in_heap(size_, true);
    std::set<std::pair<int, int>> heap;
    heap.insert(std::make_pair(0, 1));
    while (!heap.empty()) {
      std::pair<int, int> v = *heap.begin();
      heap.erase(heap.begin());
      int vertex = v.second;
      if (!in_heap[vertex]) {
        continue;
      }
      in_heap[vertex] = false;
      if (prev[vertex] != -1) {
        weight += v.first;
      }
      for (auto& [to, w] : vertex_list_[vertex]) {
        if (in_heap[to] && dist[to] > w) {
          prev[to] = vertex;
          dist[to] = w;
          heap.insert(std::make_pair(dist[to], to));
        }
      }
    }
    return weight;
  }

 private:
  int size_;
  std::vector<std::unordered_map<int, int>> vertex_list_;
  const int inf_ = 1'000'000'000;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m = 0;
  int n = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex1 = 0;
    int vertex2 = 0;
    int weight = 0;
    std::cin >> vertex1 >> vertex2 >> weight;
    graph.AddWeightedEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.Prim();
}