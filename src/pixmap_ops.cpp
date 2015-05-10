#include "field_const.h"
#include <string>

const char **to_pixmap(int size, std::string to_parse)
{
    int len  = size * 5 * 10;
    const char **result_ptr = new const char* [len + 9];

    std::string head = std::to_string(len) + " " + std::to_string(len) + " 8" + " 1";
    // Aloc and store to Pixmap.
    char *head_ptr = new char[head.length()];
    head_ptr[head.length()] = '\0';
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
    result_ptr[7] = "& c brown";
    result_ptr[8] = "* c green";

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
                case 'X': line += color_R[counter]; break;
                case ' ': line += color_B[counter]; break;
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
                default:  line += color_G[counter]; break;
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

const char **create_card(int color, int shape)
{
    const char **result_ptr = new const char* [203];

    result_ptr[0] = "120 200 2 1";
    result_ptr[1] = "# c grey";

    switch (color)
    {
        case RED:    result_ptr[2] = "  c red";    break;
        case GREEN:  result_ptr[2] = "  c green";  break;
        case BLUE:   result_ptr[2] = "  c blue";   break;
        case WHITE:  result_ptr[2] = "  c white";  break;
        case BROWN:  result_ptr[2] = "  c brown";  break;
        case ORANGE: result_ptr[2] = "  c orange"; break;
    }

    for (int i = 3; i < 203; i++)
    {
        std::string line = "";
        switch (shape)
        {
            case RECT: line = card_rect[i]; break;
            case TDWN: line = card_tdwn[i]; break;
            case BIGT: line = card_bigt[i]; break;
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
        case 'y': return BIGT;
    }
    return RECT;
}
