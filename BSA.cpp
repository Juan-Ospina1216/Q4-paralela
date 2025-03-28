#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define SIZE 100

using namespace std;

void ordenar(vector<int>& array);
int bsa(vector<int> array, int val);

int main(){
    vector<int> array(SIZE);
    for(int i = 0; i < SIZE; i++){
        array[i] = (rand()%100);
        
    }
    ordenar(array);
    for(int i = 0; i < SIZE; i++){
        printf("%d ", array[i]);
    }
    int k = rand() % SIZE;
    int val = array[k];
    printf("\nObjetivo: %d", val);

    int indice = bsa(array, val);
    if(indice != -1){
        printf("\nEl valor %d se encuentra en el indice %d", val, indice);
    }else{
        printf("\nNo se encontro el valor buscado\n");
    }
    
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

int bsa(vector<int> array, int val){
    int l = 0;
    int r = SIZE;
    int med = 0;
    int ans = -1;
    while(l <= r && ans != med){
        med = l + (r - l) / 2;
        if(array[med] == val){
            ans = med;
        }else{
            if(array[med] > val){
                r = med - 1;
            }else{
                l = med + 1;
            }
        }
    }
    return med;
}