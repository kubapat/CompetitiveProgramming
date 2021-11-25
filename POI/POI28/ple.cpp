//Polish Olympiad in Informatics
//Task: Pakowanie plecaka
//Score: 18/100

#include <stdio.h>
#include <algorithm>
#include <vector>

	std::vector <int> tab,sorted;

	int main(void) {
		int n;
		scanf("%d",&n);

		for(int i=0; i<n; i++) {
			int tmp;
			scanf("%d",&tmp);
			sorted.push_back(tmp);
			tab.push_back(tmp);
		}

		std::sort(sorted.begin(),sorted.end());

		printf("%d ",sorted[0]);
		long long int sum = (long long int)sorted[0];
		sorted[0] = -1;

		for(int i=1; i<n; i++) {
			int count = i+1;
			for(int k=0; k<n; k++) {
				if(sorted[k] == -1) continue;

				long long int trySum = sum+(long long int)sorted[k];
				int elems=0;
				for(int j=0; j<n; j++) {
					if(!trySum) break;

					if(tab[j]>trySum) continue;

					trySum-=tab[j];
					elems++;
				}
				if(elems<count) continue;

				sum+=(long long int)sorted[k];
				sorted[k]=-1;
				printf("%lld ",sum);
				break;
			}
		}

		return 0;
	}
