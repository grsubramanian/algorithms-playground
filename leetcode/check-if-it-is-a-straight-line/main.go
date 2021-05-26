func checkStraightLine(coordinates [][]int) bool {
    
    // assuming that input has length at least 2.

    refdx := coordinates[1][0] - coordinates[0][0]
    refdy := coordinates[1][1] - coordinates[0][1]

    for i := 2; i < len(coordinates); i++ {
        
        dx := coordinates[i][0] - coordinates[i - 1][0]
        dy := coordinates[i][1] - coordinates[i - 1][1]

        if refdx == 0 && dx != 0 {
            // expecting vertical line.
            return false
        }

        if refdy == 0 && dy != 0 {
            // expecting horizontal line.
            return false
        }

        if refdx * dy != dx * refdy {
            // expecting same slope.
            return false
        }
    }

    // found no discrepancy in straightness.
    return true
}
