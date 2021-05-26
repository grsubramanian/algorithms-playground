func search(nums []int, target int) int {
    
    start := 0
    end := len(nums)

    for start < end {
        mid := start + (end - start) / 2

        if nums[mid] == target {
            return mid
        } else if nums[mid] < target {
            start = mid + 1
        } else {
            end = mid
        }

    }
    return -1
}
