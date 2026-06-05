#ifndef META_ANALYZER_H
#define META_ANALYZER_H

class MetaAnalyzer {
public:
    std::unordered_map<std::string, Graph> battles;
    MetaAnalyzer(std::unordered_map<std::string, Graph> battles): battles(battles) {};
    
    std::vector<Pokemon*>* getTimeComMaiorChanceDeVitoria(){
        std::vector<Pokemon*>* bestTeam = nullptr;
        //Itera sobre cada uma das batalhas
        //Cada batalha com mais chances para um pokemon soma um ponto para o time dele
        //retorna o time com mais pontos

        return bestTeam;
    };
    Pokemon* getPokemonComMelhorDesempenho(){
        Pokemon* bestPokemon = nullptr;
        
        return bestPokemon; 
    };
    std::vector<Pokemon*> getPokemonsQueSempreGanham();
    std::vector<Graph*> getBatalhasQuePodemSerInterminaveis();
    std::vector<Graph*> getBatalhasComVitoriaMesmoComDesvantagemDeTipos();

    
};

#endif
