#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#include <boost/tokenizer.hpp>

#include "permute.h"

using std::vector;

int main(void) {
    // Use an adjacency matrix to store the edge distances.
    vector<vector<int>> adj_matrix;

    // City name set.
    auto city_names = std::set<std::string>();

    // Keep track of what city name maps to what index in the matrix.
    std::map<std::string, int> city_indices;

    // Vector of tuples for edge data.
    typedef std::tuple<std::string, std::string, int> edge_info;
    std::vector<edge_info> edge_infos;

    // Read in the input file.
    std::filebuf input_buffer;
    if (input_buffer.open("input.txt", std::ios::in)) {
        std::istream input_stream(&input_buffer);
        while (input_stream) {
            // Get the line.
            char line[256];
            input_stream.getline(line, 256);

            // Tokenize the line by space.
            std::string line_string = std::string(line);
            boost::tokenizer<> tok(line_string);
            auto tokens = std::vector<std::string>();
            for (auto i = tok.begin(); i != tok.end(); ++i) {
                tokens.push_back(*i);
            }

            // Avoid any empty lines.
            if (tokens.size() == 0)
                continue;

            // The first element needs to be added to the city name set.
            // We'll use the city name set to add the vertices to the graph.
            city_names.insert(tokens[0]);
            city_names.insert(tokens[2]);


            // Store the two cities and the distance between them so we can
            // add the edges between the vertices.
            edge_infos.push_back(edge_info(tokens[0], tokens[2], std::stoi(tokens[3])));
        }
        input_buffer.close();
    }

    // From the city name set - generate the city indices.
    size_t i = 0;
    for (auto it = city_names.begin(); it != city_names.end(); ++it) {
        city_indices[*it] = i++;
    }

    // Populate the adjacency matrix from the edge info list.
    for (size_t i = 0; i < city_names.size(); ++i) {
        adj_matrix.push_back(std::vector<int>());
        for (size_t j = 0; j < city_names.size(); ++j) {
            adj_matrix[i].push_back(0);
        }
    }


    for (auto it = edge_infos.begin(); it != edge_infos.end(); ++it) {
        auto index_from = city_indices[std::get<0>(*it)];
        auto index_to = city_indices[std::get<1>(*it)];
        auto distance = std::get<2>(*it);

        adj_matrix[index_from][index_to] = distance;
        adj_matrix[index_to][index_from] = distance;
    }

    /*
    for (size_t i = 0; i < adj_matrix.size(); ++i) {
        for (size_t j = 0; j < adj_matrix[i].size(); ++j) {
            std::cout << adj_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    */

    std::string str = "01234567";
    std::vector<std::string> permutations = permute(str);
    int minimum_distance = INT32_MAX;
    int maximum_distance = 0;
    for (auto permutation_it = permutations.begin(); permutation_it != permutations.end(); ++permutation_it) {
        // "Walk" each permuted path, calculating the distance it takes.
        int current_distance = 0;
        for (auto char_it = (*permutation_it).begin(); char_it != (*permutation_it).end(); ++char_it) {
            if (char_it == (*permutation_it).end() - 1) {
                continue;
            }

            int from = *char_it - '0';
            int to = *(char_it + 1) - '0';

            current_distance += adj_matrix[from][to];
        }
        
        // Check distance against current minimum/maximum.
        minimum_distance = std::min<int>(current_distance, minimum_distance);
        maximum_distance = std::max<int>(current_distance, maximum_distance);
    }

    std::cout << "Minimum: " << minimum_distance << "\n";
    std::cout << "Maximum: " << maximum_distance << "\n";

    return EXIT_SUCCESS;
}
