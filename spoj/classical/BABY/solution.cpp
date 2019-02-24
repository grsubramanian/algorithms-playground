#include <iostream>
#include <limits>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

void read_vector(VI & v) {
    for (int i = 0; i < v.size(); i++) {
        cin >> v[i];
    }
}

int dp(int row, int mask, VVI & memo, VI const & start, VI const & end) {
    if (row == memo.size()) {
        // all queens have been moved into their final positions.
        return 0;
    }
    if (memo[row][mask] < 0) {
        
        int ans = numeric_limits<int>::max();
        for (int i = 0; i < memo.size(); i++) {
            if (mask & (1 << i)) {
                // the final position on row i been occupied.
                continue;
            }
            ans = min(ans,
                    abs(row - i) + // need to move the queen on row 'row' to final position on row i.
                    abs(start[row] - end[i]) + // then, need to move this queen to column end[i].
                    dp(row + 1, mask | (1 << i), memo, start, end));
        }
        memo[row][mask] = ans;
    }
    return memo[row][mask];
}

int main() {

    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }

        VI start(n);
        read_vector(start);
        VI end(n);
        read_vector(end);


        VVI memo(n, VI(1 << n, -1));
        cout << dp(0, 0, memo, start, end) << "\n";
    }

    return 0;
}
