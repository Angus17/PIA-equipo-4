#include "Cabeceras.h"

struct Direcciones_Fecha
{
    char direccion[200];
    char correo_electronico[30]; // @ y punto despues
    int anio, mes, dia;          //  >=1950, 1-12 inclusive
};

struct Datos_Articulos
{
    int numero_articulo, numero_proveedor, punto_reorden; // Mayor a cero, proveedores a lo mucho 10
    char descripcion_articulo[200];                       // Validar letras, numeros, espacios
    long int inventario;                                  // Mayor o igual a cero
    double precio_compra, precio_venta;
};

struct Datos_Proveedores
{
    struct Direcciones_Fecha datos;
    int numero_proveedor;               // mayor a cero
    char nombre_proveedor[50], rfc[13]; // Letras, espacios; 13 caracteres
    char correo_electronico[30];        // @ y punto despues
    int anio, mes, dia;                 //  >=1950, 1-12 inclusive
    char direccion_proveedor[200];      // letras, espacios, numeros
    double descuento, saldo_por_pagar;  // Campo calculado
};

struct Datos_Clientes
{
    struct Direcciones_Fecha datos;
    int numero_cliente;               // Mayor a cero
    char nombre_cliente[50], rfc[13]; // Letras, espacios
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
extern void capturar_empleados(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
extern void capturar_clientes(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
extern void capturar_proveedores(struct Files_Requeridos *, struct Conjunto_Datos *, int *, const char *);
extern void controlar_ventas();
extern void controlar_compras();

// VALIDACIONES

extern void convertir_cadena_a_minuscula(char *);
extern bool verificar_articulo_proveedor(struct );
extern bool verificar_existencia_claves(FILE *, struct Conjunto_Datos *, int *);
extern bool verificar_datos_existencia(FILE *, struct Contador_Datos *, int *, int *);
extern bool verificar_existencia_proveedor(FILE *, struct Datos_Proveedores *, int *, const char *);
extern bool buscar_proveedores(FILE *, int *, const char *);
extern bool validar_cadenas(char *);

// FUNCIONES PARA EL SISTEMA

void validar_errores_por_SO();
void limpiar_buffer_STDIN();
void limpiar_terminal();
void pausar_terminal();

int main(void)
{
    struct Conjunto_Datos datos_struct;
    bool existencia_proveedores;
    int opcion;

    setlocale(LC_ALL, "es_MX.UTF-8");

    datos_struct.data_dir.ruta_file_articulos = (char *) malloc(sizeof(char) * MAX_BYTES);
    datos_struct.data_dir.ruta_file_clientes = (char *) malloc(sizeof(char) * MAX_BYTES);
    datos_struct.data_dir.ruta_file_empleados = (char *) malloc(sizeof(char) * MAX_BYTES);
    datos_struct.data_dir.ruta_file_proveedores = (char *) malloc(sizeof(char) * MAX_BYTES);

    if (datos_struct.data_dir.ruta_file_articulos == NULL ||
        datos_struct.data_dir.ruta_file_clientes == NULL ||
        datos_struct.data_dir.ruta_file_empleados == NULL ||
        datos_struct.data_dir.ruta_file_proveedores == NULL)
    {
        fprintf(stderr, "ERROR DE MEMORIA, INTENTA MAS TARDE. . .");

        return EXIT_FAILURE;
    }
    else
    {
        getcwd(datos_struct.data_dir.ruta_file_articulos, sizeof(datos_struct.data_dir.ruta_file_articulos) * MAX_BYTES);
        strcat(datos_struct.data_dir.ruta_file_articulos, "/Files_muebleria/articulos.dat");

        getcwd(datos_struct.data_dir.ruta_file_clientes, sizeof(datos_struct.data_dir.ruta_file_clientes) * MAX_BYTES);
        strcat(datos_struct.data_dir.ruta_file_clientes, "/Files_muebleria/clientes.dat");

        getcwd(datos_struct.data_dir.ruta_file_empleados, sizeof(datos_struct.data_dir.ruta_file_empleados) * MAX_BYTES);
        strcat(datos_struct.data_dir.ruta_file_empleados, "/Files_muebleria/empleados.dat");

        getcwd(datos_struct.data_dir.ruta_file_proveedores, sizeof(datos_struct.data_dir.ruta_file_proveedores) * MAX_BYTES);
        strcat(datos_struct.data_dir.ruta_file_proveedores, "/Files_muebleria/proveedores.dat");

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
                    printf("\n* *%45s%28s\n\n", "MENÚ DE OPCIONES", "* *");
                    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
                    printf("%s", "1) Articulos");
                    printf("%s", "2) Clientes");
                    printf("%s", "3) Empleados");
                    printf("%s", "4) Proveedores");
                    printf("%s", "5) Ventas");
                    printf("%s", "6) Compras");
                    printf("%s", "7) Control de inventario");
                    printf("%s", "8) Reportes");
                    printf("%s", "9) Salir");
                    printf("%10s: ", "Opcion");

                    limpiar_buffer_STDIN();

                    scanf("%d", &opcion);

                    if (opcion < 1 || opcion > 9)

                        validar_errores_por_SO();

                } while (opcion < 1 || opcion > 9);

                switch (opcion)
                {
                // Si no hay proveedores, no hay articulos
                case 1:
                    if (datos_struct.data_contador.articulos_neto < 100 && (existencia_proveedores = verificar_existencia_proveedor(datos_struct.data_files.file_proveedor, &datos_struct.data_proveedores, datos_struct.data_contador.proveedores_neto, datos_struct.data_dir.ruta_file_proveedores)))

                        capturar_articulos(&datos_struct.data_files, &datos_struct, &datos_struct.data_contador.articulos_neto, datos_struct.data_dir.ruta_file_articulos);

                    else if (!existencia_proveedores)

                        puts("No hay proveedores en existencia, la muebleria no tiene articulos");
                    else

                        puts("Se han registrado el maximo de articulos en la muebleria!");

                    break;

                case 2:
                    if (false)
                    {
                        capturar_clientes(&datos_struct.data_files, &datos_struct, &datos_struct.data_contador.clientes_neto, datos_struct.data_dir.ruta_file_articulos);
                    }
                    else
                    {
                    }

                    break;

                case 3:
                    if (datos_struct.data_contador.empleados_neto < 20)
                    {
                        capturar_empleados(&files, &datos_struct, &datos_struct.data_contador.empleados_neto, datos_struct.data_files.file_empleados);
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

                    fclose(datos_struct.data_files.file_articulos);
                    fclose(datos_struct.data_files.file_empleados);
                    fclose(datos_struct.data_files.file_clientes);
                    fclose(datos_struct.data_files.file_proveedor);
                    break;
                }

                if (opcion != 9)

                    pausar_terminal();

            } while (opcion != 9);

            limpiar_terminal();
            puts("Operación finalizada con éxito");
        }
    }
}

extern bool create_binary_files(struct Conjunto_Datos *data_all)
{

}

extern void capturar_articulos(struct Conjunto_Datos *data)
{
    char respuesta[3], proveedor_respuesta[3];
    bool descripcion_correcta, provedor_articulo;
    int i;

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

            } while (data->data_articulos.numero_articulo <= 0);

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

