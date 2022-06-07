#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./librerias/utilidades.h"
#include "./librerias/lectores.h"

int main()
{
    setlocale(LC_ALL, "");
    system("color 3e");
    char option = 'n';
    verificar_archivos();
//
//    mostrarArchivo_Lectores();

    // >>>> Repito el programa hasta que decida salir <<<<
    while (option !='s' && option!='S')
    {
        system("cls");
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














