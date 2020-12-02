# Read in each line as a number
nums = []
with open("input.txt", "r") as input_file:
    nums = [int(line.rstrip()) for line in input_file.readlines()]
    
# Sort the numbers.
nums_hi_lo = sorted(nums, reverse=True)
nums_lo_hi = sorted(nums)

# Starting with the highest number, take the next highest.
for num_hi in nums_hi_lo:
    # Starting with the lowest number, take the next lowest and add.
    for num_lo in nums_lo_hi:
        sum = num_hi + num_lo
        if sum == 2020:
            # If the sum is 2020, multiply and we're done.
            print(num_hi * num_lo)
            exit()
        elif sum > 2020:
            # If the sum exceeds 2020, move to the next iteration.
            break
