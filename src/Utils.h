enum Type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, 
    PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY, TYPE_COUNT
};

enum Category { PHYSICAL, SPECIAL, STATUS };

static float TypeChart[TYPE_COUNT][TYPE_COUNT] = {
    // DEFENDER →
    // NOR FIR WAT ELE GRA ICE FIG POI GRO FLY PSY BUG ROC GHO DRA DAR STE FAI
    /* NORMAL  */ {1,1,1,1,1,1,1,1,1,1,1,1,0.5f,0,1,1,0.5f,1},
    /* FIRE    */ {1,0.5f,0.5f,1,2,2,1,1,1,1,1,2,0.5f,1,0.5f,1,2,1},
    /* WATER   */ {1,2,0.5f,1,0.5f,1,1,1,2,1,1,1,2,1,0.5f,1,1,1},
    /* ELECTRIC*/ {1,1,2,0.5f,0.5f,1,1,1,0,2,1,1,1,1,0.5f,1,1,1},
    /* GRASS   */ {1,0.5f,2,1,0.5f,1,1,0.5f,2,0.5f,1,0.5f,2,1,0.5f,1,0.5f,1},
    /* ICE     */ {1,0.5f,0.5f,1,2,0.5f,1,1,2,2,1,1,1,1,2,1,0.5f,1},
    /* FIGHTING*/ {2,1,1,1,1,2,1,0.5f,1,0.5f,0.5f,0.5f,2,0,1,2,2,0.5f},
    /* POISON  */ {1,1,1,1,2,1,1,0.5f,0.5f,1,1,1,0.5f,0.5f,1,1,0,2},
    /* GROUND  */ {1,2,1,2,0.5f,1,1,2,1,0,1,0.5f,2,1,1,1,2,1},
    /* FLYING  */ {1,1,1,0.5f,2,1,2,1,1,1,1,2,0.5f,1,1,1,0.5f,1},
    /* PSYCHIC */ {1,1,1,1,1,1,2,2,1,1,0.5f,1,1,1,1,0,0.5f,1},
    /* BUG     */ {1,0.5f,1,1,2,1,0.5f,0.5f,1,0.5f,2,1,1,0.5f,1,2,0.5f,0.5f},
    /* ROCK    */ {1,2,1,1,1,2,0.5f,1,0.5f,2,1,2,1,1,1,1,0.5f,1},
    /* GHOST   */ {0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5f,1,1},
    /* DRAGON  */ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5f,0},
    /* DARK    */ {1,1,1,1,1,1,0.5f,1,1,1,2,1,1,2,1,0.5f,1,0.5f},
    /* STEEL   */ {1,0.5f,0.5f,0.5f,1,2,1,1,1,1,1,1,2,1,1,1,0.5f,2},
    /* FAIRY   */ {1,0.5f,1,1,1,1,2,0.5f,1,1,1,1,1,1,2,2,0.5f,1}
};
float GetEffectiveness(Type atk, Type def)
{
    return TypeChart[(int)atk][(int)def];
}
int CalculateDamage(Pokemon& attacker, Pokemon& defender, Move& move)
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

    return std::max(10, rounded);
}
