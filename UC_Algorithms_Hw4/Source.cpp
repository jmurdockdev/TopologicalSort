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

	~Digraph() {
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
		
		
	}

	bool hasCycleUtility(int v, bool visited[], bool *traceStack)
	{
		if (visited[v] == false)
		{
			visited[v] = true;
			traceStack[v] = true;

			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
			{
				if (!visited[*i] && hasCycleUtility(*i, visited, traceStack))
					return true;
				else if (traceStack[*i])
					return true;
			}

		}
		traceStack[v] = false;  
		return false;
	}

	
	bool hasCycle()
	{
	
		bool *visited = new bool[V];
		bool *traceStack = new bool[V];
		for (int i = 0; i < V; i++)
		{
			visited[i] = false;
			traceStack[i] = false;
		}

		for (int i = 0; i < V; i++)
			if (hasCycleUtility(i, visited, traceStack))
				return true;

		return false;
	}

};




int main() {

	string yes = "y";
	while (yes == "y")
	{

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


		if (digraph.hasCycle()) {

			cout << "**********************" << endl;
			cout << "THE GRAPH IS NOT A DAG" << endl;
			cout << "**********************" << endl;
			//throw new exception("The graph contains a cycle");

		}
		else {

			stack<int> Stack;
			Stack = digraph.topologicalSort();
			cout << "TOPO Sort: " << endl;
			while (Stack.empty() == false)
			{
				//cout << Stack.top() << " ";

				cout << tasks[Stack.top()] << " ";

				Stack.pop();
			}


		}

		cout << endl;

		digraph.~Digraph();

		yes = "no";

		cout << "Continue? Enter 'y'" << endl;
		cin >> yes;
		cout << "    " << endl;

	}

	return 0;

}