func allPathsSourceTarget(graph [][]int) [][]int {

    n := len(graph)
    memo := make([][][]int, n)

    out := allPathsTargetSource(graph, memo, 0)
    for _, path := range out {
        pathlen := len(path)
        for i := 0; i < pathlen / 2; i++ {
            tmp := path[i]
            path[i] = path[pathlen - 1 - i]
            path[pathlen - 1 - i] = tmp
        }
    }
    return out
}

func allPathsTargetSource(graph [][]int, memo [][][]int, node int) [][]int {

    if memo[node] == nil {
        nodePaths := make([][]int, 0)
        
        n := len(graph)
        if node == n - 1 {
            singleNodePath := []int{ n - 1 }
            nodePaths = append(nodePaths, singleNodePath)
        } else {
            for _, neighborNode := range graph[node] {
                neighborNodePaths := allPathsTargetSource(graph, memo, neighborNode)
                for _, neighborNodePath := range neighborNodePaths {
                    nodePath := make([]int, len(neighborNodePath))
                    copy(nodePath, neighborNodePath)
                    nodePath = append(nodePath, node)
                    nodePaths = append(nodePaths, nodePath)
                }
            }
        }
        memo[node] = nodePaths
    }
    return memo[node]
}
