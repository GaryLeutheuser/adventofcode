import bisect

# Read in each line as a number
nums = []
with open("input.txt", "r") as input_file:
    nums = [int(line.rstrip()) for line in input_file.readlines()]
    
nums = sorted(nums)

# Take a number from the set.
for a in nums:
    # Take another number that isn't the same.
    for b in nums:
        if b == a:
            continue

        # Compute the missing c such that a + b + c == 2020
        c = 2020 - a - b

        # Try to find it
        index = bisect.bisect(nums, c)
        if nums[index - 1] == c:
            print(a * b * c)
            exit()
