import math

def partition(lo, hi, half):
    """
    lo - low end of range
    hi - high end of range
    half - 0 for low, 1 for high
    Returns the new range of the requested half.
    """
    half_of_range = math.ceil(((hi-lo) // 2))
    if half == 0:
        # Lower half: lo stays the same, hi goes down
        # by half the range.
        lo = lo
        hi -= half_of_range
    
    if half == 1:
        # Upper half: hi stays the same, lo goes up
        # by half the range.
        lo += half_of_range
        hi = hi

    return (lo, hi)

seat_ids = []
lines = []
with open("input.txt", "r") as input_file:
    lines = [line.rstrip() for line in input_file.readlines()]
    
    for line in lines:
        # First find the row.
        lo = 0
        hi = 128
        for character in line[0:8]:
            if character == 'F':
                (lo, hi) = partition(lo, hi, 0)
            elif character == 'B':
                (lo, hi) = partition(lo, hi, 1)

        row = lo
        
        lo = 0
        hi = 8
        for character in line[7:]:
            if character == 'R':
                (lo, hi) = partition(lo, hi, 1)
            elif character == 'L':
                (lo, hi) = partition(lo, hi, 0)

        column = lo
        id = (row * 8) + column

        seat_ids.append(id)

print(f"Solution, part 1: {max(seat_ids)}")

# Look for the missing ID.
seat_ids = sorted(seat_ids)
last_id = seat_ids[1]
for id in seat_ids[2:-1]:
    if id > last_id + 1:
        print(f"Solution, part 2: {last_id}")
    last_id = id
