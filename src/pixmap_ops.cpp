/**
 * @project LABYRINTH2015
 * ICP project
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file pixmap_ops.cpp
 * @date 2015/05/10
 * @brief functions for creating valid QPixMaps from avaliabe static data
*/

#include "field_const.h"
#include <string>

/**
 * @brief to_pixmap creates allocates pixmap from availabe static data according to input string
 * @param size - size of game (can be 1 for generating free field)
 * @param to_parse - string describing fields
 * @return pointer to dynamically allocated data
 * @see free_xpm();
 */
const char **to_pixmap(int size, std::string to_parse)
{
    int len  = size * 5 * 10;
    const char **result_ptr = new const char* [len + 9];

    std::string head = std::to_string(len) + " " + std::to_string(len) + " 8" + " 1 ";
    // Aloc and store to Pixmap.
    char *head_ptr = new char[head.length()];
    for (unsigned k = 0; k < head.length(); k++)
    {   // Copy to memory.
        head_ptr[k] = head[k];
    }

    result_ptr[0] = head_ptr;
    result_ptr[1] = "@ c grey";
    result_ptr[2] = "# c black";
    result_ptr[3] = "$ c orange";
    result_ptr[4] = "% c red";
    result_ptr[5] = "! c blue";
    result_ptr[6] = "^ c white";
    result_ptr[7] = "& c #878719";
    result_ptr[8] = "* c #C440A3";

    int offset = 0;
    int counter = 0;
    for (int i = 9; i < len + 9; i++)
    {
        std::string line = "";
        for (int j = 0; j < size * 5; j++)
        {
            char type = to_parse[j + offset];
            switch (type)
            {
                case '@': line += player_1[counter]; break;
                case '&': line += player_2[counter]; break;
                case '%': line += player_3[counter]; break;
                case '!': line += player_4[counter]; break;
                case 'X': line += color_B[counter]; break;
                case ' ': line += color_G[counter]; break;
                //
                case 'a': line += item_a[counter]; break;
                case 'b': line += item_b[counter]; break;
                case 'c': line += item_c[counter]; break;
                case 'd': line += item_d[counter]; break;
                case 'e': line += item_e[counter]; break;
                case 'f': line += item_f[counter]; break;
                //
                case 'g': line += item_g[counter]; break;
                case 'h': line += item_h[counter]; break;
                case 'i': line += item_i[counter]; break;
                case 'j': line += item_j[counter]; break;
                case 'k': line += item_k[counter]; break;
                case 'l': line += item_l[counter]; break;
                //
                case 'm': line += item_m[counter]; break;
                case 'n': line += item_n[counter]; break;
                case 'o': line += item_o[counter]; break;
                case 'p': line += item_p[counter]; break;
                case 'q': line += item_q[counter]; break;
                case 's': line += item_s[counter]; break;
                //
                case 't': line += item_t[counter]; break;
                case 'u': line += item_u[counter]; break;
                case 'v': line += item_v[counter]; break;
                case 'w': line += item_w[counter]; break;
                case 'x': line += item_x[counter]; break;
                case 'y': line += item_y[counter]; break;
                default:  line += color_B[counter]; break;
            }
        }

        char *line_ptr = new char[line.length()];
        for (unsigned l = 0; l < line.length(); l++)
        {   // Copy to memory.
            line_ptr[l] = line[l];
        }
        // Save and reset line.
        result_ptr[i] = line_ptr;
        counter++;

        if (counter == 10)
        {   // Set offset.
            counter = 0;
            offset = offset + size * 5;
        }
    }
    return result_ptr;
}

/**
 * @brief create_card allocates card picture
 * @param color - color of the item card is showing
 * @param shape - shape of the item card is showing
 * @return pointer to dynamically allocated data
 * @see free_card();
 * @see decide_color(); and decide_shape();
 */
