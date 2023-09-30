Benjamin Velasquez 100/100 pts
Sean Jamen 100/100 pts
Ambos estudiantes trabajaron en conjunto en la implementacion de este programa.

¿Como ejecutar nuestro programa?
1. ejecute el programa
2. seleccionar la opcion que se ajuste a lo que desea realizar.
3. una vez hecho todo lo que necesite, salgase del programa con la opcion "0".


PROBLEMAS:
- LA OPCION (6) Y LA OPCION (7), NO NOS IMPRIME LOS DATOS QUE SE PIDEN , DEBIDO A QUE TENEMOS PROBLEMAS CON LA IMPLEMENTACION DE LAS LISTAS PARA LOS TIPO DE PUNTOS Y TURISTAS POR PAIS.
- ADEMAS LA OPCION (4) AL REGISTRAR UN TURISTA, SE REGSITRA PERO AL INTENTAR REGISTRARLO EN EL MAPA DE TURISTA POR PAIS EL PROGRAMA CRASHEA

Descripción Procedimental

1.- Registrar punto de interés (char* nombre, char* tipo, char* dirección, char* descripción)
      -Se ingresan los datos que aparecen en el paréntesis en el segundo struct.
      -Se validará que los datos no pasen de los 100 caracteres.
 
2.- Mostrar datos de punto de interés (char* nombre)
     -El usuario ingresa su nombre y se buscará para ver si existe.
     -Se mostrarán los datos si el nombre es encontrado, sino se mostrará un aviso.

3.- Eliminar punto de interés (char* nombre)
     -El usuario ingresa su nombre y se buscará para ver si existe.
     -Si es que existe se pedirá el punto de interés y se buscará si existe en la lista.
     -Si es que existe se elimina.

4.- Registrar turista (char* pasaporte, char* nombre, char* país)
     -El usuario ingresa los datos antes mencionados y se registra como un nuevo dato en el mapa de turistas

5.- Agregar lugar favorito a turista (char* pasaporte, char* nombre_lugar)
     -El usuario ingresa los datos antes mencionados, se busca el mapa con los datos del turista y    	    nn guarda en la lista de lugares favoritos.
      -Se verificará de que no se ingrese 2 veces el mismo lugar por turista.

6.- Mostrar turistas por país (char* pais)
     -Se mostrarán los turistas ordenados por número de pasaporte.
     -Se avisará si no hay turistas registrados.

7.- Mostrar todos los puntos de interés de un tipo (char* tipo)
    -Se mostrarán todos los puntos de interés de un tipo específico que estén almacenados en el mapa ppp de puntos.
     -Se avisará si no se encuentra.
8.- Importar puntos de interés y turistas desde archivos CSV (char* nombre_archivo_puntos, char* nombre_archivo_turistas)
    -Se pedirá el nombre del archivo que se quiere importar.
    -La aplicación cargará los puntos de interés y turistas, incluyendo sus lugares favoritos que guardarán en los mapas correspondientes.

9.- Exportar puntos de interés y turistas a archivos CSV (char* nombre_archivo_puntos, char* nombre_archivo_turistas)
    -Se creará un archivo con el nombre ingresado por el usuario.
    -Se guardará la información de los mapas requeridos para pasarla al archivo csv.
