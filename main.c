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

    while (option !='s' && option!='S')
    {
        system("cls");
        int usuario = menu_inicio();
        switch(usuario)
        {
        case 0:
            option = 'S';
            break;
        case 1:         // >>>> Sistema lector <<<<
            printf("");
            int indice = -1;
            int option_lector;
            do
            {
                stLector lector_actual;
                menuLector();
                fflush(stdin);
                scanf("%d", &option_lector);
                lector_case(option_lector, &indice, &lector_actual);

                if (option_lector==0)
                {
                    option = 's';
                }
            }
            while(option_lector !=10 && option_lector !=0);
            break;

        case 2:         // >>>> Sistema Administrador <<<<
            printf("");
            int reintentarAdministrador = 's';
            while (reintentarAdministrador == 's' || reintentarAdministrador == 'S')
            {
                system("cls");
                printf("\t\t\t+=========================+=========================+\n");
                printf("\t\t\t|               MENU DEL ADMINISTRADOR              |\n");
                printf("\t\t\t+=========================+=========================+\n");
                printf("Iniciar sesión: \n\n");
                if(validarAdministrador() == 1) // Todo correcto esta dentro del administrador
                {
                    int option = 1;
                    while(option != 0)
                    {
                        menuAdministrador();
                        fflush(stdin);
                        scanf("%d", &option);
                        system("cls");
                        administrador_case(option);
                        reintentarAdministrador = 'n';
                    }
                }
                else
                {
                    system("cls");
                    printf(">>                          Ha ingresado un usuario o contraseña incorrecta.\n");
                    printf("¿Desea reintentar? s/n. ");
                    fflush(stdin);
                    scanf("%c", &reintentarAdministrador);
                }
            }
            break;
        }
    }

    printf("\n\n>>>                         Fin programa!\n");
    return 0;
}














