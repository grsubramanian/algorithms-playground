type NumArray struct {
    nums []int
    psums []int
}

func Constructor(nums []int) NumArray {
    return NumArray{nums: nums, psums: make([]int, 0)}
}

func (this *NumArray) GetPrefixSum(pos int) int {

    np := len(this.psums)
    if pos >= np {
        var rsum int
        if np == 0 {
            rsum = 0
        } else {
            rsum = this.psums[np - 1]
        }
        for i := np; i <= pos; i++ {
            rsum += this.nums[i]
            this.psums = append(this.psums, rsum)
        }
    }
    return this.psums[pos]

}

func (this *NumArray) SumRange(left int, right int) int {
    if left == 0 {
        return this.GetPrefixSum(right)
    } else {
        return this.GetPrefixSum(right) - this.GetPrefixSum(left - 1)
    }
}


/**
 * Your NumArray object will be instantiated and called as such:
 * obj := Constructor(nums);
 * param_1 := obj.SumRange(left,right);
 */
