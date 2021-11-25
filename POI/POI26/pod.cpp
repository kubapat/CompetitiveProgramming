//Polish Olympiad in Informatics
//Task: Podciągi
//Score: 20/100

#include <bits/stdc++.h>

bool alfa[26], alfabig[26], cyfry[10];

int main() {
    int n;
    scanf("%d", & n);
    for (int m = 0; m < n; m++) {
        for (int t = 0; t < 26; t++) {
            alfa[t] = false;
            alfabig[t] = false;
            if (t < 10) cyfry[t] = false;
        }

        long long int x, k = 2;
        scanf("%lld", & x);

        while (x > 1) {

            while (x % k == 0) {
                bool found = false;

                for (int i = 0; i < 26; i++) {
                    if (!alfa[i]) {
                        alfa[i] = true;
                        found = true;
                        for (int z = 0; z < (k - 1); z++) printf("%c", i + 97);
                        break;
                    }
                }

                if (!found) {
                    for (int i = 0; i < 26; i++) {
                        if (!alfabig[i]) {
                            alfabig[i] = true;
                            found = true;
                            for (int z = 0; z < (k - 1); z++) printf("%c", i + 65);
                            break;
                        }
                    } //End of for
                } //End of if

                if (!found) {
                    for (int i = 0; i < 10; i++) {
                        if (!cyfry[i]) {
                            cyfry[i] = true;
                            found = true;
                            for (int z = 0; z < (k - 1); z++) printf("%c", i + 48);
                            break;
                        }
                    }
                } //End of if

                x /= k;
            }
            k++;
        }
        printf("\n");
    }
    return 0;
}
