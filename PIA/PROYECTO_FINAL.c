#include "Cabeceras.h"

struct Direcciones_Fecha
{
    char direccion[200], rfc[14];
    char correo_electronico[30];
    int anio, mes, dia;
};

struct Datos_Articulos
{
    int numero_articulo, numero_proveedor[10], punto_reorden;
    char descripcion_articulo[200];
    long int inventario;
    double precio_compra[10], precio_venta;
};

struct Datos_Proveedores
{
    struct Direcciones_Fecha datos;
    int numero_proveedor;
    char nombre_proveedor[50];
    double descuento, saldo_por_pagar;
};

struct Datos_Clientes
{
    struct Direcciones_Fecha datos;
    int numero_cliente;
    char nombre_cliente[50];
    double descuento_cliente;
};

struct Datos_Empleados
{
    struct Direcciones_Fecha datos;
    int numero_empleado;
    char nombre_empleado[50];
};

struct Datos_Control_Ventas
{
    int numero_cliente, numero_articulo, mes, dia;
    float precio;
    int cantidad, numero_empleado;
    float comision_empleado;
};

struct Datos_Control_Compras
{
    int id_compra, numero_proveedor, numero_articulo, cantidad;
    float precio, saldo_pagar;
};

struct Datos_Control_Inventario
{
    int numero_proveedor, numero_compra;
    char recibido[3];
};

struct Contador_Datos
{
    int articulos_neto, clientes_neto;
    int empleados_neto, proveedores_neto;
};

struct Files_Requeridos
{
    FILE *file_articulos;
    FILE *file_clientes;
    FILE *file_proveedor;
    FILE *file_empleados;
    FILE *file_control_ventas;
    FILE *file_control_compras;
};

struct Directorios
{
    char *ruta_file_articulos;
    char *ruta_file_empleados;
    char *ruta_file_clientes;
    char *ruta_file_proveedores;
    char *ruta_file_control_compras;
    char *ruta_file_control_ventas;
};

struct Conjunto_Datos
{
    struct Datos_Articulos data_articulos;
    struct Datos_Clientes data_clientes;
    struct Datos_Empleados data_empleados;
    struct Datos_Proveedores data_proveedores;
    struct Datos_Control_Ventas data_ventas;
    struct Datos_Control_Compras data_compras;
    struct Datos_Control_Inventario data_inventario;
    struct Files_Requeridos data_files;
    struct Contador_Datos data_contador;
    struct Directorios data_dir;
};

// FUNCIONES PRINCIPALES

extern bool create_binary_files( struct Conjunto_Datos * );
extern void capturar_articulos( struct Conjunto_Datos * );
extern void capturar_empleados( struct Conjunto_Datos * );
extern void capturar_clientes( struct Conjunto_Datos * );
extern void capturar_proveedores( struct Conjunto_Datos * );
extern void controlar_ventas( struct Conjunto_Datos * );
extern void controlar_compras( struct Conjunto_Datos * );
extern void controlar_inventario( struct Conjunto_Datos * );
extern void manejar_reportes(struct Conjunto_Datos *);
extern void refrescar_contadores( struct Conjunto_Datos * );
extern void buscar_precios( struct Conjunto_Datos *, float *, const int * , const int *);
extern void calcular_precios( struct Conjunto_Datos *, const int *, const int * );
extern void realizar_cambios_inventario(struct Conjunto_Datos *);

// VALIDACIONES
extern bool existencia_venta(struct Conjunto_Datos *); // Para menu de reportes, valida que existan ventas
extern bool buscar_existencia_articulos_proveedor(FILE *, const char *, struct Datos_Control_Compras * );
extern bool buscar_cantidades(struct Conjunto_Datos *, const int *, const int *);
extern bool buscar_proveedor_articulo(struct Conjunto_Datos *, int *);
extern bool es_bisiesto( const int * );
extern bool mes_30_dias( const int * );
extern bool dia_valido( const int *, const int *, const int *, const int * );
extern void convertir_cadena_a_minuscula( char * );
extern bool verificar_articulo_punto_reorden(FILE *, struct Datos_Articulos *, const char *, const int *);
extern bool verificar_existencia_claves( FILE *, const char *, int *, const int * );
extern bool buscar_proveedores( const int *, const int * );
extern bool validar_cadenas(const char * );
extern void liberar_memoria_salida_de_error(struct Directorios *);

// FUNCIONES PARA EL SISTEMA

void validar_errores_por_SO();
void limpiar_buffer_STDIN();
void limpiar_terminal();
void pausar_terminal();

int main(void)
{
    struct Conjunto_Datos datos_struct;
    int opcion;

    setlocale(LC_ALL, "es_MX.UTF-8");

    datos_struct.data_dir.ruta_file_articulos = (char *) malloc(sizeof(char) * MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_articulos == NULL)
    {
        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    datos_struct.data_dir.ruta_file_clientes = (char *) malloc(sizeof(char) * MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_clientes == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);

        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    datos_struct.data_dir.ruta_file_empleados = (char *) malloc(sizeof(char) * MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_empleados == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_clientes);

        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    datos_struct.data_dir.ruta_file_proveedores = (char *) malloc(MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_proveedores == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_clientes);
        free(datos_struct.data_dir.ruta_file_empleados);

        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    datos_struct.data_dir.ruta_file_control_compras = (char *) malloc(MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_control_compras == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_clientes);
        free(datos_struct.data_dir.ruta_file_empleados);
        free(datos_struct.data_dir.ruta_file_proveedores);

        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    datos_struct.data_dir.ruta_file_control_ventas = (char *) malloc(MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_control_ventas == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_clientes);
        free(datos_struct.data_dir.ruta_file_empleados);
        free(datos_struct.data_dir.ruta_file_proveedores);
        free(datos_struct.data_dir.ruta_file_control_compras);

        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }

    getcwd(datos_struct.data_dir.ruta_file_articulos, sizeof(datos_struct.data_dir.ruta_file_articulos) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_articulos, "/Files_muebleria/articulos.dat");

    getcwd(datos_struct.data_dir.ruta_file_clientes, sizeof(datos_struct.data_dir.ruta_file_clientes) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_clientes, "/Files_muebleria/clientes.dat");

    getcwd(datos_struct.data_dir.ruta_file_empleados, sizeof(datos_struct.data_dir.ruta_file_empleados) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_empleados, "/Files_muebleria/empleados.dat");

    getcwd(datos_struct.data_dir.ruta_file_proveedores, sizeof(datos_struct.data_dir.ruta_file_proveedores) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_proveedores, "/Files_muebleria/proveedores.dat");

    getcwd(datos_struct.data_dir.ruta_file_control_compras , sizeof(datos_struct.data_dir.ruta_file_control_compras) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_control_compras, "/Files_muebleria/control_compras.dat");

    getcwd(datos_struct.data_dir.ruta_file_control_ventas , sizeof(datos_struct.data_dir.ruta_file_control_ventas) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_control_ventas, "/Files_muebleria/control_ventas.dat");

    if (!create_binary_files(&datos_struct))
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_empleados);
        free(datos_struct.data_dir.ruta_file_clientes);
        free(datos_struct.data_dir.ruta_file_proveedores);

        return EXIT_FAILURE;
    }
    else
    {
        datos_struct.data_contador.articulos_neto = 0;
        datos_struct.data_contador.clientes_neto = 0;
        datos_struct.data_contador.empleados_neto = 0;
        datos_struct.data_contador.proveedores_neto = 0;

        do
        {
            do
            {
                limpiar_terminal();

                printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                printf("* *%45s%28s\n\n", "MENÚ DE OPCIONES", "* *");
                printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                printf("%s\n", "1) Articulos");
                printf("%s\n", "2) Clientes");
                printf("%s\n", "3) Empleados");
                printf("%s\n", "4) Proveedores");
                printf("%s\n", "5) Ventas");
                printf("%s\n", "6) Compras");
                printf("%s\n", "7) Control de inventario");
                printf("%s\n", "8) Reportes");
                printf("%s\n", "9) Salir");
                printf("%10s: ", "Opcion");

                limpiar_buffer_STDIN();

                scanf("%d", &opcion);

                if (opcion < 1 || opcion > 9)

                    validar_errores_por_SO();

            } while (opcion < 1 || opcion > 9);

            refrescar_contadores(&datos_struct);

            switch (opcion)
            {

            case 1:
                if (datos_struct.data_contador.articulos_neto < 100 && datos_struct.data_contador.proveedores_neto > 0)

                    capturar_articulos(&datos_struct);

                else if (datos_struct.data_contador.proveedores_neto == 0)

                        puts("No hay proveedores en existencia, la muebleria no tiene articulos");

                    else

                        puts("Se han registrado el maximo de articulos en la muebleria!");

                break;

            case 2:
                if (datos_struct.data_contador.articulos_neto > 0 && datos_struct.data_contador.empleados_neto > 0)

                    capturar_clientes(&datos_struct);

                else

                    puts("Verifica tanto la existencia de articulos como de emplead@s");

                break;

            case 3:
                if (datos_struct.data_contador.empleados_neto < 20)

                    capturar_empleados(&datos_struct);

                else

                    puts("No puedes registrar más emplead@s, límite alcanzado. . .");

                break;

            case 4:
                if (datos_struct.data_contador.proveedores_neto < 10)

                    capturar_proveedores(&datos_struct);

                else

                    puts("No puedes registrar más proveedores, límite alcanzado. . .");

                break;

            case 5:
                if (datos_struct.data_contador.clientes_neto > 0)

                    controlar_ventas(&datos_struct);

                else

                    puts("La mueblería no está lista para vender aún, faltan registros de clientes. . .");

                break;

            case 6:
                if (datos_struct.data_contador.proveedores_neto > 0)

                    controlar_compras(&datos_struct);

                else

                    puts("No existen proveedores para surtir más artículos. . .");

                break;

            case 7:
                if (buscar_existencia_articulos_proveedor(datos_struct.data_files.file_control_compras, datos_struct.data_dir.ruta_file_control_compras, &datos_struct.data_compras))

                    controlar_inventario(&datos_struct);

                else

                    puts("Todos los articulos fueron recibidos. . .");

                break;

            case 8:

                    manejar_reportes(&datos_struct);

                break;

            case 9:
                free(datos_struct.data_dir.ruta_file_articulos);
                free(datos_struct.data_dir.ruta_file_clientes);
                free(datos_struct.data_dir.ruta_file_empleados);
                free(datos_struct.data_dir.ruta_file_proveedores);
                free(datos_struct.data_dir.ruta_file_control_compras);
                free(datos_struct.data_dir.ruta_file_control_ventas);

                break;
            }

            if (opcion != 9)

                pausar_terminal();

        } while (opcion != 9);

        limpiar_terminal();
        puts("Operación finalizada con éxito");
    }

    return EXIT_SUCCESS;
}

