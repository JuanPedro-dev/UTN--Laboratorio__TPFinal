#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define  archivoLectores "archivoLectores.bin"
#define  archivoLibros "archivoLibros.bin"

#include "./utilidades.h"
#include "./lectores.h"
#include "./libros.h"

void registrarLector_Persistencia(stLector * lector)
{
    FILE * archivo = fopen(archivoLectores, "ab");
    if(archivo != NULL)
    {
        fwrite(lector, sizeof(stLector), 1, archivo);
        fclose(archivo);
    }
}

void registrarse_Persistencia()
{
    stLector aux;
    stLector lector;
    char nombre[30];
    char mail[45];
    char password[15];

    FILE * archivo = fopen(archivoLectores, "r+b");
    if(archivo != NULL)
    {
        fseek(archivo, 0, SEEK_END); // me paro en el final
        int bytes = ftell(archivo);
        if(bytes == 0)  // si el archivo estaba vacio no el primer id es 1.
        {
            lector.id = 1;
        }
        else
        {
            fseek(archivo,sizeof(stLector)*-1, SEEK_END);
            fread(&aux, sizeof(stLector), 1, archivo);
            lector.id = (aux.id) + 1;
        }
        printf("Ingrese su nombre: ");
        fflush(stdin);
        gets(nombre);
        strcpy(lector.nombre, nombre);

        printf("Ingrese su email: ");
        fflush(stdin);
        gets(mail);
        strcpy(lector.mail, mail);

        printf("Ingrese la contrase?a: ");
        fflush(stdin);
        gets(password);
        strcpy(lector.password, password);

        printf("Estado: activo (1).\n");
        lector.activo = 1;

        if(comprobarUsuarioRepetido_Persistencia(lector.mail)==0)
        {
            printf("Su ID (autom?tico) es: %d\n", lector.id); // se genera buscando el ultimo y le sumo 1.

            lector.validos = 0;
            const int TECLA_ESC=27;
            int TeclaUsuario=0;
            do
            {
                printf("?Desea cargar un libro? S/N: ");

                fflush(stdin);
                TeclaUsuario = getch();
                printf("\n");
            }
            while (TeclaUsuario !='S' && TeclaUsuario !='s' && TeclaUsuario !='n' && TeclaUsuario !='n');
            int i=0;

            while (TeclaUsuario != TECLA_ESC && TeclaUsuario !='n' && TeclaUsuario !='n'&& lector.validos < 10) // validos<10 porque dimension max son 10 libros
            {
                int idLibroACargar;
                printf("Ingrese el c?digo de su libro favorito: ");
                fflush(stdin);
                scanf("%d", &idLibroACargar);

                if(validarLibro(idLibroACargar)==1)
                {
                    if(validarFavorito_Persistencia(idLibroACargar,lector)==0) //VALIDA QUE NO ESTE CARGADO 2 VECES EL MISMO LIBRO
                    {
                        lector.listaFavoritos[i] = idLibroACargar;
                        lector.validos++;
                        i++;
                    }
                    else
                    {
                        printf("El libro ya se encuentra cargado en favoritos");
                    }
                }
                else
                {
                    printf("Error: no se encuentra ID, el libro no existe.\n");
                }

                printf("?Desea cargar otro libro? S/N: \n");
                fflush(stdin);
                TeclaUsuario = getch();
            }
            if(lector.validos == 10)
            {
                printf("El m?ximo de libros favoritos es 10.\n");
            }

            registrarLector(&lector);
            printf("                Cargado con ?xito!!!!\n");
            fclose(archivo);

        }
        else
        {
            printf("EL Usuario ya se encuentra registrado, elija otro e-mail. ");
        }

    }
    else
    {
        printf("Error: no se pudo abrir el archivo lectores desde registrarse_Persistencia.\n");
    }
    Sleep(2000);
}


int validarLector_Persistencia(const char mail[], const char password[])
{
    int indice = -1; // ver si ingreso o no correctamente, -1 no inicio y != es el indice donde se encuentra.
    stLector aux;

    FILE * archivo = fopen(archivoLectores, "rb");
    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector),1,archivo )>0 &&  indice == -1)
        {
            if (!strcmpi(aux.password, password) && !strcmpi(aux.mail, mail))
            {
                printf("Acceso correcto.\n");
                indice = ftell(archivo) / sizeof(stLector);
                indice--; // resto uno porque al leer me movi un valor y indice comienza en 0 como si fuera un arreglo.
            }
        }
    }
    else
    {
        printf("Error: no se pudo cargar el archivo lectores desde validarLector.\n");
    }
    return indice;
}

