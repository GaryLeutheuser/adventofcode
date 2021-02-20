#include <vector>
#include <string>
#include <iostream>

#include "permute.h"

using std::string;

std::vector<string> permute(const string& input) {
    auto result = std::vector<string>();

    // Base case is a string of length 1 - that's just itself.
    if (input.length() == 1) {
        result.push_back(input);
        return result;
    }

    // Otherwise, we have more permutations to find.
    // Recurse.
    for (size_t i = 0; i < input.length(); ++i) {
        // Remove each character in turn and put it at the front.
        auto input_copy = string(input);
        input_copy.erase(i, 1);

        // Get subpermutations for this configuration.
        auto sub_result = permute(input_copy);

        // Add the start character back on to each.
        for (auto it = sub_result.begin(); it != sub_result.end(); ++it) {
            (*it) = input[i] + (*it);
        }

        // Add to running list of permutations.
        result.reserve(sub_result.size());
        result.insert(result.end(), sub_result.begin(), sub_result.end());
    }

    return result;
}
