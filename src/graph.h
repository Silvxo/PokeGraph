#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "State.h"
#include <queue>

struct Edge {
    std::string next_state;
    std::string atacks_used;
};

struct Node {
    State state;
    std::vector<Edge> adj;
};

class MoveWithMultiplyer{
    public:
        int damage;
        Move move;
    
        MoveWithMultiplyer(const Move& move, int damage)
            : damage(damage), move(move) {}

        bool operator<(const MoveWithMultiplyer& other) const{
            return this->damage < other.damage;
        }
};
class Graph {
    std::unordered_set<std::string> visited;

public:
    std::unordered_map<std::string, Node> nodes;

    Graph() = default;

    // Cria o grafo com State inicial
    Graph(State& initial_state){
        verificaMeta(initial_state);
    }

    // recover 50 flame 60 watergun 90 flash 120

    void verificaMeta(State& state){


        Pokemon* a = state.p1;
        Pokemon* b = state.p2;

        std::priority_queue<MoveWithMultiplyer> heap1;
        std::priority_queue<MoveWithMultiplyer> heap2;

        bool ar = false;
        bool br = false;
        for (size_t i = 0; i < a->moves.size(); ++i) {
            heap1.push(MoveWithMultiplyer(a->moves[i], CalculateDamage(*a, *b, a->moves[i])));
            if (a->moves[i].name == "Recover") {
                ar = true;
            }
        }
        for (size_t i = 0; i < b->moves.size(); ++i) {
            heap2.push(MoveWithMultiplyer(b->moves[i], CalculateDamage(*b, *a, b->moves[i])));
            if (b->moves[i].name == "Recover") {
                br = true;
            }
        }

        std::cout << "ERRO AQUI" << std::endl;

        MoveWithMultiplyer atc1 = heap1.top(); heap1.pop();
        MoveWithMultiplyer atc2 = heap1.top(); heap1.pop();

        MoveWithMultiplyer btc1 = heap2.top(); heap2.pop();
        MoveWithMultiplyer btc2 = heap2.top(); heap2.pop();

        Pokemon* c = nullptr;
        Pokemon* d = nullptr;

        // Pokemon (std::string name, std::vector<Type> types,
        //      int hp, int attack, int defense, int spAttack, int spDefense, int speed,
        //      std::vector<Move> moves)

        if(ar){
            if (atc2.damage < 50 && btc2.damage > 50){
                c = new Pokemon(a->name, a->types, a->hp, a->attack, a->defense, a->spAttack, a->spDefense, a->speed, std::vector<Move>{atc1.move, Move{"Recover",      NORMAL, STATUS,   0}});
            }else{
                c = new Pokemon(a->name, a->types, a->hp, a->attack, a->defense, a->spAttack, a->spDefense, a->speed, std::vector<Move>{atc1.move, atc2.move});
            }
        }else{
            c = new Pokemon(a->name, a->types, a->hp, a->attack, a->defense, a->spAttack, a->spDefense, a->speed, std::vector<Move>{atc1.move, atc2.move});
        }
        if(br){
            if (btc2.damage < 50 && atc2.damage > 50){
                d = new Pokemon(b->name, b->types, b->hp, b->attack, b->defense, b->spAttack, b->spDefense, b->speed, std::vector<Move>{btc1.move, Move{"Recover",      NORMAL, STATUS,   0}});
            }else{
                d = new Pokemon(b->name, b->types, b->hp, b->attack, b->defense, b->spAttack, b->spDefense, b->speed, std::vector<Move>{btc1.move, btc2.move});
            }
        }else{
            d = new Pokemon(b->name, b->types, b->hp, b->attack, b->defense, b->spAttack, b->spDefense, b->speed, std::vector<Move>{btc1.move, btc2.move});
        }

        std::cout << "ANTES STATE" << std::endl;


        State st = State(c, d);
        std::cout << "DECLAROU STATE" << std::endl;

        this->AddState(st);
        std::cout << "ADICIONOU STATE" << std::endl;

        this->untill_end(st);
        std::cout << "DEPOIS STATE" << std::endl;

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

        for (size_t i = 0; i < a->moves.size(); ++i) {
            for (size_t j = 0; j < b->moves.size(); ++j) {
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