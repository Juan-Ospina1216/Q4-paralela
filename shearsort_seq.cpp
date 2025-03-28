#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

#define SIZE 100

void sort_row(vector<vector<int>>& matriz, int row, bool asc);
void sort_col(vector<vector<int>>& matriz, int col);
void imprimir(vector<vector<int>>& matriz);

int main(){
    srand(time(0));
    vector<vector<int>> matriz(SIZE, vector<int>(SIZE));

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            matriz[i][j] = rand() % 100;
        }
    }

    int max = log2(SIZE);

    printf("Matriz original: \n");
    imprimir(matriz);

    for(int i = 0; i < (max+1); i++){
        bool asc = true;
        for(int j = 0; j < SIZE; j++){
            sort_row(matriz, j, asc);
            asc = !asc;
        }
        /*imprimir(matriz)*/
        for(int k = 0; k < SIZE; k++){
            sort_col(matriz, k);
        }
        /*imprimir(matriz)*/
    }

    printf("Matriz final:\n");
    imprimir(matriz);

}

void imprimir(vector<vector<int>>&matriz){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void sort_row(vector<vector<int>>& matriz, int row, bool asc){
    /*Algoritmo bubble sort*/
    for(int i = 0; i < SIZE - 1; i++){
        for(int j = 0; j < SIZE - i - 1; j++){
            if((asc && matriz[row][j] > matriz[row][j+1]) || !asc && matriz[row][j] < matriz[row][j+1]){
                swap(matriz[row][j], matriz[row][j+1]);
            }
        }
    }
}

void sort_col(vector<vector<int>>& matriz, int col){
    /*Algoritmo bubble sort*/
    for(int i = 0; i < SIZE - 1; i++){
        for(int j = 0; j < SIZE - i - 1; j++){
            if(matriz[j][col] > matriz[j+1][col]){
                swap(matriz[j][col], matriz[j+1][col]);
            }
        }
    }
}