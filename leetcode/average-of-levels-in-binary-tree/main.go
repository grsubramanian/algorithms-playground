package main

import (
    "fmt"
)

type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func averageOfLevels(root *TreeNode) []float64 {
    out := make([]float64, 0)
    nAtLevel := make([]int, 0)
    out, nAtLevel = traverse(root, 0, out, nAtLevel)
    return out
}

func traverse(node *TreeNode, level int, out []float64, nAtLevel []int) ([]float64, []int) {

    if node == nil {
        return out, nAtLevel
    }

    if level >= len(out) {
        out = append(out, float64(node.Val))
        nAtLevel = append(nAtLevel, 1)
    } else {
        out[level] = (out[level] * float64(nAtLevel[level]) + float64(node.Val)) / float64(nAtLevel[level] + 1)
        nAtLevel[level] = nAtLevel[level] + 1
    }

    out, nAtLevel = traverse(node.Left, level + 1, out, nAtLevel)
    return traverse(node.Right, level + 1, out, nAtLevel)
}

func main() {
    
    a := TreeNode{
        Val: 5,
        Left: nil,
        Right: nil,
    }
    out := averageOfLevels(&a)

    fmt.Printf("Average of levels = %v\n", out)
}
