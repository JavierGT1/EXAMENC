#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Ingresar(int n) {
    char departamento[50];
    FILE *archivo = fopen("departamentos.txt", "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        printf("Ingrese el nombre del departamento %d: ", i + 1);
        scanf("%s", departamento);
        fprintf(archivo, "%s\n", departamento);
    }
    fclose(archivo);
}

int comparar(const void *a, const void *b) {
    return strcmp(*(const char **)b, *(const char **)a);
}

void Mostrar() {
    char departamentos[100][50];
    char *p[100];
    int n = 0;
    FILE *archivo = fopen("departamentos.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    
    while (fgets(departamentos[n], sizeof(departamentos[0]), archivo)) {
        departamentos[n][strcspn(departamentos[n], "\n")] = 0; 
        p[n] = departamentos[n];
        n++;
    }
    
    fclose(archivo);
    qsort(p, n, sizeof(p[0]), comparar);
    
    printf("Departamentos ordenados de Z a A:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", p[i]);
    }
}

int main() {
    int opcion, n;
    
    do {
        printf("----MENU----\n1. Ingresar Departamentos\n2. Mostrar Departamentos Ordenados\n 3.Salir\n Seleccione una opcion: ");

        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("¿Cuantos departamentos desea ingresar? ");
                scanf("%d", &n);
                Ingresar(n);
                break;
            case 2:
                Mostrar();
                break;
            case 3:
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 3);
    
    return 0;
}
