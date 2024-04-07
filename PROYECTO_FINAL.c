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
    char descripcion_articulo[100]; // Validar letras, numeros, espacios
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
//FUNCIONES PRINCIPALES
void capturar_articulos(FILE *, struct Datos_Articulos *, int *, const char *);
void capturar_empleados(FILE *, struct Datos_Empleados *, int *, const char *);
void capturar_clientes(FILE *, struct Datos_Clientes *, int *, const char *);
void capturar_proveedores(FILE *, struct Datos_Proveedores *, int *, const char *);
void controlar_ventas();
void controlar_compras();

// VALIDACIONES
void convertir_cadena_a_minuscula(char *);
bool validar_cadenas(char *);


// FUNCIONES PARA EL SISTEMA
void validar_errores_por_SO();
void limpiar_buffer_STDIN();
void limpiar_terminal();
void pausar_terminal();

int main(void)
{
    FILE *file_articulos, *file_proveedor, *file_clientes, *file_empleados;
    struct Datos_Clientes clientes;
    struct Datos_Empleados empleados;
    struct Datos_Proveedores proveedores;
    struct Datos_Articulos articulos;
    char *ruta_file_articulos, *ruta_file_empleados, *ruta_file_clientes, *ruta_file_proveedores;
    int total_articulos = 0, total_clientes = 0, total_proveedores = 0, total_empleados = 0;
    int opcion;

    setlocale(LC_ALL, "es_MX.UTF-8");

    ruta_file_articulos = malloc(sizeof(char *) * 1000);
    ruta_file_clientes = malloc(sizeof(char *) * 1000);
    ruta_file_empleados = malloc(sizeof(char *) * 1000);
    ruta_file_proveedores = malloc(sizeof(char *) * 1000);

    getcwd( ruta_file_articulos, sizeof( ruta_file_articulos ) * 1000 );
    strcat( ruta_file_articulos, "/Files_muebleria/articulos.dat" );

    getcwd( ruta_file_clientes, sizeof( ruta_file_clientes ) * 1000);
    strcat( ruta_file_clientes, "/Files_muebleria/clientes.dat");

    getcwd( ruta_file_empleados, sizeof( ruta_file_empleados ) * 1000);
    strcat( ruta_file_empleados, "/Files_muebleria/empleados.dat");

    getcwd( ruta_file_proveedores, sizeof( ruta_file_proveedores ) * 1000);
    strcat( ruta_file_proveedores, "/Files_muebleria/proveedores.dat");

    file_articulos =  fopen( ruta_file_articulos, "rb" );
    file_clientes = fopen( ruta_file_clientes, "rb" );
    file_empleados = fopen( ruta_file_empleados, "rb" );
    file_proveedor = fopen( ruta_file_proveedores, "rb" );

    if (file_articulos == NULL || 
        file_clientes == NULL || 
        file_empleados == NULL || 
        file_proveedor == NULL)
    
        fprintf(stderr, "Error de apertura con los archivos\n");
    
    else
    {
        fclose(file_articulos);
        fclose(file_clientes);
        fclose(file_empleados);
        fclose(file_proveedor);

        do
        {
            do
            {
                limpiar_terminal();

                puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
                printf("\n%45s\n\n", "MENÚ DE OPCIONES");
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
                    if (total_articulos < 100)
                    {
                        capturar_articulos(file_articulos, &articulos, &total_articulos, ruta_file_articulos);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 2:
                    if (false)
                    {
                        capturar_clientes(file_clientes, &clientes, &total_clientes, ruta_file_clientes);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 3:
                    if (total_empleados < 20)
                    {
                        capturar_empleados(file_empleados, &empleados, &total_empleados, ruta_file_empleados);
                    }
                    else
                    {
                        /* code */
                    }
                break;

                case 4:
                    if (false)
                    {
                        capturar_proveedores(file_proveedor, &proveedores, &total_proveedores, ruta_file_proveedores);
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

                    fclose(file_clientes);
                    fclose(file_articulos);
                    fclose(file_empleados);
                    fclose(file_proveedor);
                break;
            }

            if (opcion != 9)
            
                pausar_terminal();
            
        } while (opcion != 9);

        limpiar_terminal();
        puts("Operación finalizada con éxito");
    }
    

}

void capturar_articulos(FILE *archivo_articulos, struct Datos_Articulos *data_articulos, int *articulos_registrados, const char *ruta_articulos_file)
{
    char respuesta[3];

    archivo_articulos = fopen(ruta_articulos_file, "rb+");

    if (archivo_articulos == NULL)
    
        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE ARTICULOS");
    
    else
    {
        do
        {
            limpiar_terminal();

            printf("Desea agregar artículos? Si/No: ");
            fflush(stdout);
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
                    printf("Número de artículo: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data_articulos->numero_articulo));
                
                if (data_articulos->numero_articulo <= 0)
                
                    validar_errores_por_SO();
                
            } while (data_articulos->numero_articulo <= 0);

            do
            {
                
            } while (false);
            
            
        }
    }
    
    


}

void capturar_clientes(FILE *archivo_clientes, struct Datos_Clientes *data_clientes, int *clientes_registrados, const char *ruta_clientes_file)
{



}

void capturar_empleados(FILE *archivo_empleados, struct Datos_Empleados *data_empleados, int *empleados_registrados, const char *ruta_empleados_file)
{
    


}


void capturar_proveedores(FILE *archivo_proveedores, struct Datos_Proveedores *data_proveedores, int *proveedores_registrados, const char *ruta_proveedores_file)
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