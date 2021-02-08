#ifndef _SHORTEST_PATH_SEARCHER_
#define _SHORTEST_PATH_SEARCHER_

#include "main_header.hpp"

/*
 * ~~~~ Краткое описание класса:
 * Модульный класс, использующийся для поиска картчайших путей в графе Graph.
*/
template<typename Graph>
class ShortestPathSearcher {
private:
	int v_cnt;
	vector<vector<int>> sp_tracer, sp_matrix;

	/*
	 * Вспомогательная функция, возвращающая путь из промежуточных вершин полного
	 * пути от вершины v до вершины w в строке вида -k1-k2...-kn, где k1, ..., kn -
	 * вершины графа G в кратчайшем пути v-k1-k2-...-kn-w. Используется функцией
	 * get_path().
	*/
	string trace(int v, int w) const;
public:
	/* Конструктор. */
	ShortestPathSearcher(const Graph &G);

	/*
	 * Функция возвращает строку с полным кратчайшим путем от вершины v до вершины
	 * w и его стоимостью в формате: "v-k1-k2-...-kn-w, P", где k1, ..., kn -
	 * промежуточные вершины графа G на пути от вершины v до вершины w по кратчайшему
	 * пути, а P - стоимость полного кратчайшего пути.
	*/
	string get_path(int v, int w) const;
};

#endif // _SHORTEST_PATH_SEARCHER_