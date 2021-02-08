// ДАННЫЙ ФАЙЛ ПРЕДНАЗНАЧЕН ИСКЛЮЧИТЕЛЬНО ДЛЯ ТЕСТИРОВАНИЯ
// И ОТЛАДКИ ПОДКЛЮЧЕННЫХ НИЖЕ КОМПОНЕНТОВ.

#include "SparseGraph.cpp"
#include "DenseGraph.cpp"
#include "IO.cpp"
#include "ShortestPathSearcher.cpp"
#include "DeepSearcher.cpp"

using namespace std;

using Graph = DenseGraph;

int main(int argc, char const *argv[]) {
	if(argc != 2) {
		cerr << "Wrong call" << endl;
		return 1;
	}

	Graph graph(10, true);

	// Чтение графа из файла:
	cout << "reading " << argv[1] << "... ";
	if(!IO<Graph>::read_graph(graph, argv[1]))
		return 1;

	cout << "success\n" << endl;

	// Вывод считанного графа:
	cout << "Graph: " << endl;
	IO<Graph>::show_graph(graph);

	// Вывод количества ребер в графе:
	cout << "\n|E| = " << graph.E() << endl;

	// Поиск пути в графе:	
	int v = 0, w = 4; // НОМЕРА ВЕРШИН ЗАДАЮТСЯ ПРЯМО В КОДЕ СЛЕВА (из v в w)!

	DeepSearcher<Graph> DS(graph);

	vector<string> paths = DS.get_paths(v, w);

	cout << "\nPaths from " << v << " to " << w << ":" << endl;
	for(auto path : paths)
		cout << path << endl;

	// ShortestPathSearcher<Graph> SPS(graph);

	// cout << SPS.get_path(2, 3) << endl;

	return 0;
}