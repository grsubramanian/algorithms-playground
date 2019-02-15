#include <iostream>
#include <vector>

using namespace std;

typedef long long L;
typedef vector<L> VL;

int main() {

    int t; cin >> t;
    while (t--) {

        int n, u; cin >> n >> u;
        VL arr(n);
        while (u--) {
            int l, r, val; cin >> l >> r >> val;
            arr[l] += val;
            if (r < n - 1) {
                arr[r + 1] -= val;
            }
        }

        L cum = 0;
        for (int i = 0; i < n; i++) {
            L cumi = arr[i];
            arr[i] += cum;
            cum += cumi;
        }

        int q; cin >> q;
        while (q--) {
            int pos; cin >> pos;
            cout << arr[pos] << "\n";
        }
    }
    
    return 0;
}
