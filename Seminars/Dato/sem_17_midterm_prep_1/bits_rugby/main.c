#include "rugby.h"
#include <stdio.h>


void test_rugby_1() {
    // create rugby game
    char* game = "a\0 02 b\0;b\0 10 c\0;c\0 01 a\0";
    // test TotalGamesPlayed
    int total_games_played = TotalGamesPlayed(game, "a");
    printf("Total games played: %d\n", total_games_played);
    // test TotalPointsScored
    int total_points_scored = TotalPointsScored(game, "a");
    printf("Total points scored: %d\n", total_points_scored);
    // test NumWins
    int num_wins = NumWins(game, "a");
    printf("Number of wins: %d\n", num_wins);
}


// create main func
int main(int argc, char *argv[]) {
    test_rugby_1(); 
}