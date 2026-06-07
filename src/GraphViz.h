#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include "graph.h"

inline const std::string DOT_OUTPUT_DIR = "dots";

inline std::string BattleNameToFilename(const std::string& battleName) {
    std::filesystem::create_directories(DOT_OUTPUT_DIR);

    std::string filename = battleName;
    size_t pos = 0;
    while ((pos = filename.find(" vs ", pos)) != std::string::npos) {
        filename.replace(pos, 4, "_vs_");
        pos += 4;
    }
    return DOT_OUTPUT_DIR + "/" + filename + ".dot";
}

inline void ExportToGraphViz(const Graph& g, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) return;

    out << "digraph G {\n";
    out << "  node [shape=box, fontname=\"Arial\"];\n";

    for (auto const& [id, node] : g.nodes) {
        out << "  \"" << id << "\" [label=\""
            << node.state.p1->name << " (" << node.state.hp1 << "%)\\n"
            << node.state.p2->name << " (" << node.state.hp2 << "%)\"];\n";

        for (auto const& edge : node.adj) {
            out << "  \"" << id << "\" -> \"" << edge.next_state
                << "\" [label=\"" << edge.atacks_used << "\"];\n";
        }
    }
    out << "}\n";
}
