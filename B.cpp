#include <vector>
#include <iostream>

class Dsu {
 public:
  explicit Dsu(int n) : size_(n), parent_(n + 1, -1), rank_(n + 1, 1), weight_(n + 1, 0) {
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

  int Weight(int x) {
    return weight_[FindSet(x)];
  }

  void Union(int x, int y, int weight) {
    x = FindSet(x);
    y = FindSet(y);
    if (x != y) {
      int new_weight = weight_[x] + weight_[y] + weight;
      int parent = y;
      if (rank_[x] < rank_[y]) {
        parent_[x] = y;
      } else if (rank_[y] < rank_[x]) {
        parent_[y] = x;
        parent = x;
      } else {
        parent_[x] = y;
        ++rank_[y];
      }
      --size_;
      weight_[parent] = new_weight;
      return;
    }
    weight_[x] += weight;
  }

 public:
  int size_;
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> weight_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Dsu dsu(n);
  for (int i = 0; i < m; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      int first = 0;
      int second = 0;
      int weight = 0;
      std::cin >> first >> second >> weight;
      dsu.Union(first, second, weight);
    } else if (command == 2) {
      int vertex = 0;
      std::cin >> vertex;
      std::cout << dsu.Weight(vertex) << "\n";
    }
  }
}