void mostrarLector_Persistencia(const stLector lector)
{
    char nombreLibroFavorito[50];
    printf("+-------------------------------+--------------------------------------------------+\n");
    printf("  Nombre: \t\t\t|  %s \n", lector.nombre);
    printf("  Id:   \t\t\t|  %i\n", lector.id);
    printf("  Mail: \t\t\t|  %s\n", lector.mail);
    printf("  Contrase?a: \t\t\t|  %s\n", lector.password);
    if(lector.activo)
    {
        printf("  Estado Activo: \t\t|  activo (%i) \n", lector.activo);
    }
    else
    {
        printf("  Estado Activo: \t\t|  dado de baja (%i) \n", lector.activo);
    }
    printf("  N? de libros favoritos: \t|  %i\n", lector.validos);

    for(int i = 1; i < lector.validos && i < 11; i++) // i < 11 (10 max libros fav)
    {
        devolverNombreLibro(&nombreLibroFavorito,lector.listaFavoritos[i]);
        printf("  Libro favorito %i,   \t\t|  C?digo: %d \tNombre: %s",i,lector.listaFavoritos[i],nombreLibroFavorito);
    }
    printf("+-------------------------------+--------------------------------------------------+\n");
}

void mostrarArchivo_Lectores_Persistencia()
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

int posicionLector_id_Persistencia(const int id)
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
    }
    else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
    return indice;
}

void darBajaLector_Persistencia(const int indice)
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
            printf("Baja con ?xito.\n");
        }
        else
        {
            printf("El Lector ya se encuentra dado de baja.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo cargar el archivo lectores en darBajaLector.\n");
    }
}

void modificarLector_Persistencia(const int indice)
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
        mostrarLector(aux);
        printf("Ingrese el nombre: ");
        fflush(stdin);
        gets(nombre);
        strcpy(aux.nombre, nombre);

        printf("Ingrese el email: ");
        fflush(stdin);
        gets(email);
        strcpy(aux.mail, email);

        printf("Ingrese la contrase?a: ");
        fflush(stdin);
        gets(password);
        strcpy(aux.password, password);

        printf("ID: autom?tico: .\n", aux.id);

        int validos = 0;
        const int TECLA_ESC=27;
        int TeclaUsuario=0;

        do
        {
            printf("?Desea cargar un libro? S/N: ");

            fflush(stdin);
            TeclaUsuario = getch();
            printf("\n");
        }
        while (TeclaUsuario !='S' && TeclaUsuario !='s' && TeclaUsuario !='n' && TeclaUsuario !='N');

        int i=0;
        while (TeclaUsuario != TECLA_ESC && TeclaUsuario !='n' && TeclaUsuario !='N'&& validos < 10) // validos<10 porque dimension max son 10 libros
        {
            int idLibroACargar;
            printf("Ingrese el c?digo de su libro favorito: ");
            fflush(stdin);
            scanf("%d", &idLibroACargar);

            if(validarLibro(idLibroACargar) == 1)
            {
                if(validarFavorito_Persistencia(idLibroACargar,aux)==0)
                {
                    aux.listaFavoritos[validos+1] = idLibroACargar;
                    validos++;
                    i++;
                }
                else
                {
                    printf("El libro ya se encuentra cargado ");
                }
            }
            else
            {
                printf("Error: no se encuentra ID, el libro no existe.\n");
            }
            printf("?Desea cargar otro libro? S/N: \n");
            fflush(stdin);
            TeclaUsuario = getch();
        }

        if(validos == 10)
        {
            printf("El m?ximo de libros favoritos es 10.\n");
        }

        aux.validos = validos;

        do
        {
            printf("Ingrese 1 para activo o 0 para inactivo: ");
            fflush(stdin);
            scanf("%d",&aux.activo);
        }
        while(aux.activo!=0 && aux.activo!=1);

        fwrite(&aux, sizeof(stLector), 1, archivo);
        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo cargar el archivo.\n");
    }
}


