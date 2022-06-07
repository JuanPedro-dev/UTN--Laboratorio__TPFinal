#include <stdio.h>#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./utilidades.h"
#include "./lectores.h"

void registrarLector(stLector * lector)
{
    registrarLector_Persistencia(lector);
}

void registrarse()
{
    registrarse_Persistencia();
}

int validarLector(const char mail[], const char password[])
{
    validarLector_Persistencia(mail, password);
}

void mostrarLector(const stLector lector)
{
    mostrarLector_Persistencia(lector);
}

void mostrarArchivo_Lectores()
{
    mostrarArchivo_Lectores_Persistencia();
}

int posicionLector_id(const int id)
{
    posicionLector_id_Persistencia(id);
}

void darBajaLector(const int indice)
{
    darBajaLector_Persistencia(indice);
}

void modificarLector(const int indice)
{
    modificarLector_Persistencia(indice);
}

void leerFavoritos_lector(const int indice)
{
    leerFavoritos_lector_Persistencia(indice);
}

void lector_case(const int option)
{
    lector_case_Persistencia(option);
}
