//Wrocławskie Sparingi Informatyczne
//Wieża
//100/100

#include <stdio.h>
#include <vector>

long long int n, suma;
int k;

std::vector <long long int> liczby;

int main(void) {
    scanf("%lld %d", &n, &k);

    if (k > n) {
        printf("NIE");
        return 0;
    }

    for (int i = 0; i < k; i++) {
        liczby.push_back(i + 1);
        suma += (i + 1);

        if (suma > n) {
            printf("NIE");
            return 0;
        }
    }

    liczby[liczby.size() - 1] += (n - suma);

    for (int i = 0; i < (liczby.size() - 1); i++) {
        if (liczby[i] == liczby[liczby.size() - 1]) {
            printf("NIE");
            return 0;
        }
    }

    for (auto it: liczby) printf("%lld ", it);

    return 0;
}
