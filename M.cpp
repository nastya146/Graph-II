#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <unordered_map>

class Graph {
 public:
  explicit Graph(int n) : size_(n), matrix_(n) {
  }

  void Build() {
    for (int i = 0; i < size_; ++i) {
      matrix_[i].resize(size_);
      for (int j = 0; j < size_; ++j) {
        std::cin >> matrix_[i][j];
      }
    }
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

  std::vector<std::vector<int>> FloydWarshall() {
    std::vector<std::vector<std::vector<int>>> dp(size_ + 1);
    dp[0] = matrix_;
    for (int k = 1; k <= size_; ++k) {
      dp[k].resize(size_);
      for (int from = 0; from < size_; ++from) {
        dp[k][from].resize(size_);
        for (int to = 0; to < size_; ++to) {
          dp[k][from][to] = std::min(dp[k - 1][from][to], dp[k - 1][from][k - 1] + dp[k - 1][k - 1][to]);
        }
      }
    }
    return dp[size_];
  }

 private:
  int size_;
  std::vector<std::vector<int>> matrix_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  graph.Build();
  std::vector<std::vector<int>> paths = graph.FloydWarshall();
  for (auto& from : paths) {
    for (auto& length : from) {
      std::cout << length << " ";
    }
    std::cout << "\n";
  }
}