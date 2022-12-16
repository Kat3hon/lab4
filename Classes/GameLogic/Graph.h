#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include <fstream>



// Forward declaration of Edge class
template <class T>
class Edge;



/////////////////////////////////////////////////////////////////////
//                      GENERAL GRAPH CLASS                        //
/////////////////////////////////////////////////////////////////////


///     THIS IS AN ABSTRACT BASE CLASS AND SHOULD NOT BE INSTANTIATED
///     This class represents a general graph. This graph is implemented
///     in an adjacency list format.
template <class T>
class Graph {

protected:
    /// 'Adjacency list'
    std::vector<std::vector<Edge<T>>> adj_list;

    // Number of nodes
    unsigned int N;

public:
    /// Default constructor and parameterized constructor
    Graph():N(0) { };

    Graph(std::vector<Edge<T>> in_vec, unsigned int size):N(size) {
        adj_list.resize(size);
        for (unsigned int i = 0; i < in_vec.size(); i++) {
            add_edge(in_vec[i]);
        }
    };


    /// Add an edge to the graph (with two additional overloads)
    void add_edge(Edge<T> new_edge) {
        // Due to the adjacency list representation, each 'node' is considered
        // to be an integer between 0 and the length of the adjacency list. The
        // nodes must be continuous, because we cannot leave a gap in our adjacency
        // list, at least as it is currently implemented with vectors.

        // If either node is not included in the adjacency list, resize
        while (new_edge.source >= N || new_edge.destination >= N) {
            adj_list.resize(N + 1);
            N++;
        }

        // Add the new edge
        this->adj_list[new_edge.source].push_back(new_edge);
    }

    void add_edge(unsigned int source, unsigned int destination, T metadata) {
        // If either node is not included in the adjacency list, resize
        while (source >= N || destination >= N) {
            this->adj_list.resize(this->N + 1);
            N++;
        }

        // Add the new edge
        auto* temp = new Edge<T>;
        temp->source = source;
        temp->destination = destination;
        temp->meta_data = metadata;

    }

    void add_edge(unsigned int source, unsigned int destination) {
        // If either node is not included in the adjacency list, resize
        while (source >= N || destination >= N) {
            this->adj_list.resize(this->N + 1);
            N++;
        }

        // Add the new edge
        auto* temp = new Edge<T>;
        temp->source = source;
        temp->destination = destination;
        this->adj_list[temp->source].push_back(*temp);
    }

    virtual void load_graph() = 0;

    /// Run the implemented graph search algorithm
    virtual std::list<unsigned int> run_algorithm(unsigned int start_node, unsigned int end_node) = 0;


    virtual /// Print the graph:
    void print_graph() {
        for (unsigned int i = 0; i < this->adj_list.size(); i++) {
            for (unsigned int j = 0; j < this->adj_list[i].size(); j++) {
                std::cout << "Source: " << this->adj_list[i][j].source << " Destination: " << adj_list[i][j].destination << " Metadata: " << adj_list[i][j].meta_data << std::endl;
            }
        }
    }
};


/////////////////////////////////////////////////////////////////////
//                            EDGE CLASS                           //
/////////////////////////////////////////////////////////////////////


/// This class represents the edges of the graph.
template <class T>
class Edge {
public:
    int source, destination;
    T meta_data;
};



/////////////////////////////////////////////////////////////////////
//                    DERIVED MAZE_GRAPH CLASS                     //
/////////////////////////////////////////////////////////////////////



// Struct to hold metadata for the Maze_graph class
struct T_MetaData {
    int int_data;
    std::string string_data;
};

//. Derived class implementing the maze problem (with user-defined struct as metadata template parameter)
class Maze_graph : public Graph<T_MetaData> {
protected:

    /// MEMBERS UNIQUE TO THE DERIVED CLASS
    /// 'Path' character to follow, in the maze
    char search_char;
    /// 'End' character to end at, in the maze
    char end_char;
    /// 'Start' character to start at, in the maze
    char start_char;
    /// Integer identifier of the starting node
    unsigned int start_node;
    /// Integer identifier of the ending node
    unsigned int end_node;
    /// Width of the maze
    unsigned int maze_width;
    /// Vector that stores the maze after it is read from a file
    std::vector<std::vector<char>> maze;

    /// MEMBERS INHERITED FROM THE BASE CLASS (REMINDER)
    /// unsigned int N;
    /// std::vector<std::vector<Edge<T>>> adj_list;

public:

    // Maze graph constructors
    Maze_graph(char in_search_char, char in_end_char, char in_start_char, const std::vector<Edge<T_MetaData>>& in_vec, unsigned int size):
    search_char(in_search_char), end_char(in_end_char), start_char(in_start_char) {

        this->adj_list.resize(size);
        this->N = size;
        for (auto & i : in_vec) {
            this->add_edge(i);
        }
    }

    explicit Maze_graph(char in_search_char = '\0', char in_end_char = '\0', char in_start_char = '\0'):
    search_char(in_search_char), end_char(in_end_char), start_char(in_start_char) {
        this->N = 0;
    }


    void print_graph() override {
        for (auto & i : this->adj_list) {
            for (auto & j : i) {
                std::cout << "Source: " << j.source << " Destination: " << j.destination << " Metadata: " << j.meta_data.int_data << " " << j.meta_data.string_data << std::endl;
            }
        }
    }


