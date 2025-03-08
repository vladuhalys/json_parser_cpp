#ifndef JSON_READER_H
#define JSON_READER_H

#include <string>
using namespace std;


class IJsonReader {
public:
    virtual string read(const string& filename) = 0;
};

class JsonReader
{
public:
    static string * read(const string& filename);
};
#endif // JSON_READER_H
