#include "SparseGraph.hpp"

// Вспомогательная функция удаления узла l->next из списка,
// в котором он находится.
void SparseGraph::delete_next(link l) {
	link garbage = l->next;
	l->next = l->next->next;
	delete garbage;
}

// Вспомогательная функция проверки существования пути из вершины from_v в
// вершину to_v в графе. Если ребро существует, функция возвращает его
// стоимость, иначе возвращает 0.
int SparseGraph::path_exists(int from_v, int to_v) const {
	if(from_v >= v_cnt || to_v >= v_cnt)
		return 0;
	for(auto curr = adjLists[from_v]; curr != nullptr; curr = curr->next)
		if(curr->v == to_v)
			return curr->c;
	return 0;
}

// Конструктор.
// ~~~~ Описание параметров:
// V - количество вершин; _directed - параметр, определяющий направленность/
// ненаправленность графа.
// ~~~~ Примечания:
// Параметр _directed имеет значение по умолчанию, равное true.
SparseGraph::SparseGraph(int V, bool _directed) :
	adjLists(V, nullptr), v_cnt(V), e_cnt(0), _directed(_directed) { }

// Деструктор. Освобождает память, выделенную под списки смежности.
SparseGraph::~SparseGraph() {
	for(int i = 0; i < v_cnt; ++i) {
		if(adjLists[i] == nullptr)
			continue;

		link pre = adjLists[i], curr = adjLists[i]->next;
		while(curr != nullptr) {
			delete pre;
			pre = curr;
			curr = curr->next;
		}
		delete pre;
	}
}

// Функция возвращает количество вершин в графе.
int SparseGraph::V() const { return v_cnt; }

// Функция возвращает количество ребер в графе.
int SparseGraph::E() const { return e_cnt; }

// Функция проверки ориентированности графа.
bool SparseGraph::directed() const { return _directed; }

// Функция проверки существования в графе ребра e. Если ребро существует,
// функция возвращает его стоимость, иначе возвращает 0.
int SparseGraph::edge(Edge e) const { return path_exists(e.v, e.w); }

// Функция проверки существования в графе ребра из вершины v в вершину w. Если
// ребро существует, функция возвращает его стоимость, иначе возвращает 0.
int SparseGraph::edge(int v, int w) const { return path_exists(v, w); }

// Функция добавления ребра e в граф. Если граф ненаправленнный, добавляется
// также "противоположно направленное" ребро (см. перегруженную версию функции
// - insert(int, int, int)).
void SparseGraph::insert(Edge e) { insert(e.v, e.w, e.c); }

// Функция добавления в граф ребра, ведущего из вершины v в вершину w, стоимостью с.
// Если граф ненаправленный, добавляется также ребро из w в v, стоимостью с.
void SparseGraph::insert(int v, int w, int c) {
	if(v >= v_cnt || w >= v_cnt)
		return;
	if(adjLists[v] == nullptr){
		adjLists[v] = new node(w, c);
		++e_cnt;
		// Если граф ненаправленный и ребра из w в v не существует, добавляем его.
		if(!_directed && !path_exists(w, v))
			insert(w, v, c);
	}
	else {
		link temp = adjLists[v];
		while(temp->next != nullptr) {
			if(temp->v == w)
				return;
			temp = temp->next;
		}

		if(temp->v != w) {
			temp->next = new node(w, c);
			++e_cnt;
			// Если граф ненаправленный и ребра из w в v не существует, добавляем его.
			if(!_directed && !path_exists(w, v))
				insert(w, v, c);
		}
	}
}

// Функция удаления ребра e из графа. Если граф ненаправленнный, удаляется
// также "противоположно направленное" ребро (см. перегруженную версию функции
// - remove(int, int)).
void SparseGraph::remove(Edge e) { remove(e.v, e.w); }

// Функция удаления из графа ребра, ведущего из вершины v в вершину w.
// Если граф ненаправленный, удаляется также ребро из w в v.
void SparseGraph::remove(int v, int w) {
	if(v >= v_cnt || w >= v_cnt)
		return;
	if(!path_exists(v, w))
		return;
	if(adjLists[v] == nullptr)
		return;

	link temp = adjLists[v];
	if(adjLists[v]->v == w) {
		adjLists[v] = adjLists[v]->next;
		delete temp;
		--e_cnt;
		// Если граф ненаправленный и ребро из w в v существует, удаляем его.
		if(!_directed && path_exists(w, v))
			remove(w, v);
		return;
	}
	while(temp->next != nullptr) {
		if(temp->next->v == w) {
			delete_next(temp);
			--e_cnt;
			// Если граф ненаправленный и ребро из w в v существует, удаляем его.
			if(!_directed && edge(w, v))
				remove(w, v);
			return;
		}
		temp = temp->next;
	}
}

// Статический метод, идентифицирует ребра, представленные в строке data,
// создает их и сохраняет в векторе edges.
// ~~~~ Примечания:
// Ожидаемые данные - пары чисел, перечисленные через запятую. Числа в паре
// разделены символом '-'. Пара "n-m" интерпретируется как ребро из вершины n
// в вершину m.
// ~~~~ Пример:
// Для data = "1-2,1-3,3-2" будет идентифицирован следующий набор ребер:
// Edge(1, 2), Edge(1, 3), Edge(3, 2).
void SparseGraph::scan_edges(vector<Edge> &edges, string data) {
	string delimiter = ";", token;
	size_t pos1 = 0, pos2 = 0, pos3 = 0;
	stringstream ss;
	int v, w, c;
	while((pos1 = data.find(delimiter)) != string::npos) {
		token = data.substr(0, pos1);
		if(token.length() != 0 && (pos2 = token.find('-')) != string::npos &&
				(pos3 = token.find(',')) != string::npos)
		{
			token[pos2] = ' ';
			token[pos3] = ' ';
			ss.str(token);
			ss >> v >> w >> c;
			edges.push_back(Edge(v, w, c));
		}

		data.erase(0, pos1 + delimiter.length());
		ss.clear();
	}
	
	if(data.length() != 0 && (pos2 = data.find('-')) != string::npos && 
			(pos3 = data.find(',')) != string::npos)
	{
		data[pos2] = ' ';
		data[pos3] = ' ';
		ss.str(data);
		ss >> v >> w >> c;
		edges.push_back(Edge(v, w, c));
	}
}

/* Выражения (1), (2), (3) и (4) ниже описывают класс внутреннего итератора для
класса SparseGraph: */

// Конструктор. G - граф, к которому применяется итератор, v - номер вершины,
// смежные с которой возвращаются методами begin(), next() и end().
SparseGraph::adjIterator::adjIterator(const SparseGraph &G, int v) : G(G), V(v) {	// (1)
	if(v >= G.v_cnt)																//
		curr = nullptr;																//
	else																			//
		curr = G.adjLists[V];														//
}																					//

// Метод возвращает индекс первой вершины, смежной с вершиной v.
int SparseGraph::adjIterator::begin() {	// (2)
	if(G.adjLists[V] != nullptr)		//
		return G.adjLists[V]->v;		//
	return -1;							//
}										//

// Метод возвращает индекс следующей смежной вершины и изменяет текущее
// состояние итератора.
int SparseGraph::adjIterator::next() {	// (3)
	if(curr == nullptr)					//
		return -1;						//
	curr = curr->next;					//
	if(curr == nullptr)					//
		return -1;						//
	return curr->v;						//
}										//

// Метод проверки текущего состояния итератора. Если все смежные с v вершины
// пройдены, будет возвращено true, иначе false.
bool SparseGraph::adjIterator::end() { return curr == nullptr; } // (4)