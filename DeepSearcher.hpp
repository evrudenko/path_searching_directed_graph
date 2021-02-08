#ifndef _DEEP_SEARCHER_
#define _DEEP_SEARCHER_

#include "main_header.hpp"

/*
 * ~~~~ Краткое описание класса:
 * Модульный класс поиска путей в графе Graph.
*/
template<typename Graph>
class DeepSearcher {
private:
	const Graph &G;

	/*
	 * ~~~~ Красткое описание метода:
	 * Основной метод класса, реализующий логику поиска путей.
	 * ~~~~ Примечания:
	 * Метод использует рекурсию.
	 * ~~~~ Описание параметров:
	 * #1 v - стартовая вершина;
	 * #2 w - конечная вершина искомых путей;
	 * #3 prior_path - путь до вершины v, полученный в предыдущих вызовах (при первом вызове
	 * равен "");
	 * #4 marked - вектор пройденных на предыдущих шагах вершин (при первом вызове пуст,
	 * см. реализацию метода get_paths());
	 * #5 curr_costs - числовое значение, представляющее стоимость пути prior_path (при первом
	 * вызове равен 0).
	*/
	vector<string> _get_paths(int v, int w, string prior_path,
		vector<int> marked, int curr_costs) const;
public:
	/* Конструктор. */
	DeepSearcher(const Graph &G);

	/*
	 * ~~~~ Краткое описание функции:
	 * Функция поиска путей из вершины v в вершину w в графе G.
	 * ~~~~ Примечания:
	 * Каждый элемент возвращаемого вектора содержит уникальный путь, записанный в строку
	 * вида "-v-k1-k2-...-kn-w, costs", где k1, ..., kn - номера промежуточных вершин
	 * на пути, а costs - числовое значение, равное стоимости соответствующего пути.
	 * Использует внутренний метод _get_paths().
	*/
	vector<string> get_paths(int v, int w) const;
};

#endif // _DEEP_SEARCHER_