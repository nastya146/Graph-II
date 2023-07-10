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

  explicit Graph(int n) : size_(n + 1) {
  }

  void AddEdge(int from, int to, int weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  bool Relax(Edge& edge, int k, std::vector<int>& dist, std::vector<int>& len) {
    int u = edge.to;
    int v = edge.from;
    if (dist[v] != inf_ && dist[u] > dist[v] + edge.weight ) {
      dist[u] = dist[v] + edge.weight;
      len[u] = len[v] + 1;
      return true;
    }
    return false;
  }

  int BellmanFord(int begin, int end, int k) {
    std::vector<int> len(size_, 0);
    std::vector<int> dist(size_, inf_);
    dist[begin] = 0;
    for (int i = 1; i <= k; ++i) {
      for (auto& edge : edges_list_) {
        if (Relax(edge, k, dist, len)) {
          std::cout << "Relax(it - from - to )" << i << " " << edge.from << " " << edge.to << "\n";
          for (auto& l: len) {
            std::cout << l << " ";
          }
          std::cout << "\n";
        }
      }
      std::cout << i << " dist\n";
      for (auto& d : dist) {
        std::cout << d << " ";
      }
      std::cout << "\n";
    }
    return dist[end] == inf_ ? -1 : dist[end];
  }

 private:
  int size_;
  // std::vector<std::unordered_map<int, int>> vertex_list_;
  const int inf_ = 1'000'000'000;
  std::vector<Edge> edges_list_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m = 0;
  int n = 0;
  int begin = 0;
  int end = 0;
  int k = 0;
  std::cin >> n >> m >> k >> begin >> end;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex1 = 0;
    int vertex2 = 0;
    int weight = 0;
    std::cin >> vertex1 >> vertex2 >> weight;
    graph.AddEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.BellmanFord(begin, end, k);
}