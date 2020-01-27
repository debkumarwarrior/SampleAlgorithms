class Solution:
    def twoSum(self, nums, target):
        numbers = dict()
        for i in range(len(nums)):
            if nums[i] not in numbers:
                numbers[nums[i]] = [i]
            else:
                numbers[nums[i]].append(i)
        #print(numbers)
        for i in range(len(nums)):
            sec = target - nums[i]
            if sec == nums[i]:
                if len(numbers[sec]) > 1:
                    return numbers[sec]
            else:
                if sec in numbers:
                    return i,numbers[sec][0]


if __name__ == '__main__':
    soln = Solution()
	soln.twoSum([3,2,1,7,5], 5)
