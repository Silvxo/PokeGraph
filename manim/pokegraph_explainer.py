"""Manim animation explaining the PokeGraph battle-graph logic.

Render with:
    python -m manim -qh manim/pokegraph_explainer.py PokeGraphExplainer
"""

from manim import *

# ---- palette -------------------------------------------------------------
BG = "#0f1117"
P1_COLOR = "#ff7043"      # Charizard / team 1 (orange)
P2_COLOR = "#7e57c2"      # Alakazam / team 2 (purple)
WIN_COLOR = "#43d17a"     # team 1 wins  (green)
LOSS_COLOR = "#ef5350"    # team 1 loses (red)
EDGE_COLOR = "#5a6378"
ACCENT = "#ffd54f"


def state_node(p1, hp1, p2, hp2, fill=BG, border=WHITE, width=2.6, height=1.25):
    """A battle-state node: two Pokemon with their HP percentages."""
    box = RoundedRectangle(
        corner_radius=0.16, width=width, height=height,
        stroke_color=border, stroke_width=3, fill_color=fill, fill_opacity=0.55,
    )
    t1 = Text(f"{p1}  {hp1}%", font_size=22, color=P1_COLOR, weight=BOLD)
    t2 = Text(f"{p2}  {hp2}%", font_size=22, color=P2_COLOR, weight=BOLD)
    rows = VGroup(t1, t2).arrange(DOWN, buff=0.12)
    rows.move_to(box.get_center())
    g = VGroup(box, rows)
    g.box = box
    return g


