#include <iostream>
#include <vector>
#include <set>

struct Graph {
  std::vector<std::vector<int>> matrix_;
  int size_;
  const int inf_ = 1'000'000'000;

  explicit Graph(int n) : matrix_(n + 1), size_(n + 1){};

  void Build() {
    for (int i = 0; i < size_; ++i) {
      matrix_[i].resize(size_);
      for (int j = 0; j < size_ - 1; ++j) {
        std::cin >> matrix_[i][j];
      }
    }
    for (int i = 0; i < size_ - 1; ++i) {
      matrix_[i][size_ - 1] = matrix_[size_ - 1][i];
    }
  }

  int ArgMin(std::vector<int>& dist, const std::vector<bool>& unvisit) {
    int ptr = -1;
    for (int i = 0; i < size_; ++i) {
      if (ptr == -1 || (unvisit[i] && (dist[ptr] > dist[i]))) {
        ptr = i;
      }
    }
    return ptr;
  }

  int PrimMst() {
    int weight = 0;
    std::vector<int> distance(size_, inf_);
    distance[0] = 0;
    std::vector<int> prev(size_, -1);
    std::set<int> unvisited;
    std::vector<bool> in_heap(size_, true);
    in_heap[0] = false;
    for (int i = 1; i < size_; ++i) {
      unvisited.insert(i);
    }
    int count = 0;
    while (count != size_) {
      int vertex = ArgMin(distance, in_heap);
      ++count;
      distance[vertex] = inf_;
      in_heap[vertex] = false;
      if (prev[vertex] != -1) {
        weight += matrix_[vertex][prev[vertex]];
      }
      for (int i = 0; i < size_; ++i) {
        if (in_heap[i] && distance[i] > matrix_[vertex][i]) {
          prev[i] = vertex;
          distance[i] = matrix_[vertex][i];
        }
      }
    }
    return weight;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  graph.Build();
  std::cout << graph.PrimMst();
}