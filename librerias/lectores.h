#ifndef LECTORES_H_INCLUDED
#define LECTORES_H_INCLUDED

/** prototipado y definicion de estructuras */

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

int menu_inicio();                              // Menu 1


#endif // LECTORES_H_INCLUDED
