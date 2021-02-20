groups = []
with open("input.txt", "r") as inputfile:
    raw_input = inputfile.read()
    groups = raw_input.split("\n\n")

counts = 0
for group in groups:
    people = group.split("\n")
    answer_sets = []
    for person in people:
        answer_set = set()
        for character in person:
            answer_set.add(character)
        if len(answer_set) != 0:
            answer_sets.append(answer_set)
    
    # Common answers only.
    if len(answer_sets) == 1:
        counts += len(answer_sets[0])
    else:
        common_answers = answer_sets[0].intersection(*answer_sets[1:])
        counts += len(common_answers)

print(counts)
