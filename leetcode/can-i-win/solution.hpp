#include <vector>

using namespace std;

typedef vector<int> VI;

class Solution {

    public:
        bool canIWin(int maxnum, int total) {
            if (maxnum * (maxnum + 1) / 2 < total) {
                return false;
            }
            VI memo(1 << maxnum, -1);
            return dp(maxnum, total, 0, memo) == 1;
        }

    private:
        int dp(const int M, int total, int used, VI & memo) {
            if (memo[used] < 0) {
                int can_win = 0;
                for (int pick = 1, p = 1; pick <= M; pick++, p <<= 1) {
                    if (used & p) {
                        continue;
                    }

                    if ((pick >= total) || (dp(M, total - pick, used | p, memo) == 0)) {
                        can_win = 1;
                        break;
                    }
                }
                memo[used] = can_win;
            }

            return memo[used];
        }
};

