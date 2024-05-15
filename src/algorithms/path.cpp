#include "path.hpp"
#include "../map.hpp"
#include <vector>
#include <queue>

bool is_walkable(pos p, Game* game){
    return game->map->tileMap[p.x][p.y]->walkable;
}

std::vector<pos> get_adjacent(pos p, Game* game){
    std::vector<pos> adj;
    for(int i = 0; i<=2; i++){
        for(int j = 0; j<=2; j++){
            if (i == 1 && j == 1) continue;
            if (!game->map->inMap(p.x, p.y)) continue;
            adj.push_back({p.x+i-1,p.y+j-1});
        }
    }
    return adj;
}

/* 1  procedure BFS(G, root) is
 2      let Q be a queue
 3      label root as explored
 4      Q.enqueue(root)
 5      while Q is not empty do
 6          v := Q.dequeue()
 7          if v is the goal then
 8              return v
 9          for all edges from v to w in G.adjacentEdges(v) do
10              if w is not labeled as explored then
11                  label w as explored
12                  w.parent := v
13                  Q.enqueue(w)
 * */

std::vector<pos> bfs(pos root, pos dst){
    std::queue<pos> q;
}

std::vector<pos> find_path(pos src, pos dest, Game* game){
    std::vector<pos> path;
    return path;
}