extern bool create_binary_files(struct Conjunto_Datos *data_all)
{
    int i;
    char respuesta[3];
    bool entornos_creados = false;
    struct Datos_Articulos articles = {0, {0}, 0, "", 0L, {0.0L}, 0.0L};
    struct Datos_Proveedores suppliers = {{"", "", "", 0, 0, 0}, 0, "", 0.0L, 0.0L};
    struct Datos_Empleados employees = {{"", "", "", 0, 0, 0}, 0, ""};


    do
    {
        data_all->data_files.file_articulos = fopen(data_all->data_dir.ruta_file_articulos, "rb");
        data_all->data_files.file_empleados = fopen(data_all->data_dir.ruta_file_empleados, "rb");
        data_all->data_files.file_proveedor = fopen(data_all->data_dir.ruta_file_proveedores, "rb");

        if (data_all->data_files.file_articulos == NULL
            && data_all-> data_files.file_empleados == NULL
            && data_all->data_files.file_proveedor == NULL)
        {
            data_all->data_files.file_articulos = fopen(data_all->data_dir.ruta_file_articulos, "wb");
            data_all->data_files.file_empleados = fopen(data_all->data_dir.ruta_file_empleados, "wb");
            data_all->data_files.file_proveedor = fopen(data_all->data_dir.ruta_file_proveedores, "wb");

            if (data_all->data_files.file_articulos == NULL
                || data_all-> data_files.file_empleados == NULL
                || data_all->data_files.file_proveedor == NULL)
            {
                fprintf(stderr, "ERROR DE ARCHIVOS, INTENTE MAS TARDE. . .");
                return false;
            }

            for ( i = 0; i < 100; i++)

                fwrite(&articles, sizeof(articles), 1, data_all->data_files.file_articulos);

            for ( i = 0; i < 10; i++)

                fwrite(&suppliers, sizeof(suppliers), 1, data_all->data_files.file_proveedor);

            for ( i = 0; i < 20; i++)

                fwrite(&employees, sizeof(employees), 1, data_all->data_files.file_empleados);

            fclose(data_all->data_files.file_articulos);
            fclose(data_all->data_files.file_proveedor);
            fclose(data_all->data_files.file_empleados);

            puts("ENTORNOS BINARIOS CREADOS CORRECTAMENTE!");
            pausar_terminal();
            return true;
        }
        else if (data_all->data_files.file_articulos == NULL)
            {
                data_all->data_files.file_articulos = fopen(data_all->data_dir.ruta_file_articulos, "wb");

                if (data_all->data_files.file_articulos == NULL)
                {
                    fprintf(stderr, "ERROR DE ARCHIVOS, INTENTE MAS TARDE. . .");
                    return false;
                }

                for ( i = 0; i < 100; i++)

                    fwrite(&articles, sizeof(articles), 1, data_all->data_files.file_articulos);

                fclose(data_all->data_files.file_articulos);
            }
            else if (data_all->data_files.file_empleados == NULL)
                {
                    data_all->data_files.file_empleados = fopen(data_all->data_dir.ruta_file_empleados, "wb");

                    if (data_all-> data_files.file_empleados == NULL)
                    {
                        fprintf(stderr, "ERROR DE ARCHIVOS, INTENTE MAS TARDE. . .");
                        return false;
                    }

                    for ( i = 0; i < 20; i++)

                        fwrite(&employees, sizeof(employees), 1, data_all->data_files.file_empleados);

                    fclose(data_all->data_files.file_empleados);
                }
                else if (data_all->data_files.file_proveedor == NULL)
                    {
                        data_all->data_files.file_proveedor = fopen(data_all->data_dir.ruta_file_proveedores, "wb");

                        if (data_all->data_files.file_proveedor == NULL)
                        {
                            fprintf(stderr, "ERROR DE ARCHIVOS, INTENTE MAS TARDE. . .");
                            return false;
                        }

                        for ( i = 0; i < 10; i++)

                            fwrite(&suppliers, sizeof(suppliers), 1, data_all->data_files.file_proveedor);

                        fclose(data_all->data_files.file_proveedor);
                    }
                    else
                    {
                        fclose(data_all->data_files.file_articulos);
                        fclose(data_all->data_files.file_proveedor);
                        fclose(data_all->data_files.file_empleados);

                        entornos_creados = true;
                    }

    } while (!entornos_creados);

    do
    {
        limpiar_terminal();

        printf("Desea ingresar todos los registros de nuevo? Si/No: ");
        limpiar_buffer_STDIN();
        fgets(respuesta, sizeof(respuesta), stdin);

        convertir_cadena_a_minuscula(respuesta);

        if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0)

            validar_errores_por_SO();

    } while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0);

    if (strcmp(respuesta, "si") == 0)
    {
        data_all->data_files.file_articulos = fopen(data_all->data_dir.ruta_file_articulos, "wb");
        data_all->data_files.file_empleados = fopen(data_all->data_dir.ruta_file_empleados, "wb");
        data_all->data_files.file_proveedor = fopen(data_all->data_dir.ruta_file_proveedores, "wb");

        if (data_all->data_files.file_articulos == NULL
            || data_all-> data_files.file_empleados == NULL
            || data_all->data_files.file_proveedor == NULL)
        {
            fprintf(stderr, "ERROR DE ARCHIVOS, INTENTE MAS TARDE. . .");
            return false;
        }

        for ( i = 0; i < 100; i++)

            fwrite(&articles, sizeof(articles), 1, data_all->data_files.file_articulos);

        for ( i = 0; i < 10; i++)

            fwrite(&suppliers, sizeof(suppliers), 1, data_all->data_files.file_proveedor);

        for ( i = 0; i < 20; i++)

            fwrite(&employees, sizeof(employees), 1, data_all->data_files.file_empleados);

        fclose(data_all->data_files.file_articulos);
        fclose(data_all->data_files.file_proveedor);
        fclose(data_all->data_files.file_empleados);

        puts("ENTORNOS BINARIOS CREADOS CORRECTAMENTE!");
        pausar_terminal();
    }

    return true;
}

extern void capturar_articulos(struct Conjunto_Datos *data)
{
    char respuesta[3], proveedor_respuesta[3];
    bool descripcion_correcta, provedor_articulo, clave_existente = false;
    bool proveedor_existente, proveedor_ya_ingresado;
    int i;
    const int type_of_file = 1, file_proveedores = 3;

    data->data_files.file_articulos = fopen(data->data_dir.ruta_file_articulos, "rb+");

    if (data->data_files.file_articulos == NULL)

        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE ARTICULOS");

    else
    {
        do
        {
            limpiar_terminal();

            printf("Desea agregar artículos? Si/No: ");
            limpiar_buffer_STDIN();
            fgets(respuesta, sizeof(respuesta), stdin);

            respuesta[strcspn(respuesta, "\n")] = '\0';

            convertir_cadena_a_minuscula(respuesta);

            if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0)

                validar_errores_por_SO();

        } while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0);

        while (strcmp(respuesta, "si") == 0 && data->data_contador.articulos_neto < 100)
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

                else if (data->data_contador.articulos_neto > 0)
                    {
                        clave_existente = verificar_existencia_claves(data->data_files.file_articulos, data->data_dir.ruta_file_articulos, &data->data_articulos.numero_articulo, &type_of_file);

                        if (clave_existente)
                        {
                            limpiar_terminal();
                            puts("La clave ingresada ya existe en el sistema. . .");
                            pausar_terminal();
                        }
                    }

            } while (data->data_articulos.numero_articulo <= 0 || data->data_articulos.numero_articulo > 100 || clave_existente);

            do
            {
                limpiar_terminal();

                printf("Descripción del artículo: ");
                limpiar_buffer_STDIN();
                fgets(data->data_articulos.descripcion_articulo, sizeof(data->data_articulos.descripcion_articulo), stdin);

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

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Cuántos artículos existen en el inventario?: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%ld", &data->data_articulos.inventario) != 1);

                if (data->data_articulos.inventario < 1)

                    validar_errores_por_SO();

            } while (data->data_articulos.inventario < 1);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Cuál es el precio de venta al público?: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%lf", &data->data_articulos.precio_venta) != 1);

                if (data->data_articulos.precio_venta < 1)

                    validar_errores_por_SO();

            } while (data->data_articulos.precio_venta < 1);

            provedor_articulo = true;
            i = 0;

            while (i < data->data_contador.proveedores_neto && provedor_articulo)
            {

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Ingresa el numero de proveedor que maneja el articulo %d (1-10): ", data->data_articulos.numero_articulo);
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_articulos.numero_proveedor[i]) != 1);

                    if (data->data_articulos.numero_proveedor[i] < 1)

                        validar_errores_por_SO();

                    else
                    {
                        proveedor_existente = verificar_existencia_claves(data->data_files.file_proveedor, data->data_dir.ruta_file_proveedores, &data->data_articulos.numero_proveedor[i], &file_proveedores);

                        if (!proveedor_existente)
                        {
                            limpiar_terminal();
                            puts("El proveedor ingresado no existe en el catálogo. . .");
                            pausar_terminal();
                        }
                        else

                            proveedor_ya_ingresado = buscar_proveedores(&data->data_articulos.numero_proveedor[i], &i);

                    }

                } while (data->data_articulos.numero_proveedor[i] < 1 || !proveedor_existente || proveedor_ya_ingresado);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Precio que maneja el proveedor, en el artículo: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%lf", &data->data_articulos.precio_compra[i]) != 1);

                    if (data->data_articulos.precio_compra[i] < 1.0)

                        validar_errores_por_SO();

                } while (data->data_articulos.precio_compra[i] < 1.0);

                i++;

                if (i < data->data_contador.proveedores_neto)
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Existen mas proveedores que manejen el articulo? Si/No: ");
                        limpiar_buffer_STDIN();
                        fgets(proveedor_respuesta, sizeof(proveedor_respuesta), stdin);

                        proveedor_respuesta[strcspn(proveedor_respuesta, "\n")] = '\0';

                        convertir_cadena_a_minuscula(proveedor_respuesta);

                        if (strcmp(proveedor_respuesta, "si") != 0 && strcmp(proveedor_respuesta, "no") != 0)

                            validar_errores_por_SO();

                    } while (strcmp(proveedor_respuesta, "si") != 0 && strcmp(proveedor_respuesta, "no") != 0);

                    if (strcmp(proveedor_respuesta, "no") == 0)

                        provedor_articulo = false;

                }
                else
                {
                    puts("No hay mas proveedores en el catalogo");
                    pausar_terminal();
                }
            }


            fseek(data->data_files.file_articulos, data->data_contador.articulos_neto * sizeof(data->data_articulos), SEEK_SET);
            fwrite(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

            data->data_contador.articulos_neto++;

            if (data->data_contador.articulos_neto < 100)
            {
                do
                {
                    limpiar_terminal();

                    printf("Desea agregar más artículos? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(respuesta, sizeof(respuesta), stdin);

                    respuesta[strcspn(respuesta, "\n")] = '\0';

                    convertir_cadena_a_minuscula(respuesta);

                    if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0)

                        validar_errores_por_SO();

                } while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0);
            }
            else
            {
                limpiar_terminal();
                puts("Has alcanzado el límite máximo de artículos por ingresar. . .");
                pausar_terminal();
            }
        }

        fclose(data->data_files.file_articulos);
    }
}

