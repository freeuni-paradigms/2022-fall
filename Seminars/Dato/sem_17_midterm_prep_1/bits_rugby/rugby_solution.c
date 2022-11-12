#include "rugby.h"

#include <string.h>
#include <stdio.h>

// <team_name(str)><space(1bit)><score(1bit)><score(1bit)><space(1bit)><team_name(str)><;<1bit>

// “a 02 b;b 10 c”

typedef struct {
    char* first_name;
    char* second_name;
    unsigned char first_score;
    unsigned char second_score;
    int length;
} GameInfo;

GameInfo parseGame(char* ptr) {
    GameInfo info;
    info.info_length = 0;
    info.first_team = ptr;
    int name_length = strlen(info.first_team) + 1;
    ptr += name_length; //skip first team name
    info.info_length += name_length;
    ptr++; //skip space
    info.first_score = *(unsigned char*)ptr;
    ptr++; //skip first score
    info.second_score = *(unsigned char*)ptr;
    ptr++; //skip second score
    ptr++; //skip space;
    info.info_length += 4;
    info.second_team = ptr;
    name_length = strlen(info.second_team) + 1;
    ptr += name_length; //skip second team name
    info.info_length += name_length;
    //print info
    // printf("first team: %s, first score: %d, second team: %s, second score: %d, info length: %d\n", info.first_team, info.first_score, info.second_team, info.second_score, info.info_length);
    return info;
}


int TotalGamesPlayed(void* results, char* team_name) {
    int gamesPlayed = 0;
    char* ptr = (char*)results;
    while (1) {
        GameInfo info = parseGame(ptr);
        if (strcmp(info.first_name, team_name) == 0 || strcmp(info.second_name, team_name) == 0) {
            gamesPlayed++;
        }
        ptr += info.length;
        if (*ptr == '\0') {
            break;
        }
        ptr++;
    }
    return gamesPlayed;
}

int TotalPointsScored(void* results, char* team_name) {
    int pointsScored = 0;
    char* ptr = (char*)results;
    while (1) {
        GameInfo info = parseGame(ptr);
        if (strcmp(info.first_name, team_name) == 0) {
            pointsScored += info.first_score;
        }
        else if (strcmp(info.second_name, team_name) == 0) {
            pointsScored += info.second_score;
        }
        ptr += info.length;
        if (*ptr == '\0') {
            break;
        }
        ptr++;
    }
    return pointsScored;
}

int NumWins(void* results, char* team_name) {
    int winCount = 0;
    char* ptr = (char*)results;
    while (1) {
        GameInfo info = parseGame(ptr);
        if (strcmp(info.first_name, team_name) == 0 && info.first_score > info.second_score) {
            winCount++;
        }
        else if (strcmp(info.second_name, team_name) == 0 && info.first_score < info.second_score) {
            winCount++;
        }
        ptr += info.length;
        if (*ptr == '\0') {
            break;
        }
        ptr++;
    }
    return winCount;
}
