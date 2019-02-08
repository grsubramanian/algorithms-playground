#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int, int> PI;
typedef vector< PI > VPI;
typedef vector< VPI > VVPI;
typedef queue<PI> QPI;

int main() {

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n <= 9) {
            cout << n << "\n";
            continue;
        }

        // last digit of num that has whose sum of digits = row, and remainder % n = column.
        VVI lastdig(n + 1, VI(n, -1));

        // (row, column) in (n + 1, n) matrix of the parent number.
        VVPI parent(n + 1, VPI(n));

        QPI work;
        for (int k = 1; k <= 9; k++) {
            lastdig[k][k % n] = k;
            work.push(make_pair(k, k % n));
        }

        while (!work.empty()) {
            PI pos(work.front()); work.pop();
            int r = pos.first, c = pos.second;
            
            for (int nextdig = 0; nextdig <= 9; nextdig++) {
                int nr = r + nextdig, nc = (c * 10 + nextdig) % n;
                if (nr > n) {
                    continue;
                }

                if (lastdig[nr][nc] >= 0) {
                    // discovered a better way to get here before.
                    continue;
                }

                lastdig[nr][nc] = nextdig;
                parent[nr][nc] = make_pair(r, c);
                work.push(make_pair(nr, nc));

                if (nr == n && nc == 0) {
                    break;
                }
            }
        }

        stringstream ss;
        int r = n, c = 0;
        while (!(r == 0 && c == 0)) {
            ss << lastdig[r][c];
            PI p(parent[r][c]);
            r = p.first, c = p.second;
        }
        string out(ss.str());
        reverse(out.begin(), out.end());
        cout << out << "\n";
    }

    return 0;
}
