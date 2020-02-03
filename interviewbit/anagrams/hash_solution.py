class Solution:
    # @param A : tuple of strings
    # @return a list of list of integers
    def anagrams(self, A):
        
        memo = {}
        for i, w in enumerate(A):
            h = [0] * 26
            for c in w:
                h[ord(c) - ord('a')] += 1
            th = tuple(h)
            if th in memo:
                memo[th].append(i + 1)
            else:
                memo[th] = [i + 1]
        
        out = []
        for th, i_list in memo.items():
            out.append(i_list)
        return out
