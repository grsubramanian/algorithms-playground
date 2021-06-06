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

    var dfs func(*ListNode, *TreeNode) bool
    dfs = func(listNode *ListNode, treeNode *TreeNode) bool {

        if listNode == nil {
            return true
        }

        if treeNode == nil {
            return false
        }

        if treeNode.Val == listNode.Val {
            next := listNode.Next
            if dfs(next, treeNode.Left) || dfs(next, treeNode.Right) {
                return true
            }
        }
        if listNode == head {
           return dfs(listNode, treeNode.Left) || dfs(listNode, treeNode.Right)
        } else {
            return false
        }
    }
    return dfs(head, root)
}
