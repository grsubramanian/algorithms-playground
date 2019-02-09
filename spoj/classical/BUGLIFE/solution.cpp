#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

bool bipartite(VVI const & adj) {

    int n = adj.size();
    VI color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] >= 0) {
            continue;
        }
        color[i] = 0;

        stack<int> work;
        work.push(i);
        while (!work.empty()) {
            int b = work.top(); work.pop();
            int bcolor = color[b];
            for (int c : adj[b]) {
                int ccolor = 1 - bcolor;
                if (color[c] < 0) {
                    // never discovered.
                    color[c] = ccolor;
                    work.push(c);
                } else {
                    if (color[c] == bcolor) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, m; cin >> n >> m;

        VVI adj(n, VI());
        for (int i = 0; i < m; i++) {
            int b1, b2; cin >> b1 >> b2; b1--; b2--;
            adj[b1].push_back(b2);
            adj[b2].push_back(b1);
        }

        cout << "Scenario #" << t << ":\n";
        if (bipartite(adj)) {
            cout << "No suspicious bugs found!\n";
        } else {
            cout << "Suspicious bugs found!\n";
        }
    }

    return 0;
}
