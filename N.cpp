#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <unordered_map>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : size_(n + 1), vertex_list_(n + 1) {
  }

  // 0-white, 1-gray, 2-black
  void DFS(int vertex, int end, std::vector<int>& colours, std::vector<std::pair<int, int>>& prev) {
    colours[vertex] = 1;
    for (auto& [u, cap] : vertex_list_[vertex]) {
      if (colours[u] == 0 && cap > 0) {
        prev[u] = std::make_pair(vertex, cap);
        if (u == end) {
          return;
        }
        DFS(u, end, colours, prev);
      }
    }
    colours[vertex] = 2;
  }

  void AddWeightedEdge(int from, int to, int weight) {
    int cur_weight = vertex_list_[from][to];
    if (cur_weight == 0 || cur_weight > weight) {
      vertex_list_[from][to] = weight;
    }
  }

  int FordFulkerson(int begin, int end) {
    int flow = 0;
    std::vector<int> colours(size_, 0);
    std::vector<std::pair<int, int>> marks(size_, std::make_pair(-1, 0));
    DFS(begin, end, colours, marks);
    while (marks[end].first != -1) {
      int prev = end;
      int cur_flow = marks[prev].second;
      std::queue<int> river;
      river.push(end);
      while (prev != begin) {
        river.push(prev);
        cur_flow = std::min(cur_flow, marks[prev].second);
        prev = marks[prev].first;
      }
      flow += cur_flow;
      river.push(begin);
      while (river.front() != begin) {
        int to = river.front();
        river.pop();
        int from = river.front();
        vertex_list_[from][to] -= cur_flow;
        vertex_list_[to][from] += cur_flow;
      }
      colours.clear();
      marks.clear();
      colours.resize(size_, 0);
      marks.resize(size_, std::make_pair(-1, 0));
      DFS(begin, end, colours, marks);
    }
    return flow;
  }

 private:
  int size_;
  std::vector<std::unordered_map<int, int>> vertex_list_;
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
    int capacity = 0;
    std::cin >> vertex1 >> vertex2 >> capacity;
    graph.AddWeightedEdge(vertex1, vertex2, capacity);
  }
  std::cout << graph.FordFulkerson(1, n);
}