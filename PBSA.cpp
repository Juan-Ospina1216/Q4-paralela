#include <iostream>
#include <omp.h>
#include <vector>
#define SIZE 100
using namespace std;

int busquedaBinariaParalela(vector<int> arr, int val, int numHilos);
void ordenar(vector<int>& array);

int main(int argc, char*argv[]) {
    vector<int> arr(SIZE);
    int numHilos = atoi(argv[1]);  /*Número de hilos a usar*/

    for(int i = 0; i < SIZE; i++){
        arr[i] = rand() % 100;
    }
    ordenar(arr);
    for(int i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    int x = rand() % SIZE;
    int val = arr[x];

    int indice = busquedaBinariaParalela(arr, val, numHilos);

    if (indice != -1)
        printf("\nEl valor %d se encuentra en el indice %d", val, indice);
    else
        printf("\nElemento no encontrado");

    return 0;
}

void ordenar(vector<int>& array){
    for(int i = 0; i < SIZE - 1; i++){
        for(int j = 0; j < SIZE - i - 1; j++){
            if(array[j] > array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
}

int busquedaBinariaParalela(vector<int> arr, int val, int numHilos) {
    int l = 0, r = SIZE - 1;

    while (l <= r) {
        int encontrado = -1; 
        
        /*Se divide el arreglo en P hilos*/
        #pragma omp parallel num_threads(numHilos)
        {
            int id = omp_get_thread_num();
            int inicio = l + (id * (r - l + 1)) / numHilos;
            int fin = l + ((id + 1) * (r - l + 1)) / numHilos - 1;

            /*Revisa los extremos*/
            if (arr[inicio] == val) {
                #pragma omp critical
                encontrado = inicio;
            }
            if (arr[fin] == val) {
                #pragma omp critical
                encontrado = fin;
            }
        }

        if (encontrado != -1) {
            return encontrado;
        }

        int nuevoIzq = -1, nuevoDer = -1;

        #pragma omp parallel for num_threads(numHilos)
        for (int i = 0; i < numHilos; i++) {
            int inicio = l + (i * (r - l + 1)) / numHilos;
            int fin = l + ((i + 1) * (r - l + 1)) / numHilos - 1;

            if (val > arr[inicio] && val < arr[fin]) {
                #pragma omp critical
                {
                    nuevoIzq = inicio;
                    nuevoDer = fin;
                }
            }
        }

        /*Si no se encontró el elemento*/
        if (nuevoIzq == -1 || nuevoDer == -1) {
            return -1;
        }

        /*Se reduce el rango de la busqueda*/
        l = nuevoIzq;
        r = nuevoDer;
    }

    return -1;
}