extern void capturar_clientes(struct Conjunto_Datos *data)
{
    char existencia_cliente[3], expresion[] = "^[A-Za-z0-9._-]+@[a-z]+\\.[a-z]{2,}$";
    char expresion_3[] = "^([A-Z]{4})([0-9]{6})([A-Z0-9]{3})$";
    char expresion_2[] = "^([0-9A-Za-z ]+) #([0-9]+) ([A-Za-z ]+)\\, ([A-Za-z ]+)\\, ([A-Za-z ]+)$";
    regex_t regular, regular_2, regular_3;
    bool descripcion_correcta, clave_existente = false;
    int regex = regcomp(&regular, expresion, REG_EXTENDED);
    int regex_2 = regcomp(&regular_2, expresion_2, REG_EXTENDED);
    int regex_3 = regcomp(&regular_3, expresion_3, REG_EXTENDED);
    const int type_of_file = 2;

    do
    {
        limpiar_terminal();

        printf("Desea ingresar clientes? Si/No: ");
        limpiar_buffer_STDIN();
        fgets(existencia_cliente, sizeof(existencia_cliente), stdin);

        existencia_cliente[strcspn(existencia_cliente, "\n")] = '\0';

        convertir_cadena_a_minuscula(existencia_cliente);

        if (strcmp(existencia_cliente, "si") != 0 && strcmp(existencia_cliente, "no") != 0)

            validar_errores_por_SO();
    } while (strcmp(existencia_cliente, "si") != 0 && strcmp(existencia_cliente, "no") != 0);

    if (strcmp(existencia_cliente, "si") == 0)
    {
        data->data_files.file_clientes = fopen(data->data_dir.ruta_file_clientes, "rb+");

        if (data->data_files.file_clientes == NULL)

            fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE CLIENTES");

        else
        {
            while (strcmp(existencia_cliente, "si") == 0)
            {
                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de cliente: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_clientes.numero_cliente) != 1);

                    if (data->data_clientes.numero_cliente <= 0)

                        validar_errores_por_SO();

                    else if (data->data_contador.clientes_neto > 0)
                        {
                            clave_existente = verificar_existencia_claves(data->data_files.file_clientes, data->data_dir.ruta_file_clientes, &data->data_clientes.numero_cliente, &type_of_file);

                            if (clave_existente)
                            {
                                limpiar_terminal();
                                puts("La clave ingresada ya existe en el sistema. . .");
                                pausar_terminal();
                            }
                        }

                } while (data->data_clientes.numero_cliente <= 0 || clave_existente);

                fseek(data->data_files.file_clientes, 0L, SEEK_END); // Apuntar a EOF

                do
                {
                    limpiar_terminal();

                    printf("Nombre del cliente: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_clientes.nombre_cliente, sizeof(data->data_clientes.nombre_cliente), stdin);

                    data->data_clientes.nombre_cliente[strcspn(data->data_clientes.nombre_cliente, "\n")] = '\0';

                    if (strlen(data->data_clientes.nombre_cliente) > 0)

                        descripcion_correcta = validar_cadenas(data->data_clientes.nombre_cliente);

                } while (strlen(data->data_clientes.nombre_cliente) == 0 || !descripcion_correcta);

                do
                {
                    limpiar_terminal();

                    printf("RFC del cliente: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_clientes.datos.rfc, sizeof(data->data_clientes.datos.rfc), stdin);

                    *(data->data_clientes.datos.rfc + (strcspn(data->data_clientes.datos.rfc, "\n"))) = '\0';

                    regex_3 = regexec(&regular_3, data->data_clientes.datos.rfc, 0, NULL, 0);

                    if (regex_3 != 0)

                        validar_errores_por_SO();

                } while (regex_3 != 0);

                do
                {
                    limpiar_terminal();

                    printf("Correo electronico del cliente: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_clientes.datos.correo_electronico, sizeof(data->data_clientes.datos.correo_electronico), stdin);

                    *((data->data_clientes.datos.correo_electronico) + (strcspn(data->data_clientes.datos.correo_electronico, "\n"))) = '\0';

                    regex = regexec(&regular, data->data_clientes.datos.correo_electronico, 0, NULL, 0);

                    if (regex != 0)

                        validar_errores_por_SO();

                } while (regex != 0);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Descuento de cliente: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%lf", &data->data_clientes.descuento_cliente) != 1);

                    if (data->data_clientes.descuento_cliente < 0.0 || data->data_clientes.descuento_cliente > 1.0)

                        validar_errores_por_SO();

                } while (data->data_clientes.descuento_cliente < 0.0 || data->data_clientes.descuento_cliente > 1.0);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Año de nacimiento: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_clientes.datos.anio) != 1);

                    if (data->data_clientes.datos.anio < 1950 || data->data_clientes.datos.anio > 2006)

                        validar_errores_por_SO();

                } while (data->data_clientes.datos.anio < 1950 || data->data_clientes.datos.anio > 2006);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Mes de nacimiento (1-12): ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_clientes.datos.mes) != 1);

                    if (data->data_clientes.datos.mes < 1 || data->data_clientes.datos.mes > 12)

                        validar_errores_por_SO();


                } while (data->data_clientes.datos.mes < 1 || data->data_clientes.datos.mes > 12);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Dia de nacimiento: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_clientes.datos.dia) != 1);

                    if (!dia_valido(&data->data_clientes.datos.dia, &data->data_clientes.datos.mes, &data->data_clientes.datos.anio, &type_of_file))

                        validar_errores_por_SO();

                } while (!dia_valido(&data->data_clientes.datos.dia, &data->data_clientes.datos.mes, &data->data_clientes.datos.anio, &type_of_file));

                do
                {
                    limpiar_terminal();

                    printf("Por último, ingresa su dirección usando el siguiente formato\n"
                            "NOTA!: Cambia los campos entre () ignorando todos los parentesis\n"
                            "(Calle) #(numero) (Colonia,Fracc...etc.), (Municipio), (Estado):\n\n");
                    limpiar_buffer_STDIN();
                    fgets(data->data_clientes.datos.direccion, sizeof(data->data_clientes.datos.direccion), stdin);

                    *(data->data_clientes.datos.direccion + (strcspn(data->data_clientes.datos.direccion, "\n"))) = '\0';

                    regex_2 = regexec(&regular_2, data->data_clientes.datos.direccion, 0, NULL, 0);

                    if (regex_2 != 0)

                        validar_errores_por_SO();

                } while (regex_2 != 0);

                data->data_contador.clientes_neto++;

                fwrite(&data->data_clientes, sizeof(data->data_clientes), 1, data->data_files.file_clientes);

                do
                {
                    limpiar_terminal();

                    printf("Desea ingresar más clientes? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(existencia_cliente, sizeof(existencia_cliente), stdin);

                    existencia_cliente[strcspn(existencia_cliente, "\n")] = '\0';

                    convertir_cadena_a_minuscula(existencia_cliente);

                    if (strcmp(existencia_cliente, "si") != 0 && strcmp(existencia_cliente, "no") != 0)

                        validar_errores_por_SO();
                } while (strcmp(existencia_cliente, "si") != 0 && strcmp(existencia_cliente, "no") != 0);

            }

            fclose(data->data_files.file_clientes);
        }
    }

    regfree(&regular);
    regfree(&regular_2);
    regfree(&regular_3);
}

