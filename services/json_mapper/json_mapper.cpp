#include "json_mapper.h"

#include <stack>

bool JsonMapper::isWhitespace(char c)
    {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

bool JsonMapper::isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

string JsonMapper::parseStringValue(const string& json, size_t& i)
    {
        string value;
        ++i; // Skip opening quote
        while (i < json.size() && json[i] != '\"')
        {
            if (json[i] == '\\' && i + 1 < json.size())
            {
                value += json[i + 1];
                i += 2;
            }
            else
            {
                value += json[i];
                ++i;
            }
        }
        return value;
    }

string JsonMapper::parseNumberValue(const string& json, size_t& i)
    {
        string value;
        while (i < json.size() && (isDigit(json[i]) || json[i] == '.' || json[i] == '-' || json[i] == 'e' || json[i] == 'E'))
        {
            value += json[i];
            ++i;
        }
        --i; // Adjust position for main loop
        return value;
    }

void JsonMapper::parseJson(const string& jsonString, map<string, string>& jsonMap)
    {
        enum class State { KEY, VALUE, OBJECT, ARRAY };
        State state = State::OBJECT;
        string currentKey;
        stack<State> stateStack;
        stack<string> keyStack;
        stack<int> arrayIndexStack;

        for (size_t i = 0; i < jsonString.size(); ++i)
        {
            char c = jsonString[i];
            
            if (isWhitespace(c)) continue;

            switch (state)
            {
            case State::OBJECT:
                if (c == '{') continue;
                if (c == '}')
                {
                    if (!stateStack.empty())
                    {
                        state = stateStack.top();
                        stateStack.pop();
                        keyStack.pop();
                    }
                }
                else if (c == '\"')
                {
                    state = State::KEY;
                    --i; // Reprocess quote in KEY state
                }
                break;

            case State::KEY:
                if (c == '\"')
                {
                    currentKey = parseStringValue(jsonString, i);
                    if (!keyStack.empty())
                    {
                        currentKey = keyStack.top() + "." + currentKey;
                    }
                    state = State::VALUE;
                }
                break;

            case State::VALUE:
                if (c == ':') continue;
                
                if (c == '\"')
                {
                    string value = parseStringValue(jsonString, i);
                    jsonMap[currentKey] = value;
                    state = State::OBJECT;
                }
                else if (c == '{')
                {
                    stateStack.push(State::OBJECT);
                    keyStack.push(currentKey);
                    state = State::OBJECT;
                }
                else if (c == '[')
                {
                    stateStack.push(State::OBJECT);
                    keyStack.push(currentKey);
                    arrayIndexStack.push(0);
                    state = State::ARRAY;
                }
                else if (isDigit(c) || c == '-')
                {
                    string value = parseNumberValue(jsonString, i);
                    jsonMap[currentKey] = value;
                    state = State::OBJECT;
                }
                break;

            case State::ARRAY:
                if (c == ']')
                {
                    if (!stateStack.empty())
                    {
                        state = stateStack.top();
                        stateStack.pop();
                        keyStack.pop();
                        arrayIndexStack.pop();
                    }
                }
                else if (c == '\"')
                {
                    string value = parseStringValue(jsonString, i);
                    string arrayKey = keyStack.top() + "[" + to_string(arrayIndexStack.top()) + "]";
                    jsonMap[arrayKey] = value;
                    arrayIndexStack.top()++;
                }
                else if (c == '{')
                {
                    string arrayKey = keyStack.top() + "[" + to_string(arrayIndexStack.top()) + "]";
                    keyStack.push(arrayKey);
                    arrayIndexStack.top()++;
                    state = State::OBJECT;
                }
                else if (isDigit(c) || c == '-')
                {
                    string value = parseNumberValue(jsonString, i);
                    string arrayKey = keyStack.top() + "[" + to_string(arrayIndexStack.top()) + "]";
                    jsonMap[arrayKey] = value;
                    arrayIndexStack.top()++;
                }
                break;
            }
        }
    }

void JsonMapper::map_json(string json, JsonObject& object)
    {
        vector<string> fields = object.toJsonFields();
        map<string, string> jsonMap;
        parseJson(json, jsonMap);
        object.fromJson(jsonMap);
    }
