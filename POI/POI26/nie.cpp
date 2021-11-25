//Polish Olympiad in Informatics
//Task: Niedbałość
//Score: 30/100

#include <bits/stdc++.h>

std::string a,b;

void lcs() {
	int L[a.length()+1][b.length()+1], alen,blen;

	for(int i = 0; i <= a.length(); i++) {
           for(int j = 0; j <= b.length(); j++) {
              if(!i || !j) L[i][j]=0;
              else if(a[i-1] == b[j-1]) L[i][j] = L[i-1][j-1]+1;
              else L[i][j] = std::max(L[i-1][j], L[i][j-1]);
	    }
	}

	alen = a.length();
	blen = b.length();
	int i = L[alen][blen];

	char LCS[i+1];

	LCS[i] = '\0';

	while(alen && blen) {
            if(a[alen-1] == b[blen-1]) {
                LCS[i-1] = a[alen-1];
                i--; alen--; blen--;
            } else if(L[alen-1][blen] > L[alen][blen - 1]) alen--;
              else blen--;

	}

	printf("%s\n",LCS);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> a >> b;
    lcs();

    return 0;
}
