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

	No usamos variable global para ver la dimension de listaFavoritos pues falla alguna veces...
*/

typedef struct
{
    char nombre[30];
    char mail[45];
    char password[15];
    int id;
    int listaFavoritos[10]; // m�ximo 10 favoritos...
    int validos;
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
void darBajaLector(const int indice);
void modificarLector(const int indice);
void leerFavoritos_lector(const int indice); // modificar para ver los nombres de los libros



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


stLector validarLector(const char mail[], const char password[])
{
    int flag = 0; // ver si ingreso o no correctamente, flag = 0 (incorrecto) y flag = 1 (correcto log in)
    stLector aux;

//    printf("Ingrese su Email: ");
//    fflush(stdin);
//    gets(mail);
//
//    printf("Ingrese su contrase�a: ");
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

void menuLector()
{
    printf("\t\t\t+=========================+=========================+\n");
    printf("\t\t\t|                 MENU DE LECTORES                  |\n");
    printf("\t\t\t+=========================+=========================+\n");
    printf("    1. Registrarse.     \n");
    printf("    2. Login/Entrar.    \n");
    printf("    3. Ver mi Perfil.   \n");
    printf("    4. Ver lista de libros. \n");
    printf("    5. Mostrar libro(Caracteristicas).   \n");
    printf("    6. Marcar como favorito un libro.\n");
    printf("    7. Desmarcar como favorito un libro.\n");
    printf("    8. Ver mis libros favoritos.\n");
    printf("    9. Ver mis libros favoritos.\n");
    printf("   10. Darse de baja de la aplicaci�n.\n\n");
    printf("    0. Salir o Volver al menu principal.\n");

    printf("\n ELIJA UNA OPCI�N: ");
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

    printf("\n ELIJA UNA OPCI�N: ");
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
        printf("\t\t\t+=========================+=========================+\n");
        printf("                            \n\n");
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
        } else
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
        } else
        {
            printf("No se encuentra el ID del lector.\n");
        }
        printf(">>> Se ha modificado con �xito.\n");
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
        } else
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
        } else
        {
            printf("No se encuentra el ID del libro.\n");
        }
        printf(">>> Se ha modificado con �xito.\n");
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
//    registrarLector(&lectores[0]);



    mostrarArchivo_Lectores();





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Repito el programa hasta que decida salir
    while (option !='s' && option!='S')
    {
//        system("cls");
        int usuario = menu_inicio();
        if(usuario == 1)
        {
                                        // Sistema lector
            stLector Lector_actual;
            char user_actual[30];
            char user_password;
            int option_lector;
            menuLector();
        }
        else
        {
            printf("\t\t\t+=========================+=========================+\n");
            printf("\t\t\t|               MENU DEL ADMINISTRADOR              |\n");
            printf("\t\t\t+=========================+=========================+\n");
            int reintentarAdministrador = 's';
            while (reintentarAdministrador == 's' || reintentarAdministrador == 'S')
            {
                printf("Iniciar sesi�n: \n\n");
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
                    printf(">>                          Ha ingresado un usuario o contrase�a incorrecta.\n");
                    printf("�Desea reintentar? s/n. ");
                    fflush(stdin);
                    scanf("%c", &reintentarAdministrador);
                }
            }
        }
        printf("�Desea salir? s/n. ");
        fflush(stdin);
        scanf("%c", &option);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    printf("\n\n>>>                         Fin programa!\n");
    return 0;
}


