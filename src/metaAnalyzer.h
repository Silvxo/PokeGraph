#ifndef META_ANALYZER_H
#define META_ANALYZER_H

#include <unordered_map>
#include <vector>
#include <string>


class MetaAnalyzer {
public:
    std::unordered_map<std::string, Graph> tournament;
    std::vector<Pokemon*>* team1;
    std::vector<Pokemon*>* team2;
    MetaAnalyzer(std::unordered_map<std::string, Graph> tournament, std::vector<Pokemon*>* team1, std::vector<Pokemon*>* team2): tournament(tournament), team1(team1), team2(team2) {};
    
    std::vector<Pokemon*>* getTimeComMaiorChanceDeVitoria(){
        std::vector<Pokemon*>* bestTeam = nullptr;
        //Itera sobre cada uma das batalhas
        //Cada batalha com mais chances para um pokemon soma um ponto para o time dele
        //retorna o time com mais pontos

        int team1Wins = 0;
        int team2Wins = 0;

        for(auto [battleName, battleGraph] : tournament){
   

            for (auto [id, node] : battleGraph.nodes) {
                if (node.state.hp1 <= 0 && node.state.hp2 > 0) team2Wins++;
                if (node.state.hp2 <= 0 && node.state.hp1 > 0) team1Wins++;
            }
        }

        if(team1Wins > team2Wins) return team1;
        else if (team2Wins > team1Wins) return team2;
        return nullptr; // Empate
    };

    std::vector<Pokemon*> getPokemonComMelhorDesempenho(){
        std::vector<Pokemon*> bestPokemons = {};

        // nome do pokemon, numero de vitorias, numero de batalhas
        std::unordered_map<Pokemon* , std::pair<int, int>> pokemonStats = {};
        int bestWinRate = -1;

        // Para cada batalha finalizada, 
        // conta batalha para os dois participantes
        // e vitoria para o vencedor
        for(auto [battleName, battleGraph] : tournament){
            for (auto [id, node] : battleGraph.nodes) {
                if (node.state.hp1 <= 0 && node.state.hp2 > 0){
                    pokemonStats[node.state.p2].first++; // Vitoria
                    pokemonStats[node.state.p2].second++; // Batalha
                    pokemonStats[node.state.p1].second++; // Batalha
                }
                if (node.state.hp2 <= 0 && node.state.hp1 > 0){
                    pokemonStats[node.state.p1].first++; // Vitoria
                    pokemonStats[node.state.p1].second++; // Batalha
                    pokemonStats[node.state.p2].second++; // Batalha
                }
            }
        }

        for(const auto& [pokemon, stats] : pokemonStats){
            double winRate = (double)stats.first / stats.second;
            if(winRate > bestWinRate){
                bestWinRate = winRate;
                bestPokemons.clear();
                bestPokemons.push_back(pokemon);
            }
            if(winRate == bestWinRate){
                bestPokemons.push_back(pokemon);
            }
        }

        return bestPokemons; 
    };

    std::vector<std::string> getBatalhasComPokemonsInvictos(){
        std::vector<std::string> alwaysWinners = {};

        for(auto [battleName, battleGraph] : tournament){
            bool pokemon1AlwaysWins = true;
            bool pokemon2AlwaysWins = true;
            std::string winnerName = "";

            for(auto [id, node] : battleGraph.nodes){
                if(node.state.hp1 <= 0 && node.state.hp2 > 0) 
                    winnerName = node.state.p2->name;
                    pokemon1AlwaysWins = false;
                if(node.state.hp2 <= 0 && node.state.hp1 > 0){
                    winnerName = node.state.p1->name;
                    pokemon2AlwaysWins = false;
                }
                if(!pokemon1AlwaysWins && !pokemon2AlwaysWins) break; // Se ambos já perderam, não precisa continuar verificando
            }
            if(pokemon1AlwaysWins || pokemon2AlwaysWins){
                alwaysWinners.push_back(battleName + " -> " + winnerName);
            }
        }        
        return alwaysWinners;
    };

