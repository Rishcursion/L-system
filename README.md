# Fractal Maker
A hobby C project for generating recursive structures using formal language and L-systems, produces an SVG output that can be viewed in the browser.

## Theory
In L-systems, we begin with a generator or a simple initial structure, and recursively update each part of the generator with an initiator, resulting in an infinitelygrowing pattern as defined by the grammar. 
The L-system grammar consists of the following:
 - Variables 
 - Axiom
 - Postulates

The variables are part of the symbols present in the grammar associated with a specific action for e.g.
- F, G -> draw a line
- \+ -> turn right
- \- -> turn left
- [ -> push current state to stack
- ] -> restore previous state from stack.

By formalizing a grammar, we can draw infinitely repeating patterns just from a small initial seed, for e.g.

```
Variables: a,b
axiom: a
postulates:
    i) a -> ab 
    ii) b -> ba 
Aim: Derive the string abba from the axiom
i)      a
        |
ii)     ab
        / \
iii)   ab ba

we can continue if we want to generate more complex patterns, but this results in exponential growth of memory required so be careful :D
       / \   / \
iv)   ab ba ab ba
     / \/ \/ \ / \
   ab ba ba ab ab ba ba ab (roughly doubles every generation for this specific pattern)
```

## Requirements
```
gcc (GCC) 15.2.1 20251112
(or)
clang version 21.1.6
```

## Setup
```
# Clone the repository via https

git clone https://github.com:Rishcursion/L-system.git 
```

## Usage
```
# Compile and link all C files using your preferred compiler
gcc turtle.c render.c buffer_struct.c gen.c -lm -o <program name>
# Run the program with desired L-system Context Free Grammar
./<program name> <number of iterations> <turn angle> <axiom/seed> [<postulate LHS> <postulate RHS>]*repeat
```

