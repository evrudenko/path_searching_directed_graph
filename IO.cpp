#include "IO.hpp"

// Функция замены "лишних" символов, передающихся в векторе extra_chars, в строке
// str. Замена осуществляется на символ, переданный в параметр replacement, по
// умолчанию равный ' '.
template<typename Graph>
void IO<Graph>::replace_extra_chars(string &str,
	const vector<char> &extra_chars, const char replacement)
{
	for(auto &ch : str)
		if(find(extra_chars.begin(), extra_chars.end(), ch) != extra_chars.end())
			ch = replacement;
}

// Функция вывода графа G. Вывод осуществляется в виде списков смежности.
template<typename Graph>
void IO<Graph>::show_graph(const Graph &G) {
	for(int v = 0; v < G.V(); ++v) {
		cout << v << ": ";
		typename Graph::adjIterator iter(G, v);
		for(int w = iter.begin(); !iter.end(); w = iter.next())
			cout << "(" << w << ", $" << G.edge(v, w) << "); ";
		cout << endl;
	}
}

// Функция чтения графа G из файла filename.
// ~~~~ Примечания:
// К тексту файла применяется следующее форматирование:
// - символы, переданные в векторе extra_chars, заменяются на пробелы;
// - подряд идущие пробелы заменяются одним пробелом;
// - пробелы в начале и конце строки удаляются.
// Для параметра extra_chars предоставляется аргумент по умолчанию, равный {} (пустому вектору).
template<typename Graph> // ***** !!! ИМЕЕТ СМЫСЛ ДОБАВИТЬ В ШАБЛОН ТИП, ОТДЕЛЬНО ОПРЕДЕЛЯЮЩИЙ ТИП ВХОДНЫХ ДАННЫХ.
bool IO<Graph>::read_graph(Graph &G, const string &filename, const vector<char> &extra_chars) {
	ifstream fin(filename);

	if(!fin.is_open()) {
		cout << "reading error" << endl;
		return false;
	}

	// Последовательно считываем и форматируем данные.
	string data = "", buff_string;
	while(getline(fin, buff_string)) {
		format_string(buff_string, extra_chars);
		data += buff_string + '\n';
	}

	// Передаем отформатированные данные для выявления представленных в них
	// ребер графа. Идентифицированные ребра сохраняются в векторе edges.
	vector<Edge> edges;
	Graph::scan_edges(edges, data);
	
	for(auto edge : edges)
		G.insert(edge);

	fin.close();
	return true;
}

// Вспомогательная функция форматирования строки. Выполняет замену "лишних" символов строки,
// переданных в векторе etra_chars, на пробелы (в целях сохранения целостности данных), а также
// заменяет подряд идущие пробелы на один пробел и удаляет пробелы в начале и конце строки.
// ~~~~ Описание параметров:
// str - форматируемая строка; extra_chars - вектор символов, подлежащих удалению из строки.
// ~~~~ Примечания:
// Для параметра extra_chars предоставляется аргумент по умолчанию, равный {} (пустому вектору).
template<typename Graph>
void IO<Graph>::format_string(string &str, const vector<char> &extra_chars) {
	// Заменяем символы, не относящиеся к данным, на пробелы.
	replace_extra_chars(str, extra_chars);
	
	// Удаляем подряд идущие пробелы.
	// tail_begin - указатель на элемент после последнего для НОВОЙ последовательности.
	auto tail_begin = unique(str.begin(), str.end(), [](char left, char right) {	// (1)
		return isspace(left) && isspace(right) && left == right;					//
	});																				//
	// Удаление из исходной строки не используемые более символы. Это необходимо,	//
	// потому что предыдущая конструкция сохраняет исходные размеры строки.			//
	str.erase(tail_begin, str.end());												//

	// Конструкция (1) решает только проблему последовательно идущих пробелов, но пробелы
	// в начале и конце строки также являются избыточными. Удаляем, их, если они есть:
	if(str[0] == ' ' || find(extra_chars.begin(), extra_chars.end(), str[0]) != extra_chars.end())
		str.erase(0, 1);
	if(str[str.length() - 1] == ' ')
		str.erase(str.length() - 1, 1);
}