#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

#define SIZE 100

void sort_row(vector<vector<int>>& matriz, int row, bool asc);
void transpuesta(vector<vector<int>>& matriz);
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
  /*imprimir(matriz);*/

  for(int i = 0; i < (max+1); i++){
    bool asc = true;
    #pragma omp parallel for
    for(int j = 0; j < SIZE; j++){
      if(j%2 == 1){
        asc = false;
      }else{asc = true;}
      sort_row(matriz, j, asc);
    }
    transpuesta(matriz);
    #pragma omp parallel for
    for(int k = 0; k < SIZE; k++){
      sort_row(matriz, k, true);
    }
    transpuesta(matriz);
  }
  printf("Matriz final:\n");
  imprimir(matriz);
}

void imprimir(vector<vector<int>>& matriz){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

void sort_row(vector<vector<int>>& matriz, int row, bool asc){
  for(int i = 0; i < SIZE - 1; i++){
    for(int j = 0; j < SIZE - i - 1; j++){
      if((asc && matriz[row][j] > matriz[row][j+1]) || !asc && matriz[row][j] < matriz[row][j+1]){
        swap(matriz[row][j], matriz[row][j+1]);
      }
    }
  }
}

void transpuesta(vector<vector<int>>& matriz){
  vector<vector<int>> transp(SIZE, vector<int>(SIZE));
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      transp[j][i] = matriz[i][j];
    }
  }
  matriz = transp;
}