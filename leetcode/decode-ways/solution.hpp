#include <vector>

using namespace std;

typedef vector<int> VI;

class Solution {
    public:
        int numDecodings(string const & s) {
            int N = s.size();
            VI memo(N + 1);
            memo[N] = 1;
            memo[N - 1] = can_start_at(s, N - 1) ? 1 : 0;
            for (int i = N - 2; i >= 0; i--) {
                if (!can_start_at(s, i)) {
                    continue;
                }
                memo[i] = memo[i + 1] + (can_pair_with_next(s, i) ? memo[i + 2] : 0);
            }

            return memo[0];
        }
    private:
        bool can_start_at(string const & s, int pos) {
            return s[pos] != '0';
        }

        bool can_pair_with_next(string const & s, int pos) {
            return (s[pos] == '1') || (s[pos] == '2' && s[pos + 1] <= '6');
        }
};
