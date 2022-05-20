#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>

typedef struct {
    int id;
    char mail[45];
    char password[15];
    char listaFavoritos[10][30]; // máximo 10 favoritos...
    char nombre[30];
    int activo;    // alta de usuario. 1: activo y 0: inactivo.
} stLector;

typedef struct {
    int id;
    char nombre[50];
    char autor[30];
    char genero[15];        // Terror, aventura,
} stLibro;

typedef struct {
    int id;
    char mail[45];
    char password[15];
} stAdministrador;


int menu_inicio();
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int validarAdministrador()
{
    char email[30]= "administrador@biblioteca.com";
    char emailUser[30];
    int flag = 0; // ver si ingreso o correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)
    printf("Ingrese su Email: ");
    fflush(stdin);
    scanf("%s", &emailUser); // no podes hacer un scan en strings fgets()


    if(!strcmpi(&email, &emailUser))
    {
        printf("Bienvenido a la Biblioteca\n");
        flag = 1;
    }else
    {
        printf("Ha ingresado un usuario o contraseña incorrecta\n");

    }
    return flag;
}



int main()
{
    setlocale(LC_ALL, "");
    system("color 3e");
    int usuario = menu_inicio();

    if(usuario == 1)
    {

        printf("                                    Sistema de Biblioteca (Lector).\n\n");
    }else
    {
        printf("                                    Sistema de Biblioteca (Administrador).\n\n");
        validarAdministrador();

    }

    printf("\n\n>>>                         Fin programa!\n");
    return 0;
}


int menu_inicio()
{
    int option;
    printf("                                    Sistema de Biblioteca.\n\n");

    do
    {
        printf(" Seleccione una opción para continuar.\n");
        printf("    1. Lector.\n");
        printf("    2. Administrador.\n\n");

        printf("   Tu respuesta: ");
        fflush(stdin);
        scanf("%d", &option);
        if(option!=1 && option!=2)
        {
            printf(">>>                         Error, ingrese un valor valido.\n\n");
        }
    } while(option != 1 && option!=2);
    return option;
}
