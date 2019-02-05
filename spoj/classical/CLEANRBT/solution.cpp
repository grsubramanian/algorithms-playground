#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

int dy[] = { -1, 0, 1,  0 };
int dx[] = {  0, 1, 0, -1 };

int shortest_plen(VI const & room, int m, int n, int start, int end) {
    if (start == end) {
        return 0;
    }

    VI distance(m * n, -1);
    distance[start] = 0;

    queue<int> work;
    work.push(start);

    while (!work.empty()) {
        int ind = work.front(); work.pop();
        int y = ind / n, x = ind % n;
        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k], nx = x + dx[k];
            if (ny < 0 || ny >= m || nx < 0 || nx >= n) {
                continue;
            }
            int nind = ny * n + nx;
            if (room[nind] == 1) {
                continue;
            }

            if (distance[nind] >= 0) {
                continue;
            }

            distance[nind] = distance[ind] + 1;
            if (nind == end) {
                return distance[nind];
            }
            work.push(nind);
        }
    }

    return -1;
}

int setmask(int mask, int pos) {
    return mask | (1 << pos);
}

int clearmask(int mask, int pos) {
    return ~setmask(~mask, pos);    
}

int getmask(int mask, int pos) {
    return (mask >> pos) & 1;
}

int main() {

    while (true) {
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }

        VI room(m * n);
        int start;
        VI points;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c; cin >> c;
                int ind = n * i + j;
                if (c == 'x') {
                    room[ind] = 1;
                } else if (c == 'o') {
                    start = ind;
                } else if (c == '*') {
                    points.push_back(ind);
                }
            }
        }

        points.insert(points.begin(), start);
        int N = points.size();
        VVI splen(N, VI(N));
        bool can_clean = true;
        for (int l = 0; l < N; l++) {
            for (int r = 0; r < N; r++) {
                if (l > r) {
                    splen[l][r] = splen[r][l];
                } else {
                    int x = shortest_plen(room, m, n, points[l], points[r]);
                    if (x < 0) {
                        can_clean = false;
                        break;
                    }
                    splen[l][r] = x;
                }
            }
        }

        if (!can_clean) {
            cout << "-1\n";
            continue;
        }

        VVI dpcache(N, VI(1 << N, numeric_limits<int>::max()));
        for (int s = 0; s < N; s++) {
            dpcache[s][0] = 0; // Nothing to do if all is clean.
            for (int u = 0; u < N; u++) {
                dpcache[s][1 << u] = splen[s][u]; // Just one dirty spot left.
            }
        }

        for (int bm = 1; bm < (1 << N); bm++) {
            for (int s = 0; s < N; s++) {
                if (getmask(bm, s)) {
                    // Start at a clean spot.
                    continue;
                }

                if (dpcache[s][bm] != numeric_limits<int>::max()) {
                    // Precomputed as base case.
                    continue;
                }

                for (int u = 0; u < N; u++) {
                    if (!getmask(bm, u)) {
                        // Pick a dirty spot to clean.
                        continue;
                    }

                    int ubm = clearmask(bm, u); // Clean spot u.
                    dpcache[s][bm] = min(dpcache[s][bm], splen[s][u] + dpcache[u][ubm]);
                }
            }
        }
        int init_bm = clearmask((1 << N) - 1, 0); // Initial bitmask with starting spot clean.
        cout << dpcache[0][init_bm] << "\n";
    }

    return 0;
}
