#pragma once
#include "stdlib.h"
#include "vector"
#include "string"
#include "Moves.h"

class Pokemon {
    public:
    std::string name;
    std::vector<Type> types;
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;

    std::vector<Move> moves;
    Pokemon (std::string name, std::vector<Type> types,
             int hp, int attack, int defense, int spAttack, int spDefense, int speed,
             std::vector<Move> moves)
    {
        this->name = name;
        this->types = types;
        this->hp = hp;
        this->attack = attack;
        this->defense = defense;
        this->spAttack = spAttack;
        this->spDefense = spDefense;
        this->speed = speed;
        this->moves = moves;
    }
};

inline int CalculateDamage(Pokemon& attacker, Pokemon& defender, Move& move)
{
    if (move.category == STATUS)
        return 0;

    float atkStat = (move.category == PHYSICAL) ? attacker.attack  : attacker.spAttack;
    float defStat = (move.category == PHYSICAL) ? defender.defense : defender.spDefense;
    float effectiveness = 1.0f;
    for (Type t : defender.types)
        effectiveness *= GetEffectiveness(move.type, t);

    float stab = 1.0f;
    for (Type t : attacker.types)
    {
        if (t == move.type)
        {
            stab = 1.5f;
            break;
        }
    }

    float damage  = (((22.0f * move.power * (atkStat / defStat)) / 50.0f) + 2.0f) * stab * effectiveness;
    float percent = (damage / defender.hp) * 100.0f;
    int rounded   = (int)std::ceil(percent / 10.0f) * 10;

    return std::fmax(10, rounded);
}
