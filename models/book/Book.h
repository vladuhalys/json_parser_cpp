#ifndef BOOK_H
#define BOOK_H

#include "../../core/json_object.h"

class Book : public JsonObject
{
public:
    string title;
    string author;
    string isbn;

    vector<string> toJsonFields() override;
    void fromJson(map<string, string> jsonMap) override;
};

#endif // BOOK_H
