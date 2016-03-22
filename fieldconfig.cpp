#include "fieldconfig.h"

FieldConfig::FieldConfig()
{
    FieldConfig(easy);
}

FieldConfig::FieldConfig(int level)
{
    m_level = level;

    switch(level) {
        case easy:
            FieldConfig(9, 9, 10);
        break;

        case medium:
            FieldConfig(30, 18, 25);
        break;

        case hard:
            FieldConfig(18, 30, 40);
        break;
    }
}

FieldConfig::FieldConfig(int w, int h, int bombs)
{
    m_width = w;
    m_height = h;
    m_bombs = bombs;
}

