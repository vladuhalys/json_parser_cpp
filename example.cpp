#include "core/json_parser.h"
#include "repositories/example_repository.h"

int main(int argc, char* argv[])
{
    JsonParser parser;
    Example object;

    parser.parse(object, "assets/json/example.json", ParsingPath::FILE_FORMAT);
    ExampleRepository::print(object);
    
    return 0;
}
