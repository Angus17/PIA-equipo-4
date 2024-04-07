#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

struct Datos_Articulos
{
    int numero_articulo, numero_proveedor, punto_reorden; // Mayor a cero, proveedores a lo mucho 10
    char descripcion_articulo[100]; // Validar letras, numeros, espacios
    long int inventario; //Mayor o igual a cero
    double precio_compra, precio_venta;
};

struct Datos_Proveedores
{
    int numero_proveedor; //mayor a cero
    char nombre_proveedor[50], rfc[13]; // Letras, espacios; 13 caracteres
    char correo_electronico[30];// @ y punto despues
    int anio, mes, dia; //  >=1950, 1-12 inclusive
    char direccion_proveedor[200]; //letras, espacios, numeros
    double descuento, saldo_por_pagar; // Campo calculado
};

struct Datos_Clientes
{
    int numero_cliente; // Mayor a cero
    char nombre_cliente[50], rfc[13]; // Letras, espacios
    char correo_electronico[30];// @ y punto despues
    double descuento_cliente; // 0 - 1
    int anio, mes, dia; // 1950-2006 inclusive, 1-12 inclusive
    char direccion_cliente[200]; //letras, espacios, numeros
};

struct Datos_Empleados
{
    int numero_empleado; // 1000 - 10000
    char nombre_empleado[50]; // Letras, espacios
    char correo_electronico[30];// @ y punto despues
    int anio, mes, dia; // 1990 - actual, 
    char direccion_empleado[200]; //letras, espacios, numeros
};

int main(void)
{
    FILE *file_articulos, *file_proveedor, *file_clientes, *file_empleados;
    struct Datos_Articulos articulos = {0, 0, 0, "", 0L, 0.0, 0.0};
    struct Datos_Proveedores proveedores = {0, "", "", "", 0, 0, 0, "", 0.0, 0.0};
    struct Datos_Clientes clientes = {0, "", "", "", 0.0, 0, 0, 0, ""};
    struct Datos_Empleados empleados = {0, "", "", 0, 0, 0, ""};
    int i;
    char *ruta_file_articulos, *ruta_file_empleados, *ruta_file_clientes, *ruta_file_proveedores;

    setlocale(LC_CTYPE, "es_MX.UTF-8");

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

    file_articulos =  fopen( ruta_file_articulos, "wb" );
    file_clientes = fopen( ruta_file_clientes, "wb" );
    file_empleados = fopen( ruta_file_empleados, "wb" );
    file_proveedor = fopen( ruta_file_proveedores, "wb" );

    if (file_articulos == NULL || 
        file_clientes == NULL || 
        file_empleados == NULL || 
        file_proveedor == NULL)

        fprintf( stderr,"Ocurrió un problema al crear los archivos. . .");

    else
    {
        for ( i = 0; i < 100; i++)
        
            fwrite(&articulos, sizeof(struct Datos_Articulos), 1, file_articulos);
        
        for ( i = 0; i < 20; i++)
        
            fwrite(&empleados, sizeof(struct Datos_Empleados), 1, file_empleados);
        
        for ( i = 0; i < 10; i++)
        
            fwrite(&proveedores, sizeof(struct Datos_Proveedores), 1, file_proveedor);
        
        
        fwrite(&clientes, sizeof(struct Datos_Clientes), 1, file_clientes);

        puts("Archivos creados exitosamente!");

        free(ruta_file_articulos);
        free(ruta_file_clientes);
        free(ruta_file_empleados);
        free(ruta_file_proveedores);

        fclose(file_clientes);
        fclose(file_articulos);
        fclose(file_empleados);
        fclose(file_proveedor);
    }
}