func averageOfLevels(root *TreeNode) []float64 {

    out := make([]float64, 0)
    if root == nil {
        return out
    }

    nodeq := make([]*TreeNode, 0)
    levelq := make([]int, 0)
    nodeq = append(nodeq, root)
    levelq = append(levelq, 0)

    currLevelSum := 0
    currLevel := 0
    currLevelCount := 0

    for len(nodeq) > 0 {
        
        node := nodeq[0]
        level := levelq[0]

        nodeq = nodeq[1:]
        levelq = levelq[1:]

        if level > currLevel {
            currLevel += 1 // = level
            out = append(out, float64(currLevelSum) / float64(currLevelCount))
            currLevelCount = 1
            currLevelSum = node.Val
        } else {
            currLevelCount += 1
            currLevelSum += node.Val
        }

        if node.Left != nil {
            nodeq = append(nodeq, node.Left)
            levelq = append(levelq, level + 1)
        }
        
        if node.Right != nil {
            nodeq = append(nodeq, node.Right)
            levelq = append(levelq, level + 1)
        }
    }
    out = append(out, float64(currLevelSum) / float64(currLevelCount))
    return out
}
