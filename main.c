#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
/**
    nombre de los archivos.
	archivoLectores.bin
	archivoLibros.bin
*/

typedef struct
{
    int id;
    char mail[45];
    char password[15];
    int listaFavoritos[10]; // máximo 10 favoritos...
    int validos;
    char nombre[30];
    int activo;    // alta de usuario. 1: activo y 0: inactivo.

} stLector;

typedef struct
{
    int id;
    char nombre[50];
    char autor[30];
    char genero[15];        // Terror, aventura,
} stLibro;

typedef struct
{
    int id;
    char mail[45];
    char password[15];
} stAdministrador;


int menu_inicio();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int validarAdministrador()
{
    char email[30]= "administrador@biblioteca.com";
    char contrasenia[30] = "admin123";
    char emailUser[30];
    char contraseniaUser[30];
    int flag = 0; // ver si ingreso o correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)

    printf("Ingrese su Email: ");
    fflush(stdin);
    gets(emailUser);

    printf("Ingrese su contraseña: ");
    fflush(stdin);
    gets(contraseniaUser);

    if(!strcmpi(email, emailUser) && !strcmpi(contraseniaUser, contrasenia))
    {
        printf("\n>>Bienvenido a la biblioteca.\n");
        flag = 1;
    }
    else
    {
        printf("Ha ingresado un usuario o contraseña incorrecta.\n");
    }
    return flag;
}

int validarLector(const stLector lectores[])
{
//    int flag = 0; // ver si ingreso o correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)
//
//    printf("Ingrese su Email: ");
//    fflush(stdin);
//
//    printf("Ingrese su contraseña: ");
//    fflush(stdin);
//
//
//    FILE * archivo = fopen("archivoLectores.bin", "rb");
//    if(archivo != NULL)
//    {
//        while(fread(&aux, sizeof(stLector), )
//
//    } else
//    {
//        printf("Error: no se pudo cargar el archivo.\n");
//    }
//
//    return flag;
}

void mostrarLector(const stLector lector)
{
    printf("................................... \n");
    printf("Nombre: %s\n", lector.nombre);
    printf("Id:%i\n", lector.id);
    printf("Mail: %s\n", lector.mail);
    printf("Contraseña: %s\n", lector.password);
    printf("Cantidad de libros favoritos: %i\n", lector.validos);
    printf("Activo (1: activo, 2: inactivo.): %i \n", lector.activo);
    for(int i = 0; i < lector.validos; i++)
    {
        printf("libro favorito %i, codigo: %i \n",i,lector.listaFavoritos[i]);
    }
    printf("................................... \n");
}

void escribeLector(stLector * lector)
{
    FILE* archivo = fopen("archivoLectores.bin", "ab");
    if(archivo != NULL)
    {
        fwrite(lector, sizeof(stLector), 1 , archivo);

        fclose(archivo);
    }
}

void mostrarArchivo()
{
    FILE * archivo = fopen("archivoLectores.bin", "rb");
    stLector aux;

    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector),1,archivo)>0 )
        {
            mostrarLector(aux);
        }

        fclose(archivo);
    } else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

int main()
{
    setlocale(LC_ALL, "");
    system("color 3e");
    char option;

    // Creo un lector para probar
    stLector lectores[20];
    lectores[0].activo = 1;
    lectores[0].id = 1;
    strcpy(lectores[0].nombre, "Lector 1");
    strcpy(lectores[0].mail, "Lector1@gmail.com");
    strcpy(lectores[0].password, "lector1");
    lectores[0].listaFavoritos[0] = 643;
    lectores[0].listaFavoritos[1] = 123;
    lectores[0].listaFavoritos[2] = 321;
    lectores[0].validos = 3;


    escribeLector(&lectores[0]);

    // Veo lo que tiene el archivo
    mostrarArchivo();


    // Repito el programa hasta que decida salir
    do
    {
//        system("cls");
//        int usuario = menu_inicio();
//        if(usuario == 1)
//        {
//
//            printf("                                    Sistema de Biblioteca (Lector).\n\n");
//        }
//        else
//        {
//            printf("                                    Sistema de Biblioteca (Administrador).\n\n");
//            if(validarAdministrador() == 1)
//            {
//                // menu de administrador
//            }
//
//        }

        printf("¿Desea salir? s/n. ");
        fflush(stdin);
        scanf("%c", &option);
    }
    while (option !='s' && option!='S');




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
    }
    while(option != 1 && option!=2);
    return option;
}
