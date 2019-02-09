#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long L;
typedef vector<L> VL;
typedef vector<int> VI;

L prefix_count(VL const & bit, int idx) {

    L ans = 0;
    while (idx > 0) {
        ans += bit[idx];
        idx -= (idx & -idx);
    }
    return ans;
}

L total_count(VL const & bit) {
    return prefix_count(bit, bit.size() - 1);
}

void increment(VL & bit, int idx) {
    while (idx < bit.size()) {
        bit[idx] += 1;
        idx += (idx & -idx);
    }
}

int main() {

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        VI arr(n);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // Compress arr elements into the range [1, n].
        VI arr2(arr);
        sort(arr2.begin(), arr2.end());
        for (int i = 0; i < n; i++) {
            int sorted_idx = upper_bound(arr2.begin(), arr2.end(), arr[i]) - arr2.begin();
            arr[i] = sorted_idx; // 1-indexed position in sorted order.
        }

        // Binary Indexed Tree to count the number of elements greater in array prefix.
        VL bit(n + 1); 

        L ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (total_count(bit) - prefix_count(bit, arr[i]));
            increment(bit, arr[i]);
        }
        cout << ans << "\n";
    }
    return 0;
}
