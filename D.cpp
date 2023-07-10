#include <vector>
#include <iostream>
#include <algorithm>

struct Edge {
  int from;
  int to;
  int weight;
};

class Graph {
 public:
  void AddEdge(int from, int to, int weight) {
    edges_list_.emplace_back(Edge{from, to, weight});
  }

  std::vector<Edge>& SortedEdges() {
    std::sort(edges_list_.begin(), edges_list_.end(),
              [](Edge& first, Edge& second) { return first.weight < second.weight; });
    return edges_list_;
  }

 private:
  std::vector<Edge> edges_list_;
};

class Dsu {
 public:
  explicit Dsu(int n) : size_(n + 1), parent_(n + 1, -1), rank_(n + 1, 1) {
    for (int i = 0; i < n + 1; ++i) {
      parent_[i] = i;
    }
  }

  void MakeSet(int i) {
    parent_[i] = i;
    rank_[i] = 1;
    ++size_;
  }

  int FindSet(int x) {
    if (x == parent_[x]) {
      return x;
    }
    parent_[x] = FindSet(parent_[x]);
    return parent_[x];
  }

  void Union(int x, int y) {
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

 private:
  int size_;
  std::vector<int> parent_;
  std::vector<int> rank_;
};

int KruskalMST(Graph& graph, int size) {
  int weight = 0;
  std::vector<Edge> sorted_edges = graph.SortedEdges();
  Dsu dsu(size);
  for (auto& edge : sorted_edges) {
    if (dsu.FindSet(edge.from) != dsu.FindSet(edge.to)) {
      dsu.Union(edge.from, edge.to);
      weight += edge.weight;
    }
  }
  return weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph;
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int weight = 0;
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }
  std::cout << KruskalMST(graph, n);
}