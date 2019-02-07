#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int, int> PI;

bool soldier_coverage_non_overlapping(VVI const & network, VI & covered, int start, int max_dist) {

    if (covered[start] == 1) {
        covered[start] = 2; // only to be consistent. don't need for problem.
        return false;
    }

    if (max_dist == 0) {
        covered[start] = 1;
    } else {
        VI covered_by_soldier(covered.size());
        covered_by_soldier[start] = 1;

        queue<PI> work;
        work.push(make_pair(start, 0));
        while (!work.empty()) {
            PI p(work.front()); work.pop();
            int c = p.first, d = p.second;
            for (int nc : network[c]) {
                if (covered[nc] == 1) {
                    covered[nc] = 2; // only to be consistent. don't need for problem.
                    return false;
                }

                if (covered_by_soldier[nc] == 1) {
                    continue;
                }

                int nd = d + 1;
                if (nd <= max_dist) {
                    covered_by_soldier[nc] = 1;
                    if (nd < max_dist) {
                        work.push(make_pair(nc, nd));
                    }
                }
            }
        }
        for (int i = 0; i < covered_by_soldier.size(); i++) {
            if (covered_by_soldier[i] == 1) {
                covered[i] = 1;
            }
        }
    }

    return true;
}

int main() {

    int T; cin >> T;
    while (T--) {
        int N, R, M; cin >> N >> R >> M;

        VVI network(N, VI());
        for (int i = 0; i < R; i++) {
            int r1, r2; cin >> r1 >> r2;
            r1--; r2--;
            network[r1].push_back(r2);
            network[r2].push_back(r1);
        }

        VI covered(N);
        bool non_overlapping = true;
        for (int j = 0; j < M; j++) {
            int K, S; cin >> K >> S;
            K--;
            if (!(non_overlapping = soldier_coverage_non_overlapping(network, covered, K, S))) {
                break;
            }
        }

        bool fully_covered =
            count_if(
                    covered.begin(),
                    covered.end(),
                    [](int d) { return d == 0; })
                == 0;
        if (non_overlapping && fully_covered) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
