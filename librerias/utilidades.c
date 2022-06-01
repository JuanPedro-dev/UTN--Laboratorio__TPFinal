#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./utilidades.h"
#include "./lectores.h"

int menu_inicio()
{
    menu_inicio_Persistencia();
}

void verificar_archivos()
{
    verificar_archivos_Persistencia();
}

int validarAdministrador()
{
    validarAdministrador_Persistencia();
}

void menuLector()
{
    menuLector_Persistencia();
}
