#ifndef LIBROS_PERSISTENCIA_H_INCLUDED
#define LIBROS_PERSISTENCIA_H_INCLUDED
#include "./utilidades.h"

void mostrarLibros_Persistencia();
void devolverNombreLibro_Persistencia(char* nombre[50], int idAbuscar);
void crearLibros_Persistencia();
void guardaLibro_Persistencia(stLibro libro);
stLibro creaLibro_Persistencia();
int ultimoId_Persistencia();
int compruebaLibro_Persistencia(char nombrePropuesto[50]);
void editarLibro_Persistencia();
int buscarPosicionLibro_Persistencia(int idABuscar);
void borrarLibros_Persistencia();
int validarLibro_Persistencia(int idABuscar);
void mostrarLibro_Persistencia();
void darDeAltaLibros_Persistencia();

#endif // LIBROS_PERSISTENCIA_H_INCLUDED
