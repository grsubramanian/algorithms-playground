#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> Node;

typedef vector<char> VC;
typedef vector< VC > VVC;

typedef vector<int> VI;
typedef vector< VI > VVI;
typedef vector< VVI > VVVI;

int dy[] = { -1, 0, 1,  0 };
int dx[] = {  0, 1, 0, -1 };

void set(int & bitmask, int pos) {
    bitmask |= (1 << pos);
}

int isset(int bitmask, int pos) {
    return (bitmask >> pos) & 1;
}

int main() {
 
    while (true) {
        int M, N; cin >> M >> N;
        if (M == 0 && N == 0) {
            break;
        }

        VVC maze(M, VC(N, '.'));
        int start_y = 0, start_x = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                char c; cin >> c;
                if (c == '*') {
                    start_y = i;
                    start_x = j;
                }
                if      (c == 'R') { c = 'A'; }
                else if (c == 'r') { c = 'a'; }
                else if (c == 'G') { c = 'C'; }
                else if (c == 'g') { c = 'c'; }
                else if (c == 'Y') { c = 'D'; }
                else if (c == 'y') { c = 'd'; }
                // B and b remain the same.
                //

                maze[i][j] = c;
            }
        }

        VVVI distance(M, VVI(N, VI(16, -1)));
        distance[start_y][start_x][0] = 0;

        Node node(make_tuple(start_y, start_x, 0));
        queue<Node> work;
        work.push(node);

        while (!work.empty()) {
            Node node(work.front());
            work.pop();

            int y = get<0>(node), x = get<1>(node), bm = get<2>(node);
            
            for (int k = 0; k < 4; k++) {
                int ny = y + dy[k], nx = x + dx[k], nbm = bm;
                if (ny < 0 || ny >= M || nx < 0 || nx >= N) {
                    continue;
                }

                char c = maze[ny][nx];
                if (c == '#') {
                    continue;
                }
                
                if (c >= 'A' && c <= 'D') {
                    // Door.
                    if (!isset(nbm, c - 'A')) {
                        continue;
                    }
                } else if (c >= 'a' && c <= 'd') {
                    set(nbm, c - 'a');
                }

                if (distance[ny][nx][nbm] >= 0) {
                    continue;
                }

                distance[ny][nx][nbm] = distance[y][x][bm] + 1;
                work.push(make_tuple(ny, nx, nbm));
            }
        }

        int steps = -1;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (maze[i][j] == 'X') {
                    for (int l = 0; l < 16; l++) {
                        int dist = distance[i][j][l];
                        if (dist >= 0) {
                            if (steps == -1) {
                                steps = dist;
                            } else {
                                steps = min(steps, dist);
                            }
                        }
                    }
                }
            }
        }

        if (steps < 0) {
            cout << "The poor student is trapped!\n";
        } else {
            cout << "Escape possible in " << steps << " steps.\n";
        }
    }
    return 0;
}
