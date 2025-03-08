#include "Book.h"

vector<string> Book::toJsonFields()
{
    return { "title", "author", "isbn" };
}

void Book::fromJson(map<string, string> jsonMap)
{
    title = jsonMap.count("title") ? jsonMap["title"] : "";
    author = jsonMap.count("author") ? jsonMap["author"] : "";
    isbn = jsonMap.count("isbn") ? jsonMap["isbn"] : "";
}
