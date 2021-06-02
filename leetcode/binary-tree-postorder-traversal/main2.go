/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func postorderTraversal(node *TreeNode) []int {

    out := make([]int, 0)

    stk := make([]*TreeNode, 0)
    var lastVisitedNode *TreeNode
    lastVisitedNode = nil
    for len(stk) > 0 || node != nil {
        
        if node != nil {
            // This is the first time we are exploring the node, so we need to add it to the stack
            // and move to the work on the left sub-tree.
            stk = append(stk, node)
            node = node.Left
        } else {

            // We've reached here from a leaf. That's the only way 'node' can be 'nil'. Thus, we have
            // either completed traversal of a left sub-tree of the 'root' or a right sub-tree of the
            // 'root'. We consider these two cases separately.

            root := stk[len(stk) - 1]

            if root.Right == nil || root.Right == lastVisitedNode {
                // The right sub-tree is either missing, or we just finished traversing it, so we can
                // visit the root, and thus complete working on the sub-tree rooted at 'root'.
                out = append(out, root.Val)
                lastVisitedNode = root
                stk = stk[:len(stk) - 1]
            } else {
                // We still need to traverse the right sub-tree.
                node = root.Right
            }
            
        }
    }
    return out
}
