#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class IJsonObject
{
public:
    virtual ~IJsonObject() = default;
    virtual vector<string> toJsonFields() = 0;
    virtual void fromJson(map<string, string> jsonMap) = 0;
};

class JsonObject : public IJsonObject
{
public:
    virtual vector<string> toJsonFields() {
        return {};
    }
    virtual void fromJson(map<string, string> jsonMap) {}
    virtual ~JsonObject() = default;
};


#endif // JSON_OBJECT_H
