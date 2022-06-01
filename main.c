#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./librerias/utilidades.h"
#include "./librerias/lectores.h"

void lector_case(const int option)
{

    int indice;
    int id_user_actual;
    stLector lector_actual;
    char mail[45];
    char password[15];

    int flag_logIn = 0;
    switch(option)
    {
    case 1:
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  REGISTRO LECTOR                  |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        registrarse();
        break;
    case 2:
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  INICIAR SESIÓN                   |\n");
        printf("\t\t\t+=========================+=========================+\n\n");

        printf("Ingrese su mail: ");
        fflush(stdin);
        gets(mail);

        printf("Ingrese su contraseña: ");
        fflush(stdin);
        gets(password);

        indice = validarLector(mail, password);
        if(indice == -1)
        {
            printf("Error: el mail o su contraseña son incorrectas.\n");
        }
        printf("El usuario id actual: %d\n", indice);

        system("pause");
        break;

    case 4:
        if(flag_logIn == 0)
        {
            printf("Primero inicie sesión.\n");
        } else
        {
            printf("                    Ver lista de libros.\n");
            leerFavoritos_lector(indice);
        }
        break;

    }
}

void menuAdministrador()
{
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
    printf("    8. Agregar un libro: \n\n");
    printf("    0. Salir o Volver al menu principal.\n");

    printf("\n ELIJA UNA OPCIÓN: ");
}

void administrador_case(const int option)
{
    int indice;
    int id_user;

    switch(option)
    {
    case 1:
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
        printf("                            Dar de baja un lectores\n\n");
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
            printf("No se encuentra el ID del lector.\n");
        }
        system("pause");
        break;
    case 3:
        printf("                            Modificar los datos de un lector \n\n");
        printf("Ingrese el ID del lector: ");
        fflush(stdin);
        scanf("%d", &id_user);
        indice = posicionLector_id(id_user);
        if(indice!=-1)
        {
            modificarLector(indice);
        }
        else
        {
            printf("No se encuentra el ID del lector.\n");
        }
        printf(">>> Se ha modificado con éxito.\n");
        system("pause");
        break;
    case 4:
        printf("                            Ver los libros favoritos de un lector\n\n");
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
            printf("No se encuentra el ID del lector.\n");
        }
        system("pause");
        break;
    ///////////////////////////////////////////////////////////////////////////////////////
    case 5:
        printf("                            Dar de alta un libro\n\n");
        printf("Ingrese el ID del libro: ");
        fflush(stdin);
        scanf("%d", &id_user);
        indice = posicionLector_id(id_user); // cambiar buscar posicion que tiene un libro.
        if(indice!=-1)
        {
            //funcion que modifica un libro
        }
        else
        {
            printf("No se encuentra el ID del libro.\n");
        }
        printf(">>> Se ha modificado con éxito.\n");
        system("pause");
        break;

        ///////////////////////////////////////////////////////////////////////////////////////
    }
}

int main()
{
    setlocale(LC_ALL, "");
    system("color 3e");
    char option = 'n';
    verificar_archivos();

    mostrarArchivo_Lectores();

    // >>>> Repito el programa hasta que decida salir <<<<
    while (option !='s' && option!='S')
    {
//        system("cls");
        int usuario = menu_inicio();
        if(usuario == 1)
        {
                                            // >>>> Sistema lector <<<<
            stLector Lector_actual;
            char user_actual[30];
            char user_password;
            int option_lector;
            menuLector();
            fflush(stdin);
            scanf("%d", &option_lector);
            lector_case(option_lector);
        }
        else
        {
            printf("\t\t\t+=========================+=========================+\n");
            printf("\t\t\t|               MENU DEL ADMINISTRADOR              |\n");
            printf("\t\t\t+=========================+=========================+\n");
            int reintentarAdministrador = 's';
            while (reintentarAdministrador == 's' || reintentarAdministrador == 'S')
            {
                printf("Iniciar sesión: \n\n");
                if(validarAdministrador() == 1) // Todo correcto esta dentro del administrador
                {
                    int option = 1;
                    while(option != 0)
                    {
                        menuAdministrador();
                        fflush(stdin);
                        scanf("%d", &option);
                        administrador_case(option);
                        reintentarAdministrador = 'n';
                    }
                }
                else
                {
                    printf(">>                          Ha ingresado un usuario o contraseña incorrecta.\n");
                    printf("¿Desea reintentar? s/n. ");
                    fflush(stdin);
                    scanf("%c", &reintentarAdministrador);
                }
            }
        }
        printf("¿Desea salir? s/n. ");
        fflush(stdin);
        scanf("%c", &option);
    }

    printf("\n\n>>>                         Fin programa!\n");
    return 0;
}














