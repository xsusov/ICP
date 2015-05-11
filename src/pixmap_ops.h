#ifndef PIXMAP_OPS_H
#define PIXMAP_OPS_H

#include <string>

const char **to_pixmap(int size, std::string to_parse);
void free_xpm(int x, const char **to_delete);

const char **create_card(int color, int shape);
void free_card(const char **to_delete);

int decide_color(char quest);
int decide_shape(char quest);

const char **create_figure(char figure);
void free_figure(const char **to_delete);

#endif // PIXMAP_OPS_H
