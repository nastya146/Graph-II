#include <vector>
#include <iostream>

class Dsu {
 public:
  explicit Dsu(int n) : size_(n), parent_(n, -1), rank_(n, 1) {
    for (int i = 0; i < n; ++i) {
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

  int CountSet() {
    return size_;
  }

 private:
  int size_;
  std::vector<int> parent_;
  std::vector<int> rank_;
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Dsu dsu(n);
  std::vector<std::pair<int, int>> edges(m);
  for (auto& u : edges) {
    std::cin >> u.first >> u.second;
  }
  for (int i = 0; i < m; ++i) {
    int u = edges[i].first;
    int v = edges[i].second;
    dsu.Union(u, v);
    if (dsu.CountSet() == 1) {
      std::cout << i + 1;
      break;
    }
  }
}