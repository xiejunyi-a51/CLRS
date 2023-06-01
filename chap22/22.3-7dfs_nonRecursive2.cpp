#include <algorithm>
#include <cstddef>
#include <forward_list>
#include <unordered_map>
#include <vector>
enum class Color { White = 0, Grey = 1, Black = 2 };
struct Vertex {
  int d = 0;
  int f = 0;
  Color color;
  Vertex *pi = nullptr;
};

using AdjacentList = std::forward_list<Vertex *>;
using Graph = std::unordered_map<Vertex *, AdjacentList>;

void dfs_forest(Graph &graph) {
  int time = 0;
  for (auto node : graph) {
    if (node.first->color == Color::White) {
      std::vector<Vertex *> stack{node.first};
      while (!stack.empty()) {
        auto u = stack.back();
        if (u->color == Color::White) {
          u->color = Color::Grey;
          time = time + 1;
          u->d = time;
          for (auto v : graph[u]) {
            if (v->color == Color::White) {
              v->pi = u;
              stack.push_back(v);
            }
          }
        }
        else if (u->color == Color::Grey)
        {
          time = time + 1;
          u->f = time;
          u->color = Color::Black;
          stack.pop_back();
        }
        else {
          stack.pop_back();
        }
      }
    }
  }
}