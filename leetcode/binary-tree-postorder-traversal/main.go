/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func postorderTraversal(root *TreeNode) []int {

    out := make([]int, 0)

    var recurse func(*TreeNode, []int) []int
    recurse = func(node *TreeNode, out []int) []int {
        if node == nil {
            return out
        }
        out = recurse(node.Left, out)
        out = recurse(node.Right, out)
        return append(out, node.Val)
    }

    return recurse(root, out)
}
