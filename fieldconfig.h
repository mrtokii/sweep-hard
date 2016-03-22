#ifndef FIELDCONFIG_H
#define FIELDCONFIG_H


class FieldConfig
{


    int m_width;
    int m_height;
    int m_bombs;
    int m_level;

public:
    explicit FieldConfig();
    explicit FieldConfig(int level);
    explicit FieldConfig(int w, int h, int bombs);

    enum { easy, medium, hard, custom };

    int width() { return m_width; }
    int height() { return m_height; }
    int bombs() { return m_bombs; }
    int level() {  }

};

#endif // FIELDCONFIG_H
