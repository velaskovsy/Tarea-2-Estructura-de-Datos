#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "funciones_answers.h"
#include "hashmap.h"
#include "list.h"

//=============================== ESTRUCTURAS ======================================
struct Turista{
    char pasaporte[101];  
    char nombre[101];
    char pais[101];
    List* lugaresFavoritos;
};

struct PuntoTuristico{
    char nombre[101];
    char tipo[101];
    char direccion[101];
    char horario[101];
    char descripcion[101];
};

//============================== MAPAS ==============================================

// MAPA DE TURISTAS POR PAÍS 
typedef struct {
    char clavePais[101];
    List* turistas;  
} MapaTuristasPais;

// MAPA DE PUNTOS DE INTERÉS POR TIPO (museo, parque, monumento, etc)
typedef struct {
    char claveTipo[101]; // Clave: Nombre del tipo de punto de interés
    List* tipoPuntos; // Valor: Lista de puntos turisticos
} MapaTipoDePuntos;

//====================================================================================

//FUNCION LIBERAR MEMORIA: LIBERA LA MEMORIA DE LOS MAPAS USADOS
void liberarMemoria(HashMap *mapaTuristas,HashMap *mapaPuntosTuristicos,HashMap *mapaTuristasPorPais,HashMap *mapaPuntosPorTipo){
    free(mapaTuristas);
    free(mapaTuristasPorPais);
    free(mapaPuntosTuristicos);
}

