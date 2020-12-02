valid_count = 0

with open("input.txt", "r") as input_file:
    lines = [line.rstrip() for line in input_file.readlines()]
    for line in lines:
        # Split into the tokens.
        tokens = line.split("-")
        lower_bound = int(tokens[0])
        tokens = tokens[1].split(' ')
        upper_bound = int(tokens[0])
        letter = tokens[1][0]
        string = tokens[2]

        # Check the password.
        count = 0
        for char in string:
            if char == letter:
                count += 1

        if count >= lower_bound and count <= upper_bound:
            print(f"{string} was valid.")
            print(f"There were {count} instances of {letter}.")
            valid_count += 1

    print(valid_count)
