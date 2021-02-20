groups = []
with open("input.txt", "r") as inputfile:
    raw_input = inputfile.read()
    groups = raw_input.split("\n\n")

counts = 0
for group in groups:
    answer_set = set()
    for character in group:
        if character == '\n':
            continue
        answer_set.add(character)
    counts += len(answer_set)

print(counts)
