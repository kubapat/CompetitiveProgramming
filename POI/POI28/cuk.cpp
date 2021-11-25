//Polish Olympiad in Informatics
//Task: Cukiernia
//Score: 100/100

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#define DEBUG if(0)

	std::vector <std::pair<long long int,std::pair<long long int,long long int>>> koszta;
	std::vector <short int> wybrany;
	int a,b,c;

	long long int zwrocKoszt(int i, short int el) {
		if(el == 1) return koszta[i].first;
		else if(el == 2) return koszta[i].second.first;
		else return koszta[i].second.second;
	}

	int liczebnoscGrupy(short int el) {
		if(el==1) return a;
		else if(el == 2) return b;
		else return c;
	}

	long long int szukaj(short int index) {
		long long int min = LLONG_MAX,kosztJedynki,zmianaResztyNaJeden=LLONG_MAX,indeksJeden;
		if(a==1) indeksJeden = 1;
		else if(b==1) indeksJeden = 2;
		else if(c==1) indeksJeden = 3;
		else indeksJeden = -1;

		for(int i=0; i<koszta.size(); i++) {
			if(liczebnoscGrupy(wybrany[i]) == 1) {
				kosztJedynki = zwrocKoszt(i,index) - zwrocKoszt(i,wybrany[i]);
				continue;
			}

			min = std::min(zwrocKoszt(i,index)-zwrocKoszt(i,wybrany[i]),min);
			if(indeksJeden!=-1) zmianaResztyNaJeden = std::min(zmianaResztyNaJeden,zwrocKoszt(i,indeksJeden)-zwrocKoszt(i,wybrany[i]));
		}

		if(indeksJeden != -1) min = std::min(min,zmianaResztyNaJeden+kosztJedynki);

		return min;
	}

	long long int szukaj2(short int index) {
		long long int min = LLONG_MAX;

        for(int i=0; i<koszta.size(); i++) min = std::min(zwrocKoszt(i,index)-zwrocKoszt(i,wybrany[i]),min);

        return min;
    }

	long long int szukajDwoch(short int x, short int y) {
		short int index[2]; index[0]=x, index[1]=y;
		long long int roznica[4][2],indexroz[4][2];
		for(int i=0; i<4; i++) for(int j=0; j<2; j++) roznica[i][j]=LLONG_MAX,indexroz[i][j]=0;

		for(int i=0; i<koszta.size(); i++) {
			for(int k=0; k<2; k++) {
				if(zwrocKoszt(i,index[k])-zwrocKoszt(i,wybrany[i]) <= roznica[index[k]][0]) {
					roznica[index[k]][1]  = roznica[index[k]][0];
					indexroz[index[k]][1] = indexroz[index[k]][0];
					roznica[index[k]][0]  = zwrocKoszt(i,index[k])-zwrocKoszt(i,wybrany[i]);
					indexroz[index[k]][0] = i;
				} else if(zwrocKoszt(i,index[k])-zwrocKoszt(i,wybrany[i]) <= roznica[index[k]][1]) {
					roznica[index[k]][1]  = zwrocKoszt(i,index[k])-zwrocKoszt(i,wybrany[i]);
                    indexroz[index[k]][1] = i;
				}
			}
		}

		if(indexroz[index[0]][0] != indexroz[index[1]][0]) return roznica[index[0]][0]+roznica[index[1]][0];
		else if(roznica[index[0]][0]+roznica[index[1]][1] < roznica[index[0]][1]+roznica[index[1]][0]) return roznica[index[0]][0]+roznica[index[1]][1];
		else return roznica[index[0]][1]+roznica[index[1]][0];
	}

	int main(void) {
		int n;
		scanf("%d",&n);

		bool zeroA=true,zeroB=true,zeroC=true;

		for(int i=0; i<n; i++) {
			long long int ax,bx,cx;
			scanf("%lld %lld %lld",&ax,&bx,&cx);
			long long int kosztA = bx+cx,kosztB=ax+cx,kosztC=ax+bx;
			koszta.push_back({kosztA,{kosztB,kosztC}});
			if(ax) zeroA=false;

			if(bx) zeroB=false;

			if(cx) zeroC=false;
		}

		if(n==1 || (zeroA && zeroB) || (zeroB && zeroC) || (zeroA && zeroC)) {
			printf("0");
			return 0;
		}

		long long int koszt=0;
		for(auto el : koszta) {
			if(el.first <= el.second.first && el.first <= el.second.second) {
				koszt += el.first;
				a++;
				wybrany.push_back(1);
			} else if(el.second.first <= el.first && el.second.first <= el.second.second) {
				koszt += el.second.first;
				b++;
				wybrany.push_back(2);
			} else {
				koszt += el.second.second;
				c++;
				wybrany.push_back(3);
			}
		}

		DEBUG printf("Wybrano A:%d B:%d C:%d\n",a,b,c);

		if(zeroA) {
			if(b && c) { printf("%lld",koszt); return 0; }
			else if(b) koszt += szukaj2(3);
			else koszt += szukaj2(2);
		} else if(zeroB) {
			if(a && c) { printf("%lld",koszt); return 0; }
			else if(a) koszt += szukaj2(3);
			else koszt += szukaj2(1);
		} else if(zeroC) {
			if(a && b) { printf("%lld",koszt); return 0; }
			else if(a) koszt += szukaj2(2);
			else koszt += szukaj2(1);
		}
		else if(a && b && !c)  koszt += szukaj(3);
		else if(!a && b && c)  koszt += szukaj(1);
		else if(a && !b && c)  koszt += szukaj(2);
		else if(a && !b && !c) koszt += szukajDwoch(2,3);
		else if(!a && !b && c) koszt += szukajDwoch(1,2);
		else if(!a && b && !c) koszt += szukajDwoch(1,3);

		printf("%lld",koszt);
		return 0;
	}
