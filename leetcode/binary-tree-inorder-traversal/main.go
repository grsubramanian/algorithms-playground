/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func inorderTraversal(root *TreeNode) []int {
    
    out := make([]int, 0)

    var recurse func(*TreeNode, []int) []int
    recurse = func(root *TreeNode, out []int) []int {
        if root == nil {
            return out
        }
        out = recurse(root.Left, out)
        out = append(out, root.Val)
        return recurse(root.Right, out)
    }
    return recurse(root, out)
}
