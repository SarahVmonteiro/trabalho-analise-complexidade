#include <stdio.h>
#include <time.h>
int buscaSequencial(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}
int buscaBinaria(int arr[], int n, int x) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (arr[meio] == x)
            return meio;
        else if (arr[meio] < x)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
int main() {
    FILE *arquivo1 = fopen("dados_sequencial.csv", "w");
    FILE *arquivo2 = fopen("dados_binaria.csv", "w");
    fprintf(arquivo1, "n,tempo\n");
    fprintf(arquivo2, "n,tempo\n");

    for (int n = 1000; n <= 10000; n += 1000) { // testa para diferentes tamanhos
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        clock_t inicio, fim;
        double tempo;
        inicio = clock();
        for (int i = 0; i < 1000; i++) { // executa a busca sequencial 1000 vezes para obter um tempo mais preciso
            buscaSequencial(arr, n, -1);
        }
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // calcula o tempo gasto em segundos
        printf("Sequencial | n = %d | tempo = %f\n", n, tempo);
        fprintf(arquivo1, "%d,%f\n", n, tempo);

        inicio = clock();
       for (int i = 0; i < 1000; i++) { // executa a busca binária 1000 vezes para obter um tempo mais preciso
            buscaBinaria(arr, n, -1);
        }
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // calcula o tempo gasto em segundos
        printf("Binaria | n = %d | tempo = %f\n", n, tempo);
        fprintf(arquivo2, "%d,%f\n", n, tempo);
    }
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;
}