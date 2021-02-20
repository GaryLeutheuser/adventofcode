#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

#include <boost/tokenizer.hpp>

using boost::adjacency_list;
using boost::vecS;
using boost::undirectedS;
using boost::property;
using boost::vertex_name_t;
using boost::edge_weight_t;
using boost::property_map;

struct City {
    std::string name;
};

struct Road {
    int distance;
};

int main(void) {
    // City name set.
    auto city_names = std::set<std::string>();

    // Vector of tuples for edge data.
    typedef std::tuple<std::string, std::string, int> edge_info;
    std::vector<edge_info> edge_infos;

    // Read in the input file.
    std::filebuf input_buffer;
    if (input_buffer.open("input_simple.txt", std::ios::in)) {
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

    typedef adjacency_list<vecS, vecS, undirectedS, City, Road> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef std::pair<int, int> Edge;

    Graph g(0);
    std::map<std::string, int> city_indices;
    for (auto it = city_names.begin(); it != city_names.end(); ++it) {
        auto v = boost::add_vertex(g);
        g[v].name = *it;

        // Keep track of which city has what index in the map.
        city_indices[*it] = v;
    }


    // Now, with the lookup table, we can manipulate vertices by city name.
    // This will let us fill in the road lengths much easier.
    // g[city_indices["Arbre"]].name = "ArbreNEW";

    for (auto it = edge_infos.begin(); it != edge_infos.end(); ++it) {
        // Add the edge.
        auto city_from = std::get<0>(*it);
        auto city_to = std::get<1>(*it);
        auto e = boost::add_edge(city_indices[city_from], city_indices[city_to], g);

        // Add the distance.
        g[e.first].distance = std::get<2>(*it);
    }

    for (auto i = boost::edges(g).first; i != boost::edges(g).second; ++i) {
        auto edge = *i;
        std::cout << g[edge.m_source].name << ", " << g[edge.m_target].name << " = ";
        std::cout << g[edge].distance << "\n";
    }

    // Everything is in!
    // Time to actually solve the problem, lol.
    // Since we don't have to end where we began, this is not
    // an exact instance of TSP.
    //
    // There aren't too many cities, so we could brute force.
    // Let's try that first.
    //
    // Every city connects to every city.
    //  So, have a stack of each city.
    //      For each city in the stack, have a stack of every
    //      other city.s   

    return EXIT_SUCCESS;
}
s