                        printf("Ingresa el numero de proveedor que maneja el articulo %d: ");
                        limpiar_buffer_STDIN();
                    } while (scanf("%d", data->data_articulos.numero_proveedor) != 1);

                    if (data->data_articulos.numero_proveedor < 1)

                        validar_errores_por_SO();

                    else

                        proveedor_existente = verificar_existencia_proveedor(data->data_files.file_proveedor, &data->data_proveedores, &data->data_contador.proveedores_neto, &data->data_dir.ruta_file_proveedores);

                } while (data->data_articulos.numero_proveedor < 1 || !proveedor_existente);

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
        }

        fclose(data->data_files.file_articulos);
    }
}

extern void capturar_clientes(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *clientes_registrados, const char *ruta_clientes_file)
{
}

extern void capturar_empleados(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *empleados_registrados, const char *ruta_empleados_file)
{
}

extern void capturar_proveedores(struct Files_Requeridos *archivos, struct Conjunto_Datos *data, int *proveedores_registrados, const char *ruta_proveedores_file)
{
}

extern void controlar_ventas()
{
}

extern void controlar_compras()
{
}

extern void convertir_cadena_a_minuscula(char *caracter)
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

bool buscar_proveedores(FILE *archivo_proveedores, int *clave_proveedor, const char *directorio_proveedores)
{
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