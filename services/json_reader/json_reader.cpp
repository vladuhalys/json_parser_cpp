#include "json_reader.h"

#include <fstream>

string * JsonReader::read(const string& filename)
{
    fstream file;
    string line;
    string * json = new string();
    file.open(filename, ios::in);
    if (!file.is_open())
    {
        return nullptr;
    }
    while (getline(file, line))
    {
        *json += line;
    }
    file.close();
    return json;
}
