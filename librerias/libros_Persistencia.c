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

//Muestra todos los libros
void mostrarLibros_Persistencia()
{
    stLibro buffer;
    int librosFavoritos[10];

    FILE* archivo=fopen(archivoLibros,"rb");
    if(archivo!=NULL)
    {
        int posicionFavoritos=0;
        while((fread(&buffer,sizeof(stLibro),1,archivo))>0)
        {
            printf("ID: %d \n",buffer.id);
            printf("Nombre: %s",buffer.nombre);
            printf("Autor: %s",buffer.autor);
            printf("Genero: %s",buffer.genero);
            printf("Activo: %i\n\n",buffer.activo);
        }
    }
}
void devolverNombreLibro_Persistencia(char* nombre[50], int idABuscar)
{
    int encontrado=0;
    stLibro buffer;
    FILE* archivo=fopen(archivoLibros,"rb");
    if(archivo!=NULL)
    {
        while((fread(&buffer,sizeof(stLibro),1,archivo))>0 && encontrado==0)
        {
            if(buffer.id==idABuscar)
            {
                strcpy(nombre,buffer.nombre);
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de libros ");
    }
    fclose(archivo);
}


stLibro creaLibro_Persistencia()
{

    stLibro nuevoLibro;

    char tituloNuevo[50];

    nuevoLibro.id=ultimoId_Persistencia()+1;
    printf("Ingrese el titulo: ");

    fflush(stdin);
    fgets(tituloNuevo,50,stdin);

    if((compruebaLibro_Persistencia(tituloNuevo)==1))
    {
        printf("El libro ya se encuentra registrado \n");
        nuevoLibro.activo=0;
    }
    else
    {
        strcpy(nuevoLibro.nombre,tituloNuevo);
        printf("Ingrese el autor: ");
        fflush(stdin);
        fgets(nuevoLibro.autor,30,stdin);
        printf("Ingrese el genero: ");
        fflush(stdin);
        fgets(nuevoLibro.genero,15,stdin);
        nuevoLibro.activo=1;
    }

    return nuevoLibro;
}


void crearLibros_Persistencia()
{
    stLibro nuevoLibro={.id=0,.nombre="",.genero="",.autor="",.activo=0};
    stLibro limpiaLibro={.id=0,.nombre="",.genero="",.autor="",.activo=0};

    char opc;
    do
    {
        nuevoLibro=creaLibro_Persistencia();
        if(nuevoLibro.activo!=0)
        {
            guardaLibro_Persistencia(nuevoLibro);
        }
        printf("?Desea agregar otro libro? S: Salir, Intro: Continuar. ");
        opc=getchar();
        fflush(stdin);
        nuevoLibro=limpiaLibro;
    }while(opc!='s' && opc!='S');
}

void guardaLibro_Persistencia(stLibro libro)
{
    if(libro.activo==1)
    {
        FILE* archivo=fopen(archivoLibros,"ab");
        if(archivo!=NULL)
        {
            fwrite(&libro,sizeof(stLibro),1,archivo);
        }
        else
        {
            printf("No se pudo abrir el archivo de libros \n");
        }
        fclose(archivo);
    }
}


int ultimoId_Persistencia()
{
    int iDLibro=0;
    stLibro buffer;


    FILE* archivoDeLibros=fopen(archivoLibros,"rb");
    if(archivoDeLibros!=NULL)
    {
        while((fread(&buffer,sizeof(stLibro),1,archivoDeLibros))>0)
        {
            iDLibro=buffer.id;
        }
    }

    fclose(archivoDeLibros);

    return iDLibro;
}

int compruebaLibro_Persistencia(char nombrePropuesto[50])
{

    int duplicado=0;

    stLibro libro;
    FILE* archivo=fopen(archivoLibros,"rb");
    if(archivo!=NULL)
    {
        while((fread(&libro,sizeof(stLibro),1,archivo))>0)
        {

            if((strcmpi(nombrePropuesto,libro.nombre))==0)
            {
                duplicado=1;
            }
        }
        fclose(archivo);
    }
    else
    {
        duplicado=-1;
    }

    return duplicado;
}

void editarLibro_Persistencia()
{
    int posicion;
    char opc='a';
    int idABuscar;
    stLibro libro;
    stLibro libroEditado;
    stLibro limpiaLibro={.id=0,.nombre="",.autor="",.genero="",.activo=1};
    do
    {
        printf(" Ingrese el ID del libro a editar:  ");
        scanf("%i",&idABuscar);
        posicion=buscarPosicionLibro_Persistencia(idABuscar);
        if(posicion>=0)
        {
            FILE* archivo=fopen(archivoLibros,"r+b");
            if(archivo!=NULL)
            {
                fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
                fread(&libro,sizeof(stLibro),1,archivo);
                libroEditado.id=libro.id;

                printf(" \n Nombre: %s Ingrese el nuevo titulo. O presione Intro para mantener el actual: ",libro.nombre);
                fflush(stdin);
                fgets(libroEditado.nombre,50,stdin);

                if(libroEditado.nombre[0]=='\n')
                {
                    strcpy(libroEditado.nombre,libro.nombre);
                }
                printf(" Autor: %s Ingrese el nuevo autor (Intro: mantener el actual): ",libro.autor);
                fflush(stdin);
                fgets(libroEditado.autor,30,stdin);

                if(libroEditado.autor[0]=='\n')
                {
                    strcpy(libroEditado.autor,libro.autor);
                }

                printf(" Genero: %s Ingrese el nuevo genero (Intro: mantener el actual): ",libro.genero);
                fflush(stdin);
                fgets(libroEditado.genero,15,stdin);

                if(libroEditado.genero[0]=='\n')
                {
                    strcpy(libroEditado.genero,libro.genero);
                }
                int estado;
                do
                {
                    printf(" Activo: %i \n Ingrese el nuevo estado: 1: Activo, 0: Inactivo (Intro: mantener el actual) ",libro.activo);
                    fflush(stdin);
                    estado=getchar();

                    if(estado!=48 && estado!=49 && estado!=10)
                    {
                        printf(" Opci?n invalida! \n");
                    }
                }while(estado!=48 && estado!=49 && estado!=10); //VALORES ASCII 0=48 1=49 10=Intro
                if(estado==48)
                {
                    libroEditado.activo=0;
                }
                else if(estado==10)
                {
                    libroEditado.activo=libro.activo;
                }
                else
                {
                    libroEditado.activo=1;
                }
                fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
                fwrite(&libroEditado,sizeof(stLibro),1,archivo);
            }
            else
            {
                printf("No se pudo abrir el archivo de libros ");
            }
            fclose(archivo);
        }
        else
        {
            printf("No se encontro el libro con el ID indicado. \n\n");
        }


    printf("?Desea editar otro libro?: S: Salir, Intro: Continuar ");
    fflush(stdin);
    opc=getchar();
    libroEditado=limpiaLibro;
    }while(opc!='s' && opc!='S');
}

int buscarPosicionLibro_Persistencia(int idABuscar)
{
    int posicion=-1;
    stLibro buffer;
    FILE* archivo=fopen(archivoLibros,"rb");
    if(archivo!=NULL)
    {
        while((fread(&buffer,sizeof(stLibro),1,archivo))>0 && posicion==-1)
        {
            if(buffer.id==idABuscar)
            {
                posicion=ftell(archivo)/sizeof(stLibro);
                posicion--;
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de libros ");
    }
    fclose(archivo);
    return posicion;
}

void borrarLibros_Persistencia()
{
    int posicion;
    int idABorrar;
    stLibro libroTemp;
    char opc='a';
    do
    {

        printf("Ingrese el ID a borrar: ");
        scanf("%d",&idABorrar);
        posicion=buscarPosicionLibro_Persistencia(idABorrar);
        if(posicion==-1)
        {
            printf("No se encontr? el ID del libro. \n ");
        }
        else
        {
            FILE* archivo=fopen(archivoLibros,"r+b");
            fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
            fread(&libroTemp,sizeof(stLibro),1,archivo);
            if(libroTemp.activo == 1)
            {
                fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
                libroTemp.activo=0;
                fwrite(&libroTemp,sizeof(stLibro),1,archivo);
                printf("Baja con ?xito.\n");

            }
            else

            {
                printf("El libro ya se encuentra dado de baja \n");
            }
            fclose(archivo);
        }

    printf("?Desea dar de baja otro libro? S: Salir, Intro: Continuar. ");
    fflush(stdin);
    opc=getchar();
    }while(opc!='s' && opc!='S');
}

int validarLibro_Persistencia(int idABuscar) //0 no encontrado, 1 encontrado -1 no disponible
{
    int encontrado=0;
    stLibro buffer;
    FILE* archivo=fopen(archivoLibros,"rb");
    if(archivo!=NULL)
    {
        while((fread(&buffer,sizeof(stLibro),1,archivo))>0 && encontrado==0)
        {
            if(buffer.id == idABuscar)
            {
                if(buffer.activo==1)
                {
                    encontrado = 1;
                }
                else
                {
                    encontrado =-1;
                }
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de libros ");
    }
    fclose(archivo);
    return encontrado;
}

void mostrarLibro_Persistencia()
{
    int idLibroAMostrar;
    printf("Ingrese el ID del libro a visualizar: ");
    scanf("%d",&idLibroAMostrar);
    if(validarLibro_Persistencia(idLibroAMostrar)!=0)
    {
        FILE* archivo=fopen(archivoLibros,"rb");
        if(archivo!=NULL)
        {
            stLibro buffer;
            int flagEncontrado=0;

            while(fread(&buffer,sizeof(buffer),1,archivo)>0&&flagEncontrado==0)
            {
                if(buffer.id==idLibroAMostrar)
                {
                    printf("ID: %d \n",buffer.id);
                    printf("Nombre: %s",buffer.nombre);
                    printf("Autor: %s",buffer.autor);
                    printf("Genero: %s",buffer.genero);
                    if(buffer.activo==1)
                    {
                        printf("Estado: Disponible \n");
                    }
                    else
                    {
                        printf("Estado: No disponible \n");
                    }

                    flagEncontrado=1;
                }
            }
            fclose(archivo);
        }
        else
        {
            printf("No se pudo abrir el archivo de libros.\n");
        }
    }
    else
    {
        printf("No se encontr? el libro indicado ");
    }
}

void darDeAltaLibros_Persistencia()
{
    int posicion;
    int idABorrar;
    stLibro libroTemp;
    char opc='a';
    do
    {

        printf("Ingrese el ID del Libro a dar de alta: ");
        scanf("%d",&idABorrar);
        posicion=buscarPosicionLibro_Persistencia(idABorrar);
        if(posicion==-1)
        {
            printf("No se encontr? el ID del libro. \n");
        }
        else
        {
            FILE* archivo=fopen(archivoLibros,"r+b");
            fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
            fread(&libroTemp,sizeof(stLibro),1,archivo);
            if(libroTemp.activo == 0)
            {
                fseek(archivo,posicion*sizeof(stLibro),SEEK_SET);
                libroTemp.activo=1;
                fwrite(&libroTemp,sizeof(stLibro),1,archivo);
                printf("El libro ha sido dado de alta. \n");
            }
            else
            {
                printf("El libro ya se encuentra dado de alta. \n");
            }
            fclose(archivo);
        }
        printf("?Desea dar de alta otro libro? S: Salir, Intro: Continuar. ");
        fflush(stdin);
        opc=getchar();
    }
    while(opc!='s' && opc!='S');
}
