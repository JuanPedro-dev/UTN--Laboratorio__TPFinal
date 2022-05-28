#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>

#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./persistenciaLectores.h"


int menu_inicio_persistencia()
{
    int option;
    printf("\t\t\t+=========================+=========================+\n");
    printf("\t\t\t|               SISTEMA DE BIBLIOTECA               |\n");
    printf("\t\t\t+=========================+=========================+\n");

    do
    {
        printf(" Seleccione una opción para continuar.\n");
        printf("    1. Lector.\n");
        printf("    2. Administrador.\n");


        printf("\n ELIJA UNA OPCIÓN: ");
        fflush(stdin);
        scanf("%d", &option);
        if(option!=1 && option!=2)
        {
            printf("                         >>> Error, ingrese un valor valido. <<<\n\n");
        }
    }
    while(option != 1 && option!=2);
    return option;
}