    /// Load the graph from an input file
    void load_graph() override {
        int count = 0;
        // Open input file
        std::ifstream maze_file("maze.txt");

        // Temp variables used to store file data
        char char_temp;
        std::vector<char> vec_temp;

        // Fill maze vector with file data
        while (maze_file.get(char_temp)) {
            // Store maze in the array
            if (char_temp != '\n') {
                vec_temp.push_back(char_temp);
                count++;
            }
            else {
                this->maze.push_back(vec_temp);
                vec_temp.resize(0);
                this->maze_width = count;
                count = 0;
            }
        }
        // Add final vector
        this->maze.push_back(vec_temp);

        // DEBUG: PRINT MAZE
        std::cout << "Rows: " << this->maze.size() << " Columns: " << this->maze[0].size() << std::endl;
        for (auto & i : this->maze) {
            for (char j : i) {
                std::cout << j;
            }
            std::cout << std::endl;
        }

        // Add edges to adjacency list
        for (unsigned int i = 0; i < this->maze.size(); i++) {
            for (unsigned int j = 0; j < this->maze[i].size(); j++) {
                char_temp = this->maze[i][j];

                if (char_temp == this->start_char) {
                    // Add the starting node to the adjacency list (also assume that the node underneath it is connected)
                    this->start_node = this->maze_width * i + j;
                    this->add_edge(this->start_node, this->maze_width * (i + 1) + j);
                }
                else if (char_temp == this->end_char) {
                    this->end_node = this->maze_width * i + j;
                }
                else if (char_temp == this->search_char || char_temp == this->start_char) {
                    // Check to see if any of the surrounding nodes are also path characters
                    if (this->maze[i][j - 1] == this->search_char || this->maze[i][j - 1] == this->end_char) {
                        this->add_edge(this->maze_width * i + j, this->maze_width * i + j - 1);
                    }
                    if (this->maze[i][j + 1] == this->search_char || this->maze[i][j + 1] == this->end_char) {
                        this->add_edge(this->maze_width * i + j, this->maze_width * i + j + 1);
                    }
                    if (this->maze[i-1][j] == this->search_char || this->maze[i - 1][j] == end_char) {
                        this->add_edge(this->maze_width * i + j, this->maze_width * (i-1) + j);
                    }
                    if (this->maze[i + 1][j] == this->search_char || this->maze[i + 1][j] == this->end_char) {
                        this->add_edge(this->maze_width * i + j, this->maze_width * (i + 1) + j);
                    }
                }
            }

        }
    }


    /// Search algorithm to find a path through the maze
    std::list<unsigned int> run_algorithm(unsigned int start_node, unsigned int end_node) override {
        // CREATE STACK
        std::stack<unsigned int> start_stack;
        start_stack.push(start_node);

        // CREATE LIST OF VISITED NODES ("PATH")
        std::list<unsigned int> path;

        // CALL DFS FUNCTION
        return DFS(start_stack, path, end_node);
    }


    /// Depth first search algorithm
    std::list<unsigned int> DFS(std::stack<unsigned int> in_stack, std::list<unsigned int> path, unsigned int end_node) {
        // Stores current node
        unsigned int curr_node = 0;

        // Check if the stack is empty (occurrs when we reach the end of a path without finding the end node)
        if (in_stack.empty()) {
            return *(new std::list<unsigned int>);
        }

        // Add top stack element to path
        path.push_back(in_stack.top());

        // Check to see if we have reached the end node
        if (in_stack.top() == end_node) {
            return path;
        }

        // Remove top stack element
        curr_node = in_stack.top();
        in_stack.pop();

        int run = 1;
        // Add nodes connected to the node we just removed
        // If we have more than one path, create a new stack for each path so that we can try all of them
        for (auto & i : this->adj_list[curr_node]) {
            // Check to see if we have already seen the node we are about to add
            run = 1;
            for (unsigned int & k : path) {
                if (k == i.destination) {
                    run = 0;
                }
            }
            if (run == 1) {
                // If we have not already visited this node:
                in_stack.push(i.destination);
                std::list<unsigned int> path_temp = DFS(in_stack, path, end_node);

                // If this resursive call found the end node, return this path!
                if (!path_temp.empty()) {
                    return path_temp;
                }
            }
        }

        // If no path is return yet (the maze is unsolvable):
        return *(new std::list<unsigned int>);
    }


    /// Print the new, solved maze
    void print_maze(const std::list<unsigned int>& in_list) {
        int solution = 0;
        for (unsigned int i = 0; i < this->maze.size(); i++) {
            for (unsigned int j = 0; j < this->maze[i].size(); j++) {
                // Check to see if this is a coordinate that is part of the solution
                solution = 0;
                for (auto & k : in_list) {
                    if (k == (i * this->maze_width + j) && (i * this->maze_width + j) != this->start_node && (i * this->maze_width + j) != this->end_node) {
                        solution = 1;
                    }
                }
                // If the coordinate is part of the solution, print a "+"
                if (solution == 1) {
                    std::cout << "+";
                }
                else {
                    std::cout << this->maze[i][j];
                }
            }
            // After each line, print a newline
            std::cout << std::endl;
        }
    }



};
