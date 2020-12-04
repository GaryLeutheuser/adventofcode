from functools import reduce

def count_trees(grid, x_increment, y_increment):
    # Access as grid[y][x], upper left corner is 0, 0
    # Starting at the upper left corner, check each spot
    # progressing as 3 right 1 down.
    #
    # When you get out of bounds, wrap back around to the other side.
    x = 0
    y = 0
    # Until the bottom, keep moving and checking.
    tree_count = 0
    while y < len(grid):
        # Is there a tree? Add to count.
        if grid[y][x] == '#':
            tree_count += 1
        
        # Update position.
        x = (x + x_increment) % len(grid[0])
        y += y_increment

    return tree_count

# Read in the input
# Goal is a 2D grid
grid = []
with open("input.txt", "r") as inputfile:
    lines = [line.rstrip() for line in inputfile.readlines()]
    for line in lines:
        grid.append([char for char in line])

results = []
results.append(count_trees(grid, 1, 1))
results.append(count_trees(grid, 3, 1))
results.append(count_trees(grid, 5, 1))
results.append(count_trees(grid, 7, 1))
results.append(count_trees(grid, 1, 2))

print(reduce((lambda a, b: a * b), results))
