//Wrocławskie Sparingi Informatyczne
//Cykliczne kontrole
//40/100

#include <bits/stdc++.h>
#define DEBUG if(0)
/*
 List of funcs:
  - fillNotUsed() - fills a vector with chars, which have appeared,
  - fillUsed() - fills a vector with chars, which haven't appeared,
  - checkUsed() - looks for char in used chars vector, which doesn't collide with neighbours,
  - checkNotUsed() - looks for char in not used chars vector, which doesn't collide with neighbours.
*/

std::string res, alfa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::vector <char> used, notused;

void fillNotUsed() {
    for (int i = 0; i < 26; i++) {
        bool is = false;

        for (int k = 0; k < used.size(); k++) {
            if (alfa[i] == used[k]) {
                is = true;
                break;
            }
        }

        if (!is) notused.push_back(alfa[i]);
    }

}

int fillUsed() {
    for (int i = 0; i < res.length(); i++) {
        bool is = false;

        if (res[i] != '?') {
            for (int k = 0; k < used.size(); k++) {
                if (res[i] == used[k]) {
                    is = true;
                    break;
                }
            }

            if (!is) used.push_back(res[i]);
        }

        if(i) {
            if (res[i] == res[i - 1] && res[i - 1] != '?') {
                printf("NIE");
                return -1;
            }
        }

    }

    return 0;

}

bool checkUsed(char left, char right, int index) {
    bool found = false;
    for (int k = 0; k < used.size(); k++) {
        if (left != used[k] && right != used[k]) {
            found = true;
            res[index] = used[k];
            break;
        }
    }

    return found;
}

bool checkNotUsed(char left, char right, int index) {
    bool found = false;
    for (int k = 0; k < notused.size(); k++) {
        if (left != notused[k] && right != notused[k]) {
            found = true;
            res[index] = notused[k];

            //Adding to vector of used chars and removing from vector of notused chars
            used.push_back(notused[k]);
            notused.erase(notused.begin() + k);

            break;
        }
    }

    return found;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> res;

    if (res.length() == 1) {
        printf("NIE");
        return 0;
    }

    int status = fillUsed();

    if(status == -1) return 0;

    fillNotUsed();
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == '?') {
            char l, r;

            //Setting correct left char and right char
            if ((i + 1) != res.length() && (i - 1) >= 0) {
                l = res[i - 1];
                r = res[i + 1];
            }

            if ((i + 1) == res.length()) r = res[0];
            else r = res[i + 1];

            if ((i - 1) < 0) l = res[res.length() - 1];
            else l = res[i - 1];

            bool stat = checkUsed(l, r, i);

            if (!stat) { //If not found in set of used chars
                stat = checkNotUsed(l, r, i);
                if (!stat) { //If not found neither in set of used, nor in set of not used chars
                    printf("NIE");
                    return 0;
                }
            }

        } //If given char is '?'
    }

    DEBUG {
     printf("\nUżyte: ");

     for(int i=0;i<used.size();i++) printf("%c ",used[i]);

     printf("Nieużyte: ");

     for(int i=0;i<notused.size();i++) printf("%c ",notused[i]);
    }

    for (int i = 0; i < res.length(); i++) {
        if (i != 0) {
            if (res[i] == res[i - 1]) {
                printf("NIE");
                return 0;
            }
        }

    }

    std::cout << used.size() << "\n" << res;
    return 0;
}
