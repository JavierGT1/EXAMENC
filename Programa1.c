#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[20];
    int codigo;
    int sueldo;
    int horas;
} Trabajador;

void ingresarTrabajador(Trabajador **trabajadores, int *n){
    printf("¿Cuantos trabajadores desea ingresar? ");
    scanf("%d",n);

    *trabajadores = (Trabajador *)malloc(*n * sizeof(Trabajador));
    for (int i=0; i<*n; i++) {
        printf("Ingrese el nombre del empleado: \n");
        scanf("%s", (*trabajadores)[i].nombre);
        printf("Ingrese el codigo del empleado: \n");
        scanf("%d", &(*trabajadores)[i].codigo);
        printf("Ingrese el sueldo del empleado: \n");
        scanf("%d", &(*trabajadores)[i].sueldo);
        printf("Ingrese las horas trabajadas del empleado: \n");
        scanf("%d", &(*trabajadores)[i].horas);
    }
}

int comparar(const void *a, const void *b) {
    return strcmp(((Trabajador *)a)->nombre, ((Trabajador *)b)->nombre);
}

void mostrarTrabajadores(Trabajador *trabajadores, int n){
    qsort(trabajadores, n, sizeof(Trabajador), comparar);
    printf("Datos de los Trabajadores ordenados:\n");
    for (int i=0; i<n; i++) {
        printf("\nNombre: %s \nCodigo: %d \nSueldo:Q.%d \nHoras: %d\n",
               trabajadores[i].nombre, trabajadores[i].codigo, trabajadores[i].sueldo, trabajadores[i].horas);
    }
}

void buscarCodigo(Trabajador *trabajadores, int n, int codigo){
    for (int i=0; i<n; i++) {
        if (trabajadores[i].codigo == codigo) {
            printf("Nombre: %s \nCodigo: %d \nSueldo:Q.%d \nHoras: %d\n",
                   trabajadores[i].nombre, trabajadores[i].codigo, trabajadores[i].sueldo, trabajadores[i].horas);
            return;
        }
    }
    printf("\nEmpleado con codigo %d no encontrado\n", codigo);
}

void buscarNombre(Trabajador *trabajadores, int n, char *nombre){
    for (int i=0; i<n; i++) {
        if (strcmp(trabajadores[i].nombre, nombre) == 0) {
            printf("Nombre: %s \nCodigo: %d \nSueldo:Q.%d \nHoras: %d\n",
                   trabajadores[i].nombre, trabajadores[i].codigo, trabajadores[i].sueldo, trabajadores[i].horas);
            return;
        }
    }
    printf("El trabajador con nombre %s no se ha encontrado\n", nombre);
}

int main() {
    Trabajador *trabajadores = NULL;
    int n=0, op=0, codigo;
    char nombre[50];

    do {
        printf("----MENU----\nSeleccione una opcion:\n1. Ingresar Trabajadores\n2. Consulta General\n3. Consulta por Codigo\n4. Consulta por Nombre\n5. Salir\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                ingresarTrabajador(&trabajadores, &n);
                break;

            case 2:
                mostrarTrabajadores(trabajadores, n);
                break;

            case 3:
                printf("Ingrese el codigo del trabajador: \n");
                scanf("%d", &codigo);
                buscarCodigo(trabajadores, n, codigo);
                break;

            case 4:
                printf("Ingrese el nombre del trabajador: \n");
                scanf("%s", nombre);
                buscarNombre(trabajadores, n, nombre);
                break;

            case 5:
                printf("Gracias por su preferencia. Saliendo...\n");
                break;

            default:
                printf("\nOpcion incorrecta \n");
        }
    }while (op!=5);

    free(trabajadores);
    return 0;
}