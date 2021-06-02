
type Work struct {
    Node *TreeNode
    ExploreLeftBranch bool
}

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
    if root == nil {
        return out
    }

    stk := make([]Work, 0)

    // For every node, we'll add two entries to the stack, one for exploring the left branch
    // and another for exploring the right branch.
    stk = append(stk, Work{Node: root, ExploreLeftBranch: false})
    stk = append(stk, Work{Node: root, ExploreLeftBranch: true})
    for len(stk) > 0 {
        
        work := stk[len(stk) - 1]
        stk = stk[:len(stk) - 1]

        if work.ExploreLeftBranch {
            if work.Node.Left != nil {
                stk = append(stk, Work{Node: work.Node.Left, ExploreLeftBranch: false})
                stk = append(stk, Work{Node: work.Node.Left, ExploreLeftBranch: true})
            }
        } else {
            out = append(out, work.Node.Val)
            if work.Node.Right != nil {
                stk = append(stk, Work{Node: work.Node.Right, ExploreLeftBranch: false})
                stk = append(stk, Work{Node: work.Node.Right, ExploreLeftBranch: true})
            }
        }
    }
    return out
}
