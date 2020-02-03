class Solution:
    # @param A : tuple of strings
    # @return a list of list of integers
    def anagrams(self, A):
        
        if len(A) == 0:
            return []
        
        histograms = []
        for i, w in enumerate(A):
            h = [0] * 26
            for c in w:
                h[ord(c) - ord('a')] += 1
            histograms.append((tuple(h), i + 1))
        
        sorted_histograms = sorted(histograms)
        
        out = []
        cache = []
        for j in range(len(sorted_histograms)):
            if j > 0 and sorted_histograms[j][0] == sorted_histograms[j - 1][0]:
                cache.append(sorted_histograms[j][1])
            else:
                if len(cache) > 0:
                    out.append(cache)
                cache = [sorted_histograms[j][1]]
        
        if len(cache) > 0:
            out.append(cache)
        
        return out
