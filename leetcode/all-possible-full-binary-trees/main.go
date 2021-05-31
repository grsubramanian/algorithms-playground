/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func allPossibleFBT(n int) []*TreeNode {
    
    out := make([]*TreeNode, 0)

    if n == 1 {
        out = append(out, &TreeNode{Val: 0})
    } else if n % 2 == 1 {
        
        for lcount := 1; lcount < n - 1; lcount += 2 {
            
            lout := allPossibleFBT(lcount)
            rout := allPossibleFBT(n - lcount - 1)

            for _, ltree := range lout {
                for _, rtree := range rout {
                    
                    root := TreeNode{Val: 0}

                    // no deep copies, can reuse nodes.
                    root.Left = ltree
                    root.Right = rtree
                    out = append(out, &root)
                }
            }

        }

    }

    return out
}
