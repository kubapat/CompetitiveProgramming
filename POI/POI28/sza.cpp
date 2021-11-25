//Polish Olympiad in Informatics
//Task: Szablon Bajtogrodu
//Score: 36/100

#include <iostream>
#include <map>
#include <set>
#include <vector>
#define SIZE 2005
#define DEBUG if(0)

	char edgeLetter[SIZE][SIZE];
	std::vector <int> pol[SIZE];
	std::set <std::string> words,working;
	std::map <std::string,bool> occurs[SIZE][SIZE];

	void dfs(int u,int prev,std::string word, std::vector <int> used) {
		DEBUG {
			printf("W pozycji %d z pozycji %d ze słowem %s\nW historii mam: ",u,prev,word.c_str());
			for(auto el : used) printf("%d ",el);
			printf("\n");
		}
		if(word != "") words.insert(word);

		int last=-1;
		for(auto el : used) {
			if(last == -1) {
				last = el;
				continue;
			}
			occurs[el][last][word] = true;
			occurs[last][el][word] = true;
			last = el;
		}

		for(auto el : pol[u]) {
			if(el == prev) continue;

			used.push_back(el);
			dfs(el,u,word+edgeLetter[u][el],used);
			used.pop_back();
		}
	}

	int main(void) {
		std::ios_base::sync_with_stdio(0);
		std::cin.tie(0);
		std::cout.tie(0);

		int n;
		std::cin >> n;

		for(int i=1;i<n;i++) {
			int a,b;
			char symbol;
			std::cin >> a >> b >> symbol;
			edgeLetter[a][b] = symbol;
			edgeLetter[b][a] = symbol;
			pol[a].push_back(b);
			pol[b].push_back(a);
		}

		for(int i=1;i<=n;i++) {
			dfs(i,i,"",std::vector<int>{i});
		}

		for(auto el : words) {
			bool ok=true;
			for(int i=1;i<=n;i++) {
				for(auto con : pol[i]) {
					if(!occurs[i][con][el]) {
						ok = false;
						break;
					}  //else printf("Pomiędzy %d, a %d występuje %s\n",i,con,el.c_str());
				}
			}

			if(ok) working.insert(el);
		}

		std::cout << working.size() << "\n";
		for(auto el : working) std::cout << el << "\n";

		return 0;
	}
