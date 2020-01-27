class Solution:
    # @param A : list of integers
    # @return an integer
    def solve(self, P):
        N = len(P)
        
        # for all nodes, compute children.
        C = [None] * N
        for i in range(N):
            C[i] = []
        for i in range(N):
            if P[i] >= 0:
                C[P[i]].append(i)
        
        # do an iterative DFS, since recursive DFS
        # encounters stack overflow.
        memo = [None] * N
        node_stack = []
        node_stack.append(0)
        
        while len(node_stack) > 0:
            node = node_stack[-1]
            
            all_children_explored = True
            for cnode in C[node]:
                if memo[cnode] is None:
                    all_children_explored = False
                    node_stack.append(cnode)
            
            if all_children_explored:
                l1, l2 = (0, 0)
                for cnode in C[node]:
                    cl1, cl2 = memo[cnode]
                    l1, l2 = (max(l1, cl1, l2 + cl2 + 1), max(l2, cl2 + 1))
                memo[node] = (l1, l2)
                node_stack.pop()
        
        return memo[0][0]
        
