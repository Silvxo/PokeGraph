#include <string>
#include <unordered_map>
#include <vector>
#include "State.h"


int main()
{
    std::vector<Pokemon*> team1 =
    {
        new Pokemon("Charizard", { FIRE,    FLYING  },  78,  84,  78, 109,  85, 100, { Flamethrower, Hurricane,   ShadowBall,  Recover }),
        new Pokemon("Feraligatr",{ WATER            },  85, 105, 100,  79,  83,  78, { Liquidation,  IcePunch,    Crunch,      Earthquake }),
        new Pokemon("Scizor",    { BUG,     STEEL   },  70, 130, 100,  55,  80,  65, { IronHead,     MetalClaw,   BugBuzz,     Recover }),
        new Pokemon("Decidueye", { GRASS,   GHOST   },  78, 107,  75, 100, 100,  70, { LeafBlade,    ShadowClaw,  EnergyBall,  Recover }),
        new Pokemon("Garchomp",  { DRAGON,  GROUND  }, 108, 130,  95,  80,  85, 102, { Earthquake,   DragonClaw,  Crunch,      FirePunch }),
        new Pokemon("Reuniclus", { PSYCHIC          }, 110,  65,  75, 125,  85,  30, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    std::vector<Pokemon*> team2 =
    {
        new Pokemon("Blastoise", { WATER            },  79,  83, 100,  85, 105,  78, { HydroPump,    IceBeam,     AuraSphere,  Recover }),
        new Pokemon("Blaziken",  { FIRE,    FIGHTING},  80, 120,  70, 110,  70,  80, { Flamethrower, CloseCombat, FirePunch,   ThunderPunch }),
        new Pokemon("Chesnaught",{ GRASS,   FIGHTING},  88, 107, 122,  74,  75,  64, { LeafBlade,    CloseCombat, Earthquake,  Recover }),
        new Pokemon("Tyranitar", { ROCK,    DARK    }, 100, 134, 110,  95, 100,  61, { Crunch,       RockSlide,   Earthquake,  IcePunch }),
        new Pokemon("Gengar",    { GHOST,   POISON  },  60,  65,  60, 130,  75, 110, { ShadowBall,   SludgeBomb,  Thunderbolt, Recover }),
        new Pokemon("Alakazam",  { PSYCHIC          },  55,  50,  45, 135,  95, 120, { PsychicMove,  Psystrike,   ShadowBall,  Recover })
    };

    return 0;
}