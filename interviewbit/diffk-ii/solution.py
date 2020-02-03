class Solution:
    # @param A : tuple of integers
    # @param B : integer
    # @return an integer
    def diffPossible(self, A, B):
        memo = {}
        for a in A:
            if a in memo:
                return 1
            
            memo[a + B] = None # dummy value.
            if B != 0:
                memo[a - B] = None # dummy value.
        
        return 0

