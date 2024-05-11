#include "Cabeceras.h"

struct Direcciones_Fecha
{
    char direccion[200], rfc[14];
    char correo_electronico[30]; // @ y punto despues
    int anio, mes, dia;          //  >=1950, 1-12 inclusive
};

struct Datos_Articulos
{
    int numero_articulo, numero_proveedor[10], punto_reorden; // Mayor a cero, proveedores a lo mucho 10
    char descripcion_articulo[200];                       // Validar letras, numeros, espacios
    long int inventario;                                  // Mayor o igual a cero
    double precio_compra, precio_venta;
};

struct Datos_Proveedores
{
    struct Direcciones_Fecha datos;
    int numero_proveedor;               // mayor a cero
    char nombre_proveedor[50]; // Letras, espacios; 13 caracteres       //  >=1950, 1-12 inclusive
    double descuento, saldo_por_pagar;  // Campo calculado
};

struct Datos_Clientes
{
    struct Direcciones_Fecha datos;
    int numero_cliente;               // Mayor a cero
    char nombre_cliente[50]; // Letras, espacios
    double descuento_cliente;         // 0 - 1
};

struct Datos_Empleados
{
    struct Direcciones_Fecha datos;
    int numero_empleado;      // MAX_BYTES - MAX_BYTES0
    char nombre_empleado[50]; // Letras, espacios
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
};

struct Directorios
{
    char *ruta_file_articulos;
    char *ruta_file_empleados;
    char *ruta_file_clientes;
    char *ruta_file_proveedores;
    char *ruta_file_control_compras;
    char *ruta_file_control_ventas;
    char *ruta_file_control_inventarios;
};

struct Conjunto_Datos
{
    struct Datos_Articulos data_articulos;
    struct Datos_Clientes data_clientes;
    struct Datos_Empleados data_empleados;
    struct Datos_Proveedores data_proveedores;
    struct Files_Requeridos data_files;
    struct Contador_Datos data_contador;
    struct Directorios data_dir;
};

// FUNCIONES PRINCIPALES

extern bool create_binary_files(struct Conjunto_Datos *);
extern void capturar_articulos(struct Conjunto_Datos *);
extern void capturar_empleados(struct Conjunto_Datos *);
extern void capturar_clientes(struct Conjunto_Datos *);
extern void capturar_proveedores(struct Conjunto_Datos *);
extern void controlar_ventas(struct Conjunto_Datos *);
extern void controlar_compras(struct Conjunto_Datos *);
extern void controlar_inventario(struct Conjunto_Datos *);
extern void manejar_reportes();
extern void refrescar_contadores(struct Conjunto_Datos *);

// VALIDACIONES

extern bool es_bisiesto(const int *);
extern bool mes_30_dias(const int *);
extern bool dia_valido(const int *, const int *, const int *, const int *);
extern void convertir_cadena_a_minuscula(char *);
extern bool verificar_articulo_proveedor();
extern bool verificar_existencia_claves(FILE *, int *, const int *);
extern bool verificar_existencia_proveedor(FILE *, struct Datos_Proveedores *, const int *, const char *);
extern bool buscar_proveedores(FILE *, int *, const char *);
extern bool validar_cadenas(const char *);

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

    datos_struct.data_dir.ruta_file_control_inventarios = (char *) malloc(MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_control_ventas == NULL)
    {
        free(datos_struct.data_dir.ruta_file_articulos);
        free(datos_struct.data_dir.ruta_file_clientes);
        free(datos_struct.data_dir.ruta_file_empleados);
        free(datos_struct.data_dir.ruta_file_proveedores);
        free(datos_struct.data_dir.ruta_file_control_compras);
        free(datos_struct.data_dir.ruta_file_control_ventas);

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

    getcwd(datos_struct.data_dir.ruta_file_control_inventarios , sizeof(datos_struct.data_dir.ruta_file_control_inventarios) * MAX_BYTES);
    strcat(datos_struct.data_dir.ruta_file_control_inventarios, "/Files_muebleria/control_inventario.dat");

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
                {
                    capturar_clientes(&datos_struct);
                }
                else
                {

                }

                break;

            case 3:
                if (datos_struct.data_contador.empleados_neto < 20)
                {
                    capturar_empleados(&datos_struct);
                }
                else
                {
                    /* code */
                }
                break;

            case 4:
                if (datos_struct.data_contador.proveedores_neto < 10)
                {
                    capturar_proveedores(&datos_struct);
                }
                else
                {
                    /* code */
                }
                break;

            case 5:
                if (datos_struct.data_contador.clientes_neto > 0)
                {
                    /* code */
                }
                else
                {
                    puts("La mueblería no está lista para vender aún. . .");
                }
                break;

            case 6:
                if (datos_struct.data_contador.proveedores_neto > 0)
                {
                    /* code */
                }
                else
                {
                    puts("No existen proveedores para surtir artículos. . .");
                }
                break;

            case 7:
                if (false)
                {
                    /* code */
                } /* code */
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
                free(datos_struct.data_dir.ruta_file_articulos);
                free(datos_struct.data_dir.ruta_file_clientes);
                free(datos_struct.data_dir.ruta_file_empleados);
                free(datos_struct.data_dir.ruta_file_proveedores);
                break;
            }

            if (opcion != 9)

                pausar_terminal();

        } while (opcion != 9);

        limpiar_terminal();
        puts("Operación finalizada con éxito");
    }

}

