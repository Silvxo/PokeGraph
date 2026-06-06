#include "stdlib.h"
#include "string"
#include "Utils.h"

class Move {
    public:
    std::string name;
    Type type;
    Category category;
    int power;

    Move(
        std::string name,
        Type type,
        Category category,
        int power)
    {
        this->name = name;
        this->type = type;
        this->category = category;
        this->power = power;
    }
};
static Move Recover        ("Recover",      NORMAL, STATUS,   0);
static Move BodySlam       ("Body Slam",    NORMAL, PHYSICAL,   85);
static Move Boomburst      ("Boomburst",    NORMAL, SPECIAL,   140);
static Move FirePunch      ("Fire Punch",   FIRE,   PHYSICAL,   75);
static Move Flamethrower   ("Flamethrower", FIRE,   SPECIAL, 90);
static Move Liquidation    ("Liquidation",  WATER,  PHYSICAL,   85);
static Move HydroPump      ("Hydro Pump",   WATER,  SPECIAL,   110);
static Move ThunderPunch   ("Thunder Punch",   ELECTRIC,  PHYSICAL,   75);
static Move Thunderbolt    ("Thunderbolt",  ELECTRIC,  SPECIAL, 90);
static Move LeafBlade      ("Leaf Blade",   GRASS,  PHYSICAL,   90);
static Move EnergyBall     ("Energy Ball",  GRASS,  SPECIAL, 90);
static Move IcePunch       ("Ice Punch",    ICE,    PHYSICAL,   75);
static Move IceBeam        ("Ice Beam",     ICE,    SPECIAL, 90);
static Move CloseCombat    ("Close Combat", FIGHTING,  PHYSICAL,  120);
static Move AuraSphere     ("Aura Sphere",  FIGHTING,  SPECIAL, 80);
static Move PoisonJab      ("Poison Jab",   POISON, PHYSICAL,   80);
static Move SludgeBomb     ("Sludge Bomb",  POISON, SPECIAL, 90);
static Move Earthquake     ("Earthquake",   GROUND, PHYSICAL,  100);
static Move MudSlap        ("Mud-Slap",     GROUND, SPECIAL, 20);
static Move DrillPeck      ("Drill Peck",   FLYING, PHYSICAL,   80);
static Move Hurricane      ("Hurricane",    FLYING, SPECIAL,   110);
static Move PsychicMove    ("Psychic",      PSYCHIC,   SPECIAL, 90);
static Move Psystrike      ("Psystrike",    PSYCHIC,   SPECIAL,   100);
static Move Megahorn       ("Megahorn",     BUG,    PHYSICAL,  120);
static Move BugBuzz        ("Bug Buzz",     BUG,    SPECIAL, 90);
static Move RockSlide      ("Rock Slide",   ROCK,   PHYSICAL,   75);
static Move AncientPower   ("Ancient Power",   ROCK,   SPECIAL, 60);
static Move ShadowClaw     ("Shadow Claw",  GHOST,  PHYSICAL,   70);
static Move ShadowBall     ("Shadow Ball",  GHOST,  SPECIAL, 80);
static Move DragonClaw     ("Dragon Claw",  DRAGON, PHYSICAL,   80);
static Move DracoMeteor    ("Draco Meteor", DRAGON, SPECIAL,   130);
static Move Crunch         ("Crunch",       DARK,   PHYSICAL,   80);
static Move DarkPulse      ("Dark Pulse",   DARK,   SPECIAL, 80);
static Move MetalClaw      ("Metal Claw",   STEEL,  PHYSICAL,   50);
static Move IronHead       ("Iron Head",    STEEL,  PHYSICAL,   80);
static Move PlayRough      ("Play Rough",   FAIRY,  PHYSICAL,   90);
static Move DazzlingGleam  ("Dazzling Gleam",  FAIRY,  SPECIAL, 80);