#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
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
    std::unordered_set<std::string> visited;

public:
    std::unordered_map<std::string, Node> nodes;

    Graph() = default;

    // Cria o grafo com State inicial
    Graph(State& initial_state){
        AddState(initial_state);
        untill_end(initial_state);
    }

    void untill_end(State& state){
        if (state.hp1 <= 0 || state.hp2 <= 0){
            return;
        }

        std::string id = state.Identity();
        if (visited.count(id))
            return;
        visited.insert(id);
        
        Pokemon* a = state.p1;
        Pokemon* b = state.p2;

        for (int i=0; i < a->moves.size(); i++){
            for (int j=0; j < b->moves.size(); j++){
                if (a->moves[i].name == "Recover" && state.hp1 >= 100 &&
                    b->moves[j].name == "Recover" && state.hp2 >= 100)
                    continue;

                auto next_state = AddEdge(state, i, j);
                untill_end(next_state);
            }
        }        
    };

    void AddState(State& s) {
        std::string id = s.Identity();
        if (!nodes.count(id))
            nodes.emplace(id, Node{s, {}});
    }
    
    State AddEdge(State& from, int i, int j){

        State next = from.Step(i, j);
        std::string fromId = from.Identity();
        std::string toId   = next.Identity();

        if (toId == fromId)
            return from;
        
        AddState(from);
        AddState(next);
        
        nodes.at(fromId).adj.push_back(Edge{
            toId,
            from.p1->moves[i].name + " | " + from.p2->moves[j].name
        });

        return next;
    }

    // Gera o grafo dai pode utilizar ele
    std::unordered_map<std::string, Node> generate(){
        return this->nodes;
    }
};