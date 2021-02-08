#ifndef _GRAPH_IO_
#define _GRAPH_IO_

#include "main_header.hpp"

/*
 * ~~~~ Краткое описание назначения класса:
 * Вспомогательный шаблонный класс для ввода и вывода графов.
*/
template<typename Graph>
class IO {
private:
	/*
	 * Вспомогательныя функция замены символов, переданных в векторе extra_chars, в строке
	 * str на символ replacement. 
	*/
	inline static void replace_extra_chars(string &str,
		const vector<char> &extra_chars, const char replacement = ' ');
	/* 
	 * ~~~~ Описание функции:
	 * Вспомогательная функция форматирования строки str. Выполняет удаление лишних пробелов
	 * и всех символов, переданных в векторе extra_chars, из форматируемой строки. Использует
	 * функцию replace_extra_chars().
	 * ~~~~ Описание параметров:
	 * str - форматируемая строка; extra_chars - вектор символов, подлежащих удалению из строки.
	*/
	static void format_string(string &str, const vector<char> &extra_chars = {});
public:
	/* Функция вывода графа G в стандартный поток вывода. */
	static void show_graph(const Graph &G);
	
	/*
	 * ~~~~ Описание функции:
	 * Функция чтения графа из файла filename.
	 * ~~~~ Примечания об использовании:
	 * В случае ошибки при попытке открытия файла функция возвращает false, а если файл
	 * был открыт успешно true.
	 * Функция фактически идентифицирует ребра графа по соответствующим данным в файле
	 * filename при помощи статического метода класса Graph, Graph::scan_edges() и
	 * добавляет их в уже существующий граф G.
	 * ~~~~ Описание параметров:
	 * G - граф для записи данных; filename - имя файла с данными о графе; extra_chars -
	 * вектор символов, подлежащих удалению из текста файла (например, угловые скобки [],
	 * если данные для графа создаются автоматически без соответствующего форматирования).
	*/
	static bool read_graph(Graph &G, const string &filename, const vector<char> &extra_chars = {});
};

#endif // _GRAPH_IO_