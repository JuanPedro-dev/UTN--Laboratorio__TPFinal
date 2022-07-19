#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"
#include "./utilidades.h"
#include "./lectores.h"
#include "./libros_Persistencia.h"

void mostrarLibros()
{
    mostrarLibros_Persistencia();
}
void devolverNombreLibro(char* nombre[50], int idABuscar)
{
    devolverNombreLibro_Persistencia(nombre,idABuscar);
}
void crearLibros()
{
    crearLibros_Persistencia();
}
void guardaLibro(stLibro libro)
{
    guardaLibro_Persistencia(libro);
}
void editarLibro()
{
    editarLibro_Persistencia();
}
void borrarLibros()
{
    borrarLibros_Persistencia();
}
int validarLibro(int idABuscar)
{
    validarLibro_Persistencia(idABuscar);
}
void mostrarLibro()
{
    mostrarLibro_Persistencia();
}
void darDeAltaLibros()
{
    darDeAltaLibros_Persistencia();
}
