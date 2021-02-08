#include "ShortestPathSearcher.hpp"

/* Прим.: алгоритм неэффективен для решаемой задачи!!! Создан класс BreadthFirstSearcher! */

// Вспомогательная функция, возвращающая путь из промежуточных вершин полного
// пути от вершины v до вершины w в строке вида -k1-k2...-kn, где k1, ..., kn -
// вершины графа G в кратчайшем пути v-k1-k2-...-kn-w. Используется функцией
// get_path().
template<typename Graph>
string ShortestPathSearcher<Graph>::trace(int v, int w) const {
	int k = sp_tracer[v][w];
	if(k == 0)
		return "";
	return trace(v, k) + "-" + to_string(k) + trace(k, w);
}

// Конструктор. Строит матрицу смежности sp_matrix для графа G, проверяя
// каждое его ребро, и далее корректирует ее по алгоритму Флойда поиска
// кратчайших путей, также строит матрицу трассировки путей sp_tracer для
// возможности просмотра полного пути, помимо стоимости этого пути.
template<typename Graph>
ShortestPathSearcher<Graph>::ShortestPathSearcher(const Graph &G) :
	sp_tracer(G.V()), sp_matrix(G.V()), v_cnt(G.V())
{
	for(int i = 0; i < v_cnt; ++i) {
		sp_tracer[i].assign(v_cnt, 0);
		sp_matrix[i].assign(v_cnt, 0);
	}
	// Составление матрицы смежности из графа G
	for(int i = 0; i < v_cnt; ++i)
		for(int j = 0; j < v_cnt; ++j) {
			if(i == j)
				sp_matrix[i][j] = 0;
			else
				sp_matrix[i][j] = G.edge(i, j);
		}

	// Алгоритм Флойда поиска кратчайших путей.
	for(int k = 0; k < v_cnt; ++k) {
		for(int i = 0; i < v_cnt; ++i) {
			for(int j = 0; j < v_cnt; ++j) {
				if(sp_matrix[i][k] != 0 && sp_matrix[k][j] != 0 &&
					(sp_matrix[i][k] + sp_matrix[k][j] < sp_matrix[i][j] ||
						sp_matrix[i][j] == 0 && i != j))
				{
					sp_matrix[i][j] = sp_matrix[i][k] + sp_matrix[k][j];
					sp_tracer[i][j] = k;
				}
			} // for
		} // for
	} // for

}

// Функция возвращает строку с полным кратчайшим путем от вершины v до вершины
// w и его стоимостью в формате: "v-k1-k2-...-kn-w, P", где k1, ..., kn -
// промежуточные вершины графа G на пути от вершины v до вершины w по кратчайшему
// пути, а P - стоимость полного кратчайшего пути.
template<typename Graph>
string ShortestPathSearcher<Graph>::get_path(int v, int w) const {
	return to_string(v) + trace(v, w) + "-" + to_string(w) + ", " +
		(sp_matrix[v][w] == 0 && v != w ? "inf" : to_string(sp_matrix[v][w]));
}