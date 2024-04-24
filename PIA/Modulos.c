/* #include <stdio.h>
#include <stdbool.h>

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



} */