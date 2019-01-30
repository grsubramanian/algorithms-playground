#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int, int> PI;
typedef vector< PI > VPI;

VPI openings(VVI const & maze) {
    VPI openings;

    int m = maze.size(), n = maze[0].size();
    for (int i = 0; i < m; i++) {
        if (maze[i][0] == 0) {
            openings.emplace_back(i, 0);
        }
        if (n > 1 && maze[i][n - 1] == 0) {
            openings.emplace_back(i, n - 1);
        }
    }

    for (int j = 1; j < n - 1; j++) {
        if (maze[0][j] == 0) {
            openings.emplace_back(0, j);
        }
        if (m > 1 && maze[m - 1][j] == 0) {
            openings.emplace_back(m - 1, j);
        }
    }
    return openings;
}

int dy[] = { -1, 0, 1,  0 };
int dx[] = {  0, 1, 0, -1 };

bool valid_based_on_bfs(VVI & maze) {
    int m = maze.size(), n = maze[0].size();
    VPI o(openings(maze));
    if (o.size() != 2) {
        return false;
    }

    maze[o[0].first][o[0].second] = 2;
    queue<PI> work;
    work.push(o[0]);
    while (!work.empty()) {
        PI p(work.front());
        work.pop();
        int y = p.first, x = p.second;
        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k], nx = x + dx[k];
            if (ny < 0 || ny >= m || nx < 0 || nx >= n) {
                continue;
            }

            if (maze[ny][nx] != 0) {
                continue;
            }

            maze[ny][nx] = 2;
            PI q(ny, nx);
            if (q == o[1]) {
                return true;
            }
            work.push(q);
        }
    }

    return maze[o[1].first][o[1].second] == 2;
}

bool valid_based_on_dfs(VVI & maze) {
    int m = maze.size(), n = maze[0].size();
    VPI o(openings(maze));
    if (o.size() != 2) {
        return false;
    }

    stack<PI> work;
    work.push(o[0]);
    while (!work.empty()) {
        PI p(work.top());
        work.pop();
        int y = p.first, x = p.second;
        if (maze[y][x] == 2) {
            continue;
        }
        maze[y][x] = 2;
        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k], nx = x + dx[k];
            if (ny < 0 || ny >= m || nx < 0 || nx >= n) {
                continue;
            }

            if (maze[ny][nx] != 0) {
                continue;
            }

            PI q(ny, nx);
            if (q == o[1]) {
                return true;
            }
            work.push(q);
        }
    }

    return maze[o[1].first][o[1].second] == 2;
}

bool valid(VVI & maze) {
    return valid_based_on_dfs(maze);
}

int main() {
    
    int t; cin >> t;
    while (t--) {
        int m, n; cin >> m >> n;
        VVI maze(m, VI(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c; cin >> c;
                maze[i][j] = (c == '#') ? 1 : 0;
            }
        }
        if (valid(maze)) {
            cout << "valid\n";
        } else {
            cout << "invalid\n";
        }
    }
 
    return 0;
}
