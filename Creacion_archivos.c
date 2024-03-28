#include <stdio.h>
#include <stdlib.h>
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
    struct Datos_Clientes clientes;
    struct Datos_Empleados empleados;
    struct Datos_Proveedores proveedores;
    struct Datos_Articulos articulos;

    setlocale(LC_CTYPE, "es_MX.UTF-8");

    file_articulos =  fopen("Files_muebleria/articulos.dat","wb");
    file_clientes = fopen("Files_muebleria/clientes.dat","wb");
    file_empleados = fopen("Files_muebleria/empleados.dat","wb");
    file_proveedor = fopen("Files_muebleria/proveedores.dat","wb");

    if (file_articulos == NULL || 
        file_clientes == NULL || 
        file_empleados == NULL || 
        file_proveedor == NULL)

        puts("Ocurrió un problema al crear los archivos. . .");

    else
    {
        fwrite(&clientes, sizeof(struct Datos_Clientes), 1, file_clientes);
        fwrite(&empleados, sizeof(struct Datos_Empleados), 1, file_empleados);
        fwrite(&articulos, sizeof(struct Datos_Articulos), 1, file_articulos);
        fwrite(&proveedores, sizeof(struct Datos_Proveedores), 1, file_proveedor);

        puts("Archivos creados exitosamente!");

        fclose(file_clientes);
        fclose(file_articulos);
        fclose(file_empleados);
        fclose(file_proveedor);
    }
}