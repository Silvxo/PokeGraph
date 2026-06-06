#include <string>
#include <unordered_map>
#include <vector>
#include "graph.h"

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
            for(int i = 0; i < team1.size() - 1; i++){
                for(int j = i; j < team2.size(); j++){
                    //generateBattle

                    Pokemon* pk1 = team1[i];
                    Pokemon* pk2 = team2[j];

                    State initial(pk1, pk2);
                    Graph battle(initial);
                    battles.insert({pk1->name + " vs " + pk2->name, std::move(battle)});
                }
            }
            return battles;
        }
};