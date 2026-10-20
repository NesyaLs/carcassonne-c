#include <stdio.h>
#include <stdlib.h>
#include "test_player_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include "test_player_utils.h"

// Fonction pour tester get_score_from_move
int test_get_score_from_move() {
    struct move_t move = {
        .player_id = 0,  // Remplacez PLAYER_COLOR_1 par la couleur appropriée
        .x = 5,
        .y = 3,
        .tile = { .c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} }, // Initialisez correctement la tile
        .meeple = NO_CONNECTION       // Remplacez NO_CONNECTION par la valeur appropriée
    };
    struct world_t world; // Initialisez votre structure world ici
    // Initialisez le monde ici si nécessaire

    int expected_score = 8; // Score attendu basé sur l'implémentation fictive
    int score = get_score_from_move(move, &world);

    return score == expected_score ? 1 : 0;
}

// Fonction pour tester get_best_move
int test_get_best_move() {
    struct move_t move_playable[3] = {
        {
            .player_id = 0, // Remplacez PLAYER_COLOR_1 par la couleur appropriée
            .x = 0,
            .y = 0,
            .tile = { .c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} },
            .meeple = NO_CONNECTION // Remplacez NO_CONNECTION par la valeur appropriée
        },
        {
            .player_id = 0, // Remplacez PLAYER_COLOR_1 par la couleur appropriée
            .x = 1,
            .y = 1,
            .tile = { .c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} },
            .meeple = NO_CONNECTION // Remplacez NO_CONNECTION par la valeur appropriée
        },
        {
            .player_id = 0, // Remplacez PLAYER_COLOR_1 par la couleur appropriée
            .x = 2,
            .y = 2,
            .tile = { .c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} },
            .meeple = NO_CONNECTION // Remplacez NO_CONNECTION par la valeur appropriée
        }
    };

    struct world_t world; // Initialisez votre structure world ici
    // Initialisez le monde ici si nécessaire

    struct tile_t tile = CARC_TILE_GREEN; // Initialisez correctement votre tile
    unsigned int id_player = 1; // Définissez id_player à une valeur appropriée
    int nb_available_move = 3; // Nombre de mouvements disponibles

    struct move_t best_move = get_best_move(move_playable, &world, nb_available_move, tile, id_player);

    // Le meilleur mouvement devrait être celui avec les coordonnées (2, 2)
    if (best_move.x == 2 && best_move.y == 2) {
        return 1;
    }
    return 0;
}
