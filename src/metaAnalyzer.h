#ifndef META_ANALYZER_H
#define META_ANALYZER_H

class MetaAnalyzer {
public:
    std::unordered_map<std::string, Graph> battles;
    MetaAnalyzer(std::unordered_map<std::string, Graph> battles): battles(battles) {};
    
    std::vector<Pokemon*>* getTimeComMaiorChanceDeVitoria();
    Pokemon* getPokemonComMelhorDesempenho();
    std::vector<Pokemon*> getPokemonsQueSempreGanham();
    std::vector<Graph*> getBatalhasQuePodemSerInterminaveis();
    std::vector<Graph*> getBatalhasComVitoriaMesmoComDesvantagemDeTipos();

};

#endif
