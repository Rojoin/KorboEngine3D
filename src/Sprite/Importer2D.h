#pragma once
#include <string>

class Importer2D
{
public:
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};
