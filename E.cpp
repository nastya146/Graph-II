#include <vector>
#include <iostream>
#include <algorithm>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class Graph {
 public:
  void AddEdge(int64_t from, int64_t to, int64_t weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  std::vector<Edge>& SortedEdges() {
    std::sort(edges_list_.begin(), edges_list_.end(),
              [](Edge& first, Edge& second) { return first.weight < second.weight; });
    return edges_list_;
  }

  std::vector<Edge>& Edges() {
    return edges_list_;
  }

 private:
  std::vector<Edge> edges_list_;
};

class Dsu {
 public:
  explicit Dsu(int64_t n) : size_(n), parent_(n + 1, -1), rank_(n + 1, 1) {
    for (int64_t i = 0; i < n + 1; ++i) {
      parent_[i] = i;
    }
  }

  void MakeSet(int64_t i) {
    parent_[i] = i;
    rank_[i] = 1;
    ++size_;
  }

  int64_t FindSet(int64_t x) {
    if (x == parent_[x]) {
      return x;
    }
    parent_[x] = FindSet(parent_[x]);
    return parent_[x];
  }

  void Union(int64_t x, int64_t y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x != y) {
      if (rank_[x] < rank_[y]) {
        parent_[x] = y;
      } else if (rank_[y] < rank_[x]) {
        parent_[y] = x;
      } else {
        parent_[x] = y;
        ++rank_[y];
      }
      --size_;
    }
  }

  int64_t CountSet() {
    return size_;
  }

 private:
  int64_t size_;
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
};

int64_t BoruvkaMST(Graph& graph, int64_t size) {
  int64_t weight = 0;
  const int64_t inf = 1'000'000'000;
  std::vector<Edge> edges = graph.Edges();
  Dsu dsu(size);
  while (dsu.CountSet() > 1) {
    std::vector<Edge> min_edge(size + 1, {0, 0, inf});
    for (auto& edge : edges) {
      int64_t component_v = dsu.FindSet(edge.from);
      int64_t component_u = dsu.FindSet(edge.to);
      if (component_u != component_v) {
        if (edge.weight < min_edge[component_v].weight) {
          min_edge[component_v] = edge;
        }
        if (edge.weight < min_edge[component_u].weight) {
          min_edge[component_u] = edge;
        }
      }
    }
    for (auto& edge : min_edge) {
      if (edge.weight == inf || dsu.FindSet(edge.from) == dsu.FindSet(edge.to)) {
        continue;
      }
      weight += edge.weight;
      dsu.Union(edge.from, edge.to);
    }
  }
  return weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Graph graph;
  for (int64_t i = 0; i < m; ++i) {
    int64_t from = 0;
    int64_t to = 0;
    int64_t weight = 0;
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }
  std::cout << BoruvkaMST(graph, n);
}