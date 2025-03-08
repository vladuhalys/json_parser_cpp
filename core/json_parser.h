#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../services/json_reader/json_reader.h"
#include "../services/json_mapper/json_mapper.h"

enum ParsingPath {
    STRING_FORMAT,
    FILE_FORMAT
};

class IJsonParser
{
public:
    virtual void parse(JsonObject &object, const string& path, ParsingPath type_of_path) = 0;
};

class JsonParser : public IJsonParser, public IJsonReader
{
public:
    string read(const string& filename) override
    {
        return (JsonReader::read(filename) == nullptr) ? "" : *JsonReader::read(filename);
    }
    void parse(JsonObject &object, const string& path, ParsingPath type_of_path) override
    {
        string json;
        (type_of_path == ParsingPath::FILE_FORMAT) ? json = read(path) : json = path;
        JsonMapper mapper;
        mapper.map_json(json, object);
    }
};
#endif // JSON_PARSER_H
