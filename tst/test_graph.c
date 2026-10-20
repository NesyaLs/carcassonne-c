#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_graph.h"

// Fonction de test pour add_tile_to_world_graph
int test_add_tile_to_world_graph() {
    struct world_t world;
    struct move_t move;
    igraph_t graph;
    world.graph_board = &graph;
    world.num_placed_tiles = 0;

    create_empty_graph(&graph);

    // Initialise le monde et le mouvement
    move.tile.t[0] = 1;
    move.x = 0;
    move.y = 0;
    for (int i = 0; i < MAX_TILES; i++) {
        world.tiles[i] = PLACED_TILE_EMPTY;
    }

    add_tile_to_world_graph(&world, &move);

    int vertices = igraph_vcount(world.graph_board);
    int edges = igraph_ecount(world.graph_board);

    igraph_destroy(&graph);

    return (vertices > 0 && edges > 0);
}

int test_get_connected_vertices() {
    igraph_t graph;
    create_empty_graph(&graph);

    igraph_add_vertices(&graph, 5, 0);
    igraph_add_edge(&graph, 0, 1);
    igraph_add_edge(&graph, 1, 2);
    igraph_add_edge(&graph, 2, 3);
    igraph_add_edge(&graph, 3, 4);

    int num_vertices;
    int *connected_vertices = get_connected_vertices(&graph, 2, &num_vertices);

    int result = 1;
    printf(" %d " , num_vertices);
    if(num_vertices != 5) {
        result = 0;
    }
    free(connected_vertices);
    igraph_destroy(&graph);
    return result;
}

int test_add_tile_graph() {
    igraph_t graph; 
    create_empty_graph(&graph);
    struct tile_t tile = CARC_TILE_GREEN;
    add_tile_graph(&graph, &tile, 0, 12);
    int result = 1;
    if(igraph_vcount(&graph) != 13 || igraph_ecount(&graph) != 12) {
        result = 0;
    }

    igraph_destroy(&graph);
    return result;
}

