#include "Pokemon.h"

class State {
    public:
    Pokemon* p1; int hp1;
    Pokemon* p2; int hp2;
    State(Pokemon* p1, Pokemon* p2) {
        this->p1 = p1;
        this->p2 = p2;
        hp1 = 100;
        hp2 = 100;
    }
    State() {
        p1 = nullptr;
        p2 = nullptr;
        hp1 = 0;
        hp2 = 0;
    }
    State(Pokemon* p1, Pokemon* p2, int hp1, int hp2)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->hp1 = hp1;
        this->hp2 = hp2;
    }
    std::string Identity() {
        return p1->name + "_" + std::to_string(hp1) + "_" +
               p2->name + "_" + std::to_string(hp2);
    }

    void ApplyMove(Pokemon* attacker, Pokemon* defender, int& attackerHP, int& defenderHP, Move& move)
    {
        if (attackerHP <= 0 || defenderHP <= 0)
            return;

        int damage = CalculateDamage(*attacker, *defender, move);

        defenderHP = std::max(0, defenderHP - damage);
    }
    void ApplyRecover(int& attackerHP, int& defenderHP)
    {
        if (attackerHP <= 0 || defenderHP <= 0)
            return;

        attackerHP = std::min(100, attackerHP + 50);
    }
    State Step(int moveIndex1, int moveIndex2)
    {
        State next = *this;

        Move move1 = p1->moves[moveIndex1];
        Move move2 = p2->moves[moveIndex2];

        bool p1First = p1->speed >= p2->speed;

        if (p1First) {
            if (move1.name == "Recover") ApplyRecover(next.hp1, next.hp2);
            else                         ApplyMove(p1, p2, next.hp1, next.hp2, move1);

            if (move2.name == "Recover") ApplyRecover(next.hp2, next.hp1);
            else                         ApplyMove(p2, p1, next.hp2, next.hp1, move2);
        }
        else {
            if (move2.name == "Recover") ApplyRecover(next.hp2, next.hp1);
            else                         ApplyMove(p2, p1, next.hp2, next.hp1, move2);

            if (move1.name == "Recover") ApplyRecover(next.hp1, next.hp2);
            else                         ApplyMove(p1, p2, next.hp1, next.hp2, move1);
        }

        return next;
    }
};