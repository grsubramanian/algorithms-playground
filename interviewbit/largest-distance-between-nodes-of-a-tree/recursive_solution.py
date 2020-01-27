import resource
import sys

# Will segfault without this line.
resource.setrlimit(resource.RLIMIT_STACK, [0x10000000, resource.RLIM_INFINITY])
sys.setrecursionlimit(0x100000)

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
        
        self.C = C
        
        l1, _ = self.longest_paths(0)
        return l1
    
    def longest_paths(self, node):
        
        l1, l2 = (0, 0)
        
        c = self.C[node]
        if len(c) > 0:
            for cnode in c:
                cl1, cl2 = self.longest_paths(cnode)
                l1, l2 = (max(l1, cl1, l2 + cl2 + 1), max(l2, cl2 + 1))
            
        return (l1, l2)
        