const char **create_card(int color, int shape)
{
    const char **result_ptr = new const char* [203];

    result_ptr[0] = "120 200 2 1";
    result_ptr[1] = "# c grey";

    switch (color)
    {
        case RED:    result_ptr[2] = "  c red";      break;
        case GREEN:  result_ptr[2] = "  c #C440A3";  break;
        case BLUE:   result_ptr[2] = "  c blue";     break;
        case WHITE:  result_ptr[2] = "  c white";    break;
        case BROWN:  result_ptr[2] = "  c #878719";  break;
        case ORANGE: result_ptr[2] = "  c orange";   break;
    }

    for (int i = 3; i < 203; i++)
    {
        std::string line = "";
        switch (shape)
        {
            case RECT: line = card_rect[i]; break;
            case TDWN: line = card_tdwn[i]; break;
            case BIGI: line = card_bigi[i]; break;
            case CRSS: line = card_crss[i]; break;
        }

        char *line_ptr = new char[line.length()];
        for (unsigned l = 0; l < line.length(); l++)
        {   // Copy to memory.
            line_ptr[l] = line[l];
        }
        // Save and reset line.
        result_ptr[i] = line_ptr;
    }
    return result_ptr;
}

/**
 * @brief create_figure allocates and creates figure pixmap
 * @param figure - char representing player figure
 * @return pointer to dynamically allocated data
 * @see free_figure();
 */
const char **create_figure(char figure)
{
    const char **result_ptr = new const char* [16];

    result_ptr[0] = "10 10 5 1";
    result_ptr[1] = "% c red";
    result_ptr[2] = "@ c none";
    result_ptr[3] = "! c blue";
    result_ptr[4] = "# c black";
    result_ptr[5] = "* c #C440A3";

    for (int i = 6; i < 16; i++)
    {
        std::string line = "";
        switch (figure)
        {
            case '@': line += player_1[i-6]; break;
            case '&': line += player_2[i-6]; break;
            case '%': line += player_3[i-6]; break;
            case '!': line += player_4[i-6]; break;
        }

        char *line_ptr = new char[line.length()];
        for (unsigned l = 0; l < line.length(); l++)
        {   // Copy to memory.
            line_ptr[l] = line[l];
        }
        // Save and reset line.
        result_ptr[i] = line_ptr;
    }
    return result_ptr;
}

/**
 * @brief free_card deallocates card
 * @param to_delete - pointer to card data
 */
void free_card(const char **to_delete)
{
    // Delete individual strings;
    for (int i = 3; i < 203; i++)
    {
        delete [] to_delete[i];
    }
    // Delete array of pointers.
    delete [] to_delete;
}

/**
 * @brief free_figure deallocates figure
 * @param to_delete - pointer to figure data
 */
void free_figure(const char **to_delete)
{
    // Delete individual strings;
    for (int i = 6; i < 16; i++)
    {
        delete [] to_delete[i];
    }
    // Delete array of pointers.
    delete [] to_delete;
}

/**
 * @brief free_xpm deallocates pixmap
 * @param size - size of game (1 for free field)
 * @param to_delete - pointer to pixmap data
 */
void free_xpm(int size, const char **to_delete)
{
    // Delete map head.
    delete [] to_delete[0];
    // Delete individual strings;
    int len = size * 5 * 10;
    for (int i = 9; i < len + 9; i++)
    {
        delete [] to_delete[i];
    }
    // Delete array of pointers.
    delete [] to_delete;
}

/**
 * @brief decide_color decides color card item should be
 * @param quest - actual players's quest
 * @return color code
 * @see FIELD_CONST_H for enums
 */
int decide_color(char quest)
{
    switch (quest)
    {
        case 'a':
        case 'g':
        case 'm':
        case 't': return RED;
        case 'b':
        case 'h':
        case 'n':
        case 'u': return GREEN;
        case 'c':
        case 'i':
        case 'o':
        case 'v': return BLUE;
        case 'd':
        case 'j':
        case 'p':
        case 'w': return WHITE;
        case 'e':
        case 'k':
        case 'q':
        case 'x': return BROWN;
        case 'f':
        case 'l':
        case 's':
        case 'y': return ORANGE;
    }
    return RED;
}

/**
 * @brief decide_shape decides shape card item should be
 * @param quest - actual players's quest
 * @return shape code
 * @see FIELD_CONST_H for enmus
 */
int decide_shape(char quest)
{
    switch (quest)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f': return RECT;
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l': return TDWN;
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 's': return CRSS;
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y': return BIGI;
    }
    return RECT;
}