extern void capturar_empleados(struct Conjunto_Datos *data)
{
    char existencia_empleado[3], expresion[] = "^[A-Za-z0-9._-]+@[a-z]+\\.[a-z]{2,}$";
    char expresion_3[] = "^([A-Z]{4})([0-9]{6})([A-Z0-9]{3})$";
    char expresion_2[] = "^([0-9A-Za-z ]+) #([0-9]+) ([A-Za-z ]+)\\, ([A-Za-z ]+)\\, ([A-Za-z ]+)$";
    regex_t regular, regular_2, regular_3;
    bool descripcion_correcta, clave_existente;
    int regex = regcomp(&regular, expresion, REG_EXTENDED), anio, mes;
    int regex_2 = regcomp(&regular_2, expresion_2, REG_EXTENDED);
    int regex_3 = regcomp(&regular_3, expresion_3, REG_EXTENDED);
    const int type_of_file = 4;

    time_t tiempo = time(NULL);
    struct tm *time_actual = localtime(&tiempo);

    anio = time_actual->tm_year + 1900;
    mes = time_actual->tm_mon + 1;

    do
    {
        limpiar_terminal();

        printf("Existen emplead@s? Si/No: ");
        limpiar_buffer_STDIN();
        fgets(existencia_empleado, sizeof(existencia_empleado), stdin);

        existencia_empleado[strcspn(existencia_empleado, "\n")] = '\0';

        convertir_cadena_a_minuscula(existencia_empleado);

        if (strcmp(existencia_empleado, "si") != 0 && strcmp(existencia_empleado, "no") != 0)

            validar_errores_por_SO();
    } while (strcmp(existencia_empleado, "si") != 0 && strcmp(existencia_empleado, "no") != 0);

    if (strcmp(existencia_empleado, "si") == 0)
    {
        data->data_files.file_empleados = fopen(data->data_dir.ruta_file_empleados, "rb+");

        if (data->data_files.file_empleados == NULL)

            fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE EMPLEADOS");

        else
        {
            while (strcmp(existencia_empleado, "si") == 0 && data->data_contador.empleados_neto < 20)
            {
                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de emplead@: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_empleados.numero_empleado) != 1);

                    if (data->data_empleados.numero_empleado < 1000 || data->data_empleados.numero_empleado > 10000)

                        validar_errores_por_SO();

                    else if (data->data_contador.empleados_neto > 0)
                        {
                            clave_existente = verificar_existencia_claves(data->data_files.file_empleados, data->data_dir.ruta_file_empleados, &data->data_empleados.numero_empleado, &type_of_file);

                            if (clave_existente)
                            {
                                limpiar_terminal();
                                puts("La clave ingresada ya existe en el sistema. . .");
                                pausar_terminal();
                            }
                        }

                } while (data->data_empleados.numero_empleado < 1000 || data->data_empleados.numero_empleado > 10000 || clave_existente);

                do
                {
                    limpiar_terminal();

                    printf("Nombre del emplead@: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_empleados.nombre_empleado, sizeof(data->data_empleados.nombre_empleado), stdin);

                    data->data_clientes.nombre_cliente[strcspn(data->data_clientes.nombre_cliente, "\n")] = '\0';

                    if (strlen(data->data_empleados.nombre_empleado) > 0)

                        descripcion_correcta = validar_cadenas(data->data_empleados.nombre_empleado);

                } while (strlen(data->data_empleados.nombre_empleado) == 0 || !descripcion_correcta);

                do
                {
                    limpiar_terminal();

                    printf("RFC del emplead@: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_empleados.datos.rfc, sizeof(data->data_empleados.datos.rfc), stdin);

                    *(data->data_empleados.datos.rfc + (strcspn(data->data_empleados.datos.rfc, "\n"))) = '\0';

                    regex_3 = regexec(&regular_3, data->data_empleados.datos.rfc, 0, NULL, 0);

                    if (regex_3 != 0)

                        validar_errores_por_SO();

                } while (regex_3 != 0);

                do
                {
                    limpiar_terminal();

                    printf("Correo electrónico del emplead@: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_empleados.datos.correo_electronico, sizeof(data->data_empleados.datos.correo_electronico), stdin);

                    *((data->data_empleados.datos.correo_electronico) + (strcspn(data->data_empleados.datos.correo_electronico, "\n"))) = '\0';

                    regex = regexec(&regular, data->data_empleados.datos.correo_electronico, 0, NULL, 0);

                    if (regex != 0)

                        validar_errores_por_SO();

                } while (regex != 0);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Año de contratación: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_empleados.datos.anio) != 1);

                    if (data->data_empleados.datos.anio < 1950 || data->data_empleados.datos.anio > anio)

                        validar_errores_por_SO();

                } while (data->data_empleados.datos.anio < 1950 || data->data_empleados.datos.anio > anio);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Mes de contratación (1-12): ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_empleados.datos.mes) != 1);

                    if ((data->data_empleados.datos.anio == anio && data->data_empleados.datos.mes > mes) || (data->data_empleados.datos.anio < anio && (data->data_empleados.datos.mes < 1 || data->data_empleados.datos.mes > 12)))

                        validar_errores_por_SO();

                } while ((data->data_empleados.datos.anio == anio && data->data_empleados.datos.mes > mes) || (data->data_empleados.datos.anio < anio && (data->data_empleados.datos.mes < 1 || data->data_empleados.datos.mes > 12)));

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Dia de contratación: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_empleados.datos.dia) != 1);

                    if (!dia_valido(&data->data_empleados.datos.dia, &data->data_empleados.datos.mes, &data->data_empleados.datos.anio, &type_of_file))

                        validar_errores_por_SO();

                } while (!dia_valido(&data->data_empleados.datos.dia, &data->data_empleados.datos.mes, &data->data_empleados.datos.anio, &type_of_file));

                do
                {
                    limpiar_terminal();

                    printf("Por último, ingresa su dirección usando el siguiente formato\n"
                            "NOTA!: Cambia los campos entre () ignorando todos los parentesis\n"
                            "(Calle) #(numero) (Colonia,Fracc...etc.), (Municipio), (Estado):\n\n");
                    limpiar_buffer_STDIN();
                    fgets(data->data_empleados.datos.direccion, sizeof(data->data_empleados.datos.direccion), stdin);

                    *(data->data_empleados.datos.direccion + (strcspn(data->data_empleados.datos.direccion, "\n"))) = '\0';

                    regex_2 = regexec(&regular_2, data->data_empleados.datos.direccion, 0, NULL, 0);

                    if (regex_2 != 0)

                        validar_errores_por_SO();

                } while (regex_2 != 0);

                data->data_contador.empleados_neto++;

                fseek(data->data_files.file_empleados, data->data_contador.empleados_neto * sizeof(data->data_empleados), SEEK_SET);
                fwrite(&data->data_empleados, sizeof(data->data_empleados), 1, data->data_files.file_empleados);

                do
                {
                    limpiar_terminal();

                    printf("Desea ingresar más emplead@s? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(existencia_empleado, sizeof(existencia_empleado), stdin);

                    existencia_empleado[strcspn(existencia_empleado, "\n")] = '\0';

                    convertir_cadena_a_minuscula(existencia_empleado);

                    if (strcmp(existencia_empleado, "si") != 0 && strcmp(existencia_empleado, "no") != 0)

                        validar_errores_por_SO();
                } while (strcmp(existencia_empleado, "si") != 0 && strcmp(existencia_empleado, "no") != 0);

            }

            fclose(data->data_files.file_empleados);
        }
    }

    regfree(&regular);
    regfree(&regular_2);
    regfree(&regular_3);
}

extern void capturar_proveedores(struct Conjunto_Datos *data)
{
    char existencia_proveedor[3], expresion[] = "^[A-Za-z0-9._-]+@[a-z]+\\.[a-z]{2,}$";
    char expresion_3[] = "^([A-Z]{4})([0-9]{6})([A-Z0-9]{3})$";
    char expresion_2[] = "^([A-Za-z0-9]+) #([0-9]+) ([A-Za-z ]+)\\, ([A-Za-z ]+)\\, ([A-Za-z ]+)$";
    regex_t regular, regular_2, regular_3;
    bool descripcion_correcta, clave_existente;
    int regex = regcomp(&regular, expresion, REG_EXTENDED), anio, mes;
    int regex_2 = regcomp(&regular_2, expresion_2, REG_EXTENDED);
    int regex_3 = regcomp(&regular_3, expresion_3, REG_EXTENDED);
    const int type_of_file = 3;

    time_t tiempo = time(NULL);
    struct tm *time_actual = localtime(&tiempo);

    anio = time_actual->tm_year + 1900;
    mes = time_actual->tm_mon + 1;

    do
    {
        limpiar_terminal();

        printf("Existen proveedores? Si/No: ");
        limpiar_buffer_STDIN();
        fgets(existencia_proveedor, sizeof(existencia_proveedor), stdin);

        existencia_proveedor[strcspn(existencia_proveedor, "\n")] = '\0';

        convertir_cadena_a_minuscula(existencia_proveedor);

        if (strcmp(existencia_proveedor, "si") != 0 && strcmp(existencia_proveedor, "no") != 0)

            validar_errores_por_SO();

    } while (strcmp(existencia_proveedor, "si") != 0 && strcmp(existencia_proveedor, "no") != 0);

    if (strcmp(existencia_proveedor, "si") == 0)
    {
        data->data_files.file_proveedor = fopen(data->data_dir.ruta_file_proveedores, "rb+");

        if (data->data_files.file_proveedor == NULL)

            fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE PROVEEDORES");

        else
        {
            while (strcmp(existencia_proveedor, "si") == 0 && data->data_contador.proveedores_neto < 10)
            {
                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de proveedor (1-10): ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_proveedores.numero_proveedor) != 1);

                    if (data->data_proveedores.numero_proveedor <= 0 || data->data_proveedores.numero_proveedor > 10)

                        validar_errores_por_SO();
                    else if (data->data_contador.proveedores_neto > 0)
                        {
                            clave_existente = verificar_existencia_claves(data->data_files.file_proveedor, data->data_dir.ruta_file_proveedores, &data->data_proveedores.numero_proveedor, &type_of_file);

                            if (clave_existente)
                            {
                                limpiar_terminal();
                                puts("La clave ingresada ya existe en el sistema. . .");
                            }
                        }

                } while (data->data_proveedores.numero_proveedor <= 0 || data->data_proveedores.numero_proveedor > 10 || clave_existente);

                do
                {
                    limpiar_terminal();

                    printf("Nombre del proveedor: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_proveedores.nombre_proveedor, sizeof(data->data_proveedores.nombre_proveedor), stdin);

                    data->data_proveedores.nombre_proveedor[strcspn(data->data_proveedores.nombre_proveedor, "\n")] = '\0';

                    if (strlen(data->data_proveedores.nombre_proveedor) > 0)

                        descripcion_correcta = validar_cadenas(data->data_proveedores.nombre_proveedor);

                } while (strlen(data->data_proveedores.nombre_proveedor) == 0 || !descripcion_correcta);

                do
                {
                    limpiar_terminal();

                    printf("RFC del proveedor: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_proveedores.datos.rfc, sizeof(data->data_proveedores.datos.rfc), stdin);

                    *(data->data_proveedores.datos.rfc + (strcspn(data->data_proveedores.datos.rfc, "\n"))) = '\0';

                    regex_3 = regexec(&regular_3, data->data_proveedores.datos.rfc, 0, NULL, 0);

                    if (regex_3 != 0)

                        validar_errores_por_SO();

                } while (regex_3 != 0);

                do
                {
                    limpiar_terminal();

                    printf("Correo electrónico del proveedor: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_proveedores.datos.correo_electronico, sizeof(data->data_proveedores.datos.correo_electronico), stdin);

                    *((data->data_proveedores.datos.correo_electronico) + (strcspn(data->data_proveedores.datos.correo_electronico, "\n"))) = '\0';

                    regex = regexec(&regular, data->data_proveedores.datos.correo_electronico, 0, NULL, 0);

                    if (regex != 0)

                        validar_errores_por_SO();

                } while (regex != 0);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Descuento por proveedor: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%lf", &data->data_proveedores.descuento) != 1);

                    if (data->data_proveedores.descuento < 0.0 || data->data_proveedores.descuento > 1.0)

                        validar_errores_por_SO();

                } while (data->data_proveedores.descuento < 0.0 || data->data_proveedores.descuento > 1.0);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Año de inicios: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_proveedores.datos.anio) != 1);

                    if (data->data_proveedores.datos.anio < 1950 || data->data_proveedores.datos.anio > anio)

                        validar_errores_por_SO();

                } while (data->data_proveedores.datos.anio < 1950 || data->data_proveedores.datos.anio > anio);

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Mes de inicios (1-12): ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_proveedores.datos.mes) != 1);

                    if ((data->data_proveedores.datos.anio == anio && data->data_proveedores.datos.mes > mes) || (data->data_proveedores.datos.anio < anio && (data->data_proveedores.datos.mes < 1 || data->data_proveedores.datos.mes > 12)))

                        validar_errores_por_SO();


                } while ((data->data_proveedores.datos.anio == anio && data->data_proveedores.datos.mes > mes) || (data->data_proveedores.datos.anio < anio && (data->data_proveedores.datos.mes < 1 || data->data_proveedores.datos.mes > 12)));

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Dia de inicios: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_proveedores.datos.dia) != 1);

                    if (!dia_valido(&data->data_proveedores.datos.dia, &data->data_proveedores.datos.mes, &data->data_proveedores.datos.anio, &type_of_file))

                        validar_errores_por_SO();

                } while (!dia_valido(&data->data_proveedores.datos.dia, &data->data_proveedores.datos.mes, &data->data_proveedores.datos.anio, &type_of_file));

                do
                {
                    limpiar_terminal();

                    printf("Por último, ingresa su dirección usando el siguiente formato\n"
                            "NOTA!: Cambia los campos entre () ignorando todos los parentesis\n"
                            "(Calle) #(numero) (Colonia,Fracc...etc.), (Municipio), (Estado):\n\n");
                    limpiar_buffer_STDIN();
                    fgets(data->data_proveedores.datos.direccion, sizeof(data->data_proveedores.datos.direccion), stdin);

                    *(data->data_proveedores.datos.direccion + (strcspn(data->data_proveedores.datos.direccion, "\n"))) = '\0';

                    regex_2 = regexec(&regular_2, data->data_proveedores.datos.direccion, 0, NULL, 0);

                    if (regex_2 != 0)

                        validar_errores_por_SO();

                } while (regex_2 != 0);

                data->data_contador.proveedores_neto++;

                fseek(data->data_files.file_proveedor, data->data_proveedores.numero_proveedor * sizeof(data->data_proveedores), SEEK_SET);
                fwrite(&data->data_proveedores, sizeof(data->data_proveedores), 1, data->data_files.file_proveedor);

                if (data->data_contador.proveedores_neto < 10)
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Desea ingresar más proveedores? Si/No: ");
                        limpiar_buffer_STDIN();
                        fgets(existencia_proveedor, sizeof(existencia_proveedor), stdin);

                        existencia_proveedor[strcspn(existencia_proveedor, "\n")] = '\0';

                        convertir_cadena_a_minuscula(existencia_proveedor);

                        if (strcmp(existencia_proveedor, "si") != 0 && strcmp(existencia_proveedor, "no") != 0)

                            validar_errores_por_SO();
                    } while (strcmp(existencia_proveedor, "si") != 0 && strcmp(existencia_proveedor, "no") != 0);
                }
                else
                {
                    limpiar_terminal();
                    puts("Limite maximo alcanzado!");
                }
            }

            fclose(data->data_files.file_proveedor);
        }
    }

    regfree(&regular);
    regfree(&regular_2);
    regfree(&regular_3);
}

