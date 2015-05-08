#include "field_const.h"
#include <string>

const char **to_pixmap(int size, std::string to_parse)
{
    int len  = size * 5 * 10;
    const char **result_ptr = new const char* [len + 4];

    std::string head = std::to_string(len) + " " + std::to_string(len) + " 3" + " 1";
    // Aloc and store to Pixmap.
    char *head_ptr = new char[head.length()];
    head_ptr[head.length()] = '\0';
    for (unsigned k = 0; k < head.length(); k++)
    {   // Copy to memory.
        head_ptr[k] = head[k];
    }

    result_ptr[0] = head_ptr;
    result_ptr[1] = "$ c green";
    result_ptr[2] = "@ c blue";
    result_ptr[3] = "# c red";

    int offset = 0;
    int counter = 0;
    for (int i = 4; i < len + 4; i++)
    {
        std::string line = "";
        for (int j = 0; j < size * 5; j++)
        {
            char type = to_parse[j + offset];
            switch (type)
            {
                case 'X': line += color_R[counter]; break;
                case ' ': line += color_B[counter]; break;
                case '@':
                case '&': line += player_2[counter]; break;
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

void free_xpm(int x, const char **to_delete)
{
    // Delete map head.
    delete [] to_delete[0];
    // Delete individual strings;
    int len = 60 * x + 3;
    for (int i = 3; i < len; i++)
    {
        delete [] to_delete[i];
    }
    // Delete array of pointers.
    delete [] to_delete;
}
