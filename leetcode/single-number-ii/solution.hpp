#include <limits>
#include <vector>

using namespace std;

typedef vector<int> VI;

class Solution {
    public:
        int singleNumber(VI & nums) {
    
            int ans = 0;
            int pow2 = 1;
            int bits_left = sizeof(int) * CHAR_BIT;
            while (bits_left--) { 
                int count_1s = 0;
                for (int num : nums) {
                    count_1s += ((num & pow2) != 0);
                }
                if (count_1s % 3 == 1) {
                    ans |= pow2;
                }
                if (bits_left > 0) {
                    pow2 <<= 1;
                }
            }

            return ans;
        }
};

