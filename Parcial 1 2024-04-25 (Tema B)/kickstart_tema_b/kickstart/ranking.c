/*
  @file ranking.c
  @brief Implements store structure and methods
*/
#include <stdlib.h>
#include "ranking.h"
#include <string.h>

static const int NUMBER_OF_RANKING_VARS = 6;

Ranking ranking_from_file(FILE *file) {

    Ranking ranking;
    int a,b,c;
    char d[20], e[20];
    float f;

    int res = fscanf(file, EXPECTED_RANKING_FILE_FORMAT, &a, &b, &c, d, e, &f);
    /* COMPLETAR: se leyo correctamente? */
    if (res != NUMBER_OF_RANKING_VARS) {
        fprintf(stderr, "Invalid ranking file format.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(ranking.name,d);
    strcpy(ranking.team,e);

    /* COMPLETAR: campos de ranking */
    ranking.pos = a;
    ranking.pos_prev = b;
    ranking.diff = c;
    ranking.points = f;

    return ranking;
}

 float total_track_points_per_team(RankingTable a, char *team_name) {
    float sum = 0;
    // Primero debo recorrer la tabla, para ello uso dos for anidados
    for (int pos = 0; pos < NO_PLAYERS; pos++){
        for (int type = road; type <= track; type++){
            // Ahora debo chequear si el nombre del equipo es igual al que me pasaron por parametro
            if (strcmp(a[pos][type].team, team_name) == 0){
                // Si es igual, entonces debo sumar los puntos
                sum += a[pos][type].points;
            }
        }
    }
    return sum;
} 
