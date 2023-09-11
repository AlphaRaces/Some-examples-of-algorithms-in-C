#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Inicializa con puntos el camino
void initArray(int n, char M[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = '.';
        }   
    }
}
// Imprime el camino
void printCaminata(int n, char M[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ",M[i][j]);
        }   
        printf("\n");
    }
}
// Función para eliminar las direcciones que no están disponibles
void eliminarDireccion(int direcciones[], int *len, int elementoAEliminar) {
    int encontrado = 0;

    for (int i = 0; i < *len; i++) {
        if (direcciones[i] == elementoAEliminar) {
            encontrado = 1;
            // Desplazar los elementos posteriores una posición hacia atrás
            for (int j = i; j < *len - 1; j++) {
                direcciones[j] = direcciones[j + 1];
            }
            // Reducir el tamaño del arreglo
            (*len)--;
            i--; // Ajustar el índice después del desplazamiento
        }
    }
}    
// Función recursiva que busca el camino
void generar_Caminata(int n, char M[n][n], int i, int j, char letra) {
    
    int path; // esta variable se usará más adelante y será la dirección en que nos moveremos
    int direcciones[4] = {0,1,2,3};
    int l = sizeof(direcciones)/sizeof(direcciones[0]); 
    M[i][j] = letra;

    // elimino la direccion hacia arriba
    if (i == 0 ) { 
        eliminarDireccion(direcciones,&l,0);
    } else if (M[i-1][j] != '.') {
        eliminarDireccion(direcciones,&l,0);
    }
    // elimino la direccion hacia abajo
    if (i == n-1 ) { 
        eliminarDireccion(direcciones,&l,1);
    } else if (M[i+1][j] != '.') {
        eliminarDireccion(direcciones,&l,1);
    }
    // elimino la direccion hacia la izquierda
    if (j == 0 ) { 
        eliminarDireccion(direcciones,&l,2);
    } else if (M[i][j-1] != '.') {
        eliminarDireccion(direcciones,&l,2);
    }
    // elimino la direccion hacia la derecha
    if (j == n-1 ) { 
        eliminarDireccion(direcciones,&l,3);
    } else if (M[i][j+1] != '.') {
        eliminarDireccion(direcciones,&l,3);
    }

    if (l > 0) { 
        int index_direction = rand() % l;
        path = direcciones[index_direction]; // el camino se elige sobre las drecciones disponibles
        if (path == 0) {
            generar_Caminata(n, M, i-1, j, letra + 1);
        } else if (path == 1) {
            generar_Caminata(n, M, i+1, j, letra + 1);
        } else if (path == 2) {
            generar_Caminata(n, M, i, j-1, letra + 1);
        } else if (path == 3) {
            generar_Caminata(n, M, i, j+1, letra + 1);
        }   
    }
}


int main() {
    int n = 10;
    char M[10][10];
    srand(time(NULL));
    initArray(n,M);
    int i = 0, j = 0; // Iniciamos el camino desde arriba en la izquierda
    char letra = 'A'; // primera marca para el camino 
    generar_Caminata(n,M,i,j,letra);
    printCaminata(n,M);
}