void mostrarOpciones(){           

    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                            MENÚ                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n");
    printf("╔═════════════════════════════════════════════════════════════╗\n");
    printf("║ 1. Registrar punto de interés                               ║\n");
    printf("║ 2. Mostrar datos de punto de interés                        ║\n");
    printf("║ 3. Eliminar punto de interés                                ║\n");
    printf("║ 4. Registrar turista                                        ║\n");
    printf("║ 5. Agregar lugar favorito a turista                         ║\n");
    printf("║ 6. Mostrar turistas por país                                ║\n");
    printf("║ 7. Mostrar todos los puntos de interés de un tipo           ║\n");
    printf("║ 8. Importar puntos de interés y turistas desde archivos CSV ║\n");
    printf("║ 9. Exportar puntos de interés y turistas a archivos CSV     ║\n");
    printf("║ 0. Salir                                                    ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
    printf("Seleccione una opción: ");
}
//FUNCION MOSTRAR MENU
void mostrarMenu(HashMap* mapaTuristas, HashMap* mapaPuntosTuristicos, HashMap* mapaTuristasPorPais, HashMap* mapaPuntosPorTipo){  
    unsigned short opciones;
    do {
        // USO DE ARRAY PARA ALMACENAR LA OPCION ELEGIDA 
        char opcion[2]; 
        mostrarOpciones();
        scanf("%1s", opcion);
        getchar();
        //VERIFICAMOS SI UN DIGITO 
        if (isdigit(opcion[0])) {
            // CONVERTIRMOS EL CARACTER A NUMERO 
            opciones = atoi(opcion);
            switch (opciones) {
                case 1:
                    // LLAMADO A LA FUNCION REGISTRAR PUNTO DE INTERES 
                    registrarPuntoDeInteres(mapaPuntosTuristicos, mapaPuntosPorTipo);
                    break;
                case 2:
                    // LLAMADO A LA FUNCION MOSTRAR PUNTO DE INTERES 
                    mostrarDatosPuntosInteres(mapaPuntosTuristicos);
                    break;
                case 3:
                    // LLAMADO A LA FUNCION ELIMINAR PUNTO DE INTERES 
                    eliminarPuntoDeInteres(mapaPuntosTuristicos, mapaPuntosPorTipo);
                    break;
                case 4:
                    /// LLAMADO A LA FUNCION REGISTRAR TURISTA 
                    registrarTurista(mapaTuristas);
                    break;
                case 5:
                    // LLAMADO A LA FUNCION AGREGAR LUGAR FAVORITO A TURISTA
                    AgregarLugarFavoritoTurista(mapaTuristas);
                    break;
                case 6:
                    // LLAMADO A LA FUNCION MOSTRAR TURISTAS POR PAIS
                    mostrarTuristasPorPais(mapaTuristasPorPais, mapaTuristas);
                    break;
                case 7:
                    // LLAMADO A LA FUNCION MOSTRAR PUNTOS DE INTERES DE UN TIPO
                    mostrarPuntosDeInteresDeTipo(mapaPuntosPorTipo);
                    break;
                case 8:
                    // LLAMADO A LA FUNCION IMPORTAR DATOS 
                    importarCSV(mapaPuntosTuristicos, mapaPuntosPorTipo, mapaTuristas);
                    break;
                case 9:
                    // LLAMADO A LA FUNCION EXPORTAR DATOS REGISTRADOS
                    exportarCSV(mapaPuntosTuristicos, mapaTuristas);
                    break;
                case 0:
                    //SALIR DE LA APLICACION
                    printf("Saliendo de la aplicación\n");
                    break;
                default:
                    printf("\nOpción no válida. seleccione nuevamente.\n");
            }
        } else {
            printf("\nopción no válida. Ingrese un número.\n");
        }

    } while (opciones != 0);
}


//FUNCIÓN CREARPUNTOTURISTICO: RESERVA MEMORIA PARA LOS DATOS DEL PUNTO TURISTICO
PuntoTuristico * crearPuntoTuristico(char* nombre, char* tipo, char* direccion, char* horario, char* descripcion) {
    
    PuntoTuristico * puntoTuristico = (PuntoTuristico*) malloc(sizeof(PuntoTuristico));
    if(puntoTuristico == NULL) 
    {
        printf("Error al asignar memoria para punto de interés.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(puntoTuristico->nombre,nombre);
    strcpy(puntoTuristico->tipo,tipo);
    strcpy(puntoTuristico->direccion,direccion);
    strcpy(puntoTuristico->horario,horario);
    strcpy(puntoTuristico->descripcion,descripcion);
    
    return puntoTuristico;
}


// OPCIÓN (1) REGISTRAR PUNTOS DE INTERES
void registrarPuntoDeInteres(HashMap* mapaPuntosTuristicos, HashMap* mapaPuntosPorTipo) {
    char nombre[101];
    char tipo[101];
    char direccion[101];
    char horario[101];
    char descripcion[101];

    //SE LEEN LOS DATOS A REGISTRAR
    printf("Ingrese el nombre del punto de interés (máximo 100 caracteres): ");
    scanf("%100[^\n]s",nombre);
    getchar();

    if (searchMap(mapaPuntosTuristicos, nombre) != NULL) {
        printf("El punto de interés con nombre '%s' ya existe.\n", nombre);
        return;
    }

    printf("Ingrese el tipo del punto de interés (máximo 100 caracteres): ");
    scanf("%100[^\n]s",tipo);
    getchar();

    printf("Ingrese la dirección del punto de interés (máximo 100 caracteres): ");
    scanf("%100[^\n]s",direccion);
    getchar();

    printf("Ingrese el horario del punto de interés (máximo 100 caracteres): ");
    scanf("%100[^\n]s",horario);
    getchar();

    printf("Ingrese una breve descripción del punto de interés (máximo 100 caracteres): ");
    scanf("%100[^\n]s",descripcion);
    getchar();

    //LLAMADO A FUNCION crearPuntoTuristico 
    PuntoTuristico* nuevoPunto = crearPuntoTuristico(nombre, tipo, direccion, horario, descripcion);
    //INSERTAR EN EL MAPA EL PUNTO TURISTICO
    insertMap(mapaPuntosTuristicos, nuevoPunto->nombre, nuevoPunto);   

    // VERIFICAR SI EL TIPO YA EXISTE EN EL MAPA DE TIPOS
    Pair* tipoPuntosPair = searchMap(mapaPuntosPorTipo, tipo);
    MapaTipoDePuntos* tipoPuntos;
    
    if (tipoPuntosPair == NULL) {
        // SI NO EXISTE SE CREA UN NODO DEL TIPO Y SE AGREGA EL PUNTO DE INTERES
        tipoPuntos = (MapaTipoDePuntos*)malloc(sizeof(MapaTipoDePuntos));
        if (tipoPuntos == NULL){
            exit(EXIT_FAILURE);
        }
        
        strcpy(tipoPuntos->claveTipo, tipo);
        tipoPuntos->tipoPuntos = createList();
        insertMap(mapaPuntosPorTipo, tipoPuntos->claveTipo, tipoPuntos);
    } else {
        // SI EL TIPO YA EXISTE SE OBTIENE EL NODO
        tipoPuntos = (MapaTipoDePuntos*)tipoPuntosPair->value;
    }

    // SE AGREGA EL NOMBRE DEL PUNTO DE INTERES A LA LISTA DE TIPO QUE LE CORRESPONDE 
    pushBack(tipoPuntos->tipoPuntos, nuevoPunto->nombre);

    printf("Punto de interés '%s' registrado exitosamente.\n", nombre);
}

// OPCIÓN (2) MOSTRAR PUNTOS DE INTERES
void mostrarDatosPuntosInteres(HashMap* mapaPuntosTuristicos) {
    char nombre[101];
    printf("\nIngrese el nombre del punto de interés a mostrar (máximo 100 caracteres): ");
    scanf("%100[^\n]s", nombre); 
    getchar();
    
    Pair* puntoTuristico = searchMap(mapaPuntosTuristicos, nombre);
    if (puntoTuristico == NULL){
        printf("\nNo se encontró un punto de interes con el nombre %s.\n",nombre);
        return;
    } 
    PuntoTuristico* puntoDeInteres = puntoTuristico->value;
    printf("\nDatos del punto de interés '%s':\n", puntoDeInteres->nombre);
    printf("Tipo: %s\n", puntoDeInteres->tipo);
    printf("Dirección: %s\n", puntoDeInteres->direccion);
    printf("Horario: %s\n", puntoDeInteres->horario);
    printf("Descripción: %s\n", puntoDeInteres->descripcion);
}

// OPCIÓN (3) ELIMINAR PUNTO DE INTERES
void eliminarPuntoDeInteres(HashMap* mapaPuntosTuristicos, HashMap* mapaPuntosPorTipo) {
    char nombre[101];

    printf("\nIngrese el nombre del punto de interés a eliminar (máximo 100 caracteres): ");
    scanf("%100[^\n]s", nombre);
    getchar();

    Pair* puntoTuristico = searchMap(mapaPuntosTuristicos, nombre);

    if (puntoTuristico != NULL) {
        PuntoTuristico* puntoDeInteres = puntoTuristico->value;
        char tipo[101];
        strcpy(tipo, puntoDeInteres->tipo);

        eraseMap(mapaPuntosTuristicos, nombre);
        printf("El punto de interés '%s' ha sido eliminado correctamente.\n", nombre);

        MapaTipoDePuntos* tipoPuntos = (MapaTipoDePuntos*)searchMap(mapaPuntosPorTipo, tipo);
        if (tipoPuntos != NULL) {
            eraseMap(mapaPuntosPorTipo, tipo);
        }
    } else {
        printf("No se encontró un punto turístico con el nombre '%s'.\n", nombre);
    }
}

//FUNCIÓN CREARTURISTA: RESERVA MEMORIA PARA LOS DATOS DEL TURISTA
Turista * crearTurista(char* pasaporte, char* nombre, char* pais){
    Turista * turista = (Turista*)malloc(sizeof(Turista));
    if (turista == NULL) {
        printf("Error al asignar memoria para el turista.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(turista->pasaporte, pasaporte);
    strcpy(turista->nombre, nombre);
    strcpy(turista->pais, pais);
    
    turista->lugaresFavoritos = createList();
    
    return turista;
}

// OPCIÓN (4) REGISTRAR TURISTA
void registrarTurista(HashMap* mapaTuristas, HashMap* mapaTuristasPorPais) {
    char pasaporte[10];
    char nombre[101];
    char pais[101];

    // SE LEEN LOS DATOS A REGISTRAR
    printf("\nIngrese el número de pasaporte del turista (máximo 9 caracteres): ");
    scanf("%9s", pasaporte);
    getchar();

    // SE VERIFICA SI EL TURISTA YA ESTÁ REGISTRADO
    if (searchMap(mapaTuristas, pasaporte) != NULL) {
        printf("El turista con pasaporte '%s' ya está registrado.\n", pasaporte);
        return;
    }

    printf("Ingrese el nombre del turista (máximo 100 caracteres): ");
    scanf("%100[^\n]s", nombre);
    getchar();

    printf("Ingrese el país de origen del turista (máximo 100 caracteres): ");
    scanf("%100[^\n]s", pais);
    getchar();

    // LLAMADO A FUNCION crearTurista
    Turista* nuevoTurista = crearTurista(pasaporte, nombre, pais);

    // INSERTAR AL TURISTA EN EL MAPA
    insertMap(mapaTuristas, nuevoTurista->pasaporte, nuevoTurista);

   /* Pair* paisTurPair = searchMap(mapaTuristasPorPais, pais);
    MapaTuristasPais* paisTur;

    if (paisTurPair == NULL) {
        // SI EL PAÍS NO EXISTE EN EL MAPA DE TURISTAS POR PAÍS, SE CREA
        paisTur = (MapaTuristasPais*)malloc(sizeof(MapaTuristasPais));
        if (paisTur == NULL) {
            exit(EXIT_FAILURE);
        }

        strcpy(paisTur->clavePais, pais);
        paisTur->turistas = createList();
        insertMap(mapaTuristasPorPais, paisTur->clavePais, paisTur);
    } else {
        // SI EL PAÍS YA EXISTE EN EL MAPA, SE OBTIENE EL NODO
        paisTur = (MapaTuristasPais*)paisTurPair->value;
    }

    // SE AGREGA EL NOMBRE DEL TURISTA A LA LISTA DE TURISTAS DEL PAÍS
    pushBack(paisTur->turistas, nuevoTurista->nombre);*/

    printf("Turista %s registrado exitosamente.\n", pasaporte);
}

// OPCIÓN (5) AGREGAR LUGAR FAVORITO A TURISTA
void AgregarLugarFavoritoTurista(HashMap* mapaTuristas){
    char pasaporte[10]; 
    
    printf("Ingrese el número de pasaporte del turista: ");
    scanf("%9s", pasaporte);
    
    if (searchMap(mapaTuristas, pasaporte) != NULL){
        Pair* turistaPair = searchMap(mapaTuristas, pasaporte);
        char nombreLugar[101];
         printf("\nIngrese los lugares favoritos del turista (Ingrese 'fin' para terminar):\n");
        while (1) {
            printf("Nombre del lugar favorito (máximo 100 caracteres): ");
            scanf(" %100[^\n]s", nombreLugar);
            getchar();
            
            if (strcmp(nombreLugar, "fin") == 0){
                printf("Lugares favoritos del turista registrados exitosamente.\n");
                break; 
            }
            Turista*auxTur=turistaPair->value;
            pushBack(auxTur->lugaresFavoritos, nombreLugar);
        }
    }
    else{
        printf("\nNo se encontró un turista con el pasaporte %s.\n",pasaporte);
        return;
    }
}

//OPCION (6) MOSTRAR TURISTAS POR PAIS
void mostrarTuristasPorPais(HashMap* mapaTuristasPorPais, HashMap* mapaTuristas) {
    char pais[101];
    //SE LEE EL PAIS QUE DESEA MOSTRAR
    printf("\nIngrese el país para mostrar los turistas: ");
    scanf("%100[^\n]s", pais);
    getchar();
    
    Pair* paisTurPair = searchMap(mapaTuristasPorPais, pais);

    if (paisTurPair != NULL) {
        MapaTuristasPais* paisTur = (MapaTuristasPais*)paisTurPair->value;

        printf("\nTuristas de %s:\n", paisTur->clavePais);

        List* turistas = paisTur->turistas;
        void* current = firstList(turistas);

        while (current != NULL) {
            char* nombreTurista = (char*)current;
            printf("- Nombre: %s\n", nombreTurista);

            // Buscar al turista en el mapa de turistas para obtener sus lugares favoritos
            Pair* turistaPair = searchMap(mapaTuristas, nombreTurista);
            if (turistaPair != NULL) {
                Turista* turista = (Turista*)turistaPair->value;
                printf("  Lugares favoritos de %s:\n", nombreTurista);

                // Iterar a través de la lista de lugares favoritos del turista
                List* lugaresFavoritos = turista->lugaresFavoritos;
                void* lugarActual = firstList(lugaresFavoritos);

                while (lugarActual != NULL) {
                    char* lugar = (char*)lugarActual;
                    printf("  - %s\n", lugar);
                    lugarActual = nextList(lugaresFavoritos);
                }
            } else {
                printf("  Lugares favoritos de %s no encontrados.\n", nombreTurista);
            }

            current = nextList(turistas);
        }
    } else {
        printf("\nNo se encontraron turistas para el país '%s'.\n", pais);
    }
}


//OPCION (7) MOSTRAR PUNTOS DE INTERES POR TIPO
void mostrarPuntosDeInteresDeTipo(HashMap* mapaPuntosPorTipo) {
    char tipo[101];
    //SE LEE EL EL TIPO DE PUNTO QUE DESEA MOSTRAR
    printf("\nIngrese el tipo de punto de interés a mostrar (máximo 100 caracteres): ");
    scanf("%100s", tipo);
    getchar();

    Pair* tipoPuntos = searchMap(mapaPuntosPorTipo, tipo);

    if (tipoPuntos != NULL) {
        List* listaPuntos = (List*)tipoPuntos->value;

        if (firstList(listaPuntos) == NULL) {
            printf("\nNo hay puntos de interés de tipo '%s'.\n", tipo);
            return;
        }

        printf("\nPuntos de interés de tipo '%s':\n", tipo);

        for (void* current = firstList(listaPuntos); current != NULL; current = nextList(listaPuntos)){
            PuntoTuristico* punto = (PuntoTuristico*)current;
            printf("- Nombre: %s, Tipo: %s\n", punto->nombre, punto->tipo);
        }
    } else {
        printf("\nNo se encontraron puntos de interés de tipo '%s'.\n", tipo);
    }
}


//OPCION (8) IMPORTAR ARCHIVOS
void importarCSV(HashMap* mapaPuntosTuristicos, HashMap* mapaPuntosPorTipo, HashMap* mapaTuristas) {
    FILE* puntosCSV = fopen("puntosCSV.csv", "r");
    FILE* turistasCSV = fopen("turistasCSV.csv", "r");

    if (puntosCSV == NULL || turistasCSV == NULL) {
        printf("Error al abrir los archivos CSV para lectura.\n");
        return;
    }

    // LEER DATOS DE PUNTOS DE INTERES DESDE PUNTOSCSV.CSV
    char buffer[1024];
    fgets(buffer, sizeof(buffer), puntosCSV); 
    while (fgets(buffer, sizeof(buffer), puntosCSV) != NULL) {
        char nombre[101];
        char tipo[101];
        char direccion[101];
        char horario[101];
        char descripcion[101];

        sscanf(buffer, "%100[^,],%100[^,],%100[^,],%100[^,],%100[^\n]", nombre, tipo, direccion, horario, descripcion);

        PuntoTuristico* punto = crearPuntoTuristico(nombre, tipo, direccion, horario, descripcion);
        insertMap(mapaPuntosTuristicos, punto->nombre, punto);

        // ESTO ESTA COMENTADO DEBIDO A QUE SE CRASHEA EL PROGRAMA
        /*MapaTipoDePuntos* tipoPuntos = (MapaTipoDePuntos*)searchMap(mapaPuntosPorTipo, tipo);
        if (tipoPuntos == NULL) {
            tipoPuntos = (MapaTipoDePuntos*)malloc(sizeof(MapaTipoDePuntos));
            strcpy(tipoPuntos->claveTipo, tipo);
            tipoPuntos->tipoPuntos = createList();
            insertMap(mapaPuntosPorTipo, tipoPuntos->claveTipo, tipoPuntos);
        }

        pushBack(tipoPuntos->tipoPuntos, punto->nombre);*/
    }

    fgets(buffer, sizeof(buffer), turistasCSV);
    while (fgets(buffer, sizeof(buffer), turistasCSV) != NULL) {
        char nombre[101];
        char pais[101];
        char pasaporte[101]; 

        sscanf(buffer, "%100[^,],%100[^,],%100[^\n]", nombre, pais, pasaporte); 

        Turista* turista = crearTurista(pasaporte, nombre, pais);
        strcpy(turista->pasaporte, pasaporte); 
        insertMap(mapaTuristas, turista->nombre, turista);

        // AGREGA LOS LUGARES FAVORITOS A TURISTA 
        char* token = strtok(buffer, ","); 
        token = strtok(NULL, ","); 
        token = strtok(NULL, ","); 
        token = strtok(NULL, ",");
        while (token != NULL) {
            pushBack(turista->lugaresFavoritos, token);
            token = strtok(NULL, ",");
        }
    }

    fclose(puntosCSV);
    fclose(turistasCSV);

    printf("Datos importados desde puntos.csv y turistas.csv exitosamente.\n");
}


//OPCION (9) EXPORTAR ARCHIVOS 
void exportarCSV(HashMap* mapaPuntosTuristicos, HashMap* mapaTuristas) {
    FILE* puntosCSV = fopen("puntos_exportados.csv", "w");
    FILE* turistasCSV = fopen("turistas_exportados.csv", "w");

    if (puntosCSV == NULL || turistasCSV == NULL) {
        printf("Error al abrir los archivos CSV para escritura.\n");
        return;
    }

    fprintf(puntosCSV, "Nombre,Tipo,Direccion,Horario,Descripcion\n");

    Pair* puntoPair = firstMap(mapaPuntosTuristicos);
    while (puntoPair != NULL) {
        PuntoTuristico* punto = (PuntoTuristico*)puntoPair->value;
        fprintf(puntosCSV, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo, punto->direccion, punto->horario, punto->descripcion);
        puntoPair = nextMap(mapaPuntosTuristicos);
    }

    fprintf(turistasCSV, "Nombre,Pais,Favoritos\n");

    Pair* turistaPair = firstMap(mapaTuristas);
    while (turistaPair != NULL) {
        Turista* turista = (Turista*)turistaPair->value;
        fprintf(turistasCSV, "%s,%s,", turista->nombre, turista->pais);

        List* favoritos = turista->lugaresFavoritos;
        void* current = firstList(favoritos);

        while (current != NULL) {
            char* favorito = (char*)current;
            fprintf(turistasCSV, "%s", favorito);
            current = nextList(favoritos);
            if (current != NULL) {
                fprintf(turistasCSV, ",");
            }
        }

        fprintf(turistasCSV, "\n");
        turistaPair = nextMap(mapaTuristas);
    }

    fclose(puntosCSV);
    fclose(turistasCSV);

    printf("Datos exportados a puntos.csv y turistas.csv exitosamente.\n");
}