//Polish Olympiad in Informatics
//Task: Tablica Binarna
//Score: 100/100

#include <stdio.h>
#include <set>

	std::set <std::pair<std::pair<int,int>,std::pair<int,int>>> deleters;

	void add_rect(int x, int y, int dx, int dy) {
		auto it = deleters.find({{x,y},{dx,dy}});
		if(it == deleters.end()) deleters.insert({{x,y},{dx,dy}});
		else deleters.erase(it);
	}


	int main(void) {
		int n,m,q;
		scanf("%d %d %d",&n,&m,&q);

		while(q--) {
			int x,y,dx,dy;
			scanf("%d %d %d %d",&x,&y,&dx,&dy);
			if(x!=1) add_rect(1,1,x-1,dy); //Brak styku u gory

			if(y!=1) add_rect(1,1,dx,y-1); //Brak styku po lewej

			if(x!=1 && y!=1) add_rect(1,1,x-1,y-1); //Brak zarowno styku u gory i po lewej

			add_rect(1,1,dx,dy);
			printf("%d\n",deleters.size());
		}

		return 0;
	}
