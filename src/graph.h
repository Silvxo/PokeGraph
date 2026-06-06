#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "State.h"

struct Edge {
    std::string next_state;
    std::string atacks_used;
};

struct Node {
    State state;
    std::vector<Edge> adj;
};

class Graph {
public:
    std::unordered_map<std::string, Node> nodes;

    // Cria o grafo com State inicial
    Graph(State& initial_state){
        AddState(initial_state);
    }

    void AddState(State& s) {
        std::string id = s.Identity();
        if (!nodes.count(id))
            nodes[id] = Node{s, {}};
    }

    void AddEdge(State& from, int i, int j) {

        State next = from.Step(i, j);
        std::string fromId = from.Identity();
        std::string toId   = next.Identity();

        AddState(from);
        AddState(next);

        nodes[fromId].adj.push_back(Edge{
            toId,
            from.p1->moves[i].name + " | " + from.p2->moves[j].name
        });
    }

    // Gera o grafo dai pode utilizar ele
    std::unordered_map<std::string, Node> generate(){
        return this->nodes;
    }
};