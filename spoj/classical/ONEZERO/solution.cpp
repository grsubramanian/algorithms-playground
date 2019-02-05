#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PI;

string repr_to_str(int repr) {
    stringstream ss;
    while (repr) {
        ss << (repr & 1);
        repr >>= 1;
    }
    string out = ss.str();
    reverse(out.begin(), out.end());
    return out;
}

int dig[] = { 0, 1 };
string smallest_10_multiple(int n) {
    // Generally speaking, this is bad code since we don't
    // explicitly deallocate allocated memory on the heap.

    PI root(1 % n, 1);
    queue<PI> work;
    work.push(root);

    while (!work.empty()) {
        PI node(work.front()); work.pop();

        if (node.first == 0) {
            return repr_to_str(node.second);
        }

        for (int k = 0; k < 2; k++) {
            PI child((node.first * 10 + dig[k]) % n, (node.second << 1) + dig[k]);
            if (child.first == 0) {
                return repr_to_str(child.second);
            }
            work.push(child);
        }
    }
    return ""; // should not happen.
}

string memo[20001];
int main() {

    int K; cin >> K;
    while (K--) {
        int n; cin >> n;
        if (memo[n].empty()) {
            memo[n] = smallest_10_multiple(n);
        }
        cout << memo[n] << "\n";
    }

    return 0;
}
