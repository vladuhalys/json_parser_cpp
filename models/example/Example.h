#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "../../models/book/Book.h"

class Example : public JsonObject
{
public:
    string title;
    string url;
    string date;
    string author;
    Book book;
    string content;
    vector<string> tags;

    vector<string> toJsonFields() override
    {
        return { "title", "url", "date", "author", "book.title", "book.author", "book.isbn", "content", "tags" };
    }

    void fromJson(map<string, string> jsonMap) override
    {
        title = jsonMap.count("title") ? jsonMap["title"] : "";
        url = jsonMap.count("url") ? jsonMap["url"] : "";
        date = jsonMap.count("date") ? jsonMap["date"] : "";
        author = jsonMap.count("author") ? jsonMap["author"] : "";
        content = jsonMap.count("content") ? jsonMap["content"] : "";

        // Parse Book object
        map<string, string> bookMap;
        if (jsonMap.count("book.title")) bookMap["title"] = jsonMap["book.title"];
        if (jsonMap.count("book.author")) bookMap["author"] = jsonMap["book.author"];
        if (jsonMap.count("book.isbn")) bookMap["isbn"] = jsonMap["book.isbn"];
        book.fromJson(bookMap);

        // Parse tags array
        tags.clear();
        for (int i = 0; ; ++i)
        {
            string key = "tags[" + to_string(i) + "]";
            if (jsonMap.count(key))
            {
                tags.push_back(jsonMap[key]);
            }
            else
            {
                break;
            }
        }
    }
};

#endif // EXAMPLE_H