extern void controlar_ventas(struct Conjunto_Datos *data)
{
    char existencia_ventas[3], facturar[3], existencia_articulos[3];
    bool cliente_actual = true, clave_existente = false, cantidad_existente = false, empleado_actual = true;
    const int file_articulos = 1, file_clientes = 2, file_empleados = 4, file_ventas = 1;
    float precio = 0.0;
    int mes_actual;

    time_t tiempo = time(NULL);
    struct tm *time = localtime(&tiempo);

    mes_actual = time->tm_mon + 1;

    data->data_files.file_control_ventas = fopen(data->data_dir.ruta_file_control_ventas, "rb+");

    if (data->data_files.file_control_ventas == NULL)

        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE CONTROL DE VENTAS");

    else
    {
        do
        {
            limpiar_terminal();

            printf("Existen ventas? Si/No: ");
            limpiar_buffer_STDIN();
            fgets(existencia_ventas, sizeof(existencia_ventas), stdin);

            existencia_ventas[strcspn(existencia_ventas, "\n")] = '\0';

            convertir_cadena_a_minuscula(existencia_ventas);

            if (strcmp(existencia_ventas, "si") != 0 && strcmp(existencia_ventas, "no") != 0)

                validar_errores_por_SO();

        } while (strcmp(existencia_ventas, "si") != 0 && strcmp(existencia_ventas, "no") != 0);

        while (strcmp(existencia_ventas, "si") == 0 || strcmp(existencia_articulos, "si") == 0)
        {
            if (cliente_actual)
            {
                data->data_ventas.precio = 0.0;

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de cliente: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_ventas.numero_cliente) != 1);

                    if (data->data_ventas.numero_cliente <= 0)

                        validar_errores_por_SO();

                    else
                    {
                        clave_existente = verificar_existencia_claves(data->data_files.file_clientes, data->data_dir.ruta_file_clientes, &data->data_ventas.numero_cliente, &file_clientes);

                        if (!clave_existente)
                        {
                            limpiar_terminal();
                            puts("El cliente ingresado no existe en el sistema. . .");
                            pausar_terminal();
                        }
                    }

                } while (data->data_clientes.numero_cliente <= 0 || !clave_existente);

                cliente_actual = false;
            }

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Número de artículo: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_ventas.numero_articulo) != 1);

                if (data->data_ventas.numero_articulo <= 0 || data->data_ventas.numero_articulo > 100)

                    validar_errores_por_SO();

                else if (data->data_contador.articulos_neto > 0)
                    {
                        clave_existente = verificar_existencia_claves(data->data_files.file_articulos, data->data_dir.ruta_file_articulos, &data->data_ventas.numero_articulo, &file_articulos);

                        if (!clave_existente)
                        {
                            limpiar_terminal();
                            puts("El artículo ingresado no existe en el sistema. . .");
                            pausar_terminal();
                        }
                    }

            } while (data->data_ventas.numero_articulo <= 0 || data->data_ventas.numero_articulo > 100 || !clave_existente);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Cantidad a llevar: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_ventas.cantidad) != 1);

                if (data->data_ventas.cantidad < 1)

                    validar_errores_por_SO();

                else
                {
                    cantidad_existente = buscar_cantidades(data, &data->data_ventas.numero_articulo, &data->data_ventas.cantidad);

                    if (!cantidad_existente)
                    {
                        limpiar_terminal();
                        puts("No manejamos esa cantidad que usted pide. . .");
                        pausar_terminal();
                    }
                }

            } while (data->data_ventas.cantidad < 1 || !cantidad_existente);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Mes de venta (1-%d): ", mes_actual);
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_ventas.mes) != 1);

                if (data->data_ventas.mes < 1 || data->data_ventas.mes > mes_actual)

                    validar_errores_por_SO();


            } while (data->data_ventas.mes < 1 || data->data_ventas.mes > mes_actual);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Dia de venta: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_ventas.dia) != 1);

                if (!dia_valido(&data->data_ventas.dia, &data->data_ventas.mes, NULL, &file_ventas))

                    validar_errores_por_SO();

            } while (!dia_valido(&data->data_ventas.dia, &data->data_ventas.mes, NULL, &file_ventas));

            buscar_precios(data, &precio, &file_ventas, NULL);

            printf("Precio neto: $%.2f\n\n", precio);
            pausar_terminal();

            if (empleado_actual)
            {
                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de emplead@: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_ventas.numero_empleado) != 1);

                    if (data->data_ventas.numero_empleado <= 0 || data->data_ventas.numero_empleado > 20)

                        validar_errores_por_SO();

                    else if (data->data_contador.empleados_neto > 0)
                        {
                            clave_existente = verificar_existencia_claves(data->data_files.file_empleados, data->data_dir.ruta_file_empleados, &data->data_ventas.numero_empleado, &file_empleados);

                            if (!clave_existente)
                            {
                                limpiar_terminal();
                                puts("El empleado ingresado no existe en el sistema. . .");
                                pausar_terminal();
                            }
                        }

                } while (data->data_empleados.numero_empleado <= 0 || data->data_empleados.numero_empleado > 20 || !clave_existente);

                empleado_actual = false;
            }

            do
            {
                limpiar_terminal();

                printf("Agregar otro artículo? Si/No: ");
                limpiar_buffer_STDIN();
                fgets(existencia_articulos, sizeof(existencia_articulos), stdin);

                existencia_articulos[strcspn(existencia_articulos, "\n")] = '\0';

                convertir_cadena_a_minuscula(existencia_articulos);

                if (strcmp(existencia_articulos, "si") != 0 && strcmp(existencia_articulos, "no") != 0)

                    validar_errores_por_SO();
            } while (strcmp(existencia_articulos, "si") != 0 && strcmp(existencia_articulos, "no") != 0);

            if (strcmp(existencia_articulos, "no") == 0)
            {
                cliente_actual = true;
                empleado_actual = true;

                calcular_precios(data, &file_ventas, NULL);

                limpiar_terminal();

                data->data_files.file_clientes = fopen(data->data_dir.ruta_file_clientes, "rb");

                if (data->data_files.file_clientes == NULL)

                    printf("TOTAL DE LA VENTA AL CLIENTE #%d: $%.2f\n\n", data->data_ventas.numero_cliente, data->data_ventas.precio);

                else
                {
                    fseek(data->data_files.file_clientes, data->data_ventas.numero_cliente * sizeof(data->data_clientes), SEEK_SET);
                    fread(&data->data_clientes, sizeof(data->data_clientes), 1, data->data_files.file_clientes);

                    printf("TOTAL DE LA VENTA AL CLIENTE (%s): $%.2f\n\n", data->data_clientes.nombre_cliente, data->data_ventas.precio);

                }

                data->data_ventas.comision_empleado = 0.05;

                fwrite(&data->data_ventas, sizeof(data->data_ventas), 1, data->data_files.file_control_ventas);

                do
                {
                    limpiar_terminal();

                    printf("Desea facturar? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(facturar, sizeof(facturar), stdin);

                    facturar[strcspn(facturar, "\n")] = '\0';

                    convertir_cadena_a_minuscula(facturar);

                    if (strcmp(facturar, "si") != 0 && strcmp(facturar, "no") != 0)

                        validar_errores_por_SO();

                } while (strcmp(facturar, "si") != 0 && strcmp(facturar, "no") != 0);

                if (strcmp(facturar, "si") == 0)
                {
                    limpiar_terminal();

                    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

                    if (data->data_files.file_clientes == NULL)

                        printf("%40s%d\n\n", "FACTURA DE CLIENTE #", data->data_ventas.numero_cliente);

                    else

                        printf("%40s%s\n\n", "FACTURA DE CLIENTE: ", data->data_clientes.nombre_cliente);

                    printf("%-30s %-30s\n\n", "# ARTICULO", "CANTIDAD");

                    rewind(data->data_files.file_control_ventas);

                    while (fread(&data->data_ventas, sizeof(data->data_ventas), 1, data->data_files.file_control_ventas))

                        printf("%-30d %-30d\n", data->data_ventas.numero_articulo, data->data_ventas.cantidad);

                    printf("%-40s$%.2f\n\n", "PRECIO TOTAL DE COMPRA: ", data->data_ventas.precio);

                    data->data_files.file_empleados = fopen(data->data_dir.ruta_file_empleados, "rb");

                    if (data->data_files.file_empleados == NULL)

                        printf("%-40s: #%d\n", "L@ ANTENDIÓ EL/LA EMPLEAD@", data->data_ventas.numero_empleado);

                    else
                    {
                        fseek(data->data_files.file_empleados, data->data_ventas.numero_empleado * sizeof(data->data_empleados), SEEK_SET);
                        fread(&data->data_empleados, sizeof(data->data_empleados), 1, data->data_files.file_empleados);

                        printf("%-40s: %s\n", "L@ ANTENDIÓ EL/LA EMPLEAD@", data->data_empleados.nombre_empleado);

                        fclose(data->data_files.file_empleados);
                    }

                    printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                }

                data->data_files.file_articulos = fopen(data->data_dir.ruta_file_articulos, "rb+");

                if (data->data_files.file_articulos == NULL)

                    liberar_memoria_salida_de_error(&data->data_dir);

                fseek(data->data_files.file_articulos, data->data_ventas.numero_articulo * sizeof(data->data_articulos), SEEK_SET);
                fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

                data->data_articulos.inventario -= data->data_ventas.cantidad;

                fclose(data->data_files.file_articulos);

                do
                {
                    limpiar_terminal();

                    printf("Agregar otra venta? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(existencia_ventas, sizeof(existencia_ventas), stdin);

                    existencia_ventas[strcspn(existencia_ventas, "\n")] = '\0';

                    convertir_cadena_a_minuscula(existencia_ventas);

                    if (strcmp(existencia_ventas, "si") != 0 && strcmp(existencia_ventas, "no") != 0)

                        validar_errores_por_SO();

                } while (strcmp(existencia_ventas, "si") != 0 && strcmp(existencia_ventas, "no") != 0);
            }
        }

        fclose(data->data_files.file_control_ventas);

    }
}

