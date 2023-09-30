#include <stdio.h>
#include "funciones_answers.h"
#include "hashmap.h"
#include "list.h"

int main() {
    HashMap* mapaTuristas = createMap(50);  // Mapa para almacenar datos de turistas
    HashMap* mapaPuntosTuristicos = createMap(50);  // Mapa para almacenar datos de puntos turísticos
    HashMap* mapaTuristasPorPais = createMap(50);  // Mapa para almacenar turistas por país
    HashMap* mapaPuntosPorTipo = createMap(50);  // Mapa para almacenar puntos de interés por tipo
    
    mostrarMenu(mapaTuristas, mapaPuntosTuristicos, mapaTuristasPorPais, mapaPuntosPorTipo);
    liberarMemoria(mapaTuristas,mapaPuntosTuristicos,mapaTuristasPorPais,mapaPuntosPorTipo);
    return 0;
}
