#include <bits/stdc++.h>
using namespace std;

const int dr[4] = {-1,  0, +1,  0};
const int dc[4] = { 0, -1,  0, +1};

int getSecondsRequired(int R, int C, vector<vector<char>> G) {

  // Regular breadth-first search to find the shortest path from the start
  // cell to some ending cell.

  queue<pair<int, int>> bfsQueue;
  vector<vector<int>> distance(R, vector<int>(C, -1));
  
  vector<vector<pair<int, int>>> portalCellsByType(26);

  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      char ch = G[r][c];
      if (ch == 'S') {
        bfsQueue.push(make_pair(r, c));
        distance[r][c] = 0;
      } else if (ch >= 'a' && ch <= 'z') {
        portalCellsByType[ch - 'a'].push_back(make_pair(r, c));
      }
    }
  }
  
  while (!bfsQueue.empty()) {
    
    pair<int, int> cell = bfsQueue.front();
    bfsQueue.pop();
    
    int r = cell.first;
    int c = cell.second;
    
    for (int dir = 0; dir < 4; dir++) {
      
      int nr = r + dr[dir];
      int nc = c + dc[dir];
      
      if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
        continue;
      }
      
      if (G[nr][nc] == '#') {
        continue;
      }
      
      if (distance[nr][nc] >= 0) {
        continue; // already added to BFS queue in the past.
      }
      
      bfsQueue.push(make_pair(nr, nc));
      distance[nr][nc] = distance[r][c] + 1;
      
      if (G[nr][nc] == 'E') {
        return distance[nr][nc]; // short-circuit.
      }
    }
    
    char ch = G[r][c];
    if (ch < 'a' || ch > 'z') {
      continue;
    }
    
    // Portal cell, could teleport.
    for (pair<int, int> ncell : portalCellsByType[ch - 'a']) {
      int nr = ncell.first;
      int nc = ncell.second;
      if (distance[nr][nc] >= 0) {
        continue;
      }
      bfsQueue.push(make_pair(nr, nc));
      distance[nr][nc] = distance[r][c] + 1;
    }
    portalCellsByType[ch - 'a'].clear(); // the optimal solution shouldn't involve using the same portal type twice.
  }
  
  return -1;
}

