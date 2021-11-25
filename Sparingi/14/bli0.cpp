//Wrocławskie Sparingi Informatyczne
//Bliskie Liczby
//38/100

#include <bits/stdc++.h>

std::vector <long long int> zbior;
long long int minDiff() {
    long long int diff = LONG_MAX;

    for (int i = 0; i < zbior.size() - 1; i++)
        if (zbior[i + 1] - zbior[i] < diff)
            diff = zbior[i + 1] - zbior[i];

    return diff;
}
int main() {
    long long int x, z;
    char op;
    scanf("%lld", & x);
  
    for (int i = 0; i < x; i++) {
        std::cin >> op >> z;
        if (op == '-') {
            int pos = find(zbior.begin(), zbior.end(), z) - zbior.begin();
            zbior.erase(zbior.begin() + pos, zbior.begin() + pos + 1);
        } else if (op == '+') {
            auto it = std::upper_bound(zbior.begin(), zbior.end(), z);
            zbior.insert(it, z);
        }
        if (zbior.size() >= 2) {
            printf("%lld\n", minDiff());
        } else {
            printf("NIE\n");
        }
    }

    return 0;

}
