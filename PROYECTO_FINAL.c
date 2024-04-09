#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <regex.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#ifdef __linux__
    #include <stdio_ext.h>
#endif

struct Direcciones_Fecha
{
    char direccion[200];
    char correo_electronico[30];// @ y punto despues
    int anio, mes, dia; //  >=1950, 1-12 inclusive
};

struct Datos_Articulos
{
    int numero_articulo, numero_proveedor, punto_reorden; // Mayor a cero, proveedores a lo mucho 10
    char descripcion_articulo[200]; // Validar letras, numeros, espacios
    long int inventario; //Mayor o igual a cero
    double precio_compra, precio_venta;
};

struct Datos_Proveedores
{
    struct Direcciones_Fecha datos;
    int numero_proveedor; //mayor a cero
    char nombre_proveedor[50], rfc[13]; // Letras, espacios; 13 caracteres
    char correo_electronico[30];// @ y punto despues
    int anio, mes, dia; //  >=1950, 1-12 inclusive
    char direccion_proveedor[200]; //letras, espacios, numeros
    double descuento, saldo_por_pagar; // Campo calculado
};

struct Datos_Clientes
{
    struct Direcciones_Fecha datos;
    int numero_cliente; // Mayor a cero
    char nombre_cliente[50], rfc[13]; // Letras, espacios
    double descuento_cliente; // 0 - 1
};

struct Datos_Empleados
{
    struct Direcciones_Fecha datos;
    int numero_empleado; // 1000 - 10000
    char nombre_empleado[50]; // Letras, espacios
};

struct Contador_Datos
{
    int *articulos_neto, *clientes_neto;
    int *empleados_neto, *proveedores_neto;

};

struct Conjunto_Datos
{
    struct Datos_Articulos data_articulos;
    struct Datos_Clientes data_clientes;
    struct Datos_Empleados data_empleados;
    struct Datos_Proveedores data_proveedores;

};

struct Files_Requeridos
{
    FILE *file_articulos;
    FILE *file_clientes;
    FILE *file_proveedor;
    FILE *file_empleados;
};

//FUNCIONES PRINCIPALES

