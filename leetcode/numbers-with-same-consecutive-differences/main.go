import (
    "math"
)

func numsSameConsecDiff(n int, k int) []int {

    out := make([]int, 0)

    work := 0

    var backtrack func(int)
    backtrack = func(pos int) {

        if pos == n {
            out = append(out, work)
        } else {
            multiplier := int(math.Pow(10, float64(n - 1 - pos)))
            for digit := 0; digit <= 9; digit++ {
                var can_try bool
                if pos == 0 {
                    can_try = digit > 0
                } else {
                    diff := digit - (work / int(math.Pow(10, float64(n - pos)))) % 10
                    if diff < 0 {
                        diff = -diff
                    }
                    can_try = diff == k
                }
                if can_try {
                    work += digit * multiplier
                    backtrack(pos + 1)
                    work -= digit * multiplier
                }
            }
        }
    }

    backtrack(0)
    return out
}
