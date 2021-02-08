#ifndef _MAIN_G_HEADER_
#define _MAIN_G_HEADER_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

/*
 * ~~~~ Описание структуры:
 * Вспомогательная структура данных, представляющая направленное ребро графа (дугу),
 * в направлении от вершины v к вершине w, стоимостью c.
*/
struct Edge {
	int v, w, c;
	Edge(int v = -1, int w = -1, unsigned c = 0) : v(v), w(w), c(c) { }
};

#endif // _MAIN_G_HEADER_