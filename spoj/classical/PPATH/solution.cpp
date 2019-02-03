#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> VI;

VI is_prime(10000, 1);

void identify_primes() {
    for (int i = 2; i <= 100; i++) {
        if (!is_prime[i]) {
            continue;
        }

        for (int j = i * i; j < 10000; j += i) {
            is_prime[j] = 0;
        }
    }
}

int pow10[] = { 1, 10, 100, 1000, 10000 };

int ppath(int a, int b) {

    if (a == b) {
        return 0;
    }

    VI distance(10000, -1);
    distance[a] = 0;

    queue<int> work;
    work.push(a);
    while (!work.empty()) {
        int c = work.front();
        work.pop();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == 3 && j == 0) {
                    // Do not want to add leading zeros.
                    continue;
                }

                int k = (c / pow10[i]) % 10;
                if (j == k) {
                    // Same as current number c.
                    continue;
                }

                int cn = c + (j - k) * pow10[i];
                if (!is_prime[cn]) {
                    continue;
                }
                
                if (distance[cn] >= 0) {
                    // already discovered.
                    continue;
                }

                distance[cn] = distance[c] + 1;
                if (cn == b) {
                    return distance[cn];
                }
                work.push(cn);
            }
        }
    }

    return -1;
}

int main() {

    identify_primes();

    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int len = ppath(a, b);
        if (len < 0) {
            cout << "Impossible";
        } else {
            cout << len;
        }
        cout << "\n";
    }
    return 0;
}
