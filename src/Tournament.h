#include <string>
#include <unordered_map>
#include <vector>
#include "graph.h"
#include "GraphViz.h"

class Tournament{
    private:
        std::vector<Pokemon*> team1;
        std::vector<Pokemon*> team2;
        std::unordered_map<std::string, Graph> battles;

    public:
        Tournament(std::vector<Pokemon*> team1, std::vector<Pokemon*> team2){
            this->team1 = team1;
            this->team2 = team2;
        }

        std::unordered_map<std::string, Graph> getTournamentResults(){
            for(Pokemon* pk1: team1){
                for(Pokemon* pk2 : team2){
                    //generateBattle

                    State initial(pk1, pk2);
                    Graph battle(initial);
                    
                    battles.insert({pk1->name + " vs " + pk2->name, std::move(battle)});
                    ExportToGraphViz(battlenodes, BattleNameToFilename(pk1->name + " vs " + pk2->name));
                }
            }
            return battles;
        }
};