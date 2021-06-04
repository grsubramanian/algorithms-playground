import (
    "strings"
)

type Node struct {

    Word *string
    Children [26]*Node
}

func longestWord(words []string) string {

    empty := ""
    root := &Node{Word: &empty}
    for i := 0; i < len(words); i++ {
        word := words[i]
        node := root
        for _, c := range word {
            index := int(c) - int('a')
            childNode := node.Children[index]
            if childNode == nil {
                childNode = &Node{}
                node.Children[index] = childNode
            }
            node = childNode
        }
        // We'll point to the original word in the slice, so that we don't allocate more memory.
        node.Word = &word
    }

    candidates := make([]*string, 0)

    var dfs func(*Node)
    dfs = func(node *Node) {
        
        hasNoChild := true
        doesHaveChildThatDoesNotCorrespondToAWord := false
        for i := 0; i < 26; i++ {
            childNode := node.Children[i]
            if childNode != nil {
                hasNoChild = false
                if childNode.Word != nil {
                    dfs(childNode)
                } else {
                    doesHaveChildThatDoesNotCorrespondToAWord = true
                }
            }
        }
        if hasNoChild || doesHaveChildThatDoesNotCorrespondToAWord {
            candidates = append(candidates, node.Word)
        }
    }

    dfs(root)

    var out *string = nil
    for _, candidate := range candidates {
        if out == nil {
            out = candidate
        } else {
            if len(*candidate) > len(*out) {
                out = candidate
            } else if len(*candidate) == len(*out) {
                if strings.Compare(*candidate, *out) < 0 {
                    out = candidate
                }
            }
        }
    }
    return *out
}
