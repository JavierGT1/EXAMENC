#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[25];
    char departamento[25];
    char grado[25];
    int edad;
    int carnet;
} Estudiante;

void Registrar() {
    Estudiante estudiante;
    FILE *archivo = fopen("estudiante.txt", "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    printf("-Ingrese los datos del estudiante-\n");
    printf("Carnet: \n");
    scanf("%d", &estudiante.carnet);
    printf("Nombre: \n");
    scanf("%s", estudiante.nombre);
    printf("Grado: \n");
    scanf("%s", estudiante.grado);
    printf("Departamento: \n");
    scanf("%s", estudiante.departamento);
    printf("Edad: \n");
    scanf("%d", &estudiante.edad);
    fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
    fclose(archivo);
}

void Buscar() {
    int carnet;
    Estudiante estudiante;
    FILE *archivo = fopen("estudiante.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    int encontrar = 0;
    
    printf("Ingrese el carnet del estudiante que desea buscar: \n");
    scanf("%d", &carnet);
    while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
        if (estudiante.carnet == carnet) {
            printf("Nombre: %s\n", estudiante.nombre);
            printf("Grado: %s\n", estudiante.grado);
            printf("Departamento: %s\n", estudiante.departamento);
            printf("Edad: %d\n", estudiante.edad);
            encontrar = 1;
            break;
        }
    }
    if (!encontrar) {
        printf("No se encontro el estudiante con el carnet ingresado.\n");
    }
    fclose(archivo);
}

void Lista() {
    char grado[25];
    Estudiante estudiante;
    FILE *archivo = fopen("estudiante.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    
    printf("Ingrese el grado, para verificar la lista: \n");
    scanf("%s", grado);

    while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
        if (strcmp(estudiante.grado, grado) == 0) {
            printf("Nombre: %s\n", estudiante.nombre);
            printf("Grado: %s\n", estudiante.grado);
            printf("Departamento: %s\n", estudiante.departamento);
            printf("Edad: %d\n", estudiante.edad);
        }
    }
    fclose(archivo);
}

void Editar() {
    int carnet;
    Estudiante estudiante;
    FILE *archivo = fopen("estudiante.txt", "r");
    FILE *archivo_temp = fopen("estudiante_temp.txt", "w");
    if (archivo == NULL || archivo_temp == NULL) {
        perror("Error al abrir el archivo");
        if (archivo) fclose(archivo);
        if (archivo_temp) fclose(archivo_temp);
        return;
    }
    int encontrar = 0;

    printf("Ingrese el carnet del estudiante a editar: ");
    scanf("%d", &carnet);

    while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
        if (estudiante.carnet == carnet) {
            encontrar = 1;
            printf("Ingrese el nuevo nombre del estudiante: ");
            scanf("%s", estudiante.nombre);
            printf("Ingrese el nuevo grado del estudiante: ");
            scanf("%s", estudiante.grado);
            printf("Ingrese el nuevo departamento del estudiante: ");
            scanf("%s", estudiante.departamento);
            printf("Ingrese la nueva edad del estudiante: ");
            scanf("%d", &estudiante.edad);
        }
        fwrite(&estudiante, sizeof(Estudiante), 1, archivo_temp);
    }

    if (!encontrar) {
        printf("Este carnet no se encontro.\n");
    }

    fclose(archivo);
    fclose(archivo_temp);
    
    remove("estudiante.txt");
    rename("estudiante_temp.txt", "estudiante.txt");
}

int main() {
    int op;
    do {
        printf("----MENU----\nSeleccione una opcion: \n1. Registrar un estudiante \n2. Buscar estudiante \n3. Lista de Estudiantes \n4. Editar estudiante \n5. Salir\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                Registrar();
                break;

            case 2:
                Buscar();
                break;

            case 3:
                Lista();
                break;

            case 4:
                Editar();
                break;

            case 5:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion incorrecta.\n");
        }
    } while (op != 5);
    return 0;
}
