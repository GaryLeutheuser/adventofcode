import json


# This BFS can handle each nested element being a list, a dict, or a key/value pair.
# A key/value pair is considered terminal.
# It will yield in turn each element of the structure until all elements are explored.
# Filtered value, if set, will immediately remove any dictionary that contains a key
# with that value and not yield any of its elements.
def generative_breadth_first_search(structure: dict, filtered_value=None):
    stack = []
    for element in structure:
        stack.append(structure[element])

    # while there are still elements left
    while stack:
        element = stack.pop()

        if isinstance(element, dict) and filtered_value not in element.values():
            for key in element:
                stack.append(element[key])

        elif isinstance(element, list):
            for sub_element in element:
                stack.append(sub_element)

        else:
            yield element


if __name__ == "__main__":
    with open("2015/12/input.json") as input_file:
        input = json.load(input_file)

        g = generative_breadth_first_search(input)
        sum = 0
        for element in g:
            if isinstance(element, int):
                sum += element

        print(f"Part one: {sum}")

    with open("2015/12/input.json") as input_file:
        input = json.load(input_file)

        g = generative_breadth_first_search(input, filtered_value="red")
        sum = 0
        for element in g:
            if isinstance(element, int):
                sum += element

        print(f"Part two: {sum}")
