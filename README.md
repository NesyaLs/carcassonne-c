# Carcassonne

A C implementation of a simplified two-player Carcassonne: a game server loads two AI players as shared libraries, deals tiles and checks and scores every move.

First-year school project (semester 6, 2023-2024) at ENSEIRB-MATMECA (Bordeaux INP), built by a team of four (see [Authors](#authors)).

## Features

- **Game server** (`server`): builds a random 35-tile deck, plays the starting tile, then alternates between the two players, rejecting invalid moves and keeping each player's score until the deck runs out or a tile cannot be placed.
- **Players as plugins**: each player is a shared library (`libplayer1.so`, `libplayer2.so`) loaded at runtime with `dlopen`, implementing the common `player.h` interface (`get_player_name`, `initialize`, `play`, `finalize`).
- **Board as a graph**: each tile is a 13-vertex graph (edges and center); placed tiles are merged into one world graph with [igraph](https://igraph.org/), and connected components are used to check edge compatibility and to compute the score of roads and cities.
- **Greedy AI**: the players try every free position and all four rotations of the drawn tile, then keep the move with the best immediate score.
- **Unit tests** for the board, graph, display and player modules, with gcov coverage.

Limitations: meeples are not implemented. The server accepts a game mode (`-m`), but every game is played without meeples. The server prints its output in French.

## Tech stack

C (gnu99), GNU Make, [igraph](https://igraph.org/) 0.10, `dlopen`/shared libraries, gcov.

## Getting started

### Prerequisites

- `gcc` and `make`
- igraph 0.10 (tested with 0.10.10). If it is not packaged for your system, build it from source:

```sh
curl -LO https://github.com/igraph/igraph/releases/download/0.10.10/igraph-0.10.10.tar.gz
tar xzf igraph-0.10.10.tar.gz && cd igraph-0.10.10
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$HOME/.local/opt/igraph -DBUILD_SHARED_LIBS=ON
cmake --build build -j4 && cmake --install build
```

### Build

```sh
make install IGRAPH_PATH=$HOME/.local/opt/igraph   # default IGRAPH_PATH is /usr/local
```

This builds `server`, `libplayer1.so`, `libplayer2.so` and the `alltests` test binary and copies them to `install/`.

### Run a game

```sh
./install/server [-m MODE] ./install/libplayer1.so ./install/libplayer2.so
```

`MODE` is `0` (no meeples), `1` (infinite meeples) or `2` (finite meeples). Example output (trimmed):

```
seed: 1792537270
Nom du joueur 1: Bilal
Nom du joueur 2: Darkiki
Tour 1
Coups valide!
...
Tour 34
Coups valide!
Le gagnant est le joueur Darkiki
 Score Darkiki: 280
 Score Bilal: 176
```

### Run the tests

```sh
make test IGRAPH_PATH=$HOME/.local/opt/igraph
```

## Project structure

```
src/       server, board, graph, display, player modules and the two players
tst/       unit tests
```

The game interface headers (`deck.h`, `move.h`, `player.h`) and `deck.c` were provided by the course.

## Authors

Arthur Dufetrelle, together with three fellow ENSEIRB-MATMECA students.