extern void controlar_compras(struct Conjunto_Datos *data)
{
    char existencia_compras[3], existencia_articulos[3];
    bool proveedor_actual = true, clave_existente = false, proveedor_que_lo_maneja, punto_reorden_alcanzado = false;
    const int file_articulos = 1, file_proveedores = 3, file_compras = 2;
    float precio = 0.0;
    int numero_proveedor;
    static int numero_compra = 0;

    data->data_files.file_control_compras = fopen(data->data_dir.ruta_file_control_compras, "rb+");

    if (data->data_files.file_control_compras == NULL)

        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE CONTROL DE COMPRAS");

    else
    {


        do
        {
            limpiar_terminal();

            printf("Existen compras? Si/No: ");
            limpiar_buffer_STDIN();
            fgets(existencia_compras, sizeof(existencia_compras), stdin);

            existencia_compras[strcspn(existencia_compras, "\n")] = '\0';

            convertir_cadena_a_minuscula(existencia_compras);

            if (strcmp(existencia_compras, "si") != 0 && strcmp(existencia_compras, "no") != 0)

                validar_errores_por_SO();

        } while (strcmp(existencia_compras, "si") != 0 && strcmp(existencia_compras, "no") != 0);

        while (strcmp(existencia_compras, "si") == 0 || strcmp(existencia_articulos, "si") == 0)
        {
            if (proveedor_actual)
            {
                data->data_compras.precio = 0.0;
                numero_compra++;

                data->data_compras.id_compra = numero_compra;

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de proveedor: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_compras.numero_proveedor) != 1);

                    if (data->data_compras.numero_proveedor < 1 || data->data_compras.numero_proveedor > 10)

                        validar_errores_por_SO();

                    else
                    {
                        clave_existente = verificar_existencia_claves(data->data_files.file_proveedor, data->data_dir.ruta_file_proveedores, &data->data_compras.numero_proveedor, &file_proveedores);

                        if (!clave_existente)
                        {
                            limpiar_terminal();
                            puts("El proveedor ingresado no existe en el sistema. . .");
                            pausar_terminal();
                        }
                    }

                } while (data->data_compras.numero_proveedor < 1 || data->data_compras.numero_proveedor > 10 || !clave_existente);

                proveedor_actual = false;
            }

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Número de artículo: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_compras.numero_articulo) != 1);

                if (data->data_compras.numero_articulo < 1 || data->data_compras.numero_articulo > 100)

                    validar_errores_por_SO();

                else if (data->data_contador.articulos_neto > 0)
                    {
                        clave_existente = verificar_existencia_claves(data->data_files.file_articulos, data->data_dir.ruta_file_articulos, &data->data_compras.numero_articulo, &file_articulos);

                        if (!clave_existente)
                        {
                            limpiar_terminal();
                            puts("El artículo ingresado no existe en el sistema. . .");
                            pausar_terminal();
                        }
                        else
                        {
                            proveedor_que_lo_maneja = buscar_proveedor_articulo(data, &numero_proveedor);

                            if (!proveedor_que_lo_maneja)
                            {
                                limpiar_terminal();
                                puts("El proveedor que seleccionaste no maneja el artículo que pediste. . .");
                                pausar_terminal();
                            }
                            else
                            {
                                punto_reorden_alcanzado = verificar_articulo_punto_reorden(data->data_files.file_articulos, &data->data_articulos, data->data_dir.ruta_file_articulos, &data->data_compras.numero_articulo);

                                if (!punto_reorden_alcanzado)
                                {
                                    limpiar_terminal();
                                    puts("El artículo aún no puede ser reordenado. . .");
                                    pausar_terminal();
                                }
                            }
                        }
                    }

            } while (data->data_compras.numero_articulo < 1 || data->data_compras.numero_articulo > 100 || !clave_existente || !proveedor_que_lo_maneja || !punto_reorden_alcanzado);

            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Cantidad a comprar: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_compras.cantidad) != 1);

                if (data->data_compras.cantidad < 1)

                    validar_errores_por_SO();

            } while (data->data_compras.cantidad < 1);

            calcular_precios(data, &file_compras, &numero_proveedor);
            buscar_precios(data, &precio, &file_compras, &numero_proveedor);
            printf("Precio neto: $%.2f\n\n", precio);
            pausar_terminal();

            do
            {
                limpiar_terminal();

                printf("Agregar otro artículo? Si/No: ");
                limpiar_buffer_STDIN();
                fgets(existencia_articulos, sizeof(existencia_articulos), stdin);

                existencia_articulos[strcspn(existencia_articulos, "\n")] = '\0';

                convertir_cadena_a_minuscula(existencia_articulos);

                if (strcmp(existencia_articulos, "si") != 0 && strcmp(existencia_articulos, "no") != 0)

                    validar_errores_por_SO();

            } while (strcmp(existencia_articulos, "si") != 0 && strcmp(existencia_articulos, "no") != 0);

            if (strcmp(existencia_articulos, "si") != 0)
            {
                proveedor_actual = true;


                limpiar_terminal();

                data->data_files.file_proveedor = fopen(data->data_dir.ruta_file_proveedores, "rb");

                if (data->data_files.file_clientes == NULL)

                    printf("TOTAL DE LA COMPRA AL PROVEEDOR #%d: $%.2f\n\n", numero_proveedor, data->data_compras.precio);

                else
                {
                    fseek(data->data_files.file_proveedor, data->data_compras.numero_proveedor * sizeof(data->data_proveedores), SEEK_SET);
                    fread(&data->data_proveedores, sizeof(data->data_proveedores), 1, data->data_files.file_proveedor);

                    printf("TOTAL DE LA COMPRA AL PROVEEDOR (%s): $%.2f\n\n", data->data_proveedores.nombre_proveedor, data->data_compras.precio);

                }

                data->data_compras.saldo_pagar = data->data_compras.precio;

                fwrite(&data->data_compras, sizeof(data->data_compras), 1, data->data_files.file_control_compras);

                do
                {
                    limpiar_terminal();

                    printf("Agregar más compras? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(existencia_compras, sizeof(existencia_compras), stdin);

                    existencia_compras[strcspn(existencia_compras, "\n")] = '\0';

                    convertir_cadena_a_minuscula(existencia_compras);

                    if (strcmp(existencia_compras, "si") != 0 && strcmp(existencia_compras, "no") != 0)

                        validar_errores_por_SO();

                } while (strcmp(existencia_compras, "si") != 0 && strcmp(existencia_compras, "no") != 0);
            }
        }

        fclose(data->data_files.file_control_compras);

    }

}

