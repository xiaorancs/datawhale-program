def cmp(a, b):
    return a < b

def binarySearch(nums, target):
    left, right = 0, len(nums)-1
    while left <= right :
        mid = (left + right) // 2
        if nums[mid] == target:
            return mid
        elif cmp(nums[mid], target):
            left = mid
        else :
            right = mid
    return -1

def firstBinarySearch(nums, target):
    left, right = 0, len(nums)-1
    while left + 1 < right :
        mid = (left + right) // 2
        if nums[mid] < target :
            left = mid
        else :
            right = mid
    if nums[left] == target :
        return left
    elif nums[right] == target :
        return right
    return -1


if __name__ == "__main__":
    nums, target = [1,4,4,5,7,7,8,9,9,10], 1
    print (binarySearch(nums, target))