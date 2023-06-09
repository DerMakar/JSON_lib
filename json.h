#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>
#include <exception>
#include <typeinfo>
#include <cmath>
#include <stdexcept>


namespace json {

class Node;
// Сохраните объявления Dict и Array без изменения
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
    

};



    

class Node {
public:
    
    using Value = std::variant<std::nullptr_t, Array, Dict, int, double, std::string, bool>; //  Поместив nullptr_t в начале списка типов, вы сделаете его типом по умолчанию для этого variant

    Node() = default;

    Node(nullptr_t value);

    Node(Array value);

    Node(Dict value);

    Node(int value);

    Node(double value);

    Node(std::string value);

    Node(bool value);

    const Value& GetValue() const; // return value_
    
    bool IsInt() const;

    bool IsDouble() const;

    bool IsPureDouble() const;

    bool IsBool() const;

    bool IsString() const;

    bool IsNull() const;

    bool IsArray() const;

    bool IsMap() const;

    int AsInt() const;
    
    double AsDouble() const;
    
    bool AsBool() const;

    const std::string& AsString() const;

    const Array& AsArray() const;

    const Dict& AsMap() const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    
private:
    Value value_;
};

template <typename Value>
void PrintValue(const Value& value, std::ostream& out) {
    out << value;
}

// Перегрузка функции PrintValue для вывода значений null
void PrintValue(std::nullptr_t, std::ostream& out);
// Другие перегрузки функции PrintValue пишутся аналогично
void PrintValue(const std::string& str, std::ostream& out);

void PrintValue(bool bool_, std::ostream& out);

void PrintNode(const Node& node, std::ostream& out);

void PrintValue(const Array& array_, std::ostream& out);

void ParseString(const std::string& str, std::ostream& out);

void PrintValue(const Dict& dict, std::ostream& out);



class Document {
public:
    explicit Document(Node root);

    const Node& GetRoot() const;

    bool operator==(const Document& rhs) const;

    bool operator!=(const Document& rhs) const;

private:
    Node root_;
};

Document Load(std::istream& input);

void Print(const Document& doc, std::ostream& output);

}  // namespace json