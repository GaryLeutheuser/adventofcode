valid_count = 0

with open("input.txt", "r") as input_file:
    lines = [line.rstrip() for line in input_file.readlines()]
    for line in lines:
        # Split into the tokens.
        tokens = line.split("-")
        lower_index = int(tokens[0]) - 1
        tokens = tokens[1].split(' ')
        upper_index = int(tokens[0]) - 1
        letter = tokens[1][0]
        string = tokens[2]

        # Check the password.
        lower_index_contains_letter = (string[lower_index] == letter)
        upper_index_contains_letter = (string[upper_index] == letter)
        valid = lower_index_contains_letter ^ upper_index_contains_letter
        if valid:
            valid_count += 1

    print(valid_count)
