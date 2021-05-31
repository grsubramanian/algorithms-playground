func allPathsSourceTarget(graph [][]int) [][]int {
    ans := make([][]int, 0)

    n := len(graph)

    var dfs func([]int, int)
    dfs = func(path []int, node int) {
        path = append(path, node)
        if node == n - 1 {
            desiredPath := make([]int, len(path))
            copy(desiredPath, path)
            ans = append(ans, desiredPath)
        } else {
            for _, neighborNode := range graph[node] {
                dfs(path, neighborNode)
            }
        }
        path = path[:len(path) - 1]
    }

    path := make([]int, 0)
    dfs(path, 0)

    return ans
}
