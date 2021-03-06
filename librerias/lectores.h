#ifndef LECTORES_H_INCLUDED
#define LECTORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./utilidades.h"
#include "./lectores.h"

                                // Lector funciones
void registrarLector(stLector * lector);
void registrarse();
int validarLector(const char mail[], const char password[]);
void mostrarLector(const stLector lector);
void mostrarArchivo_Lectores();
int posicionLector_id(const int id);
void darBajaLector(const int indice);
void modificarLector(const int indice);
void leerFavoritos_lector(const int indice);
void lector_case(const int option, int *indice, stLector * lector_actual);
stLector devolverUsuario(int indice);
void agregarFavorito(stLector lector);
int validarFavorito(int libroFavorito, stLector lector);
void actualizarRegistroLector(stLector lector, int indiceLector);
void quitarLibro(int indice);
void bajaLector(int indice);
int comprobarUsuarioRepetido(char mail[45]);


#endif // LECTORES_H_INCLUDE
