/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func preorderTraversal(root *TreeNode) []int {
    
    out := make([]int, 0)
    if root == nil {
        return out
    }

    stk := make([]*TreeNode, 0)
    stk = append(stk, root)
    for len(stk) > 0 {
        
        node := stk[len(stk) - 1]
        stk = stk[:len(stk) - 1]

        out = append(out, node.Val)
        if node.Right != nil {
            stk = append(stk, node.Right)
        }
        if node.Left != nil {
            stk = append(stk, node.Left)
        }
    }

    return out
}
