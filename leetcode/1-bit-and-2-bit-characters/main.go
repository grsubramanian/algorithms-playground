func isOneBitCharacter(bits []int) bool {
    out := false
    for i := 0; i < len(bits); {
        if bits[i] == 0 {
            i++
            out = true
        } else {
            i += 2
            out = false
        }
    }
    return out
}
