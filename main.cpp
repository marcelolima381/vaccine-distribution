#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "graph.hpp"

int main() {

    int quantityCD, quantityPV, temperatureDrop;
    std::cin >> quantityCD >> quantityPV >> temperatureDrop;

    std::vector<Graph> CDGrafos;
    CDGrafos.reserve(quantityCD + 1);
    Graph graph(quantityCD + quantityPV);
    CDGrafos[0] = graph;

    bool hasRepeatedRoute = false;

    /*Data Input*/
    for (int i = 0; i < quantityCD + quantityPV; i++) {
        do {
            int input;
            if (std::cin >> input) {
                if (input != 0) {
                    /*
                     * The vertices are not differentiated in the graph.
                     * A convention was created that CDs come first and PVs soon after,
                     * and it is necessary to add quantity CD - 1 (vector starts at zero)
                     * to the PV numbering
                     * */
                    CDGrafos[0].addEdge(i, input + quantityCD - 1);
                }
            }
        } while (std::cin && std::cin.peek() != '\n' && std::cin.peek() != char(13));
    }


    if (quantityPV != 0) {
        /*
         * Stores the stations visited by all CDs, with repetition, within the temperature limit
         * */
        std::vector<int> visitedPosts;
        /**/
        for (int i = 0; i < quantityCD; i++) {
            /*Initialization of the graphs of each CD*/
            Graph graphAux(quantityCD + quantityPV);
            CDGrafos[i + 1] = graphAux;
            CDGrafos[0].BFS(i, visitedPosts, floor((90 - 60) / temperatureDrop), &CDGrafos[i + 1]);
        }

        /*Search for cycles in each graph*/
        for (int i = 1; i <= quantityCD; i++) {
            hasRepeatedRoute = CDGrafos[i].isCyclic();
            if (hasRepeatedRoute) {
                break;
            }
        }

        /*Ordering and eliminating duplicates*/
        sort(visitedPosts.begin(), visitedPosts.end());
        visitedPosts.erase(unique( visitedPosts.begin(), visitedPosts.end() ), visitedPosts.end());
        if (visitedPosts.empty()) {
            std::cout << 0 << std::endl;
            std::cout << "*" << std::endl;
            std::cout << 0 << std::endl;
            return 0;
        }

        std::cout << visitedPosts.size() << std::endl;
        for (int visitedPost : visitedPosts) {
            std::cout << visitedPost - quantityCD + 1 << " ";
        }
        std::cout << std::endl;

        if (hasRepeatedRoute) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }

    } else {
        std::cout << 0 << std::endl;
        std::cout << "*" << std::endl;
        std::cout << 0 << std::endl;
    }
    return 0;
}
