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
  explicit Graph(int n) : size_(n + 1), help_dist_(size_), potential_(size_), vertex_list_(n) {
  }

  void AddEdge(int from, int to, int weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  void AddWeightedEdge(int from, int to, int weight) {
    int cur_weight = vertex_list_[from][to];
    if (cur_weight == 0 || cur_weight > weight) {
      vertex_list_[from][to] = weight;
    }
  }

  bool Relax(Edge& edge) {
    int u = edge.to;
    int v = edge.from;
    if (help_dist_[v] != 30000 && help_dist_[u] > help_dist_[v] + edge.weight) {
      help_dist_[u] = help_dist_[v] + edge.weight;
      return true;
    }
    return false;
  }

  void BellmanFord() {
    help_dist_[0] = 0;
    for (int i = 1; i < size_ - 1; ++i) {
      for (auto& edge : edges_list_) {
        Relax(edge);
      }
    }
  }

  int64_t Dijkstra(int begin) {
    int g_size = size_ - 1;
    --begin;
    std::vector<int64_t> distance(g_size, inf_);
    distance[begin] = 0;
    std::vector<int> prev(g_size, -1);
    std::set<std::pair<int64_t, int>> heap;
    std::vector<bool> in_heap(g_size, true);
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
    int64_t cur_diam = 0;
    for (int i = 0; i < g_size; ++i) {
      if (distance[i] != inf_ && distance[i] > cur_diam) {
        cur_diam = distance[i] + potential_[i + 1] - potential_[begin + 1];
      }
    }
    return cur_diam;
  }

  void WeightUpdate() {
    for (int i = 0; i < size_ - 1; ++i) {
      for (auto& [to, weight] : vertex_list_[i]) {
        vertex_list_[i][to] = weight + potential_[i + 1] - potential_[to + 1];
      }
    }
  }

  int64_t Johnson() {
    for (int i = 1; i < size_; ++i) {
      AddEdge(0, i, 0);
    }
    BellmanFord();
    for (int i = 1; i < size_; ++i) {
      potential_[i] = help_dist_[i];
    }
    WeightUpdate();
    int64_t diam = 0;
    int64_t cur = 0;
    for (int i = 1; i < size_; ++i) {
      cur = Dijkstra(i);
      if (cur > diam) {
        diam = cur;
      }
    }
    return diam;
  }

 private:
  int size_;
  std::vector<int> help_dist_;
  std::vector<int> potential_;
  std::vector<std::unordered_map<int, int>> vertex_list_;
  const int64_t inf_ = 1'000'000;
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
    graph.AddEdge(vertex1 + 1, vertex2 + 1, weight);
    graph.AddWeightedEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.Johnson();
}