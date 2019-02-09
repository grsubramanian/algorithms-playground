#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;
typedef stack<int> SI;

void rec(VVI const & adj, VI const & parent, int s, VI & longest_path_memo, VI & longest_r2l_path_memo) {

    if (longest_path_memo[s] >= 0) {
        return;
    }

    int longest_path = 0, longest_r2l_path = 0, second_longest_r2l_path = 0;

    int num_branches = 0;
    for (int ns : adj[s]) {
        if (ns == parent[s]) {
            continue;
        }
        rec(adj, parent, ns, longest_path_memo, longest_r2l_path_memo);

        int longest_r2l_path_in_branch = longest_r2l_path_memo[ns] + 1;
        longest_path = max(longest_path, longest_path_memo[ns]);
        longest_path = max(longest_path, longest_r2l_path_in_branch);
        num_branches++;
        
        second_longest_r2l_path = max(second_longest_r2l_path, longest_r2l_path_in_branch);
        int temp = min(longest_r2l_path, second_longest_r2l_path);
        longest_r2l_path = max(longest_r2l_path, second_longest_r2l_path);
        second_longest_r2l_path = temp;
    }

    if (num_branches >= 2) {
        longest_path = max(longest_path, longest_r2l_path + second_longest_r2l_path);
    }

    longest_path_memo[s] = longest_path;
    longest_r2l_path_memo[s] = longest_r2l_path;
}

int main() {

    int N; cin >> N;
    VVI adj(N, VI());
    for (int i = 0; i < (N - 1); i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int R; cin >> R; R--;
    VI parent(N, -1);
    parent[R] = R;

    SI work;
    work.push(R);
    while (!work.empty()) {
        int x = work.top(); work.pop();
        for (int nx : adj[x]) {
            if (parent[nx] != -1) {
                continue; // to avoid revisiting the the parent in the tree.
            }
            parent[nx] = x;
            work.push(nx);
        }
    }

    VI longest_path_memo(N, -1), longest_r2l_path_memo(N, -1);
    
    int Q; cin >> Q;
    for (int q = 0; q < Q; q++) {
        int s; cin >> s; s--;
        rec(adj, parent, s, longest_path_memo, longest_r2l_path_memo);
        cout << longest_path_memo[s] << "\n";
    }

    return 0;
}
