/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isSubPath(head *ListNode, root *TreeNode) bool {

    if head == nil {
        return true
    }

    // arrays are easier to random access, so we'll use this instead of the original linked list.
    listAsArray := make([]int, 0)
    listAsArray = append(listAsArray, head.Val)
    
    // Use KMP to find out the lengths of longest proper prefixes that are also suffixes for each position
    // in the linked list.
    lenOfLongestPrefixAlsoSuffix := make([]int, 0)
    lenOfLongestPrefixAlsoSuffix = append(lenOfLongestPrefixAlsoSuffix, 0)
    
    listPos := 0
    head = head.Next
    for head != nil {

        for listPos > 0 && head.Val != listAsArray[listPos] {
            listPos = lenOfLongestPrefixAlsoSuffix[listPos - 1]
        }
        if head.Val != listAsArray[listPos] {
            listPos++
        }

        lenOfLongestPrefixAlsoSuffix = append(lenOfLongestPrefixAlsoSuffix, listPos)
        listAsArray = append(listAsArray, head.Val)
        head = head.Next
    }


    var dfs func(*TreeNode, int, []int, []int) bool 
    dfs = func(node *TreeNode, listPos int, listAsArray []int, lenOfLongestPrefixAlsoSuffix []int) bool {
        if node == nil {
            return false
        }

        for listPos > 0 && node.Val != listAsArray[listPos] {
            listPos = lenOfLongestPrefixAlsoSuffix[listPos - 1]
        }
        if node.Val != listAsArray[listPos] {
            listPos++
        }
        return listPos == len(listAsArray)
            || dfs(node.Left, listPos, listAsArray, lenOfLongestPrefixAlsoSuffix)
            || dfs(node.Right, listPos, listAsArray, lenOfLongestPrefixAlsoSuffix)
    }
    return dfs(root, 0, listAsArray, lenOfLongestPrefixAlsoSuffix)
}
