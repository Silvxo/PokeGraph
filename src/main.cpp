#include <iostream>
#include <unordered_map>
#include <vector>
#include "Tournament.h"
#include "GraphViz.h"

int main() {
    std::vector<Pokemon*> team1 = {
        new Pokemon("Charizard", { FIRE,    FLYING  },  78,  84,  78, 109,  85, 100, { Flamethrower, Hurricane,   ShadowBall,  Recover }),
        new Pokemon("Feraligatr",{ WATER            },  85, 105, 100,  79,  83,  78, { Liquidation,  IcePunch,    Crunch,      Earthquake }),
        new Pokemon("Scizor",    { BUG,     STEEL   },  70, 130, 100,  55,  80,  65, { IronHead,     MetalClaw,   BugBuzz,     Recover }),
        new Pokemon("Decidueye", { GRASS,   GHOST   },  78, 107,  75, 100, 100,  70, { LeafBlade,    ShadowClaw,  EnergyBall,  Recover }),
        new Pokemon("Garchomp",  { DRAGON,  GROUND  }, 108, 130,  95,  80,  85, 102, { Earthquake,   DragonClaw,  Crunch,      FirePunch }),
        new Pokemon("Reuniclus", { PSYCHIC          }, 110,  65,  75, 125,  85,  30, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    std::vector<Pokemon*> team2 = {
        new Pokemon("Blastoise", { WATER            },  79,  83, 100,  85, 105,  78, { HydroPump,    IceBeam,     AuraSphere,  Recover }),
        new Pokemon("Blaziken",  { FIRE,    FIGHTING},  80, 120,  70, 110,  70,  80, { Flamethrower, CloseCombat, FirePunch,   ThunderPunch }),
        new Pokemon("Chesnaught",{ GRASS,   FIGHTING},  88, 107, 122,  74,  75,  64, { LeafBlade,    CloseCombat, Earthquake,  Recover }),
        new Pokemon("Tyranitar", { ROCK,    DARK    }, 100, 134, 110,  95, 100,  61, { Crunch,       RockSlide,   Earthquake,  IcePunch }),
        new Pokemon("Gengar",    { GHOST,   POISON  },  60,  65,  60, 130,  75, 110, { ShadowBall,   SludgeBomb,  Thunderbolt, Recover }),
        new Pokemon("Alakazam",  { PSYCHIC          },  55,  50,  45, 135,  95, 120, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    Tournament tournament(team1, team2);
    auto results = tournament.getTournamentResults();

    int vitoriasTime1 = 0;
    int vitoriasTime2 = 0;
    std::unordered_map<std::string, int> vitoriasIndividuais;

    std::cout << "Iniciando a simulacao dos " << results.size() << " combates...\n\n";

    for (auto const& [battleName, graph] : results) {
        std::cout << "Simulando: " << battleName << "...\n";

        int p1Wins = 0, p2Wins = 0;
        for (auto const& [id, node] : graph.nodes) {
            if (node.state.hp1 <= 0 && node.state.hp2 > 0) p2Wins++;
            if (node.state.hp2 <= 0 && node.state.hp1 > 0) p1Wins++;
        }

        if (p1Wins > p2Wins) {
            vitoriasTime1++;
            vitoriasIndividuais[graph.nodes.begin()->second.state.p1->name]++;
        } else if (p2Wins > p1Wins) {
            vitoriasTime2++;
            vitoriasIndividuais[graph.nodes.begin()->second.state.p2->name]++;
        }

        ExportToGraphViz(graph, BattleNameToFilename(battleName));
    }

    std::cout << "\n=========================================\n";
    std::cout << "        RELATORIO DE META-GAME           \n";
    std::cout << "=========================================\n";
    std::cout << "Vitorias totais do Time 1: " << vitoriasTime1 << "\n";
    std::cout << "Vitorias totais do Time 2: " << vitoriasTime2 << "\n\n";

    if (vitoriasTime1 > vitoriasTime2) {
        std::cout << "-> O Time 1 tem a maior chance de vitoria!\n";
    } else if (vitoriasTime2 > vitoriasTime1) {
        std::cout << "-> O Time 2 tem a maior chance de vitoria!\n";
    } else {
        std::cout << "-> Os times estao perfeitamente empatados!\n";
    }

    std::cout << "\nDesempenho Individual (Vitorias):\n";
    for (auto const& [nome, vitorias] : vitoriasIndividuais) {
        std::cout << " - " << nome << ": " << vitorias << " vitorias\n";
    }
    std::cout << "=========================================\n";

    for (Pokemon* p : team1) delete p;
    for (Pokemon* p : team2) delete p;

    return 0;
}