void capturar_articulos(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
void capturar_empleados(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
void capturar_clientes(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
void capturar_proveedores(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
void controlar_ventas();
void controlar_compras();

// VALIDACIONES

void convertir_cadena_a_minuscula(char *);
bool verificar_existencia_claves(FILE *, struct Conjunto_Datos *, int *);
bool verificar_datos_existencia(FILE *, struct Contador_Datos *, int *, int *);
bool verificar_existencia_proveedor(FILE *, struct Datos_Proveedores *, int *, const char *);
bool buscar_proveedores(FILE *, struct Datos_Proveedores *, int *, const char *);
bool validar_cadenas(char *);


// FUNCIONES PARA EL SISTEMA

void validar_errores_por_SO();
void limpiar_buffer_STDIN();
void limpiar_terminal();
void pausar_terminal();

int main(void)
{
    struct Files_Requeridos files;
    struct Conjunto_Datos datos_struct;
    struct Contador_Datos datos;
    char *ruta_file_articulos, *ruta_file_empleados, *ruta_file_clientes, *ruta_file_proveedores;
    int total_articulos = 0, total_clientes = 0, total_proveedores = 0, total_empleados = 0;
    int opcion;

    setlocale(LC_ALL, "es_MX.UTF-8");

    ruta_file_articulos = malloc(sizeof(char ) * 1000);
    ruta_file_clientes = malloc(sizeof(char ) * 1000);
    ruta_file_empleados = malloc(sizeof(char ) * 1000);
    ruta_file_proveedores = malloc(sizeof(char ) * 1000);

    getcwd( ruta_file_articulos, sizeof( ruta_file_articulos ) * 1000 );
    strcat( ruta_file_articulos, "/Files_muebleria/articulos.dat" );

    getcwd( ruta_file_clientes, sizeof( ruta_file_clientes ) * 1000);
    strcat( ruta_file_clientes, "/Files_muebleria/clientes.dat");

    getcwd( ruta_file_empleados, sizeof( ruta_file_empleados ) * 1000);
    strcat( ruta_file_empleados, "/Files_muebleria/empleados.dat");

    getcwd( ruta_file_proveedores, sizeof( ruta_file_proveedores ) * 1000);
    strcat( ruta_file_proveedores, "/Files_muebleria/proveedores.dat");

    files.file_articulos =  fopen( ruta_file_articulos, "rb" );
    files.file_clientes = fopen( ruta_file_clientes, "rb" );
    files.file_empleados = fopen( ruta_file_empleados, "rb" );
    files.file_proveedor = fopen( ruta_file_proveedores, "rb" );

    if (files.file_articulos == NULL || 
        files.file_clientes == NULL || 
        files.file_empleados == NULL || 
        files.file_proveedor == NULL)
    
        fprintf(stderr, "Error de apertura con los archivos\n");
    
    else
    {
        fclose(files.file_articulos);
        fclose(files.file_clientes);
        fclose(files.file_empleados);
        fclose(files.file_proveedor);

        datos.articulos_neto = &total_articulos;
        datos.clientes_neto = &total_clientes;
        datos.empleados_neto = &total_empleados;
        datos.proveedores_neto = &total_proveedores;

        do
        {
            do
            {
                limpiar_terminal();

                puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
                printf("\n* *%45s%28s\n\n", "MENÚ DE OPCIONES", "* *");
                puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
                puts("1) Articulos");
                puts("2) Clientes");
                puts("3) Empleados");
                puts("4) Proveedores");
                puts("5) Ventas");
                puts("6) Compras");
                puts("7) Control de inventario");
                puts("8) Reportes");
                puts("9) Salir");
                printf("%10s: ", "Opcion");

                limpiar_buffer_STDIN();

                scanf("%d", &opcion);

                if (opcion < 1 || opcion > 9)
                
                    validar_errores_por_SO();

            } while (opcion < 1 || opcion > 9);

            switch (opcion)
            {
                case 1:
                    if (total_articulos < 100 && verificar_existencia_proveedor(files.file_proveedor, &datos_struct.data_proveedores, datos.proveedores_neto, ruta_file_proveedores))
                    {
                        capturar_articulos(&files, &datos_struct, &total_articulos, ruta_file_articulos);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 2:
                    if (false)
                    {
                        capturar_clientes(&files, &datos_struct, &total_clientes, ruta_file_clientes);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 3:
                    if (total_empleados < 20)
                    {
                        capturar_empleados(&files, &datos_struct, &total_empleados, ruta_file_empleados);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 4:
                    if (false)
                    {
                        capturar_proveedores(&files, &datos_struct, &total_proveedores, ruta_file_proveedores);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 5:
                    if (false)
                    {
                        /* code */
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 6:
                    if (false)
                    {
                        /* code */
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 7:
                    if (false)
                    {
                        /* code */
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 8:
                    if (false)
                    {
                        /* code */
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 9:
                    free(ruta_file_articulos);
                    free(ruta_file_clientes);
                    free(ruta_file_empleados);
                    free(ruta_file_proveedores);
                break;
            }

            if (opcion != 9)
            
                pausar_terminal();
            
        } while (opcion != 9);

        limpiar_terminal();
        puts("Operación finalizada con éxito");
    }
    

}

void capturar_articulos(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *articulos_registrados, const char *ruta_articulos_file)
{
    char respuesta[3];
    bool descripcion_correcta;
    int i;

    archivos->file_articulos = fopen(ruta_articulos_file, "rb+");

    if (archivos->file_articulos == NULL)
    
        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE ARTICULOS");
    
    else
    {
        do
        {
            limpiar_terminal();

            printf("Desea agregar artículos? Si/No: ");
            limpiar_buffer_STDIN();
            fgets(respuesta, 3, stdin);

            respuesta[strcspn(respuesta, "\n")] = '\0';
            
            convertir_cadena_a_minuscula(respuesta);

            if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0)
            
                validar_errores_por_SO();
            
        } while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0);
        
        while (strcmp(respuesta, "si") == 0 && *articulos_registrados < 100)
        {
            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Número de artículo: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_articulos.numero_articulo) != 1);
                
                if (data->data_articulos.numero_articulo <= 0 || data->data_articulos.numero_articulo > 100)
                
                    validar_errores_por_SO();
                
            } while (data->data_articulos.numero_articulo <= 0);

            do
            {
                descripcion_correcta = false;

                limpiar_terminal();

                printf("Descripción del artículo: ");
                limpiar_buffer_STDIN();
                fgets(data->data_articulos.descripcion_articulo, 200, stdin);

                data->data_articulos.descripcion_articulo[strcspn(data->data_articulos.descripcion_articulo, "\n")] = '\0';

                if (strlen(data->data_articulos.descripcion_articulo) > 0)
                
                    descripcion_correcta = validar_cadenas(data->data_articulos.descripcion_articulo);

            } while (strlen(data->data_articulos.descripcion_articulo) == 0 || !descripcion_correcta);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Agrega un punto de reorden: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_articulos.punto_reorden) != 1);
                
                if (data->data_articulos.punto_reorden <= 0)
                
                    validar_errores_por_SO();
                
            } while (data->data_articulos.punto_reorden <= 0);
            
            //iterar 10?
            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Cuántos hay en existencia en el inventario?: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%ld", &data->data_articulos.inventario) != 1);
                
                if (data->data_articulos.inventario < 0)
                
                    validar_errores_por_SO();
                
            } while (data->data_articulos.inventario < 0);
            
        }

        fclose(archivos->file_articulos);
    }
    
    


}

void capturar_clientes(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *clientes_registrados, const char *ruta_clientes_file)
{



}

void capturar_empleados(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *empleados_registrados, const char *ruta_empleados_file)
{
    


}


void capturar_proveedores(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *proveedores_registrados, const char *ruta_proveedores_file)
{



}

void controlar_ventas()
{



}

void controlar_compras()
{



}



void convertir_cadena_a_minuscula(char *caracter)
{
    while (*caracter != '\0')
    {
        *caracter = tolower(*caracter);
        caracter++;
    }
}

bool verificar_datos_existencia(FILE *, struct Contador_Datos *, int *, int *)
{



}


bool verificar_existencia_proveedor(FILE *archivo_proveedores, struct Datos_Proveedores *data, int *proveedores_totales, const char *directorio_proveedores)
{
    archivo_proveedores = fopen(directorio_proveedores, "rb");

    if (archivo_proveedores == NULL)
    {
        fprintf(stderr, "ERROR! ARCHIVO PROVEEDORES NO ES ACCESIBLE DE MOMENTO. . .");
        return false;
    }
    else
    {
        int contador = 0;

        rewind(archivo_proveedores);

        while (fread(data, sizeof(struct Datos_Proveedores), 1, archivo_proveedores) == 1)
        {
            if (data->numero_proveedor != 0)
            {
                contador++;
                *proveedores_totales = contador;
            }
        }
        
        if (*proveedores_totales == 0)
        {
            printf("NO HAY PROVEEDORES DE ARTÍCULOS, EN EXISTENCIA. . .");
            return false;
        }
        return true;
    }
    
}

bool validar_cadenas(char *caracter)
{
    while (*caracter != '\0')
    {
        if (!isalnum(*caracter) && *caracter != 32)
        
            return false;
        
        caracter++;
    }
    
    return true;
}

// Limpia buffer STDIN tanto para sistemas Windows como para UNIX/Linux
void limpiar_buffer_STDIN()
{
    #if defined(_WIN32) || defined(_WIN64)
        rewind(stdin);
    #elif __linux__
        __fpurge(stdin);
    #endif
}

// Limpia terminal tanto para sistemas Windows como para UNIX/Linux
void limpiar_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

// Pausa la terminal tanto para sistemas Windows como para UNIX/Linux
void pausar_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("pause");
    #elif __linux__
        printf("Presiona ENTER para continuar. . .");
        fflush(stdout);
        limpiar_buffer_STDIN();
        getchar();
    #endif
}

// Clasifica los mensajes de error tanto para Windows como para UNIX/Linux, cuando se ingresan datos incorrectos
void validar_errores_por_SO()
{
    #if defined(_WIN32) || defined(_WIN64)
        limpiar_terminal();

        printf("Dato/s ingresado/s no válido/s, verificar dato/s\n");
        pausar_terminal();
        limpiar_terminal();
    #elif __linux__
        limpiar_terminal();

        printf("Dato/s ingresado/s no válido/s, verificar dato/s\n");
        fflush(stdout);
        
        pausar_terminal();
        limpiar_terminal();
    #endif
}