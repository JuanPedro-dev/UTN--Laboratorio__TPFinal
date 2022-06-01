#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED


/**
    nombre de los archivos.
	archivoLectores.bin
	archivoLibros.bin

	No usamos variable global para ver la dimension de listaFavoritos pues falla alguna veces...
*/


typedef struct
{
    char nombre[30];
    char mail[45];
    char password[15];
    int id;
    int listaFavoritos[10]; // máximo 10 favoritos...
    int validos;
    int activo;             // alta de usuario. 1: activo y 0: inactivo.
} stLector;

typedef struct
{
    int id;
    char nombre[50];
    char autor[30];
    char genero[15];        // Terror, aventura,
    int activo;    // alta de libro. 1: alta y 0: baja.
} stLibro;

typedef struct
{
    int id;
    char mail[45];
    char password[15];
} stAdministrador;

int menu_inicio();
void verificar_archivos();

void menuLector();



int validarAdministrador();
#endif // UTILIDADES_H_INCLUDED