extern bool create_binary_files(struct Conjunto_Datos *data_all)
{
    int i;
    char respuesta[3];
    bool entornos_creados = false;
    struct Datos_Articulos articles = {0, {0}, 0, "", 0L, 0.0L, 0.0L};
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
    int i;
    const int type_of_file = 1;

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
                        clave_existente = verificar_existencia_claves(data->data_files.file_articulos, &data->data_articulos.numero_articulo, &type_of_file);

                        if (clave_existente)
                        {
                            limpiar_terminal();
                            puts("La clave ingresada ya existe en el sistema. . .");
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

            provedor_articulo = true;
            i = 0;

            while (i < data->data_contador.proveedores_neto && provedor_articulo)
            {
                bool proveedor_existente;

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

                        proveedor_existente = verificar_existencia_proveedor(data->data_files.file_proveedor, &data->data_proveedores, &data->data_articulos.numero_proveedor[i], data->data_dir.ruta_file_proveedores);

                } while (data->data_articulos.numero_proveedor[i] < 1 || !proveedor_existente);

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

            data->data_contador.articulos_neto++;

            fseek(data->data_files.file_articulos, data->data_contador.articulos_neto * sizeof(data->data_articulos), SEEK_SET);
            fwrite(&data->data_articulos, sizeof(data->data_articulos), 1, data->data_files.file_articulos);

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

        fclose(data->data_files.file_articulos);
    }
}

extern void capturar_clientes(struct Conjunto_Datos *data)
{
    char existencia_cliente[3], expresion[] = "^[A-Za-z0-9._-]+@[a-z]+\\.[a-z]{2,}$";
    char expresion_3[] = "^([A-Z]{4})([0-9]{6})([A-Z0-9]{3})$";
    char expresion_2[] = "^Calle #([0-9]+) Colonia ([A-Za-z ]+), Municipio ([A-Za-z ]+), Estado ([A-Za-z ]+)\\.$";
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
                            clave_existente = verificar_existencia_claves(data->data_files.file_clientes, &data->data_clientes.numero_cliente, &type_of_file);

                            if (clave_existente)
                            {
                                limpiar_terminal();
                                puts("La clave ingresada ya existe en el sistema. . .");
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
                            "NOTA!: Cambia los campos con * con tus datos, e ignorando todos los parentesis\n"
                            "(Calle #(*tu_numero) Colonia (*tu_colonia), Municipio (*tu_municipio), Estado (*tu_estado).)");
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
    char expresion_2[] = "^Calle #([0-9]+) Colonia ([A-Za-z ]+), Municipio ([A-Za-z ]+), Estado ([A-Za-z ]+)\\.$";
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

                    if (data->data_empleados.numero_empleado <= 0 || data->data_empleados.numero_empleado > 20)

                        validar_errores_por_SO();
                    else if (data->data_contador.empleados_neto > 0)
                        {
                            clave_existente = verificar_existencia_claves(data->data_files.file_empleados, &data->data_empleados.numero_empleado, &type_of_file);

                            if (clave_existente)
                            {
                                limpiar_terminal();
                                puts("La clave ingresada ya existe en el sistema. . .");
                            }
                        }

                } while (data->data_empleados.numero_empleado <= 0 || data->data_empleados.numero_empleado > 20 || clave_existente);

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
                            "NOTA!: Cambia los campos con * con tus datos, e ignorando todos los parentesis\n"
                            "(Calle #(*tu_numero) Colonia (*tu_colonia), Municipio (*tu_municipio), Estado (*tu_estado).)");
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
    char expresion_2[] = "^Calle #([0-9]+) Colonia ([A-Za-z ]+), Municipio ([A-Za-z ]+), Estado ([A-Za-z ]+)\\.$";
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
                            clave_existente = verificar_existencia_claves(data->data_files.file_proveedor, &data->data_proveedores.numero_proveedor, &type_of_file);

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
                            "NOTA!: Cambia los campos con * con tus datos, e ignorando todos los parentesis\n"
                            "(Calle #(*tu_numero) Colonia (*tu_colonia), Municipio (*tu_municipio), Estado (*tu_estado).)");
                    limpiar_buffer_STDIN();
                    fgets(data->data_proveedores.datos.direccion, sizeof(data->data_proveedores.datos.direccion), stdin);

                    *(data->data_proveedores.datos.direccion + (strcspn(data->data_proveedores.datos.direccion, "\n"))) = '\0';

                    regex_2 = regexec(&regular_2, data->data_proveedores.datos.direccion, 0, NULL, 0);

                    if (regex_2 != 0)

                        validar_errores_por_SO();

                } while (regex_2 != 0);

                data->data_contador.proveedores_neto++;

                fseek(data->data_files.file_proveedor, data->data_contador.proveedores_neto * sizeof(data->data_proveedores), SEEK_SET);
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

}

