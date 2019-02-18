#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

class Solution {
    public:
        int getMoneyAmount(int n) {
            VVI worst_case_cost(n + 1, VI(n + 1));

            for (int end = 1; end <= n; end++) {
                for (int start = end - 1; start > 0; start--) {
                    
                    int lowest_worst_case_cost = numeric_limits<int>::max();

                    for (int pick = start; pick <= end; pick++) {

                        int worst_case_cost_with_pick = 0;
                        if (pick > start) {
                            worst_case_cost_with_pick = pick + worst_case_cost[start][pick - 1];
                        }
                        if (pick < end) {
                            worst_case_cost_with_pick = max(worst_case_cost_with_pick, pick + worst_case_cost[pick + 1][end]);
                        }

                        lowest_worst_case_cost = min(lowest_worst_case_cost, worst_case_cost_with_pick);
                    }

                    worst_case_cost[start][end] = lowest_worst_case_cost;
                }
            }

            return worst_case_cost[1][n];
        }
};
