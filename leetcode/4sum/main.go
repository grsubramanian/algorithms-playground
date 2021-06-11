import (
    "sort"
)

func fourSum(nums []int, target int) [][]int {

    out := make([][]int, 0)
    if len(nums) < 4 {
        return out
    }

    var recurse func(int, int, int, []int)
    recurse = func(index int, N int, target int, work []int) {
        
        if N == 2 {
            // solve the 2 sum problem.
            // since array is sorted, we can solve this with 2 pointers
            // starting at the extremities and making their way in.
            
            start := index
            end := len(nums) - 1

            for start < end {
                sum := nums[start] + nums[end]
                if sum == target {

                    out = append(out, append(work, nums[start], nums[end]))

                    start++
                    end--

                    for start < end && nums[start] == nums[start - 1] {
                        start++
                    }
                    for start < end && nums[end] == nums[end + 1] {
                        end--
                    }

                } else if sum < target {
                    start++
                } else {
                    end--
                }
            }
        } else {
            // N > 2, we don't need to consider N == 1 or 0 cases.

            if target > N * nums[len(nums) - 1] {
                // not possible to get a solution down this path. So, terminate early.
                return
            }

            for i := index; i < len(nums) - (N - 1); i++ {
                if i == index || nums[i] != nums[i - 1] {
                    recurse(i + 1, N - 1, target - nums[i], append(work, nums[i]))
                }
            }
        }

    }

    sort.Ints(nums)
    recurse(0, 4, target, make([]int, 0))
    return out
}
