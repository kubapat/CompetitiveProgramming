//Wrocławskie Sparingi Informatyczne
//Kolejka
//36/100

#include <bits/stdc++.h>

#define SIZE 1000005

long long int tab[SIZE], licznik;

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%lld", & tab[i]);

    for (int i = 0; i < n; i++) {
        long long int maxi = -1;
        for (int k = i + 1; k < n; k++) {
            if ((i + 1) == k) licznik++;
            else if (maxi < tab[k]) licznik++;
            maxi = std::max(maxi, tab[k]);
        }
    }

    printf("%lld", licznik);
    return 0;
}
