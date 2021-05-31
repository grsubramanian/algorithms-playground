import (
    "math"
)

func myPow(x float64, n int) float64 {

    if n == 0 {
        return 1.0
    } else {
        if n > 0 {
            if x == 0 {
                return 0
            } else {
                return myPowSimple(x, n)
            }
        } else {
            if x == 0 {
                return math.Inf(1)
            } else {
                return 1.0 / myPowSimple(x, -n)
            }
        }
    }
}

func myPowSimple(x float64, n int) float64 {

    var out float64
    out = 1.0
    for n > 0 {
        if n % 2 == 1 {
            out *= x
        }

        // rephrase question from x^n to (x^2) ^ (n/2).
        x *= x
        n /= 2
    }
    return out
}
