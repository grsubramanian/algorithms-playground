/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseList(head *ListNode) *ListNode {
    
    if head == nil {
        return nil
    }

    node := head
    nextNode := node.Next
    node.Next = nil

    for nextNode != nil {
        temp := nextNode.Next
        nextNode.Next = node
        node = nextNode
        nextNode = temp
    }
    return node
}
