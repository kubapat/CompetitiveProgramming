//Wrocławskie Sparingi Informatyczne
//Sumy Fibonacciego
//21/100

#include <bits/stdc++.h>
#define ARR_SIZE 87

long long int tab[87], x;
bool koniec;

void fib(unsigned int n) {
    tab[0] = 1;
    tab[1] = 1;
  
    for (int i = 2; i < 87; i++) {
        tab[i] = tab[i - 1] + tab[i - 2];
    }
}

void printArray(long long int &arr[], int arr_size) {
    int i;
    for (i = 0; i < arr_size; i++)
        printf("%lld ", arr[i]);
    koniec = 1;
}

void printCompositions(long long int n, int i, int o) {
    static long long int arr[ARR_SIZE];
    if (!n && o == x && !koniec) {
        printArray(arr, i);
        o = -1;
    } else if (n > 0 && !koniec) {
        int k;
        for (k = 1; k < 87; k++) {
            arr[i] = tab[k];
            printCompositions(n - tab[k], i + 1, o + 1);
        }
    }
}


int main(void) {
    long long int liczba;
    scanf("%lld %lld", &liczba, &x);
  
    fib(87);
    printCompositions(liczba, 0, 0);
    if (!koniec) printf("NIE");

    return 0;
}