extern void controlar_compras(struct Conjunto_Datos *data)
{

}

extern void controlar_inventario(struct Conjunto_Datos *data)
{

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
    /* if (    ((data->data_clientes.datos.mes == 2 && !es_bisiesto(&data->data_clientes.datos.anio))
        &&  (data->data_clientes.datos.dia < 1 || data->data_clientes.datos.dia > 28)) ||
            ((data->data_clientes.datos.mes == 2 && es_bisiesto(&data->data_clientes.datos.anio))
        &&  (data->data_clientes.datos.dia < 1 || data->data_clientes.datos.dia > 29)) ||
            (mes_30_dias(&data->data_clientes.datos.mes)
        &&  data->data_clientes.datos.dia < 1 || data->data_clientes.datos.dia > 30) ||
            (!mes_30_dias(&data->data_clientes.datos.mes)
        &&  data->data_clientes.datos.dia < 1 || data->data_clientes.datos.dia > 31))
    {

    } */

    int current_year, current_month, current_day;
    time_t tiempo = time(NULL);
    struct tm *fecha_actual = localtime(&tiempo);

    current_year = fecha_actual->tm_year + 1900;
    current_month = fecha_actual->tm_mon + 1;
    current_day = fecha_actual->tm_mday;

    switch (*t_o_f)
    {
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

extern bool verificar_existencia_claves(FILE *file, int *clave, const int *t_o_f)
{
    struct Datos_Articulos articles;
    struct Datos_Clientes customers;
    struct Datos_Empleados employees;
    struct Datos_Proveedores suppliers;

    switch (*t_o_f)
    {
        case 1: // Articulos

            fseek(file, (*clave) * sizeof(articles), SEEK_SET);
            fread(&articles, sizeof(articles), 1, file);

            if (articles.numero_articulo == (*clave))

                return true;

            break;

        case 2: // Clientes

            rewind(file);

            while (fread(&customers, sizeof(customers), 1, file))
            {
                if ( (*clave) == customers.numero_cliente )

                    return true;

            }

            break;

        case 3: // Proveedores

            fseek(file, (*clave) * sizeof(suppliers), SEEK_SET);
            fread(&suppliers, sizeof(suppliers), 1, file);

            if (suppliers.numero_proveedor == (*clave))

                return true;

            break;

        case 4: // Empleados

            fseek(file, (*clave) * sizeof(employees), SEEK_SET);
            fread(&employees, sizeof(employees), 1, file);

            if (employees.numero_empleado == (*clave))

                return true;

            break;
    }

    return false;
}

bool verificar_existencia_proveedor(FILE *archivo_proveedores, struct Datos_Proveedores *data, const int *clave, const char *directorio_proveedores)
{
    archivo_proveedores = fopen(directorio_proveedores, "rb");

    if (archivo_proveedores == NULL)

        fprintf(stderr, "ERROR! ARCHIVO PROVEEDORES NO ES ACCESIBLE DE MOMENTO. . .");

    else
    {
        fseek(archivo_proveedores, (*clave) * sizeof(*data), SEEK_SET);
        fread(data, sizeof(*data), 1, archivo_proveedores);

        if ((*clave) == data->numero_proveedor)

            return true;

        fclose(archivo_proveedores);
    }

    return false;
}

/* extern bool buscar_proveedores(FILE *archivo_proveedores, int *clave_proveedor, const char *directorio_proveedores)
{

}
 */
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