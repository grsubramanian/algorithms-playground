#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long L;
typedef vector<L> VL; 

// Returns all subset sums except that of the empty subset.
VL all_subset_sums(VL const & arr, int start, int end) {

    int num = end - start + 1;
    int num_subs = (1 << num);
    VL out(num_subs);

    for (int mask = 0; mask < num_subs; mask++) {

        L ans = 0;
        for (int b = start; b <= end; b++) {
            ans += (((mask >> (b - start)) & 1) ? arr[b] : 0);
        }
        out[mask] = ans;
    }

    return out;
}

int main() {

    int N; cin >> N;
    L A, B; cin >> A >> B;
    VL arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int M = N / 2;
    VL lsums(all_subset_sums(arr, 0, M - 1));
    VL rsums(all_subset_sums(arr, M, N - 1));
    sort(rsums.begin(), rsums.end());
    
    // Picking a subset from each side (including empty from either, or empty from both). 
    L ans = 0;
    for (int i = 0; i < lsums.size(); i++) {
        auto posl = lower_bound(rsums.begin(), rsums.end(), A - lsums[i]);
        auto posr = upper_bound(rsums.begin(), rsums.end(), B - lsums[i]);
        ans += distance(posl, posr);
    }
    cout << ans << "\n";

    return 0;
}
