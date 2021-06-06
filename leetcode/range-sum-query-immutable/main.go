type NumArray struct {
    psums []int
}

func Constructor(nums []int) NumArray {
    psums := make([]int, len(nums))
    for i, num := range nums {
        var rsum int
        if i == 0 {
            rsum = 0
        } else {
            rsum = psums[i - 1]
        }
        psums[i] = rsum + num
    }
    return NumArray{psums: psums}
}

func (this *NumArray) SumRange(left int, right int) int {
    if left == 0 {
        return this.psums[right]
    } else {
        return this.psums[right] - this.psums[left - 1]
    }
}



/**
 * Your NumArray object will be instantiated and called as such:
 * obj := Constructor(nums);
 * param_1 := obj.SumRange(left,right);
 */
