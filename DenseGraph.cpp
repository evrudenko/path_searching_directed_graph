#include "DenseGraph.hpp"

// Конструктор.
// ~~~~ Описание параметров:
// V - количество вершин; _directed - параметр, определяющий направленность/
// ненаправленность графа.
// ~~~~ Примечания:
// Параметр _directed имеет значение по умолчанию, равное true.
DenseGraph::DenseGraph(int V, bool _directed) :
	adjMatrix(V), v_cnt(V), e_cnt(0), _directed(_directed)
{
	for(int v = 0; v < V; ++v)
		adjMatrix[v].assign(V, 0);
}

// Функция возвращает количество вершин в графе.
int DenseGraph::V() const { return v_cnt; }

// Функция возвращает количество ребер в графе.
int DenseGraph::E() const { return e_cnt; }

// Функция проверки ориентированности графа.
bool DenseGraph::directed() const {return _directed; }

// Функция проверки существования в графе ребра e.
// Если ребро существует, функция возвращает его стоимость, иначе возвращает 0.
int DenseGraph::edge(Edge e) const { return edge(e.v, e.w); }

// Функция проверки существования в графе ребра из вершины v в вершину w.
// Если ребро существует, функция возвращает его стоимость, иначе возвращает 0.
int DenseGraph::edge(int v, int w) const {
	if(v < v_cnt && w < v_cnt)
		return adjMatrix[v][w];
	return 0;
}

// Функция добавления ребра e в граф. Если граф ненаправленнный, добавляется
// также "противоположно направленное" ребро (см. перегруженную версию функции
// - insert(int, int, int)).
void DenseGraph::insert(Edge e) { insert(e.v, e.w, e.c); }

// Функция добавления в граф ребра, ведущего из вершины v в вершину w, стоимостью
// c. Если граф ненаправленнный, добавляется также "противоположно направленное"
// ребро.
void DenseGraph::insert(int v, int w, int c) {
	if(v >= v_cnt || w >= v_cnt || c == 0)
		return;
	if(!adjMatrix[v][w]) {
		adjMatrix[v][w] = c;
		++e_cnt;

		if(!_directed)
			insert(w, v, c);
	}
}

// Функция удаления ребра e из графа. Если граф ненаправленнный, удаляется
// также "противоположно направленное" ребро (см. перегруженную версию функции
// - remove(int, int)).
void DenseGraph::remove(Edge e) { remove(e.v, e.w); }

// Функция удаления из графа ребра, ведущего из вершины v в вершину w.
// Если граф ненаправленный, удаляется также ребро из w в v.
void DenseGraph::remove(int v, int w) {
	if(v >= v_cnt || w >= v_cnt)
		return;
	if(adjMatrix[v][w]) {
		adjMatrix[v][w] = 0;
		--e_cnt;

		if(!_directed)
			remove(w, v);
	}
}


// ~~~~ Описание метода:
// Статический метод, идентифицирующий ребра, представленные в строке data,
// создает их и сохраняет в векторе edges.
// ~~~~ Примечания:
// Ожидаемые данные - матрица смежности. Для каждого элемента матрицы номер
// строки идентифицируется как номер начальной вершины, номер столбца как конечной,
// а значение на пересечении как стоимость дуги из начальной вершины в конечную.
void DenseGraph::scan_edges(vector<Edge> &edges, string data) {
	int i = 0, j = 0, c;
	size_t pos = 0;
	stringstream ss;
	string delimiter = "\n", line;
	while((pos = data.find(delimiter)) != string::npos) {
		line = data.substr(0, pos);
		ss.str(line);
		while(ss >> c) {
			if(c != 0)
				edges.push_back(Edge(i, j, c));
			++j;
		}

		data.erase(0, pos + delimiter.length());
		ss.clear();
		j = 0, ++i;
	}
}

/* Выражения (1), (2), (3) и (4) ниже описывают класс внутреннего итератора для
класса SparseGraph: */

// Конструктор. G - граф, к которому применяется итератор, v - номер вершины,
// смежные с которой возвращаются методами begin(), next() и end().
// ~~~~ Примечания:
// В теле конструктора выполняется поиск первой существующей смежной вершины
// и задается номер вершины, начиная с которой необходимо продолжать поиск
// смежных вершин в методе next().
DenseGraph::adjIterator::adjIterator(const DenseGraph &G, int v) :	// (1)
	G(G), V(v), first(-1)									//
{																	//
	/* Поиск первой существующей вершины, смежной с вершиной v. */	//
	for(int i = 0; (v < G.v_cnt) && (i < G.v_cnt); ++i)				//
		if(G.adjMatrix[v][i]) {										//
			first = i;												//
			break;													//
		}															//
	/* Определение текущего состояния итератора. */					//
	curr = (first == -1 ? G.v_cnt : first + 1);						//
}																	//

// Метод возвращает индекс первой вершины, смежной с вершиной v.
int DenseGraph::adjIterator::begin() { return first; }	// (2)

// Метод возвращает индекс следующей смежной вершины и изменяет текущее
// состояние итератора.
int DenseGraph::adjIterator::next() {				// (3)
	for(; curr < G.v_cnt; ++curr)					//
		if((V < G.v_cnt) && G.adjMatrix[V][curr])	//
			return curr++;							//
	return -1;										//
}													//

// Метод проверки текущего состояния итератора. Если все смежные с v вершины
// пройдены, будет возвращено true, иначе false.
bool DenseGraph::adjIterator::end() { return curr >= G.v_cnt; }	// (4)