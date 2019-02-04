#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

// <height, row, col>
typedef tuple<int, int, int> Point;
typedef pair<int, int> PI;

int dy[] = { -1, 0, 1,  0 };
int dx[] = {  0, 1, 0, -1};

int water(VVI & grid) {
    int m = grid.size(), n = grid[0].size();

    // Init with points on boundary sorted by height from smallest to largest.
    priority_queue<Point, vector<Point>, greater<Point>> points;
    for (int i = 0; i < m; i++) {
        points.push(make_tuple(grid[i][0], i, 0));
        if (n > 1) {
            points.push(make_tuple(grid[i][n - 1], i, n - 1));
        }
    }
    for (int j = 1; j < n - 1; j++) {
        points.push(make_tuple(grid[0][j], 0, j));
        if (m > 1) {
            points.push(make_tuple(grid[m - 1][j], m - 1, j));
        }
    }

    int ans = 0;
    while (!points.empty()) {
        Point boundary_point(points.top()); points.pop();

        int bph = get<0>(boundary_point),
            bpy = get<1>(boundary_point),
            bpx = get<2>(boundary_point);

        queue<PI> work;
        work.push(make_pair(bpy, bpx));
        grid[bpy][bpx] = -1;

        while (!work.empty()) {
            PI pos(work.front()); work.pop();
            int y = pos.first, x = pos.second;
            for (int k = 0; k < 4; k++) {
                int ny = y + dy[k], nx = x + dx[k];
                if (ny < 0 || ny >= m || nx < 0 || nx >= n) {
                    continue;
                }

                int nh = grid[ny][nx];
                if (nh < 0) {
                    // Final height reached.
                    continue;
                }

                if (nh > bph) {
                    // Expand boundary.
                    points.push(make_tuple(nh, ny, nx));
                    continue;
                }

                ans += (bph - nh); // Submerge in water.
                work.push(make_pair(ny, nx));
                grid[ny][nx] = -1; // Now flooded, can't collect more water.
            }
        }
    }
    return ans;
}

int main() {
    int t; cin >> t;
    while (t--) {
        int m, n; cin >> m >> n; // relabeling m, n for cognitive convenience.

        VVI grid(m, VI(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        cout << water(grid) << "\n";
    }

    return 0;
}
