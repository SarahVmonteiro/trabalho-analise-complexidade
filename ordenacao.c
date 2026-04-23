#include <stdio.h>
#include <time.h>
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) { // começa do segundo elemento
        int key = arr[i]; 
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void merge(int arr[], int l, int m, int r) { // função de mesclagem para o merge sort
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) { 
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int main() {
    FILE *arq1 = fopen("dados_insertion.csv", "w");
    FILE *arq2 = fopen("dados_merge.csv", "w");
    fprintf(arq1, "n,tempo\n");
    fprintf(arq2, "n,tempo\n");

    for (int n = 1000; n <= 10000; n += 1000) {
        int arr[n], copia[n]; // array original e cópia para cada algoritmo
        for (int i = 0; i < n; i++) {
            arr[i] = n - i; // pior caso simples (vetor de ordem inversa)
        }
        clock_t inicio, fim;
        double tempo;
        for (int i = 0; i < n; i++) copia[i] = arr[i]; // copia o array original para o algoritmo de ordenação
        inicio = clock();
        insertionSort(copia, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Insertion | n=%d | tempo=%f\n", n, tempo);
        fprintf(arq1, "%d,%f\n", n, tempo);

        for (int i = 0; i < n; i++) copia[i] = arr[i]; // copia o array original para o algoritmo de ordenação
        inicio = clock();
        mergeSort(copia, 0, n - 1);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Merge | n=%d | tempo=%f\n", n, tempo);
        fprintf(arq2, "%d,%f\n", n, tempo);
    }
    fclose(arq1);
    fclose(arq2);
    return 0;
}