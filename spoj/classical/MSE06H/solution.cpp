#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
typedef vector< LL > VLL;

typedef vector<int> VI;
typedef vector< VI > VVI;

class BIT {

    public:
        BIT(int num): bit_(num + 1) {}

        LL total_sum() const {
            return prefix_sum(bit_.size() - 1);
        }

        LL prefix_sum(int pos) const {
            LL out = 0;
            while (pos > 0) {
                out += bit_[pos];
                pos -= (pos & -pos);
            }
            return out;
        }

        void increment(int pos, int val) {
            while (pos < bit_.size()) {
                bit_[pos] += val;
                pos += (pos & -pos);
            }
        }

    private:
        VLL bit_;
};

int main() {

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, M, K; cin >> N >> M >> K;
        VVI adjacencies(N + 1, VI());
        for (int k = 0; k < K; k++) {
            int e, w; cin >> e >> w;
            adjacencies[e].push_back(w);
        }

        LL num_crosses = 0;
        BIT bit(M);
        for (int e = 1; e <= N; e++) {
            for (int w : adjacencies[e]) {
                num_crosses += bit.total_sum() - bit.prefix_sum(w);
            }
            for (int w : adjacencies[e]) {
                bit.increment(w, 1);
            }
        }
        
        cout << "Test case " << t << ": " << num_crosses << "\n"; 
    }
    return 0;
}
