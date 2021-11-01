//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct date {
    int day;
    int month;
    int year;
} Date;

typedef struct movie {
    char *name;
    int rank;
    Date releaseDate;
} Movie;

void getMoviesInput(Movie ***pMovies, int *pSize);

Movie *getHighest(Movie **arr, int size);

Movie *getMovie();

char *getMovieName();

void sortMovies(Movie **arr, int size);

void printMovies(Movie **arr, int size);

void freeAll(Movie **arr, int size);

void checkMemoryAllocation(void *ptr);

void main() {
    Movie **movies, *max;
    int size;
    getMoviesInput(&movies, &size);
    max = getHighest(movies, size);
    printf("The best movie is: %s\n", max->name);
    max = getHighest(NULL, size);
    printf("The second best movie is: %s\n", max->name);
    max = getHighest(NULL, size);
    printf("The third best movie is: %s\n", max->name);
//    sortMovies(movies, size);
    printMovies(movies, size);
    freeAll(movies, size);
}

void printMovies(Movie **arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("Movie number %d\n", i + 1);
        printf("Name: %s\nRank %d\nRelease date: %d/%d/%d", arr[i]->name, arr[i]->rank, (arr[i]->releaseDate).day,
               (arr[i]->releaseDate).month, (arr[i]->releaseDate).year);
    }
}

void freeAll(Movie **arr, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        free(arr[i]->name);
        free(arr[i]);
    }
    free(arr);
}

Movie *getHighest(Movie **arr, int size) {

    static Movie **arrSaver = NULL;
    static Movie *lastMax = NULL;
    Movie *max = NULL;
    int i;
    if (arr != NULL) {
        arrSaver = arr;
        max = arr[0];
        for (i = 0; i < size; i++) {
            if (arr[i]->rank > max->rank) {
                max = arr[i];
            }
        }
    } else {
        bool found = false;
        arr = arrSaver;
        for (i = 0; i < size && !found; i++) {
            if (arr[i]->rank < lastMax->rank) {
                max = arr[i];
                found = true;
            }
        }
        for (i = 0; i < size; i++) {
            if ((arr[i]->rank > max->rank) && (arr[i]->rank < lastMax->rank)) {
                max = arr[i];
            }
        }


    }
    lastMax = max;

}

void getMoviesInput(Movie ***pMovies, int *pSize) {
    Movie **movies;
    int size, i;
    printf("please enter number of movies :");
    scanf("%d", &size);
    movies = (Movie **) malloc(sizeof(Movie *) * size);
    checkMemoryAllocation(movies);

    for (i = 0; i < size; i++) {
        printf("Movie number %d:", i + 1);
        movies[i] = getMovie();
    }

    *pMovies = movies;
    *pSize = size;
}

Movie *getMovie() {
    Movie *movie = (Movie *) malloc(sizeof(Movie));
    checkMemoryAllocation(movie);
    getchar();
    printf("Enter movie name: ");
    movie->name = getMovieName();
    printf("Enter movie rank");
    scanf("%d", &(movie->rank));
    printf("Enter movie release date (date/month/year):");
    scanf("%d %d %d", &(movie->releaseDate.day), &(movie->releaseDate.month), &(movie->releaseDate.year));

}

char *getMovieName() {
    char *str;
    int logSize = 0, phySize = 1;
    char c;
    str = (char *) malloc(sizeof(char) * phySize);
    checkMemoryAllocation(str);

    c = getchar();
    while (c != '\n') {
        if (logSize == phySize) {
            phySize *= 2;
            str = (char *) realloc(str, sizeof(char) * phySize);
            checkMemoryAllocation(str);
        }
        str[logSize] = c;
        logSize++;
        c = getchar();
    }
    if (logSize < phySize) {
        str = (char *) realloc(str, sizeof(char) * (logSize + 1));
        checkMemoryAllocation(str);
    }
    str[logSize] = '\0';
    return str;
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Memory Allocation Failed...\n");
        exit(1);
    }
}