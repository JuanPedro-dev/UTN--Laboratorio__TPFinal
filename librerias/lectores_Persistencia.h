#ifndef LECTORES_PERSISTENCIA_H_INCLUDED
#define LECTORES_PERSISTENCIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./librerias/utilidades.h"
#include "./librerias/lectores.h"

void registrarLector_Persistencia(lector);
void registrarse_Persistencia();
int validarLector_Persistencia(const char mail[], const char password[]);
void mostrarLector_Persistencia(const stLector lector);
void mostrarArchivo_Lectores_Persistencia();
int posicionLector_id_Persistencia(const int id);
void darBajaLector_Persistencia(const int indice);
void modificarLector_Persistencia(const int indice);
void leerFavoritos_lector_Persistencia(const int indice);
void lector_case_Persistencia(const int option, int *indice, stLector * lector_actual);
stLector devolverUsuario_Persistencia(int indice);
void agregarFavorito_Persistencia(stLector lector);
int validarFavorito_Persistencia(int libroFavorito, stLector lector);
void actualizarRegistroLector_Persistencia(stLector lector, int indiceLector);
void quitarLibro_Persistencia(int indice);
void bajaLector_persistencia(int indice);
int comprobarUsuarioRepetido_Persistencia(char mail[45]);

#endif // LECTORES_PERSISTENCIA_H_INCLUDED
