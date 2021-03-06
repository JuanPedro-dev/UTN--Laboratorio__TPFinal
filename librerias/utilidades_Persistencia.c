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
    do
    {
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|               SISTEMA DE BIBLIOTECA               |\n");
        printf("\t\t\t+=========================+=========================+\n");
        printf(" Seleccione una opci?n para continuar.\n");
        printf("    1. Lector.\n");
        printf("    2. Administrador.\n\n");
        printf("    0. Terminar el programa\n");


        printf("\n ELIJA UNA OPCI?N: ");
        fflush(stdin);
        scanf("%d", &option);
        if(option!=1 && option!=2 && option!=0)
        {
            printf("                         >>> Error, ingrese un valor valido. <<<\n");
            Sleep(1300);
        }
    }
    while(option != 1 && option!=2 && option!=0);
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

    printf(">>> Ingrese su contrase?a: ");
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
    system("cls");
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
    printf("    9. Darse de baja de la aplicaci?n.   \n\n");
    printf("   10. Logout (Volver al men? principal). \n");
    printf("    0. Salir del programa. \n");

    printf("\n ELIJA UNA OPCI?N: ");
}

void menuAdministrador_Persistencia()
{
    system("cls");
    printf("\t\t\t+=========================+=========================+\n");
    printf("\t\t\t|               MENU DEL ADMINISTRADOR              |\n");
    printf("\t\t\t+=========================+=========================+\n");
    printf("    1. Ver lista de lectores: \n");
    printf("    2. Dar de baja un lectores: \n");
    printf("    3. Modificar los datos de un lector: \n");
    printf("    4. Ver los libros favoritos de un lector: \n");
    printf("    5. Dar de alta un libro: \n");
    printf("    6. Modicar los atributos de un libro: \n");
    printf("    7. Dar de baja un libro: \n");
    printf("    8. Agregar un libro: \n");
    printf("    9. Ver lista de libros con caracteristicas: \n\n");
    printf("    0. Salir o Volver al menu principal.\n");

    printf("\n ELIJA UNA OPCI?N: ");
}
void administrador_case_Persistencia(const int option)
{
    int indice;
    int id_user;

    switch(option)
    {
    case 1:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                 LISTA DE LECTORES                 |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        mostrarArchivo_Lectores();
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|               FIN LISTA DE LECTORES               |\n");
        printf("\t\t\t+=========================+=========================+\n");
        system("pause");
        break;
    case 2:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                DAR BAJA A UN LECTOR               |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        printf("Ingrese el ID del lector: ");
        fflush(stdin);
        scanf("%d", &id_user);
        indice = posicionLector_id(id_user);
        if(indice!=-1)
        {
            darBajaLector(indice);
        }
        else
        {
            printf(">> No se encuentra el ID del lector.\n");
        }
        system("pause");
        break;
    case 3:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  MODIFICAR LECTOR                 |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        printf("Ingrese el ID del lector: ");
        fflush(stdin);
        scanf("%d", &id_user);
        indice = posicionLector_id(id_user);
        if(indice!=-1)
        {
            modificarLector(indice);
            printf(">>> Se ha modificado con ?xito.\n");
        }
        else
        {
            printf("No se encuentra el ID del lector.\n");
        }
        system("pause");
        break;
    case 4:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|              FAVORITOS DE UN LECTOR               |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        printf("Ingrese el ID del lector: ");
        fflush(stdin);
        scanf("%d", &id_user);
        indice = posicionLector_id(id_user);
        if(indice!=-1)
        {
            leerFavoritos_lector(indice);
        }
        else
        {
            printf(">> No se encuentra el ID del lector.\n");
        }
        system("pause");
        break;
    case 5:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                DAR ALTA A UN LIBRO                |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        darDeAltaLibros();
        break;
    case 6:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  EDITAR UN LIBRO                  |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        editarLibro();
        break;
    case 7:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                DAR DE BAJA UN LIBRO               |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        borrarLibros();
        break;
    case 8:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                   CREAR UN LIBRO                  |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        crearLibros();
        break;
    case 9:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                 LISTA DE LIBROS                   |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        mostrarLibros();
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|               FIN LISTA DE LIBROS                 |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        system("pause");
        break;
    }
}

















