#ifndef _DENSE_GRAPH_
#define _DENSE_GRAPH_

#include "main_header.hpp"

/*
 * ~~~~ Краткое описание класса:
 * Класс представляет граф при помощи матрицы смежности. Удобен для хранения
 * плотных графов с большим количеством ребер.
*/
class DenseGraph {
private:
	/* Объявление внутреннего итератора класса другом. Объявлен в этом же классе ниже. */
	friend class adjIterator;

	int v_cnt, e_cnt;
	bool _directed;
	vector<vector<int>> adjMatrix;
public:
	/*
	 * Конструктор.
	 * ~~~~ Описание параметров:
	 * V - количество вершин; _directed - параметр, определяющий направленность/
	 * ненаправленность графа, в зависимости от этого параметра далее ребра будут
	 * добавляться/удаляться парами (например, при добавлении ребра Edge(1, 2, 5)
	 * будет также добавлено ребро Edge(2, 1, 5), аналогично с удалением).
	 */
	DenseGraph(int V, bool _directed = true);

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
	 * Функция добавления в граф ребра, ведущего из вершины v в вершину w, стоимостью c.
	 * В случае, если граф неориентированный, добавляется также ребро из w в v, стоимостью c.
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
	 * Ожидаемые данные - матрица смежности. Для каждого элемента матрицы номер
	 * строки идентифицируется как номер начальной вершины, номер столбца как конечной,
	 * а значение на пересечении как стоимость дуги из начальной вершины в конечную.
	*/
	static void scan_edges(vector<Edge> &edges, string data);

	/*
	 * ~~~~ Краткое описание класса:
	 * Класс, представляющий итератор смежных вершин для заданной вершины (см.
	 * конструктор) во вмещающем классе DenseGraph.
	 * ~~~~ Примечания:
	 * Создается с указанием номера вершины, смежные с которой необходимо возвращать.
	*/
	class adjIterator {
	private:
		int curr, first, V;
		const DenseGraph &G;
	public:
		/*
		 * Конструктор. Принимает граф G и номер вешины v, смежные с которой
		 * необходимо рассмотреть. При создании первая вершина в рассматриваемом
		 * списке определяется как текущая, далее текущее состояние использует
		 * метод next().
		*/
		adjIterator(const DenseGraph &G, int v);

		/*
		 * ~~~~ Описание метода:
		 * Метод возвращает номер первой вершины, смежной с переданной вершной v.
		 * ~~~~ Примечания:
		 * Если смежных с v вершин нет, возвращаемое значение равно -1.
		*/
		int begin();

		/*
		 * ~~~~ Описание метода:
		 * Метод возвращает номер следующей смежной вершины после текущей.
		 * ~~~~ Примечания:
		 * Если следующей смежной вершины не существует или итератор дошел до
		 * конца списка, возвращаемое значение равно -1.
		*/
		int next();

		/*
		 * Метод проверки текущего состояния итератора. Если все смежные вершины
		 * пройдены, будет возвращено true, иначе false.
		*/
		bool end();
	};
};

#endif // _DENSE_GRAPH_