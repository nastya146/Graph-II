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
  std::vector<int> prev_;

  explicit Graph(int n) : prev_(n, -1), size_(n) {
  }

  void AddEdge(int from, int to, int weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  bool Relax(Edge& edge, std::vector<int>& dist) {
    int u = edge.to;
    int v = edge.from;
    if (dist[v] != 100'000 && dist[u] > dist[v] + edge.weight) {
      dist[u] = dist[v] + edge.weight;
      prev_[u] = v;
      return true;
    }
    return false;
  }

  int HasNegativeCycle() {
    std::vector<int> dist(size_, inf_);
    dist[0] = 0;
    for (int i = 0; i < size_ - 1; ++i) {
      for (auto& edge : edges_list_) {
        Relax(edge, dist);
      }
    }
    for (auto& edge : edges_list_) {
      if (Relax(edge, dist)) {
        return edge.to;
      }
    }
    return -1;
  }

 private:
  int size_;
  const int inf_ = 1'000'000'000;
  std::vector<Edge> edges_list_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  int weight = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> weight;
      if (weight != 100'000) {
        graph.AddEdge(i, j, weight);
      }
    }
  }
  int begin = graph.HasNegativeCycle();
  if (begin == -1) {
    std::cout << "NO";
  } else {
    for (int i = 0; i < n; ++i) {
      begin = graph.prev_[begin];
    }
    std::deque<int> cycle;
    cycle.push_back(begin);
    int cur = graph.prev_[begin];
    while (cur != begin) {
      cycle.push_back(cur);
      cur = graph.prev_[cur];
    }
    std::cout << "YES\n";
    std::cout << cycle.size() + 1 << "\n";
    std::cout << begin + 1 << " ";
    while (!cycle.empty()) {
      std::cout << cycle.back() + 1 << " ";
      cycle.pop_back();
    }
  }
}