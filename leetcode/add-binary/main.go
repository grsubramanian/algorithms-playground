package main

import "fmt"

func addBinary(a string, b string) string {
    
    maxlen := len(a)
    if len(b) > len(a) {
        maxlen = len(b)
    }
    out := make([]byte, 0, maxlen + 1)

    carry := 0

    i := len(a) - 1
    j := len(b) - 1
    for i >= 0 || j >= 0 {
        var aval int
        if i < 0 {
            aval = 0
        } else {
            aval = int(a[i]) - 48
            i--
        }

        var bval int
        if j < 0 {
            bval = 0
        } else {
            bval = int(b[j]) - 48
            j--
        }

        outval := carry + aval + bval
        if outval == 3 {
            carry = 1
            outval = 1
        } else if outval == 2 {
            carry = 1
            outval = 0
        } else {
            carry = 0
        }

        out = append(out, byte(outval + 48))
    }
    if carry > 0 {
        out = append(out, byte(carry + 48))
    }

    outlen := len(out)
    for k := 0; k < outlen / 2; k++ {
        temp := out[k]
        out[k] = out[outlen - 1 - k]
        out[outlen - 1 - k] = temp
    }

    return string(out)
}

func main() {

    a := "11"
    b := "1"
    c := addBinary(a, b)
    fmt.Print(c)
}
