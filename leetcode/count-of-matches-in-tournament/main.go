func numberOfMatches(n int) int {
    
    out := 0
    for n > 1 {
        out += n / 2
        n = n / 2 + n % 2
    }
    return out
}
