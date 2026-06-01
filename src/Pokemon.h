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