int menu_inicio()
{
    int option;
    printf("\t\t\t+=========================+=========================+\n");
    printf("\t\t\t|               SISTEMA DE BIBLIOTECA               |\n");
    printf("\t\t\t+=========================+=========================+\n");

    do
    {
        printf(" Seleccione una opci�n para continuar.\n");
        printf("    1. Lector.\n");
        printf("    2. Administrador.\n");


        printf("\n ELIJA UNA OPCI�N: ");
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

    printf(">>> Ingrese su contrase�a: ");
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
    FILE * archivo = fopen(archivoLectores, "ab");
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
    printf("  Contrase�a: \t\t\t|  %s\n", lector.password);
    if(lector.activo)
    {
        printf("  Estado Activo: \t\t|  activo (%i) \n", lector.activo);
    }
    else
    {
        printf("  Estado Activo: \t\t|  dado de baja (%i) \n", lector.activo);
    }

    printf("  N� de libros favoritos: \t|  %i\n", lector.validos);
    for(int i = 0; i < lector.validos && i < 10; i++) // i<10 (10 max libros fav)
    {
        printf("  libro favorito %i, \t\t|  codigo: %i \n",i,lector.listaFavoritos[i]);
    }
    printf("+-------------------------------+-------------------------------+\n");
}

void mostrarArchivo_Lectores()
{
    FILE * archivo = fopen(archivoLectores, "rb");
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

int posicionLector_id(const int id)
{
    int indice = -1; // si return -1 significa que no se encuentra
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "a+b");
    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector), 1, archivo) > 0)
        {
            if(aux.id == id)
            {
                indice = ftell(archivo) / sizeof(stLector);
                indice--;
            }
        }
        fclose(archivo);
    } else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
    return indice;
}

void darBajaLector(const int indice)
{
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "r+b"); //leer y modificar
    if(archivo != NULL)
    {
        //Me paro en la posicion del alumno
        fseek(archivo, (indice)*sizeof(stLector), SEEK_SET);
        fread(&aux, sizeof(stLector), 1, archivo );
        fseek(archivo, (indice)*sizeof(stLector), SEEK_SET);    // vuelvo

        if(aux.activo == 1)
        {
        aux.activo =0;
        fwrite(&aux, sizeof(stLector), 1, archivo);
        printf("Baja con �xito.\n");
        } else
        {
        printf("El Lector ya se encuentra dado de baja.\n");
        }

        fclose(archivo);
    } else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
}

void modificarLector(const int indice)
{
    char nombre[30];
    char email[45];
    char password[15];
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "r+b"); //leer y modificar
    if(archivo != NULL)
    {
        //Me paro en la posicion del alumno
        fseek(archivo, (indice)*sizeof(stLector), SEEK_SET);
        fread(&aux, sizeof(stLector), 1, archivo );
        fseek(archivo, (indice)*sizeof(stLector), SEEK_SET);    // vuelvo

        printf("Ingrese el nombre: ");
        fflush(stdin);
        gets(nombre);
        strcpy(aux.nombre, nombre);

        printf("Ingrese el email: ");
        fflush(stdin);
        gets(email);
        strcpy(aux.mail, email);

        printf("Ingrese la contrase�a: ");
        fflush(stdin);
        gets(password);
        strcpy(aux.password, password);

        printf("ID: No puede modificarlo evitar errores.\n");

        int validos = 0;
        const int TECLA_ESC=27;
        int TeclaUsuario=0;
        int i=0;
        while (TeclaUsuario != TECLA_ESC && validos < 10) // validos<10 porque dimension max son 10 libros
        {
            printf("Escriba el c�digo del Libro que desea guardar: ");

            int libro;
            fflush(stdin);
            scanf("%d",&libro);

            aux.listaFavoritos[i]= libro;

            printf("\n>>> Para continuar cargando presione una tecla. \n");
            printf(">>> Para salir presione ESC. \n");
            fflush(stdin);
            TeclaUsuario = getch();

            validos++;
            i++;
        }

        aux.validos = validos;

        do
        {
            printf("Ingrese 1 para activo o 0 para inactivo: \n");
            fflush(stdin);
            scanf("%d",&aux.activo);
        } while(aux.activo!=0 && aux.activo!=1);

        fwrite(&aux, sizeof(stLector), 1, archivo);
        fclose(archivo);
    } else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
}

void leerFavoritos_lector(const int indice)
{
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "rb");
    if(archivo != NULL)
    {
        fseek(archivo,(indice) * sizeof(stLector), SEEK_SET);   // Me paro en el index
        fread(&aux, sizeof(stLector), 1, archivo);              // Leo y se dezplaca

        for(int i=0; i< aux.validos; i++)
        {

            printf("C�digo: %d\n", aux.listaFavoritos[i]);
            printf("Comparar con id de libros y mostrar los nombres.\n");
        }

        fclose(archivo);
    } else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
















