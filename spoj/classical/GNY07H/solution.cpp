#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;

int main() {

    VI memo0(1), // solutions with W X 4 grid
       memo1(1), // solutions with W X 4 grid and an extra vertical 2 X 1 frees slot 
                 // aligned with top boundary or bottom boundary.
       memo2(1); // same as memo1, except the vertical 2 X 1 free slot is in the middle.

    memo0[0] = memo1[0] = memo2[0] = 1;
    
    int T; cin >> T; // rewired from N.
    for (int t = 1; t <= T; t++) {
        int W; cin >> W;
        int sz = memo0.size();
        if (W >= sz) {
            memo0.resize(W + 1);
            memo1.resize(W + 1);
            memo2.resize(W + 1);

            for (int w = sz; w <= W; w++) {
                memo0[w] = memo1[w - 1];
                if (w >= 2) {
                    memo0[w] += memo0[w - 2] + memo1[w - 2] + memo2[w - 2];
                }

                memo1[w] = memo0[w] + memo1[w - 1];

                memo2[w] = memo0[w];
                if (w >= 2) {
                    memo2[w] += memo2[w - 2];
                }
            }
        }

        cout << t << " " << memo0[W] << "\n";
    }
    

    return 0;
}
