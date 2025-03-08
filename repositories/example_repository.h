#ifndef EXAMPLE_REPOSITORY_H
#define EXAMPLE_REPOSITORY_H

#include <iostream>

using namespace std;

#include "../models/example/Example.h"

class ExampleRepository {
public:
    static void print(Example example)
    {
        cout << "Title: " << example.title << '\n';
        cout << "URL: " << example.url << '\n';
        cout << "Date: " << example.date << '\n';
        cout << "Author: " << example.author << '\n';
        cout << "Content: " << example.content << '\n';
        cout << "Tags: ";
        for (const string& tag : example.tags)
        {
            cout << tag << " ";
        }
        cout << '\n';
        cout << "Book: " << '\n';
        cout << "Title: " << example.book.title << '\n';
        cout << "Author: " << example.book.author << '\n';
        cout << "ISBN: " << example.book.isbn << '\n';
    }
};
#endif // EXAMPLE_REPOSITORY_H
