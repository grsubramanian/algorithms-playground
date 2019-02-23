#include <vector>

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PI;
typedef vector< PI > VPI;

class Solution {
    public:
        int maxProfitAssignment(VI const & difficulty, VI const & profit, VI & worker) {
            int N = difficulty.size();
            VPI jobs(N);
            for (int i = 0; i < N; i++) {
                jobs[i].first = difficulty[i];
                jobs[i].second = profit[i];
            }
            sort(jobs.begin(), jobs.end());
            sort(worker.begin(), worker.end());

            int ans = 0, i = 0, best = 0;
            for (int j = 0; j < worker.size(); j++) {
                
                while ((i < N) && (jobs[i].first <= worker[j])) {
                    best = max(best, jobs[i].second);
                    i++;
                }

                ans += best;
            }

            return ans;
        }
};
