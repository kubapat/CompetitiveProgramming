//Wrocławskie Sparingi Informatyczne
//Prostsze dwa koła
//100/100

#include <bits/stdc++.h>

int n, m;
int line = -1, pos = -1, last = -1, line2 = -1, pos2 = -1, last2 = -1; //Pos int's
char c;

bool ok, stop, tab[1001][1001];

int main(void) {
    scanf("%d %d", & n, & m);

    for (int i = 0; i < n; i++) { //Input and calculating 1st circle
        for (int k = 0; k < m; k++) {
            std::cin >> c;

            if (c == '.') { //If this is blank
                tab[i][k] = false;
                if (pos == k) stop = true;
            } else { //If it's fillen
                tab[i][k] = true;

                if (line == -1 && pos == -1) {
                    line = i;
                    last = i;
                    pos = k;
                } else if (pos == k && !stop) last++;

            }

        } //End of horizontal for
    } //End of vertical for

    for (int i = line; i < n; i++) {
        for (int k = i == line ? pos + 1 : 0; k < m; k++) {
            if (tab[i][k] && line2 == -1 && pos2 == -1) { //If 2nd cirle not found
                ok = true;
                if (i >= line && i <= last) { //If 2nd circle not found AND current position is in verical range of 1st cirlce
                    if (pos < k) { //Checking if given point is not part of 1st circle
                        for (int z = pos; z < m; z++) {
                            if (pos == k || z == k) {
                                ok = false;
                                break;
                            } else if (!tab[i][z]) break;
                        }
                    } else {
                        for (int z = pos; z >= 0; z--) {
                            if (pos == k || z == k) {
                                ok = false;
                                break;
                            } else if (!tab[i][z]) break;
                        }
                    }

                }

                if (ok) { //Starting 2nd circle
                    line2 = i;
                    last2 = i;
                    pos2 = k;
                }

            } else if (tab[i][k] && line2 != -1 && k == pos2) last2++; //Extending 2nd circle
        } //End of horizontal for
    } //End of vertical for

    printf("%d %d\n%d %d", pos, (n - (line + last) / 2) - 1, pos2, (n - (line2 + last2) / 2) - 1);

    return 0;
}
