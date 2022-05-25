#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLectores.bin"

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
    int activo;    // alta de libro. 1: alta y 0: baja.
} stLibro;

typedef struct
{
    int id;
    char mail[45];
    char password[15];
} stAdministrador;

int menu_inicio();
int validarAdministrador();
void registrarLector(stLector * lector);    // Hacer un menu luego...
void mostrarLector(const stLector lector);
void mostrarArchivo_Lectores();
stLector validarLector();
int posicionLector_id(const int id);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


stLector validarLector(const char mail[], const char password[])
{
    int flag = 0; // ver si ingreso o no correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)
    stLector aux;

//    printf("Ingrese su Email: ");
//    fflush(stdin);
//    gets(mail);
//
//    printf("Ingrese su contraseña: ");
//    fflush(stdin);
//    gets(password);

    FILE * archivo = fopen("archivoLectores.bin", "rb");
    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector),1,archivo )>0 &&  flag == 0)
        {
            if (!strcmpi(aux.password, password) && !strcmpi(aux.mail, mail))
            {
                printf("Acceso correcto (borrar linea).\n");
                flag = 1;
            }
        }
    }
    else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }

    return aux; // como hago para devolver el
}


void menuAdministrador()
{
    printf(" Sistema de Biblioteca (Administrador).\n\n");
    printf("    1. Ver lista de lectores: \n");
    printf("    2. Dar de baja un lectores: \n");
    printf("    3. Modificar los datos de un lector: \n");
    printf("    4. Ver los libros favoritos de un lector: \n");
    printf("    5. Dar de alta un libro: \n");
    printf("    6. Modicar los atributos de un libro: \n");
    printf("    7. Dar de baja un libro: \n\n");
    printf("    0. Volver: \n\n");
    printf(" Opción: ");
}

void administrador_case(const int option)
{
    switch(option)
    {
    case 1:
        printf("                            La Lista de Lectores\n\n");
        mostrarArchivo_Lectores();
        printf("                            Fin Lista de Lectores\n\n");
        break;
    case 2:
        printf("                            Dar de baja un lectores:\n\n");
        int id_user;
        printf("Ingrese el ID del lector: \n");
        fflush(stdin);
        scanf("%d", &id_user);



        break;
    }
}

int posicionLector_id(const int id)
{
    int posicion = -1; // si return -1 significa que no se encuentra
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "a+b");
    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector), 1, archivo) > 0)
        {
            if(aux.id == id)
            {
                posicion = ftell(archivo) / sizeof(stLector);
            }
        }
        fclose(archivo);
    } else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
    return posicion;
}


int main()
{
    setlocale(LC_ALL, "");
    system("color 3e");
    char option = 'n';

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
    //registrarLector(&lectores[0]);

    printf("la posicion del id es: %d", posicionLector_id(1));


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // Repito el programa hasta que decida salir
//    while (option !='s' && option!='S')
//    {
//        system("cls");
//        int usuario = menu_inicio();
//        if(usuario == 1)
//        {
//            stLector Lector_actual;
//            char user_actual[30];
//            char user_password;
//            int option_lector;
//            printf("                                    Sistema de Biblioteca (Lector).\n\n");
//
////            option_lector = funcionJuan;
//
//
//
//        }
//        else
//        {
//            printf("                                    Sistema de Biblioteca (Administrador).\n\n");
//            int reintentarAdministrador = 's';
//            while (reintentarAdministrador == 's' || reintentarAdministrador == 'S')
//            {
//                printf("Iniciar sesión: \n\n");
//
//                if(validarAdministrador() == 1) // Todo correcto esta dentro del administrador
//                {
//                    int option = 1;
//                    while(option != 0)
//                    {
//                        printf("\n>>                                Bienvenido a la biblioteca.\n\n");
//                        menuAdministrador();
//                        fflush(stdin);
//                        scanf("%d", &option);
//                        administrador_case(option);
//                        reintentarAdministrador = 'n';
//                    }
//                }
//                else
//                {
//                    printf(">>                          Ha ingresado un usuario o contraseña incorrecta.\n");
//                    printf("¿Desea reintentar? s/n. ");
//                    fflush(stdin);
//                    scanf("%c", &reintentarAdministrador);
//                }
//            }
//        }
//        printf("¿Desea salir? s/n. ");
//        fflush(stdin);
//        scanf("%c", &option);
//    }
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

int validarAdministrador()
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

void registrarLector(stLector * lector)
{
    FILE* archivo = fopen("archivoLectores.bin", "ab");
    if(archivo != NULL)
    {
        fwrite(lector, sizeof(stLector), 1, archivo);

        fclose(archivo);
    }
}

void mostrarLector(const stLector lector)
{
    printf("+-------------------------------+-------------------------------+\n");

    printf("  Nombre: \t\t\t|  %s \n", lector.nombre);
    printf("  Id:   \t\t\t|  %i\n", lector.id);
    printf("  Mail: \t\t\t|  %s\n", lector.mail);
    printf("  Contraseña: \t\t\t|  %s\n", lector.password);
    if(lector.activo)
    {
        printf("  Estado Activo: \t\t|  activo (%i) \n", lector.activo);
    }
    else
    {
        printf("  Estado Activo: \t\t|  dado de baja (%i) \n", lector.activo);
    }

    printf(" Nº de libros favoritos: \t|  %i\n", lector.validos);
    for(int i = 0; i < lector.validos; i++)
    {
        printf("  libro favorito %i, \t\t|  codigo: %i \n",i,lector.listaFavoritos[i]);
    }
    printf("+-------------------------------+-------------------------------+\n");
}

void mostrarArchivo_Lectores()
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
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}





