class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """

        ##### the array invariant shape is NZ1, NZ2, NZ3, ... Z, Z, Z,... 

        leading_nonzeroes_count = 0
        trailing_zeroes_count = 0

        N = len(nums)
        i = 0
        while i < N:
            if nums[i] == 0:
                trailing_zeroes_count += 1
                i += 1
            else:
                j = i
                while j < N and nums[j] != 0:
                    j += 1
                k = leading_nonzeroes_count
                if trailing_zeroes_count >= (j - i):
                    # 1] swap
                    for l in xrange(i, j):
                        self.swap(nums, k + l - i, l)
                else:
                    # 1] left shift
                    for l in xrange(i, j):
                        nums[k + l - i] = nums[l]
                    # 2] overwrite with zero
                    for l in xrange(j - trailing_zeroes_count, j):
                        nums[l] = 0
                leading_nonzeroes_count += (j - i)
                i = j

    def swap(self, nums, i, j):
        temp = nums[i]
        nums[i] = nums[j]
        nums[j] = temp
