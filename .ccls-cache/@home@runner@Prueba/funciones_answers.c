#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "funciones_answers.h"
#include "hashmap.h"

typedef struct {
    char nombre[50];
    char tipo[50];
    char direccion[100];
    char horario[50];
    char descripcion[200];
} PuntoTuristico;

typedef struct {
    char pasaporte[20];
    char nombre[50];
    char pais[50];
    struct Favorito* lugaresFavoritos;
    int numLugaresFavoritos; 
} Turista;

