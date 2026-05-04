# L-system

> **A tiny C program that turns a context-free grammar into a fractal SVG. Give it an axiom and a few rewrite rules, get back a snowflake or a fern. Built in a weekend because I wanted an excuse to write turtle graphics from scratch.**

L-systems are the trick that makes procedural plants in video games look organic. The premise is from theoretical CS: you start with a string (the *axiom*), apply rewrite rules in parallel a few times, and the resulting string drives a "turtle" that walks around drawing line segments. Done right, you get fractals; done wrong, you get a spirograph that ate too much.

Sample output (`examples/`):

| Fern | Dragon curve | Hilbert curve | Snowflake |
|---|---|---|---|
| `examples/tree.svg` | `examples/dragon.svg` | `examples/hilbert.svg` | `examples/snowflake.svg` |

## How it works

```
                       ┌────────────────────┐
   axiom + rules  ──▶  │  gen.c             │  ──▶  expanded string
                       │  (string rewriter) │       e.g. "F+F-F+F+F-F-F-F+F"
                       └────────────────────┘
                                                          │
                                                          ▼
                       ┌────────────────────┐
   expanded string ──▶ │  turtle.c          │  ──▶  list of (x,y) line segments
                       │  (cursor + stack)  │
                       └────────────────────┘
                                                          │
                                                          ▼
                       ┌────────────────────┐
                       │  render.c          │  ──▶  SVG to stdout
                       └────────────────────┘
```

Three pieces:
- **`gen.c`** — the grammar rewriter. Postulates are stored in a 256-entry ASCII lookup table, so substitution is O(1) per character.
- **`turtle.c`** — the turtle: position, heading, color, plus a stack so `[` and `]` save/restore state (this is what lets you draw a tree with branches).
- **`render.c`** — emits SVG `<path>` elements, normalized to fit a viewbox.

The turtle alphabet I went with:
- `F`, `G` — step forward, drawing
- `+` — turn right by `<angle>` degrees
- `-` — turn left
- `[` — push state
- `]` — pop state
- anything else — no-op (so non-drawing variables like `X` just expand silently)

## Build

```bash
gcc turtle.c render.c buffer_struct.c gen.c -lm -o lsystem
# Or with clang
clang turtle.c render.c buffer_struct.c gen.c -lm -o lsystem
```

Tested with `gcc 15.2.1` and `clang 21.1.6`; should compile cleanly with anything C99-or-later.

## Usage

```
./lsystem <iterations> <angle> <axiom> [<lhs> <rhs>]...
```

The output goes to stdout — pipe it to a `.svg` file and open in a browser.

### Examples

```bash
# Fern leaf
./lsystem 6 25.0 "-X" X "F+[[X]-X]-F[-FX]+X" F "FF" > plant.svg

# Koch snowflake
./lsystem 4 60.0 "F++F++F" F "F-F++F-F" > snowflake.svg

# Sierpinski arrowhead
./lsystem 6 60.0 F F "G-F-G" G "F+G+F" > sierpinski.svg

# Dragon curve
./lsystem 10 90.0 FX X "X+YF+" Y "-FX-Y" > dragon.svg
```

## A warning about iterations

The output string roughly doubles per iteration for non-trivial grammars. `iterations=10` on the dragon curve is fine; `iterations=15` is ~32× larger and takes a noticeable second; `iterations=20` will blow your RAM. There's no streaming — the full expanded string lives in memory before rendering. That was a deliberate simplification; a streaming rewriter would be a fun follow-up.

## Why C and not, like, Python in 30 lines

Honestly? Python *would* be 30 lines. The point wasn't the L-system — the point was practicing manual memory management on something fun enough to actually finish. The dynamic buffer in `buffer_struct.c` (read buffer + write buffer + swap), the turtle stack, the rule lookup table — those are the bits I'd struggle to write under interview pressure, so I wanted to write them under no pressure first.
