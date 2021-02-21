#include <iostream>
#include <string>
#include <tuple>

std::string look_and_say(std::string& input) {
    std::string output;

    // The first character marks the first run.
    int run_length = 1;
    char run_value = input[0];

    for (auto it = input.begin(); it != input.end() - 1; ++it) {
        // The run continues.
        if (*it == *(it + 1)) {
            ++run_length;
        }
        // The run ends.
        else {
            output.push_back(run_length + '0');
            output.push_back(run_value);

            run_length = 1;
            run_value = *(it + 1);
        }
    }

    // We hit the last character. Either it extends the
    // last run, or it is its own run of a single value.
    auto last_character = input[input.length() - 1];
    if (last_character != run_value) {
        run_length = 1;
        run_value = last_character;
    }

    output.push_back(run_length + '0');
    output.push_back(run_value);

    return output;
}

int main(void) {
    std::string input = "1113122113";
    //std::string input = "1";

    for (size_t i = 0; i < 50; ++i) {
        input = look_and_say(input);
        std::cout << input << "\n";
    }
    std::cout << input.length() << "\n";

    return EXIT_SUCCESS;
}
