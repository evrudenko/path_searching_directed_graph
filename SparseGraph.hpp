#ifndef _SPARSE_GRAPH_
#define _SPARSE_GRAPH_

#include "main_header.hpp"

/*
 * ~~~~ Краткое описание класса:
 * Класс представляет граф при помощи списков смежности. Удобен для хранения
 * разрезженных графов с малым количеством ребер.
*/
class SparseGraph {
private:
	/* Объявление внутреннего итератора класса другом. Объявлен в этом же классе ниже. */
	friend class adjIterator;

	/*
	 * Вспомогательная структура данных, представляющая звено (узел) списка и используемая
	 * в списках смежности.
	*/
	struct node {
		int v, c;
		node *next;
		node(int x, int p, node *n = nullptr) : v(x), c(p), next(n) { }
	};

	/* Синоним указателя на node (узел списка) определен для удобства. */
	typedef node* link;

	vector<link> adjLists;
	int v_cnt, e_cnt;
	bool _directed;

	/* Вспомогательная функция удаления узла l->next из списка, в котором он находится. */
	inline void delete_next(link l);

	/*
	 * ~~~~ Описание функции:
	 * Вспомогательная функция проверки существования пути из вершины
	 * from_v в вершину to_v в графе.
	 * ~~~~ Примечания:
	 * Если ребро существует, функция возвращает его стоимость, иначе возвращает 0.
	*/
	inline int path_exists(int from_v, int to_v) const;
public:
	/*
	 * Конструктор.
	 * ~~~~ Описание параметров:
	 * V - количество вершин; _directed - параметр, определяющий направленность/
	 * ненаправленность графа, в зависимости от этого параметра далее ребра будут
	 * добавляться/удаляться парами (например, при добавлении ребра Edge(1, 2)
	 * будет также добавлено ребро Edge(2, 1), аналогично с удалением).
	 */
	SparseGraph(int V, bool _directed = true);

	/* Деструктор. Освобождает память, выделенную под списки смежности. */
	~SparseGraph();

	/* Функция возвращает количество вершин в графе. */
	inline int V() const;

	/* Функция возвращает количество ребер в графе. */
	inline int E() const;

	/* Функция проверки графа на ориентированность. */
	inline bool directed() const;

	/*
	 * ~~~~ Описание функции:
	 * Функция проверки существования ребра e. 
	 * ~~~~ Примечания:
	 * Если ребро существует, функция возвращает его стоимость, иначе возвращает 0.
	 */
	inline int edge(Edge e) const;

	/*
	 * ~~~~ Описание функции:
	 * Функция проверки существования ребра, ведущего из вершины v в вершину w.
	 * ~~~~ Примечания:
	 * Если ребро существует, функция возвращает его стоимость, иначе возвращает 0.
	*/
	inline int edge(int v, int w) const;

	/*
	 * Функция добавления ребра e в граф. В случае, если граф ненаправленнный, добавляется
	 * также "противоположно направленное" ребро.
	*/
	inline void insert(Edge e);

	/*
	 * Функция добавления в граф ребра, ведущего из вершины v в вершину w.
	 * В случае, если граф неориентированный, добавляется также ребро из w в v,
	 * стоимостью c.
	*/
	void insert(int v, int w, int c);

	/*
	 * Функция удаления ребра e из графа. Если граф ненаправленнный, удаляется
	 * также "противоположно направленное" ребро.
	*/
	inline void remove(Edge e);

	/*
	 * Функция удаления из графа ребра, ведущего из вершины v в вершину w.
	 * В случае, если граф неориентированный, удаляется также ребро из w в v.
	*/
	void remove(int v, int w);

	/*
	 * ~~~~ Описание метода:
	 * Статический метод, идентифицирующий ребра, представленные в строке data,
	 * создает их и сохраняет в векторе edges.
	 * ~~~~ Примечания:
	 * Ожидаемые данные - пары чисел, перечисленные через запятую. Числа в паре
	 * разделены символом '-'. Пара "n-m" интерпретируется как ребро из вершины n
	 * в вершину m.
	 * ~~~~ Пример:
	 * Для data = "1-2,1-3,3-2" будет идентифицирован следующий набор ребер:
	 * Edge(1, 2), Edge(1, 3), Edge(3, 2).
	*/
	static void scan_edges(vector<Edge> &res, string data);

	/*
	 * Класс, представляющий итератор списков смежности класса SparseGraph.
	 * Создается с указанием номера вершины, смежные с которой необходимо возвращать.
	*/
	class adjIterator {
	private:
		link curr;
		int V;
		const SparseGraph &G;
	public:
		/*
		 * Конструктор. Принимает граф G и номер вешины v, смежные с которой
		 * необходимо рассмотреть. При создании первая вершина в рассматриваемом
		 * списке определяется как текущая, далее текущее состояние использует
		 * метод next().
		*/
		adjIterator(const SparseGraph &G, int v);

		/*
		 * ~~~~ Описание метода:
		 * Метод возвращает номер первой смежной вершины в списке.
		 * ~~~~ Примечания:
		 * Если список смежности пуст, возвращаемое значение равно -1.
		*/
		int begin();

		/*
		 * ~~~~ Описание метода:
		 * Метод возвращает номер следующей смежной вершины в списке после
		 * текущей.
		 * ~~~~ Примечания:
		 * Если следующей вершины не существует или итератор дошел до конца
		 * списка, возвращаемое значение равно -1.
		*/
		int next();

		/*
		 * Метод проверки текущего состояния итератора. Если все смежные вершины
		 * пройдены, будет возвращено true, иначе false.
		*/
		bool end();
	};
};

#endif // _SPARSE_GRAPH_