#include <algorithm>
#include <cstddef>
#include <forward_list>
#include <unordered_map>
#include <vector>
enum class Color { White = 0, Grey = 1, Black = 2 };
struct Vertex {
  int d;
  int f;
  Color color;
  Vertex *pi;
  // Vertex *nextInAdj; // another way for vertex to remember next neighbor to visit
};

using AdjacentList = std::forward_list<Vertex *>;
using Graph = std::unordered_map<Vertex *, AdjacentList>;

void dfs_forest(Graph &graph, Graph &copy) {
  int time = 0;
  for (auto &[v, _] : graph) {
    if (v->color == Color::White) {
      time = time + 1;
      v->d = time;
      v->pi = nullptr;
      v->color = Color::Grey;
      std::vector<Vertex *> stack{v};
      while (!stack.empty()) {
        auto v = stack.back();
        copy[v].remove_if([](auto v) { return v->color != Color::White; });
        if (!copy[v].empty()) {
          auto u = copy[v].front();
          copy[v].pop_front();
          time = time + 1;
          u->d = time;
          u->pi = v;
          u->color = Color::Grey;
          copy[v].erase_after(copy[v].before_begin());
          stack.push_back(u);
        } else {
          stack.pop_back();
          time = time + 1;
          v->f = time;
          v->color = Color::Black;
        }
      }
    }
  }
}