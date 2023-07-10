#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <unordered_map>

struct Edge {
  int from;
  int to;
  int weight;
};

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : size_(n), vertex_list_(n) {
  }

  void AddWeightedEdge(int from, int to, int weight) {
    vertex_list_[from].emplace_back(std::make_pair(to, weight));
  }

  int ArgMin(std::vector<int>& dist, const std::vector<bool>& unvisit) {
    int ptr = -1;
    for (int i = 0; i < size_; ++i) {
      if (unvisit[i] && (ptr == -1 || dist[ptr] > dist[i])) {
        ptr = i;
      }
    }
    return ptr;
  }

  int DijkstraM(int begin, int end) {
    std::vector<int> distance(size_, inf_);
    distance[begin] = 0;
    std::vector<bool> in_heap(size_, true);
    int count = 0;
    while (count != size_) {
      int vertex = ArgMin(distance, in_heap);
      ++count;
      if (vertex == end) {
        return distance[vertex];
      }
      in_heap[vertex] = false;
      for (auto& [i, weight] : vertex_list_[vertex]) {
        if (in_heap[i] && distance[i] > distance[vertex] + weight) {
          distance[i] = distance[vertex] + weight;
        }
      }
    }
    return -1;
  }

 private:
  int size_;
  std::vector<std::vector<std::pair<int, int>>> vertex_list_;
  const int inf_ = 2'009'000'999;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const int inf = 2'009'000'999;
  int n = 0;
  int begin = 0;
  int end = 0;
  std::cin >> n >> begin >> end;
  int weight = 0;
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> weight;
      if (weight != -1 && i != j) {
        graph.AddWeightedEdge(i, j, weight);
      }
    }
  }
  int distance = graph.DijkstraM(begin - 1, end - 1);
  std::cout << (distance == inf ? -1 : distance);
}