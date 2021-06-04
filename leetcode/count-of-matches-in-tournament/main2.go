func numberOfMatches(n int) int {
    // Since each match eliminates a contestant, and there is only one left at the end, there must be n - 1 matches total.
    return n - 1
}
