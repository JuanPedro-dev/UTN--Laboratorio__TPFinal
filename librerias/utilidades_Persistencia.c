#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./utilidades_Persistencia.h"


int menu_inicio_Persistencia()
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

void verificar_archivos_Persistencia()
{
    FILE * archivo_lectores = fopen(archivoLectores, "rb");
    FILE * archivo_libros = fopen(archivoLibros,"rb");
    if (archivo_lectores == NULL)
    {
        FILE * archivo_lectores = fopen(archivoLectores, "wb");
    }
    if (archivo_libros == NULL)
    {
        FILE * archivo_lectores = fopen(archivoLibros, "wb");
    }
    int fcloseall();
}

int validarAdministrador_Persistencia()
{
    char email[30]= "administrador@biblioteca.com";
    char contrasenia[30] = "admin123";
    char emailUser[30];
    char contraseniaUser[30];
    int flag = 0; // ver si ingreso o correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)

    printf(">>> Ingrese su Email: ");
    fflush(stdin);
    gets(emailUser);

    printf(">>> Ingrese su contraseña: ");
    fflush(stdin);
    gets(contraseniaUser);

    if(!strcmpi(email, emailUser) && !strcmpi(contraseniaUser, contrasenia))
    {
        flag = 1;
    }
    return flag;
}

void menuLector_Persistencia()
{
    printf("\t\t\t+=========================+=========================+\n");
    printf("\t\t\t|                 MENU DE LECTORES                  |\n");
    printf("\t\t\t+=========================+=========================+\n");
    printf("    1. Registrarse.         \n");
    printf("    2. Login / Entrar.      \n");
    printf("    3. Ver mi Perfil.       \n");
    printf("    4. Ver lista de libros. \n");
    printf("    5. Mostrar libro(Caracteristicas).   \n");
    printf("    6. Marcar como favorito un libro.    \n");
    printf("    7. Desmarcar como favorito un libro. \n");
    printf("    8. Ver mis libros favoritos.         \n");
    printf("    9. Darse de baja de la aplicación.   \n\n");
    printf("   10. Logout / Salir.                   \n");
    printf("    0. Salir o Volver al menu principal. \n");

    printf("\n ELIJA UNA OPCIÓN: ");
}




