    std::vector<std::string> getBatalhasQuePodemSerInterminaveis(){
        std::vector<std::string> interminaveis = {};
        // Condicoes para batalhas interminaveis:
        // 1. Ambos pokemons tem Recovery
        // 2. Um pokemon tem Recovery e o outro tem um move com dano de menos de 50% da vida do que tem Recovery (e não tem desvantagem de tipo)
        for(auto pokemonTeam1 : *team1){
            for(auto pokemonTeam2 : *team2){
                bool pokemon1HasRecovery = false;
                bool pokemon2HasRecovery = false;
                for(auto move : pokemonTeam1->moves){
                    if(move.name == "Recover") pokemon1HasRecovery = true;
                }
                for(auto move : pokemonTeam2->moves){
                    if(move.name == "Recover") pokemon2HasRecovery = true;
                }
                if(pokemon1HasRecovery && pokemon2HasRecovery){
                    interminaveis.push_back(pokemonTeam1->name + " vs " + pokemonTeam2->name);
                } else if(pokemon1HasRecovery){
                    for(auto move : pokemonTeam2->moves){
                        if(CalculateDamage(*pokemonTeam1, *pokemonTeam2, move) < (pokemonTeam1->hp / 2)){
                            interminaveis.push_back(pokemonTeam1->name + " vs " + pokemonTeam2->name);
                            break;
                        }
                    }
                } else if(pokemon2HasRecovery){
                    for(auto move : pokemonTeam1->moves){
                        if(CalculateDamage(*pokemonTeam2, *pokemonTeam1, move) < (pokemonTeam2->hp / 2)){
                            interminaveis.push_back(pokemonTeam1->name + " vs " + pokemonTeam2->name);
                            break;
                        }
                    }
                }
            }
        }
        return interminaveis;
    };

    std::vector<std::string> getBatalhasComVitoriaMesmoComDesvantagemDeTipos(){
        std::vector<std::string> vitoriasDesvantagem = {};
        for(auto [battleName, battleGraph] : tournament){
            for(auto [id, node] : battleGraph.nodes){
                if(node.state.hp1 <= 0 && node.state.hp2 > 0){
                    if(hasDisadvantage(node.state.p2, node.state.p1)){
                        vitoriasDesvantagem.push_back(battleName);
                        break; // Se já encontramos uma vitória com desvantagem, não precisamos verificar mais nessa batalha
                    }
                }
                if(node.state.hp2 <= 0 && node.state.hp1 > 0){
                    if(hasDisadvantage(node.state.p1, node.state.p2)){
                        vitoriasDesvantagem.push_back(battleName);
                        break; // Se já encontramos uma vitória com desvantagem, não precisamos verificar mais nessa batalha
                    }
                }
            }
        }
        
        return vitoriasDesvantagem;
    };

    bool hasDisadvantage(Pokemon* p1, Pokemon* p2){
        float effectiveness = GetEffectiveness(p1->types[0], p2->types[0]);
        for(auto defenderType : p2->types){
            for(auto atackerType : p1->types){
                float currentEffectiveness = GetEffectiveness(atackerType, defenderType);
                if(currentEffectiveness < 1) return true;
            }
        }
        return false;
    };

    void printMetaAnalyzerReport(){
        std::cout << "=========================================\n";
        std::cout << "        RELATORIO DE META-GAME           \n";
        std::cout << "=========================================\n";

        auto bestTeam = getTimeComMaiorChanceDeVitoria();
        if(bestTeam == team1) std::cout << "-> O Time 1 tem a maior chance de vitoria!\n";
        else if (bestTeam == team2) std::cout << "-> O Time 2 tem a maior chance de vitoria!\n";
        else std::cout << "-> Os times estao perfeitamente empatados!\n";

        std::cout << "\nMelhor(es) Pokemon(s):\n";
        auto bestPokemons = getPokemonComMelhorDesempenho();
        for(auto pokemon : bestPokemons){
            std::cout << " - " << pokemon->name << "\n";
        }

        std::cout << "\nBatalhas com Pokemons Invictos:\n";
        auto alwaysWinners = getBatalhasComPokemonsInvictos();
        for(auto battleName : alwaysWinners){
            std::cout << " - " << battleName << "\n";
        }

        std::cout << "\nBatalhas que Podem Ser Interminaveis:\n";
        auto interminaveis = getBatalhasQuePodemSerInterminaveis();
        for(auto battleName : interminaveis){
            std::cout << " - " << battleName << "\n";
        }

        std::cout << "\nBatalhas com Vitoria Mesmo com Desvantagem de Tipos:\n";
        auto vitoriasDesvantagem = getBatalhasComVitoriaMesmoComDesvantagemDeTipos();
        for(auto battleName : vitoriasDesvantagem){
            std::cout << " - " << battleName << "\n";
        }
        
        std::cout << "=========================================\n";
    }

    
};

#endif
