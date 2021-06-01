package main

import (
    "fmt"
    "sort"
)

func intersection(nums1 []int, nums2 []int) []int {
    out := make([]int, 0)
    
    sort.Ints(nums1)
    sort.Ints(nums2)

    head1 := 0
    head2 := 0

    len1 := len(nums1)
    len2 := len(nums2)

    for head1 < len1 && head2 < len2 {
        n1 := nums1[head1]
        n2 := nums2[head2]
        if n1 == n2 {
            out = append(out, n1)
            for head1 < len1 && nums1[head1] == n1 {
                head1++
            }
            for head2 < len2 && nums2[head2] == n2 {
                head2++
            }
        } else if n1 < n2 {
            head1++
        } else {
            head2++
        }
    }

    return out
}

func main() {
    nums1 := []int{1, 2, 3}
    nums2 := []int{10, 6, 3}

    intersection(nums1, nums2)
    fmt.Printf("%v, %v\n", nums1, nums2)

}
