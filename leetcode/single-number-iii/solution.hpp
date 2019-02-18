#include <vector>

using namespace std;

typedef vector<int> VI;

class Solution {
    public:
        VI singleNumber(VI & nums) {

            int xor_all = 0;
            for (int num : nums) {
                xor_all ^= num;
            }

            // We need to partition nums into two sets, such that the two
            // special elements we desire go to different partitions. Then,
            // we can simply do xor in each partition to get the special
            // elements.
            //
            // Here's a partitioner.
            //
            // It doesn't really matter which 1 bit of xor_all we check.
            // Using the right most one allows clever bit arithmetic
            // similar to the one used in Binary Indexed Trees.
            // e.g. if xor_all = 10101100, xor_all_rmost_1_bit = 100
            int xor_all_rmost_1_bit = xor_all & -xor_all;

            int a = 0, b = 0;
            for (int num : nums) {
                if (num & xor_all_rmost_1_bit) {
                    a ^= num;
                } else {
                    b ^= num;
                }
            }
            return {a, b};
        }
};
