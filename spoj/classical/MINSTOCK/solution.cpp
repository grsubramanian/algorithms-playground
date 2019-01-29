#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

template<typename Key, typename Value, typename CompareFunc = less<Value>, typename SentinelValueFunc = Value>
class PriorityQueue {
    public:
        PriorityQueue(size_t max_num) :
            heap_(max_num),
            num_(0),
            pos_in_heap_(),
            compare_func_(CompareFunc()),
            sentinel_value_func_(SentinelValueFunc()) {}

        void insert(Key const & key, Value const & value) {
            insert_at_end(key, value);
            heapify_up(num_ - 1);
        }

        void remove(Key const & key) {
            size_t pos = pos_in_heap_.find(key)->second;
            swap(pos, num_ - 1);
            remove_from_end();

            if (pos > 0 && !compare_func_(posvalue(parent(pos)), posvalue(pos))) {
                heapify_up(pos);
            } else {
                heapify_down(pos);
            }
        }

        pair<Key, Value> const & front() const {
            return heap_[0];
        }

    private:

        static size_t parent(size_t pos) {
            return (pos - 1) / 2;
        }

        static size_t lchild(size_t pos) {
            return 2 * pos + 1;
        }

        static size_t rchild(size_t pos) {
            return 2 * pos + 2;
        }

        void heapify_up(size_t pos) {
            while (pos > 0 && !compare_func_(posvalue(parent(pos)), posvalue(pos))) {
                swap(pos, parent(pos));
                pos = parent(pos);
            }
        }

        void heapify_down(size_t pos) {
            while (true) {
                size_t lchild_pos = lchild(pos);
                Value lchild_value(sentinel_value_func_());
                if (lchild_pos < num_) {
                    lchild_value = posvalue(lchild_pos);
                } else {
                    break;
                }
                size_t rchild_pos = rchild(pos);
                Value rchild_value(sentinel_value_func_());
                if (rchild_pos < num_) {
                    rchild_value = posvalue(rchild_pos);
                }

                size_t child_pos;
                Value child_value;
                if (compare_func_(lchild_value, rchild_value)) {
                    child_pos = lchild_pos;
                    child_value = lchild_value;
                } else {
                    child_pos = rchild_pos;
                    child_value = rchild_value;
                }
                if (compare_func_(posvalue(pos), child_value)) {
                    break;
                }
                swap(pos, child_pos);
                pos = child_pos;
            }
        }

        void swap(size_t posa, size_t posb) {
            std::swap(heap_[posa], heap_[posb]);
            pos_in_heap_[heap_[posa].first] = posa;
            pos_in_heap_[heap_[posb].first] = posb;
        }

        void insert_at_end(Key const & key, Value const & value) {
            heap_[num_] = make_pair(key, value);
            pos_in_heap_.insert(make_pair(key, num_));
            num_++;
        }

        void remove_from_end() {
            pos_in_heap_.erase(heap_[num_ - 1].first);
            num_--;
        }

        Value const & posvalue(size_t pos) const {
            return heap_[pos].second;
        }

        vector<pair<Key, Value>> heap_;
        map<Key, size_t> pos_in_heap_;
        size_t num_;

        SentinelValueFunc sentinel_value_func_;
        CompareFunc compare_func_;
};

template<typename Numeric>
struct max_numeric_value {

    Numeric operator()() const {
        return numeric_limits<Numeric>::max();
    }
};

int main() {

    size_t N; cin >> N;
    PriorityQueue<string, LL, less<LL>, max_numeric_value<LL>> pq(N);

    for (size_t i = 1; i <= N; i++) {
        int itype; cin >> itype;
        string x; cin >> x;
        if (itype == 3) {
            pair<string, LL> node(pq.front());
            pq.remove(node.first);
            cout << node.first << " " << i << "\n";
        } else {
            LL y; cin >> y;
            if (itype == 2) {
                pq.remove(x);
            }
            pq.insert(x, y);
        }
    }

    return 0;
}
