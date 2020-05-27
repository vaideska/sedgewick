// Реализация функций объявленных в интерфейcе

#include <math.h>
#include "point.h"                                  //подключение заголовочного файла

float distance(point a, point b) {
	float dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}