void leerFavoritos_lector_Persistencia(const int indice)
{
    stLector aux;
    FILE * archivo = fopen(archivoLectores, "rb");
    if(archivo != NULL)
    {
        fseek(archivo,(indice) * sizeof(stLector), SEEK_SET);   // Me paro en el index
        fread(&aux, sizeof(stLector), 1, archivo);              // Leo y se dezplaca

        for(int i=0; i< aux.validos; i++)
        {
            char nombreLibro[50];
            devolverNombreLibro(&nombreLibro,aux.listaFavoritos[i]);
            printf("C?digo: %d \tNombre: %s", aux.listaFavoritos[i],nombreLibro);
        }
        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

stLector devolverUsuario_Persistencia(int indice)
{
    stLector aux;
    int flag = 0;
    FILE * archivo = fopen(archivoLectores, "rb");
    if(archivo != NULL)
    {
        while(fread(&aux, sizeof(stLector), 1, archivo) > 0 && flag==0)
        {
            if(indice == aux.id)
            {
                flag = 1;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo lectores en devolverUsuario.\n");
    }
    return aux;
}


void lector_case_Persistencia(const int option, int *indice, stLector * lector_actual)
{
    char mail[45];
    char password[15];
    stLector auxi;

    switch(option)
    {
    case 1:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|              REGISTRARSE COMO LECTOR              |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        registrarse();
        break;
    case 2:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  INICIAR SESI?N                   |\n");
        printf("\t\t\t+=========================+=========================+\n\n");

        printf("Ingrese su mail: ");
        fflush(stdin);
        gets(mail);

        printf("Ingrese su contrase?a: ");
        fflush(stdin);
        gets(password);

        *indice = validarLector(mail, password);

        if(*indice == -1)
        {
            printf("Error: el mail o su contrase?a son incorrectas.\n");
        }
        else
        {
            auxi = devolverUsuario_Persistencia(*indice);
            lector_actual->activo = auxi.activo;
            lector_actual->id = auxi.id;
            lector_actual->validos = auxi.validos;
            strcpy(lector_actual->nombre, auxi.nombre);
            strcpy(lector_actual->mail, auxi.mail);
            strcpy(lector_actual->password, auxi.password);
            for(int i=0; i < lector_actual->validos; i++)
            {
                lector_actual->listaFavoritos[i] = auxi.listaFavoritos[i];
            }
        }
        Sleep(1200);
        break;
    case 3:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                PERFIL DEL USUARIO                 |\n");
        printf("\t\t\t+=========================+=========================+\n\n");

        if((*indice) == -1)
        {
            printf("Debe loguearse primero para ver su perfil.\n\n");
        }
        else
        {
            mostrarLector(*lector_actual);
        }
        system("pause");
        break;
    case 4:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                  LISTA DE LIBROS                  |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        mostrarLibros();
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|               FIN LISTA DE LIBROS                 |\n");
        printf("\t\t\t+=========================+=========================+\n");
        system("pause");
        break;
    case 5:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|           CARACTERISTICA DE UN LIBRO              |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        mostrarLibro();
        system("pause");
        break;
    case 6:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|              AGREGAR LIBRO A FAVORITOS            |\n");
        printf("\t\t\t+=========================+=========================+\n\n");

        if((*indice) == -1)
        {
            printf("Debe loguearse primero.\n\n");
        }
        else
        {
            agregarFavorito(*lector_actual);
            *lector_actual=devolverUsuario_Persistencia(*indice);
        }
        system("pause");
        break;
    case 7:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|               QUITAR LIBRO A FAVORITOS            |\n");
        printf("\t\t\t+=========================+=========================+\n\n");

        quitarLibro(*indice);
        *lector_actual = devolverUsuario_Persistencia(*indice);

        system("pause");
        break;
    case 8:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|              FAVORITOS DEL USUARIO                |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        if(*indice == -1)
        {
            printf("Primero inicie sesi?n.\n");
        }
        else
        {
            leerFavoritos_lector(*indice);
        }
        system("pause");
        break;
    case 9:
        system("cls");
        printf("\t\t\t+=========================+=========================+\n");
        printf("\t\t\t|                   DARSE DE BAJA                   |\n");
        printf("\t\t\t+=========================+=========================+\n\n");
        bajaLector(*indice);
        *lector_actual = devolverUsuario_Persistencia(*indice);
        system("pause");
        break;
    }
}

void agregarFavorito_Persistencia(stLector lector)
{
    int indiceLector = posicionLector_id(lector.id);
    int favoritoNuevo;
    printf("Ingrese el ID del libro para agregar a favoritos: ");
    fflush(stdin);
    scanf("%d",&favoritoNuevo);
    if(validarLibro_Persistencia(favoritoNuevo)==1) //VALIDA QUE SEA UN LIBRO QUE EXISTA EN ARCHIVOLIBROS.BIN
    {
        int comprobarRepetido = validarFavorito_Persistencia(favoritoNuevo,lector);
        if(comprobarRepetido == 0)//NO ESTA REPETIDO
        {
            if(lector.validos+1 < 11) // COMPRUEBA QUE NO SE HAYA LLEGADO AL LIMITE DE 10 LIBROS
            {
                lector.listaFavoritos[lector.validos]=favoritoNuevo;
                lector.validos=lector.validos+1;
                actualizarRegistroLector_Persistencia(lector,indiceLector);
                printf("Favorito Guardado! ");
            }
            else
            {
                printf("Se lleg? al limite de 10 libros, debe eliminar al menos 1 ");
            }
        }
        else
        {
            printf("El libro ya se encuentra cargado ");
        }
    }
    else if(validarLibro_Persistencia(favoritoNuevo)==0)
    {
        printf("El libro no existe ");
    }
    else
    {
        printf("El libro no se encuentra disponible");
    }
//    printf("\n");
//    system("pause");
}

//COMPRUEBA SI EL LIBRO A CARGAR YA SE ENCUENTRA CARGADO
int validarFavorito_Persistencia(int libroFavorito, stLector lector)
{
    int flagRepetido=0;

    for(int x=0; x<lector.validos; x++)
    {
        if(lector.listaFavoritos[x]==libroFavorito)
        {
            flagRepetido=1;
        }

    }
    return flagRepetido;
}

//SOBREESCRIBE EL REGISTRO DEL USUARIO INDICADO POR EL INDICE
void actualizarRegistroLector_Persistencia(stLector lector, int indiceLector)
{
    FILE* archivo=fopen(archivoLectores,"r+b");
    if(archivo!=NULL)
    {
        fseek(archivo,sizeof(stLector)*indiceLector,SEEK_SET);
        fwrite(&lector,sizeof(lector),1,archivo);
        fclose(archivo);
    }
    else
    {
        printf("No se pudo acceder al archivo de registros de usuarios ");
    }

}


void quitarLibro_Persistencia(int indice)
{
    FILE * archivo = fopen(archivoLectores, "r+b");
    if(archivo!=NULL)
    {
        if(indice != -1)
        {
            stLector lector;
            int codigo;
            fseek(archivo, indice*sizeof(lector), SEEK_CUR);
            fread(&lector, sizeof(lector), 1, archivo);
            printf("Libros favoritos del lector actual: \n\n");
            leerFavoritos_lector(indice);

            printf("\n >>Ingrese el c?digo del libro para remover: ");
            scanf("%d", &codigo);
            int flag = 0;


            for(int i=0; i < lector.validos && flag == 0; i++)
            {
                if(codigo == lector.listaFavoritos[i])
                {
                    for(int j=i; j<lector.validos; j++)
                    {
                        lector.listaFavoritos[j] = lector.listaFavoritos[j+1];
                    }
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                printf("Error: no se encuentra entre sus favoritos.\n\n");
            }
            else
            {
                printf("Se removio con ?xito.\n\n");
            }
            lector.validos--;
            fseek(archivo, -1 * sizeof(lector), SEEK_CUR);
            fwrite(&lector, sizeof(lector),1,archivo);

        }
        else
        {
            printf(">> Primero debe loguearse.\n");
        }
        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo lectores en quitarLibro()\n");
    }
}

void bajaLector_persistencia(int indice)
{
    FILE * archivo = fopen(archivoLectores, "r+b");
    if(archivo!=NULL)
    {
        if(indice != -1)
        {
            stLector lector;
            fseek(archivo, indice*sizeof(lector), SEEK_CUR);
            fread(&lector, sizeof(lector), 1, archivo);

            if(lector.activo == 0)
            {
                printf("Ud ya se encuentra dado de baja.\n\n");
            }
            else
            {
                lector.activo = 0;
                printf("Dado de Baja con ?xito.\n\n");
            }

            fseek(archivo, -1 * sizeof(lector), SEEK_CUR);
            fwrite(&lector, sizeof(lector),1,archivo);
        }
        else
        {
            printf(">> Primero debe loguearse.\n");
        }
        fclose(archivo);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo lectores en quitarLibro()\n");
    }
}


int comprobarUsuarioRepetido_Persistencia(char mail[45])
{
    int encontrado=0;
    FILE* archivo=fopen(archivoLectores,"rb");
    if(archivo!=NULL)
    {
        stLector buffer;

        while(fread(&buffer,sizeof(buffer),1,archivo)> 0 && encontrado==0)
        {
            if(strcmpi(buffer.mail,mail)==0)
            {
                encontrado=1;
            }
        }
    }
    else
    {
        printf("No se pudo comprobar el usuario, no se pudo acceder al archivo de lectores");
    }

    return encontrado;
}
