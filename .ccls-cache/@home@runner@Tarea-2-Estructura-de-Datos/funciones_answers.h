#ifndef funciones_answers_h
#define funciones_answers_h

typedef struct PuntoTuristico PuntoTuristico;
typedef struct Turista Turista;

void mostrarOpciones();
void mostrarMenu();
PuntoTuristico * crearPuntoTuristico();
void registrarPuntoDeInteres();
void mostrarDatosPuntosInteres();
void eliminarPuntoDeInteres();
Turista * crearTurista();
void registrarTurista();
void AgregarLugarFavoritoTurista();
void mostrarTuristasPorPais();
void mostrarPuntosDeInteresDeTipo();
void importarCSV();
void exportarCSV();
void liberarMemoria();

#endif // funciones_answers_h