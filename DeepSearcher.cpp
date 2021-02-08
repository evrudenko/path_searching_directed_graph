#include "DeepSearcher.hpp"

// ~~~~ Красткое описание метода:
// Основной метод класса, реализующий логику поиска путей.
// ~~~~ Примечания:
// Метод использует рекурсию.
// ~~~~ Описание параметров:
// #1 v - стартовая вершина;
// #2 w - конечная вершина искомых путей;
// #3 prior_path - путь до вершины v, полученный в предыдущих вызовах (при первом вызове
// равен "");
// #4 marked - вектор пройденных на предыдущих шагах вершин (при первом вызове пуст,
// см. реализацию метода get_paths());
// #5 curr_costs - числовое значение, представляющее стоимость пути prior_path (при первом
// вызове равен 0).
template<typename Graph>
vector<string> DeepSearcher<Graph>::_get_paths(int v, int w,
		string prior_path, vector<int> marked, int curr_costs) const
{
	// Если искомая вершина w достигнута:
	if(v == w)
		return {prior_path + "-" + to_string(v) + ", " + to_string(curr_costs)};

	vector<string> res, temp;

	// Корректировка параметров для последующих вызовов:
	marked.push_back(v);
	prior_path += "-" + to_string(v);

	// Цикл, рекурсивно вызывающий метод для каждой вершины, смежной с v:
	typename Graph::adjIterator iter(G, v);
	for(auto i = iter.begin(); !iter.end(); i = iter.next()) {
		if(find(marked.begin(), marked.end(), i) == marked.end()) {
			temp = _get_paths(i, w, prior_path, marked, curr_costs + G.edge(v, i));
			res.insert(res.end(), temp.begin(), temp.end());
		}
	}

	return res;
}

// Конструктор.
template<typename Graph>
DeepSearcher<Graph>::DeepSearcher(const Graph &graph) : G(graph) {}

// Метод для пользовательского использования. Делегирует задачу поиска методу _get_paths().
template<typename Graph>
vector<string> DeepSearcher<Graph>::get_paths(int v, int w) const {
	return _get_paths(v, w, "", {}, 0);
}