#ifndef PIXMAP_OPS_H
#define PIXMAP_OPS_H

#include <string>

const char **to_pixmap(int size, std::string to_parse);
void free_xpm(int x, const char **to_delete);


#endif // PIXMAP_OPS_H
