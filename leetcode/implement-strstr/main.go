func strStr(haystack string, needle string) int {
    n := len(needle)
    if n == 0 {
        return 0
    }

    lenOfLongestPrefixAlsoSuffix := make([]int, n)
    lenOfLongestPrefixAlsoSuffix[0] = 0
    for j := 1; j < n; j++ {
        k := j - 1
        for k >= 0 {
            l := lenOfLongestPrefixAlsoSuffix[k]
            if needle[l] == needle[j] {
                break
            }
            k = l - 1
        }

        if k >= 0 {
            lenOfLongestPrefixAlsoSuffix[j] = lenOfLongestPrefixAlsoSuffix[k] + 1
        }
    }

    i := 0
    j := 0

    m := len(haystack)
    for i < m && j < n {

        if haystack[i] == needle[j] {
            i++
            j++
        } else {
            if j > 0 {
                j = lenOfLongestPrefixAlsoSuffix[j - 1]
            } else {
                i++
            }
        }
    }
    if j == n {
        return i - n
    } else {
        return -1
    }
}
