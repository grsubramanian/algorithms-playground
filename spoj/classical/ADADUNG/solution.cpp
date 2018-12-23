#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

LL mod(LL a) {
    return a % 1000000007;
}

LL add(LL a, LL b) {
    return mod(a + b);
}

LL mul(LL a, LL b) {
    return mod(a * b);
}

class DerangementCache {

    public:
        DerangementCache():
            cache_(10000001, -1) {

            cache_[1] = 0;
            cache_[2] = 1;

            for (int i = 3; i < cache_.size(); i++) {
                cache_[i] = mul(mod(i - 1), add(cache_[i - 1], cache_[i - 2]));
            }
        }

        LL value(int N) const {
            return cache_[N];
        }

    private:
        vector<LL> cache_;
};

int main() {

    DerangementCache cache;

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        cout << cache.value(N) << "\n";
    }

    return 0;
}
