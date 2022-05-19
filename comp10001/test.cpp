#include <bits/stdc++.h>

using namespace std;

// int inters = 100, lim = 100, limst = 1000;
int inters = 55, lim = 5, limst = 200;
vector<int> adj[1000];
bool hasedge[1000][1000];
int cost[1000][1000];
int a[1000];
int idx[1000];
vector<vector<pair<int, int> > > inter[1000];
pair<int, vector<int> > cars[1000];
mt19937 g(rand());

void addedge(int u, int v)
{
	if(!hasedge[u][v] && u!=v)
	{
		hasedge[u][v]=true;
		hasedge[v][u]=true;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

vector<int> get_ran_path(int u)
{
	vector<int> res={u};
	vector<bool> used(4*inters, 0);
	used[u]=true;
	for(int i=1; i<=g()%inters*3; i++)
	{
		int v=adj[u][g()%adj[u].size()];
		if(!used[v])
		{
			u=v;
			used[u]=true;
			res.push_back(u);
			if(u>inters) break;
		}
	}
	if(u<=inters)
	{
		res.push_back(u+inters);
	}
	if(res[0]==res.back())
	{
		if(res[0]<=2*inters)
		{
			res[0]+=inters;
		}
		else
		{
			res[0]-=inters;
		}
	}
	return res;
}

signed main()
{
	for(int i=1; i<=4*inters; i++)
	{
		for(int j=1; j<=4*inters; j++)
		{
			cost[i][j]=g()%lim+1;
		}
	}

	for(int i=1; i<=3*inters; i++) idx[i]=i;
	shuffle(idx+1, idx+3*inters+1, g);

	for(int i=2; i<=inters/2; i++)
	{
		int last = g()%(i-1)+1;
		addedge(i, last);
	}
	for(int i=1; i<=inters/2; i++)
	{
		int u=g()%inters+1, v=g()%inters+1;
		addedge(u, v);
	}
	for(int i=1; i<=inters; i++)
	{
		addedge(i, inters+i);
		addedge(i, 2*inters+i);

		int splits = g()%(adj[i].size()*(adj[i].size()-1)/2)+1;
		vector<pair<int, int> > temp[splits];
		
		for(auto j:adj[i])
		{
			for(auto k:adj[i])
			{
				if(j!=k)
				{
					// if(i==2) 
					// {
					// 	cout<<j<<" "<<k;
					// 	cout<<69;
					// 	return 0;
					// }
					temp[g()%splits].push_back({j, k});
				}
			}
		}
		for(int j=0; j<splits; j++)
		{
			if(temp[j].size()) inter[i].push_back(temp[j]);
		}
	}
	for(int i=inters+1; i<=3*inters; i++)
	{
		cars[i] = {g()%limst, get_ran_path(i)};
	}
	cout<<"simulate(";
	{
		cout<<"{";
		{
			for(int i=1; i<=inters; i++)
			{
				cout<<idx[i]<<": [";
				{
					for(int j=0; j<inter[i].size(); j++)
					{
						cout<<"[";
						for(int k=0; k<inter[i][j].size(); k++)
						{
							cout<<"("<<idx[inter[i][j][k].first]<<", "<<idx[inter[i][j][k].second]<<")";
							if(k<inter[i][j].size()-1) cout<<", ";
						}
						cout<<"]";
						if(j<inter[i].size()-1) cout<<", ";
					}
				}
				cout<<"]";
				if(i<inters) cout<<", ";
			}
		}
		cout<<"}, {";
		{
			for(int i=1; i<=inters*3; i++)
			{
				for(int j=0; j<adj[i].size(); j++)
				{
					cout<<"("<<idx[i]<<","<<idx[adj[i][j]]<<"):"<<cost[i][adj[i][j]];
					if(i<inters*3||j<adj[i].size()-1) cout<<", ";
				}
			}
		}	
		cout<<"}, [";
		{
			for(int i=inters+1; i<=3*inters; i++)
			{
				if(cars[i].second.size()==1) continue;
				cout<<"("<<i-inters-1<<", [";
				for(int j=0; j<cars[i].second.size(); j++)
				{
					cout<<idx[cars[i].second[j]];
					if(j<cars[i].second.size()-1) cout<<", ";
				}
				cout<<"], "<<cars[i].first<<")";
				if(i<inters*3) cout<<", ";
			}
		}
		cout<<"]";
	}
	cout<<")";
}