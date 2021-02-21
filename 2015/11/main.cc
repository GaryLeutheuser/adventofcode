#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

// Modifies in place.
void next_password(std::string& password) {
    // Increment characters until one doesn't "wrap around",
    // or we add a character to the front.
    bool carry = false;
    for (auto r = password.rbegin(); r != password.rend(); ++r) {
        // Check for carry as we increment the character.
        carry = false;
        if (*r == 'z') {
            carry = true;
            *r = 'a';
        }
        else {
            ++(*r);
        }

        // Only continue as long as the carry is set.
        if (!carry) {
            break;
        }
    }

    // Hit the end - but carry is still set. Add 'a' to the front.
    if (carry) {
        password.insert(password.begin(), 'a');
    }
}

bool has_straight(std::string& password) {
    if (password.length() < 3) {
        return false;
    }

    // Check for 3 increasing characters in a row.
    auto it = password.begin();
    auto next = it + 1;
    auto next_next = next + 1;

    while (next_next != password.end()) {
        if (*it + 1 == *next && *it + 2 == *next_next) {
            return true;
        }

        ++it;
        ++next;
        ++next_next;
    }

    return false;
}

bool has_two_pairs(std::string& password) {
    if (password.length() < 4) {
        return false;
    }

    auto it = password.begin();
    auto next = it + 1;

    uint num_pairs = 0;
    while (next < password.end()) {
        if (*it == *next) {
            ++num_pairs;

            // Don't care about overlap with this pair.
            it += 2;
            next += 2;
        }
        else {
            // No pair - usual iteration.
            ++it;
            ++next;
        }
    }

    return (num_pairs >= 2);
}

bool forbidden_letters(char c) {
    return (c == 'i') || (c == 'o') || (c == 'l');
}

bool has_no_forbidden_letters(std::string& password) {
    return std::none_of(password.begin(), password.end(), forbidden_letters);
}

bool is_valid(std::string& password) {
    if (password.length() != 8) {
        return false;
    }

    return has_straight(password)
        && has_two_pairs(password)
        && has_no_forbidden_letters(password);
}

void next_valid_password(std::string& password) {
    // If current password is valid, force an iteration
    // to kick things off.
    if (is_valid(password)){
        next_password(password);
    }

    while (!is_valid(password)) {
        next_password(password);
    }
}

int main(void) {
    std::string password = "hepxcrrq";

    // Part 1
    next_valid_password(password);
    std::cout << "Part 1: " << password << "\n";

    // Part 2
    next_valid_password(password);
    std::cout << "Part 2: " << password << "\n";


    return EXIT_SUCCESS;
}
