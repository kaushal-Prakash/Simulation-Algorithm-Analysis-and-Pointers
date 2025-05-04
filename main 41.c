/*
 * File:   main.c
 * Author: Gunanidhi M S
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 100

typedef struct Vector {
    float x;
    float y;
    float z;
} Vector;

typedef struct MoveInfo {
    Vector velocity;
    float duration;
} MoveInfo;

int countInputFileLines(char inputFileName[]) {
    FILE* file = fopen(inputFileName, "r");
    if (!file) return 0;
    int count = 0;
    char line[MAX_LENGTH];
    while (fgets(line, MAX_LENGTH, file)) {
        count++;
    }
    fclose(file);
    return count;
}

void getPointFromString(char string[], Vector* point) {
    char* token = strtok(string, ",");
    point->x = atof(token);
    token = strtok(NULL, ",");
    point->y = atof(token);
    token = strtok(NULL, ",");
    point->z = atof(token);
}

void getMoveInfoBetweenPoints(MoveInfo* moveInfo, Vector p1, Vector p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;

    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    moveInfo->duration = distance;

    if (distance == 0.0f) {
        moveInfo->velocity.x = 0;
        moveInfo->velocity.y = 0;
        moveInfo->velocity.z = 0;
    } else {
        moveInfo->velocity.x = dx / distance;
        moveInfo->velocity.y = dy / distance;
        moveInfo->velocity.z = dz / distance;
    }
}

int main(int argc, char** argv) {
    char rawFileName[MAX_LENGTH];
    fgets(rawFileName, MAX_LENGTH, stdin);
    while (rawFileName[0] != 'q') {
        int stringEndIndex = -1;
        char* result = NULL;
        char* stringStart = &rawFileName[0];

        result = strchr(rawFileName, '\r');
        if (result == NULL) result = strchr(rawFileName, '\n');

        stringEndIndex = result - stringStart;
        char* inputFileName = malloc((stringEndIndex + 1) * sizeof(char));
        strncpy(inputFileName, rawFileName, stringEndIndex);
        inputFileName[stringEndIndex] = '\0';

        // === Start of Student Code ===

        int numPoints = countInputFileLines(inputFileName);
        Vector* points = malloc(numPoints * sizeof(Vector));

        FILE* file = fopen(inputFileName, "r");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file.\n");
            free(points);
            free(inputFileName);
            fgets(rawFileName, MAX_LENGTH, stdin);
            continue;
        }

        char line[MAX_LENGTH];
        int index = 0;
        while (fgets(line, MAX_LENGTH, file)) {
            getPointFromString(line, &points[index++]);
        }
        fclose(file);

        int numMoves = numPoints - 1;
        MoveInfo* moves = malloc(numMoves * sizeof(MoveInfo));
        float totalDuration = 0.0f;

        for (int i = 0; i < numMoves; i++) {
            getMoveInfoBetweenPoints(&moves[i], points[i], points[i + 1]);
            totalDuration += moves[i].duration;
        }

        for (int i = 0; i < numMoves; i++) {
            printf("%.2f,%.2f,%.2f,%.2f", 
                   moves[i].velocity.x, 
                   moves[i].velocity.y, 
                   moves[i].velocity.z, 
                   moves[i].duration);
            if (i < numMoves - 1)
                printf(" ");
        }
        printf(" %.2f\n", totalDuration);

        free(points);
        free(moves);

        // === End of Student Code ===

        free(inputFileName);
        inputFileName = NULL;
        fgets(rawFileName, MAX_LENGTH, stdin);
    }

    return 0;
}