extern void controlar_inventario(struct Conjunto_Datos *data)
{
    char recepcion[3];
    bool clave_existente, proveedor_pendiente_entrega, id_existente;
    const int file_proveedores = 3, file_inventario = 5;
    int auxiliar_id = 1;
    float saldo_pagar = 0.0;

    data->data_files.file_articulos = fopen(data->data_dir.ruta_file_articulos, "rb");
    data->data_files.file_control_compras = fopen(data->data_dir.ruta_file_control_compras, "rb");

    if (data->data_files.file_articulos == NULL || data->data_files.file_control_compras == NULL)

        fprintf(stderr, "ERROR: NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO DE CONTROL DE INVENTARIOS");

    else
    {
        do
        {
            limpiar_terminal();

            printf("Existen recepciones? Si/No: ");
            limpiar_buffer_STDIN();
            fgets(recepcion, sizeof(recepcion), stdin);

            recepcion[strcspn(recepcion, "\n")] = '\0';

            convertir_cadena_a_minuscula(recepcion);

            if (strcmp(recepcion, "si") != 0 && strcmp(recepcion, "no") != 0)

                validar_errores_por_SO();

        } while (strcmp(recepcion, "si") != 0 && strcmp(recepcion, "no") != 0);

        while (strcmp(recepcion, "si") == 0 && buscar_existencia_articulos_proveedor(data->data_files.file_control_compras, data->data_dir.ruta_file_control_compras, &data->data_compras))
        {
            do
            {
                do
                {
                    limpiar_terminal();

                    printf("Número de proveedor: ");
                    limpiar_buffer_STDIN();
                } while (scanf("%d", &data->data_inventario.numero_proveedor) != 1);

                if (data->data_inventario.numero_proveedor < 1 || data->data_inventario.numero_proveedor > 10)

                    validar_errores_por_SO();

                else
                {
                    clave_existente = verificar_existencia_claves(data->data_files.file_proveedor, data->data_dir.ruta_file_proveedores,&data->data_inventario.numero_proveedor, &file_proveedores);

                    if (!clave_existente)
                    {
                        limpiar_terminal();
                        puts("El proveedor ingresado no existe en el sistema. . .");
                        pausar_terminal();
                    }
                }

            } while (data->data_compras.numero_proveedor < 1 || data->data_compras.numero_proveedor > 10 || !clave_existente);

            proveedor_pendiente_entrega = buscar_existencia_articulos_proveedor(data->data_files.file_control_compras, data->data_dir.ruta_file_control_compras, &data->data_compras);

            if (!proveedor_pendiente_entrega)
            {
                limpiar_terminal();
                puts("EL PROVEEDOR YA HA REALIZADO TODAS LAS ENTREGAS PENDIENTES");
            }
            else
            {
                rewind(data->data_files.file_control_compras);

                printf("%-30s %-30s %-50s %s\n\n", "ID COMPRA", "ARTÍCULO", "DESCRIPCIÓN", "CANTIDAD");

                while (fread(&data->data_compras, sizeof(data->data_compras), 1, data->data_files.file_control_compras))
                {
                    if (data->data_compras.id_compra != 0)
                    {

                        fseek(data->data_files.file_articulos, data->data_compras.numero_articulo * sizeof(data->data_articulos), SEEK_SET);
                        fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

                        printf("%-30d %-30d %-50s %d\n", data->data_compras.id_compra, data->data_compras.numero_articulo, data->data_articulos.descripcion_articulo, data->data_compras.cantidad);

                        if (data->data_compras.id_compra == auxiliar_id + 1)

                            printf("%.2f\n\n", saldo_pagar);

                        auxiliar_id = data->data_compras.id_compra;
                        saldo_pagar = data->data_compras.saldo_pagar;
                    }
                }

                do
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Número de compra: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", &data->data_inventario.numero_compra) != 1);

                    if (data->data_inventario.numero_compra < 1)

                        validar_errores_por_SO();

                    else
                    {
                        id_existente = verificar_existencia_claves(data->data_files.file_control_compras, data->data_dir.ruta_file_control_compras, &data->data_inventario.numero_compra, &file_inventario);

                        if (!id_existente)
                        {
                            limpiar_terminal();
                            puts("El ID ingresado no existe en el sistema. . .");
                            pausar_terminal();
                        }
                    }
                } while (data->data_inventario.numero_compra < 1 || !id_existente);

                do
                {
                    limpiar_terminal();

                    printf("La orden fué recibida? Si/No: ");
                    limpiar_buffer_STDIN();
                    fgets(data->data_inventario.recibido, sizeof(data->data_inventario.recibido), stdin);

                    data->data_inventario.recibido[strcspn(data->data_inventario.recibido, "\n")] = '\0';

                    convertir_cadena_a_minuscula(data->data_inventario.recibido);

                    if (strcmp(data->data_inventario.recibido, "si") != 0 && strcmp(data->data_inventario.recibido, "no") != 0)

                        validar_errores_por_SO();

                } while (strcmp(data->data_inventario.recibido, "si") != 0 && strcmp(data->data_inventario.recibido, "no") != 0);

                if (strcmp(data->data_inventario.recibido, "si") == 0)
                {
                    realizar_cambios_inventario(data);

                    limpiar_terminal();
                    puts("SE HA CONFIRMADO CORRECTAMENTE LA RECEPCIÓN EN EL INVENTARIO!");
                    pausar_terminal();
                }

                if (buscar_existencia_articulos_proveedor(data->data_files.file_control_compras, data->data_dir.ruta_file_control_compras, &data->data_compras))
                {
                    do
                    {
                        limpiar_terminal();

                        printf("Existen más recepciones? Si/No: ");
                        limpiar_buffer_STDIN();
                        fgets(recepcion, sizeof(recepcion), stdin);

                        recepcion[strcspn(recepcion, "\n")] = '\0';

                        convertir_cadena_a_minuscula(recepcion);

                        if (strcmp(recepcion, "si") != 0 && strcmp(recepcion, "no") != 0)

                            validar_errores_por_SO();

                    } while (strcmp(recepcion, "si") != 0 && strcmp(recepcion, "no") != 0);
                }
                else
                {
                    limpiar_terminal();
                    puts("TODOS LOS PEDIDOS HAN SIDO CONFIRMADOS DE ENTREGA!");
                    pausar_terminal();
                }
            }
        }
    }
}

extern bool verificar_articulo_punto_reorden(FILE *file, struct Datos_Articulos *data_articles, const char *dir, const int *numero_articulo)
{
    file = fopen(dir, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "NO SE PUDIERON OBTENER LOS DATOS. . .");
        exit(EXIT_FAILURE);
    }

    fseek(file, (*numero_articulo) * sizeof(*data_articles), SEEK_SET);
    fread(data_articles, sizeof(*data_articles), 1, file);

    if (data_articles->inventario <= data_articles->punto_reorden)

        return true;

    return false;

}

extern void manejar_reportes(struct Conjunto_Datos *data)
{

}

extern void refrescar_contadores(struct Conjunto_Datos *data)
{
    data->data_files.file_articulos = fopen(data->data_dir.ruta_file_articulos, "rb");
    data->data_files.file_empleados = fopen(data->data_dir.ruta_file_empleados, "rb");
    data->data_files.file_proveedor = fopen(data->data_dir.ruta_file_proveedores, "rb");
    data->data_files.file_clientes = fopen(data->data_dir.ruta_file_clientes, "rb");

    rewind(data->data_files.file_articulos);
    rewind(data->data_files.file_empleados);
    rewind(data->data_files.file_proveedor);

    if (data->data_files.file_clientes != NULL)

        rewind(data->data_files.file_clientes);

    while (fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos))
    {
        if (data->data_articulos.numero_articulo != 0)

            data->data_contador.articulos_neto++;
    }

    if (data->data_files.file_clientes != NULL)
    {
        while (fread(&data->data_clientes, sizeof(data->data_clientes), 1, data->data_files.file_clientes) == 1)

            data->data_contador.clientes_neto++;

        fclose(data->data_files.file_clientes);
    }

    while (fread(&data->data_empleados, sizeof(data->data_empleados), 1, data->data_files.file_empleados))
    {
        if (data->data_empleados.numero_empleado != 0)

            data->data_contador.empleados_neto++;
    }

    while (fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos))
    {
        if (data->data_articulos.numero_articulo != 0)

            data->data_contador.articulos_neto++;
    }

    fclose(data->data_files.file_articulos);
    fclose(data->data_files.file_empleados);
    fclose(data->data_files.file_proveedor);
}

