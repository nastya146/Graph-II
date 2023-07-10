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
  explicit Graph(int n) : size_(n + 1), vertex_list_(n + 1) {
  }

  void AddEdge(int from, int to, int weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  bool Relax(Edge& edge, std::vector<int>& dist, std::vector<int>& prev) {
    int u = edge.to;
    int v = edge.from;
    if (dist[v] != inf_ && dist[u] > dist[v] + edge.weight) {
      dist[u] = dist[v] + edge.weight;
      prev[u] = prev[v];
      return true;
    }
    return false;
  }

  std::vector<int> BellmanFord() {
    std::vector<int> dist(size_, inf_);
    dist[1] = 0;
    std::vector<int> prev(size_, -1);
    for (int i = 1; i < size_ - 1; ++i) {
      for (auto& edge : edges_list_) {
        Relax(edge, dist, prev);
      }
    }
    return dist;
  }

 private:
  int size_;
  std::vector<std::unordered_map<int, int>> vertex_list_;
  const int inf_ = 30'000;
  std::vector<Edge> edges_list_;
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
    graph.AddEdge(vertex1, vertex2, weight);
  }
  std::vector<int> paths = graph.BellmanFord();
  for (int i = 1; i < n + 1; ++i) {
    std::cout << paths[i] << " ";
  }
}