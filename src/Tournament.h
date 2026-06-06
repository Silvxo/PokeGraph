#include "Pokemon.h"
#include "graph.h"
#include "battle.h"

class Tournament{
    private:
        std::vector<Pokemon*> team1;
        std::vector<Pokemon*> team2;
        std::unordered_map<std::string, Graph> battles;


    public:
        Tournament(std::vector<Pokemon*> team1, std::vector<Pokemon*> team2){
            this.team1 = team1;
            this.team2 = team2;
        }

        std::unordered_map<std::string, Graph> getTournamentResults(){
            for(Pokemon pokemonTeam1 : team1){
                for(Pokemon pokemonTeam2 : team2){
                    //generateBattle
                    Graph battle = new Graph(); 
                    battles.insert({pokemonTeam1->name + " vs " + pokemonTeam2->name, battle.generate()});
                }
            }
            return battles;
        }
}