extern void buscar_precios(struct Conjunto_Datos *data, float *precio_articulo, const int *t_o_f, const int *proveedor)
{
    data->data_files.file_articulos = fopen(data->data_dir.ruta_file_articulos, "rb");

    if (data->data_files.file_articulos == NULL)

        liberar_memoria_salida_de_error(&data->data_dir);

    if (*t_o_f == 1)
    {
        fseek(data->data_files.file_articulos, data->data_ventas.numero_articulo * sizeof(data->data_articulos), SEEK_SET);
        fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

        (*precio_articulo) = data->data_articulos.precio_venta;
    }
    else
    {
        fseek(data->data_files.file_articulos, data->data_compras.numero_articulo * sizeof(data->data_articulos), SEEK_SET);
        fread(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

        (*precio_articulo) = *(data->data_articulos.precio_compra + (*proveedor));
    }
    

    fclose(data->data_files.file_articulos);
}

extern bool buscar_existencia_articulos_proveedor(FILE *file_compras, const char *dir, struct Datos_Control_Compras *data_compras)
{
    file_compras = fopen(dir, "rb");

    if (file_compras == NULL)

        return false;

    rewind(file_compras);

    while (fread(data_compras, sizeof(*data_compras), 1, file_compras))
    {
        if (data_compras->id_compra != 0)
        {
            fclose(file_compras);
            return true;
        }
    }


    fclose(file_compras);
    return false;
}

extern bool buscar_cantidades(struct Conjunto_Datos *all_data, const int *numero_articulo, const int *cantidad_ingresada)
{
    all_data->data_files.file_articulos = fopen(all_data->data_dir.ruta_file_articulos, "rb");

    if (all_data->data_files.file_articulos == NULL)
    {
        fprintf(stderr, "NO SE PUDO LEER CORRECTAMENTE EL FICHERO. . .");
        exit(EXIT_FAILURE);
    }

    fseek(all_data->data_files.file_articulos, (*numero_articulo) * sizeof(all_data->data_articulos), SEEK_SET);
    fread(&all_data->data_articulos, sizeof(all_data->data_articulos), 1, all_data->data_files.file_articulos);

    fclose(all_data->data_files.file_articulos);

    if ((*cantidad_ingresada) > all_data->data_articulos.inventario || ((*cantidad_ingresada) - all_data->data_articulos.inventario < all_data->data_articulos.punto_reorden))

        return false;

    return true;
}

extern void calcular_precios(struct Conjunto_Datos *all_data, const int *t_o_f, const int *proveedor)
{
    if (*t_o_f == 1)
    {
        all_data->data_files.file_clientes = fopen(all_data->data_dir.ruta_file_clientes, "rb");

        if (all_data->data_files.file_clientes == NULL)
        {
            fprintf(stderr, "ERROR AL OBTENER LOS DATOS NECESARIOS. . .");
            exit(EXIT_FAILURE);
        }

        fseek(all_data->data_files.file_clientes, all_data->data_ventas.numero_cliente * sizeof(all_data->data_clientes), SEEK_SET);
        fread(&all_data->data_clientes, sizeof(all_data->data_clientes), 1, all_data->data_files.file_clientes);
    }
    else
    {
        all_data->data_files.file_proveedor = fopen(all_data->data_dir.ruta_file_proveedores, "rb");

        if (all_data->data_files.file_proveedor == NULL)
        {
            fprintf(stderr, "ERROR AL OBTENER LOS DATOS NECESARIOS. . .");
            exit(EXIT_FAILURE);
        }

        fseek(all_data->data_files.file_proveedor, all_data->data_compras.numero_proveedor * sizeof(all_data->data_proveedores), SEEK_SET);
        fread(&all_data->data_proveedores, sizeof(all_data->data_proveedores), 1, all_data->data_files.file_proveedor);
    }

    all_data->data_files.file_articulos = fopen(all_data->data_dir.ruta_file_articulos, "rb");

    if (all_data->data_files.file_articulos == NULL)
    {
        fprintf(stderr, "ERROR AL OBTENER LOS DATOS NECESARIOS. . .");
        exit(EXIT_FAILURE);
    }


    fseek(all_data->data_files.file_articulos, all_data->data_ventas.numero_articulo * sizeof(all_data->data_articulos), SEEK_SET);
    fread(&all_data->data_articulos, sizeof(all_data->data_articulos), 1, all_data->data_files.file_articulos);

    if (*t_o_f == 1)
    {
        all_data->data_ventas.precio = (all_data->data_ventas.cantidad * all_data->data_articulos.precio_venta);
        all_data->data_ventas.precio -= (all_data->data_ventas.precio * all_data->data_clientes.descuento_cliente);

        fclose(all_data->data_files.file_clientes);
    }
    else
    {
        all_data->data_compras.precio = (all_data->data_compras.cantidad * (*(all_data->data_articulos.precio_compra + (*proveedor))));
        all_data->data_compras.precio -= (all_data->data_compras.precio * all_data->data_proveedores.descuento);

        fclose(all_data->data_files.file_proveedor);
    }

    fclose(all_data->data_files.file_articulos);

}

extern void realizar_cambios_inventario(struct Conjunto_Datos *all_data)
{
    rewind(all_data->data_files.file_control_compras);

    while (fread(&all_data->data_compras, sizeof(all_data->data_compras), 1, all_data->data_files.file_control_compras))
    {
        if (all_data->data_inventario.numero_compra == all_data->data_compras.id_compra)
        {
            fseek(all_data->data_files.file_articulos, (all_data->data_compras.numero_articulo) * sizeof(all_data->data_articulos), SEEK_SET);
            fread(&all_data->data_articulos, sizeof(all_data->data_articulos), 1, all_data->data_files.file_articulos);

            all_data->data_articulos.inventario += all_data->data_compras.cantidad; // Agrega a inventario
            all_data->data_compras.id_compra = 0; // Entregada
            all_data->data_compras.saldo_pagar = 0.0; // Pagado
        }
        else if (all_data->data_inventario.numero_compra < all_data->data_compras.id_compra)

                return;

    }
}

extern bool buscar_proveedor_articulo(struct Conjunto_Datos *all_data, int *proveedor_encontrado)
{
    int i;

    all_data->data_files.file_articulos = fopen(all_data->data_dir.ruta_file_articulos, "rb");

    if (all_data->data_files.file_articulos == NULL)
    {
        fprintf(stderr, "NO SE PUDIERON OBTENER LOS DATOS NECESARIOS");
        exit(EXIT_FAILURE);
    }

    fseek(all_data->data_files.file_articulos, all_data->data_compras.numero_articulo * sizeof(all_data->data_articulos), SEEK_SET);

    fread(&all_data->data_articulos, sizeof(all_data->data_articulos), 1, all_data->data_files.file_articulos);

    fclose(all_data->data_files.file_articulos);

    for ( i = 0; i < all_data->data_contador.proveedores_neto; i++)
    {
        if (*(all_data->data_articulos.numero_proveedor + i) == all_data->data_compras.numero_proveedor)
        {
            *proveedor_encontrado = i;
            return true;
        }
    }


    return false;
}

extern bool es_bisiesto(const int *year)
{
    if ( (*year) % 4 == 0 && ((*year) % 100 != 0 || (*year) % 400 == 0) )

        return true;

    return false;
}

extern bool mes_30_dias(const int *month)
{
    switch (*month)
    {
        case 1: // Enero
        case 3: // Marzo
        case 5: // Mayo
        case 7: // Julio
        case 8: // Agosto
        case 10: // Octubre
        case 12: // Diciembre

            return false;

        default: // Abril, Junio, Septiembre, Noviembre

            return true;
    }
}

extern bool dia_valido(const int *day, const int *month, const int *year, const int *t_o_f)
{
    int current_year, current_month, current_day;
    time_t tiempo = time(NULL);
    struct tm *fecha_actual = localtime(&tiempo);

    current_year = fecha_actual->tm_year + 1900;
    current_month = fecha_actual->tm_mon + 1;
    current_day = fecha_actual->tm_mday;

    switch (*t_o_f)
    {
        case 1:

            if (    (( (*month) == 2 && !es_bisiesto(&current_year) ) &&  ( (*day) < 1 || (*day) > 28) ) ||
                    ( ( (*month) == 2 && es_bisiesto(&current_year) ) &&  ( (*day) < 1 || (*day) > 29) ) ||
                    (mes_30_dias(month) &&  ((*day) < 1 || (*day) > 30)) ||
                    (!mes_30_dias(month) &&  ((*day) < 1 || (*day) > 31)) ||
                    ((*month) == current_month && (*day) > current_day))

                return false;

            break;
        case 2:

            if (    (( (*month) == 2 && !es_bisiesto(year) ) &&  ( (*day) < 1 || (*day) > 28) ) ||
                    ( ( (*month) == 2 && es_bisiesto(year) ) &&  ( (*day) < 1 || (*day) > 29) ) ||
                    (mes_30_dias(month) &&  ((*day) < 1 || (*day) > 30)) ||
                    (!mes_30_dias(month) &&  ((*day) < 1 || (*day) > 31)))

                return false;

            break;

        default:
            if (    (( (*month) == 2 && !es_bisiesto(year) ) &&  ( (*day) < 1 || (*day) > 28) ) ||
                    ( ( (*month) == 2 && es_bisiesto(year) ) &&  ( (*day) < 1 || (*day) > 29) ) ||
                    (mes_30_dias(month) &&  ((*day) < 1 || (*day) > 30)) ||
                    (!mes_30_dias(month) &&  ((*day) < 1 || (*day) > 31)) ||
                    ((*year) == current_year && (*month) == current_month && (*day) > current_day))

                return false;
    }

    return true;

}

extern void convertir_cadena_a_minuscula(char *caracter)
{
    while (*caracter != '\0')
    {
        if (isalpha(*caracter))
        {
            *caracter = tolower(*caracter);
            caracter++;
        }
    }
}

extern bool verificar_existencia_claves(FILE *file, const char *dir, int *clave, const int *t_o_f)
{
    struct Datos_Articulos articles;
    struct Datos_Clientes customers;
    struct Datos_Empleados employees;
    struct Datos_Proveedores suppliers;
    struct Datos_Control_Compras buy;
    struct Directorios pwd;

    if (file == NULL)
    {
        file = fopen(dir, "rb");

        if (file == NULL)

            liberar_memoria_salida_de_error(&pwd);

    }

    switch (*t_o_f)
    {
        case 1: // Articulos

            fseek(file, (*clave) * sizeof(articles), SEEK_SET);
            fread(&articles, sizeof(articles), 1, file);

            fclose(file);
            if (articles.numero_articulo == (*clave))

                return true;

            break;

        case 2: // Clientes

            rewind(file);

            while (fread(&customers, sizeof(customers), 1, file))
            {
                if ( (*clave) == customers.numero_cliente )
                {
                    fclose(file);
                    return true;
                }
            }

            break;

        case 3: // Proveedores

            fseek(file, (*clave) * sizeof(suppliers), SEEK_SET);
            fread(&suppliers, sizeof(suppliers), 1, file);

            fclose(file);

            if (suppliers.numero_proveedor == (*clave))

                return true;

            break;

        case 4: // Empleados

            rewind(file);

            while (fread(&employees, sizeof(employees), 1, file))
            {
                if ( (*clave) == employees.numero_empleado )
                {
                    fclose(file);
                    return true;
                }
            }

            break;

        case 5: // Control de Inventario

            rewind(file);

            while (fread(&buy, sizeof(buy), 1, file))
            {
                if ( (*clave) == buy.id_compra )
                {
                    fclose(file);
                    return true;
                }
            }

        break;
    }

    fclose(file);
    return false;
}

extern bool buscar_proveedores(const int *proveedor, const int *total_proveedores)
{
    int i;

    for ( i = 0; i < *total_proveedores; i++)
    {
        if (*proveedor == (*(total_proveedores) + i))

            return true;

    }

    return false;
}

extern bool validar_cadenas(const char *caracter)
{
    while (*caracter != '\0')
    {
        if (!isalpha(*caracter) && *caracter != 32)

            return false;

        caracter++;
    }

    return true;
}

extern void liberar_memoria_salida_de_error(struct Directorios *dir)
{
    fprintf(stderr, "NO SE PUDO OBTENER CORRECTAMENTE EL/LOS FICHERO/S. . .");

    free(dir->ruta_file_articulos);
    free(dir->ruta_file_clientes);
    free(dir->ruta_file_control_compras);
    free(dir->ruta_file_control_ventas);
    free(dir->ruta_file_empleados);
    free(dir->ruta_file_proveedores);

    exit(EXIT_FAILURE);
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