var dirs = [][]int{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }

func updateMatrix(mat [][]int) [][]int {

    m := len(mat)
    n := len(mat[0])

    rowq := make([]int, 0)
    colq := make([]int, 0)
    for row, matrow := range mat {
        for col, _ := range matrow {
            if matrow[col] == 0 {
                rowq = append(rowq, row)
                colq = append(colq, col)
            } else {
                matrow[col] = -1 // needs work.
            }
        }
    }

    for len(rowq) > 0 {
        row := rowq[0]
        rowq = rowq[1:]
        col := colq[0]
        colq = colq[1:]

        for _, dir := range dirs {

            nrow := row + dir[0]
            ncol := col + dir[1]

            if nrow < 0 || nrow >= m {
                continue
            }
            if ncol < 0 || ncol >= n {
                continue
            }
            if mat[nrow][ncol] >= 0 {
                continue
            }

            mat[nrow][ncol] = mat[row][col] + 1
            rowq = append(rowq, nrow)
            colq = append(colq, ncol)
        }
    }

    return mat
}