class PokeGraphExplainer(Scene):
    def construct(self):
        self.camera.background_color = BG
        self.intro()
        self.what_is_a_state()
        self.the_turn_and_edges()
        self.building_the_graph()
        self.tournament()
        self.outro()

    # ------------------------------------------------------------------
    def section_title(self, text):
        t = Text(text, font_size=30, color=ACCENT, weight=BOLD)
        t.to_edge(UP, buff=0.5)
        return t

    def clear_all(self):
        self.play(*[FadeOut(m) for m in self.mobjects], run_time=0.6)

    # ------------------------------------------------------------------
    def intro(self):
        title = Text("PokeGraph", font_size=72, weight=BOLD, color=WHITE)
        sub = Text("Modeling a Pokemon battle as a graph",
                   font_size=30, color=ACCENT)
        sub.next_to(title, DOWN, buff=0.4)

        self.play(Write(title), run_time=1.2)
        self.play(FadeIn(sub, shift=UP * 0.3), run_time=0.8)
        self.wait(1.2)
        self.play(title.animate.scale(0.5).to_edge(UP), FadeOut(sub))
        self.play(FadeOut(title))

    # ------------------------------------------------------------------
    def what_is_a_state(self):
        title = self.section_title("1.  A battle = a STATE")
        self.play(FadeIn(title))

        node = state_node("Charizard", 100, "Alakazam", 100,
                          border=WHITE, width=3.4, height=1.6)
        node.move_to(ORIGIN)
        self.play(Create(node.box), Write(node[1]), run_time=1.2)

        caption = Text("Each state stores the two Pokemon and their HP",
                       font_size=26, color=GREY_B)
        caption.next_to(node, DOWN, buff=0.7)
        self.play(FadeIn(caption, shift=UP * 0.2))
        self.wait(0.8)

        # identity string
        ident = Text('id  =  "Charizard_100_Alakazam_100"',
                     font_size=24, color=ACCENT, font="monospace")
        ident.next_to(caption, DOWN, buff=0.45)
        note = Text("a unique id  ->  one node in the graph",
                    font_size=22, color=GREY_B)
        note.next_to(ident, DOWN, buff=0.3)
        self.play(Write(ident))
        self.play(FadeIn(note))
        self.wait(1.5)
        self.clear_all()

    # ------------------------------------------------------------------
    def the_turn_and_edges(self):
        title = self.section_title("2.  A turn = an EDGE")
        self.play(FadeIn(title))

        root = state_node("Charizard", 100, "Alakazam", 100, border=WHITE)
        root.to_edge(LEFT, buff=0.9)
        self.play(Create(root.box), Write(root[1]))

        explain = Text("Both pick 1 of their 4 moves  ->  4 x 4 = 16 combos",
                       font_size=24, color=GREY_B)
        explain.to_edge(DOWN, buff=0.6)
        self.play(FadeIn(explain))

        # three representative resulting states
        results = [
            ("Charizard", 20, "Alakazam", 0, WIN_COLOR, "Flamethrower | Shadow Ball"),
            ("Charizard", 0, "Alakazam", 100, LOSS_COLOR, "Flamethrower | Psychic"),
            ("Charizard", 70, "Alakazam", 100, WHITE, "Recover | Shadow Ball"),
        ]
        targets = VGroup()
        edges = VGroup()
        labels = VGroup()
        ys = [2.2, 0.0, -1.7]
        for (p1, h1, p2, h2, col, mv), y in zip(results, ys):
            n = state_node(p1, h1, p2, h2, border=col, width=2.7, height=1.2)
            n.move_to(np.array([3.2, y, 0]))
            arrow = Arrow(root.box.get_right(), n.box.get_left(),
                          color=EDGE_COLOR, stroke_width=4, buff=0.15,
                          max_tip_length_to_length_ratio=0.12)
            lbl = Text(mv, font_size=16, color=GREY_B)
            lbl.add_background_rectangle(color=BG, opacity=0.85, buff=0.06)
            direction = n.box.get_left() - root.box.get_right()
            angle = np.arctan2(direction[1], direction[0])
            normal = np.array([-direction[1], direction[0], 0])
            normal = normal / np.linalg.norm(normal)
            if normal[1] < 0:
                normal *= -1
            lbl.rotate(angle)
            lbl.move_to(arrow.get_center() + normal * 0.22)
            targets.add(n)
            edges.add(arrow)
            labels.add(lbl)

        for n, e, l in zip(targets, edges, labels):
            self.play(GrowArrow(e), FadeIn(l, scale=0.8),
                      Create(n.box), Write(n[1]), run_time=0.7)
        self.wait(0.6)

        # damage rule callout
        self.play(FadeOut(explain))
        rule = VGroup(
            Text("Step(): faster Pokemon (higher Speed) attacks first",
                 font_size=19, color=GREY_B),
            Text("damage from stats, type-effectiveness & STAB; Recover heals +50",
                 font_size=19, color=GREY_B),
        ).arrange(DOWN, buff=0.14).to_edge(DOWN, buff=0.2)
        self.play(FadeIn(rule))
        self.wait(1.6)
        self.clear_all()

    # ------------------------------------------------------------------
    def building_the_graph(self):
        title = self.section_title("3.  Build by recursion until someone faints")
        self.play(FadeIn(title))

        # root
        root = state_node("CHA", 100, "ALA", 100, border=WHITE, width=2.1, height=1.0)
        root.move_to(UP * 2.3)
        self.play(Create(root.box), Write(root[1]))

        # level 1
        win1 = state_node("CHA", 20, "ALA", 0, border=WIN_COLOR, width=2.1, height=1.0)
        loss1 = state_node("CHA", 0, "ALA", 100, border=LOSS_COLOR, width=2.1, height=1.0)
        cont = state_node("CHA", 70, "ALA", 100, border=WHITE, width=2.1, height=1.0)
        win1.move_to(np.array([-4.2, 0.4, 0]))
        loss1.move_to(np.array([0, 0.4, 0]))
        cont.move_to(np.array([4.2, 0.4, 0]))

        def connect(a, b, col=EDGE_COLOR):
            return Arrow(a.box.get_bottom(), b.box.get_top(), color=col,
                         stroke_width=3.5, buff=0.12,
                         max_tip_length_to_length_ratio=0.15)

        e1, e2, e3 = connect(root, win1), connect(root, loss1), connect(root, cont)
        self.play(GrowArrow(e1), Create(win1.box), Write(win1[1]))
        self.play(GrowArrow(e2), Create(loss1.box), Write(loss1[1]))
        self.play(GrowArrow(e3), Create(cont.box), Write(cont[1]))

        # terminal tags
        wtag = Text("WIN", font_size=20, color=WIN_COLOR, weight=BOLD).next_to(win1, DOWN, buff=0.15)
        ltag = Text("LOSS", font_size=20, color=LOSS_COLOR, weight=BOLD).next_to(loss1, DOWN, buff=0.15)
        self.play(FadeIn(wtag), FadeIn(ltag))
        msg = Text("hp <= 0  ->  terminal node (battle over)", font_size=22, color=GREY_B)
        msg.to_edge(DOWN, buff=0.55)
        self.play(FadeIn(msg))
        self.wait(0.8)

        # level 2 from the non-terminal node
        self.play(Indicate(cont.box, color=ACCENT))
        win2 = state_node("CHA", 70, "ALA", 0, border=WIN_COLOR, width=2.1, height=0.95)
        loss2 = state_node("CHA", 0, "ALA", 100, border=LOSS_COLOR, width=2.1, height=0.95)
        win2.move_to(np.array([2.9, -2.3, 0]))
        loss2.move_to(np.array([5.5, -2.3, 0]))
        e4, e5 = connect(cont, win2), connect(cont, loss2)
        self.play(GrowArrow(e4), Create(win2.box), Write(win2[1]),
                  GrowArrow(e5), Create(loss2.box), Write(loss2[1]))

        # dedup highlight: loss2 is the same id as loss1
        self.play(FadeOut(msg))
        dedup = Text('"visited" set: a repeated state is reused, never re-expanded',
                     font_size=22, color=ACCENT)
        dedup.to_edge(DOWN, buff=0.55)
        self.play(FadeIn(dedup))
        dash = DashedLine(loss2.box.get_left(), loss1.box.get_right(),
                          color=ACCENT, stroke_width=3)
        self.play(Create(dash), Indicate(loss1.box, color=ACCENT),
                  Indicate(loss2.box, color=ACCENT))
        self.wait(1.6)
        self.clear_all()

    # ------------------------------------------------------------------
    def tournament(self):
        title = self.section_title("4.  Run every matchup: who wins more?")
        self.play(FadeIn(title))

        team1 = ["Charizard", "Feraligatr", "Scizor", "Decidueye", "Garchomp", "Reuniclus"]
        team2 = ["Blastoise", "Blaziken", "Chesnaught", "Tyranitar", "Gengar", "Alakazam"]

        col1 = VGroup(*[Text(n, font_size=20, color=P1_COLOR) for n in team1]).arrange(DOWN, buff=0.22)
        col2 = VGroup(*[Text(n, font_size=20, color=P2_COLOR) for n in team2]).arrange(DOWN, buff=0.22)
        col1.to_edge(LEFT, buff=1.0).shift(DOWN * 0.3)
        col2.to_edge(RIGHT, buff=1.0).shift(DOWN * 0.3)
        h1 = Text("Team 1", font_size=24, color=P1_COLOR, weight=BOLD).next_to(col1, UP, buff=0.3)
        h2 = Text("Team 2", font_size=24, color=P2_COLOR, weight=BOLD).next_to(col2, UP, buff=0.3)
        self.play(FadeIn(col1, shift=RIGHT * 0.2), FadeIn(col2, shift=LEFT * 0.2),
                  FadeIn(h1), FadeIn(h2))

        # flurry of matchup lines
        lines = VGroup()
        for a in col1:
            for b in col2:
                lines.add(Line(a.get_right(), b.get_left(),
                               stroke_color=EDGE_COLOR, stroke_width=1, stroke_opacity=0.5))
        self.play(LaggedStartMap(Create, lines, lag_ratio=0.02, run_time=2.2))

        count = Text("6 x 6 = 36 battles, each its own graph",
                     font_size=24, color=GREY_B).to_edge(DOWN, buff=1.4)
        self.play(FadeIn(count))
        self.wait(0.6)

        verdict = VGroup(
            Text("Count terminal WIN vs LOSS nodes in every graph", font_size=22, color=GREY_B),
            Text("=>  the team with more match wins is favored", font_size=24, color=WIN_COLOR, weight=BOLD),
        ).arrange(DOWN, buff=0.2).to_edge(DOWN, buff=0.5)
        self.play(FadeOut(count), FadeIn(verdict))
        self.wait(1.8)
        self.clear_all()

    # ------------------------------------------------------------------
    def outro(self):
        title = Text("PokeGraph", font_size=60, weight=BOLD, color=WHITE)
        pts = VGroup(
            Text("state  ->  node", font_size=30, color=WHITE),
            Text("turn (move pair)  ->  edge", font_size=30, color=WHITE),
            Text("recurse until a Pokemon faints", font_size=30, color=WHITE),
            Text("export every graph to GraphViz .dot", font_size=30, color=ACCENT),
        ).arrange(DOWN, buff=0.3)
        pts.next_to(title, DOWN, buff=0.6)
        self.play(Write(title))
        self.play(LaggedStartMap(FadeIn, pts, shift=UP * 0.2, lag_ratio=0.3))
        self.wait(2.0)
        self.play(FadeOut(pts), FadeOut(title))
