#include <list>
#include <iostream>
#include <string>
#include <stack> 
#include <vector>

using namespace std;

class Digraph {


private:

	vector<list<int>> adj;
	int V;


public:


	Digraph(int V) {
		this->V = V;
		adj.resize(V);
	}

	void addEdge(int v, int w)
	{
		adj[v].push_back(w); // Add w to v’s list. consider changing to int
	}

	 
	void topologicalSortUtil(int v, bool visited[],stack<int> &Stack)
	{
		visited[v] = true;

		
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (!visited[*i]) {
				topologicalSortUtil(*i, visited, Stack);
			}
		}

		 
		Stack.push(v);
	}

	
	stack<int> topologicalSort()
	{
		stack<int> Stack;

		
		bool *visited = new bool[V];
		for (int i = 0; i < V; i++) {
			visited[i] = false;
		}

		
		for (int i = 0; i < V; i++) {
			if (visited[i] == false) {
				topologicalSortUtil(i, visited, Stack);
			}
		}


		return Stack;
		
		/*while (Stack.empty() == false)
		{
			cout << Stack.top() << " ";
			Stack.pop();
		}*/
	}

};




int main() {

	vector<string> tasks;
	string task;
	cout << "Enter tasks, enter 'quit' to stop entering tasks" << endl;

	int counter = 0;

	while (task != "quit") {

		cout << counter << ": ";
		cin >> task;

		if (task != "quit") {
			
			tasks.push_back(task);
			counter++;

		}
	}

	Digraph digraph(tasks.size());

	cout << "Enter order relation on pairs of tasks, enter '-1 -1' to stop" << endl;

	int a = 0;
	int b = 0;

	while (a != -1 && b != -1) {

		cin >> a >> b;
	

		if (a != -1 && b != -1) {
			digraph.addEdge(a, b);
		}
		

	}

	stack<int> Stack;
	Stack = digraph.topologicalSort();

	while (Stack.empty() == false)
	{
		//cout << Stack.top() << " ";

		cout << tasks[Stack.top()] << " ";

		Stack.pop();
	}

	cout << endl;

	system("pause");

	return 0;

}