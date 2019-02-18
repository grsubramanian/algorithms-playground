#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > VVI;

typedef vector<double> VD;

int isset(int mask, int pos) {
    return (mask >> pos) & 1;
}

int cleared(int mask, int pos) {
    return mask & (~(1 << pos));
}

int main() {
    cout << fixed << setprecision(4);

    while (true) {
        int m; cin >> m;
        if (m == 0) {
            break;
        }

        VI price(m), area(m);
        VVI discount(m, VI(m));
        for (int i = 0; i < m; i++) {
            cin >> price[i] >> area[i];
            int ni; cin >> ni;
            for (int j = 0; j < ni; j++) {
                int xij, yij; cin >> xij >> yij; xij--;
                discount[i][xij] = yij;
            }
        }

        VD price_memo(1 << m);
        VD area_memo(1 << m);
        double ans = numeric_limits<double>::max();
        for (int mask = 1; mask < (1 << m); mask++) {
            // Let's look at total area for this collection of pizzas.
            int a = 0;
            for (int i = 0; i < m; i++) {
                if (!isset(mask, i)) {
                    // pizza not bought.
                    continue;
                }
                a += area[i];
            }
            area_memo[mask] = a;

            // Then, let's compute the optimal price.
            double best_p = numeric_limits<double>::max();
            for (int i = 0; i < m; i++) {
                if (!isset(mask, i)) {
                    // pizza not bought.
                    continue;
                }

                double pi = price[i];
                int nmask = cleared(mask, i);

                if (mask == (1 << i)) {
                    // i is the only pizza bought.
                    best_p = pi;
                    break;
                } else {
                    // Apply discounts for pizza i based on pizzas already bought.
                    for (int j = 0; j < m; j++) {
                        if (!isset(nmask, j)) {
                            // pizza not bought.
                            continue;
                        }
                        pi *= (((double) (100 - discount[j][i])) / 100);
                    }
                }

                best_p = min(best_p, pi + price_memo[nmask]);
            }
            price_memo[mask] = best_p;

            ans = min(ans, price_memo[mask] / area_memo[mask]);
        }

        cout << ans << "\n";
    }

    return 0;
}
