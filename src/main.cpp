#include <cstdlib>
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include "double_linked_list.h"
#include "shapes.h"
#include "shapes_factory.h"

using shapes::Shape;
using shapes::Circle;
using shapes::Square;
using shapes_factory::Factory;
using shapes_factory::CircleFactory;
using shapes_factory::SquareFactory;

namespace serialization {
const std::string circle_str = "circle";
const std::string square_str = "square";

void SerializeList(const DoubleLinkedList<Shape*>& list) {
    std::ofstream file("serialize.txt", std::ios::out | std::ios::binary);
    auto size = list.GetSize();
    file.write((char*)&size, sizeof(size_t));
    uint32_t value = 0;
    std::string type;
    for (auto &shape : list) {
        Circle* circle = dynamic_cast<Circle*>(shape);
        Square* square = dynamic_cast<Square*>(shape);
        value = (circle ? circle->getRadius() : square->getSide());
        type = (circle ? circle_str : square_str);
        file.write(type.c_str(), type.size());
        file.write((char*)&value, sizeof(uint32_t));
    }
}

void DeserializeList(DoubleLinkedList<Shape*>& list) {
    std::ifstream file("serialize.txt", std::ios::in | std::ios::binary);
    size_t size = 0;
    file.read((char*)&size, sizeof(size_t));
    uint32_t value = 0;
    std::string type;
    Shape* ptr = nullptr;
    for (int i = 0; i < size; i++) {
        file.read((char*)type.c_str(), 6 * sizeof(char));
        file.read((char*)&value, sizeof(uint32_t));
        if (type.c_str() == circle_str) {
            ptr = new Circle(value);
        } else {
            ptr = new Square(value);
        }
        type.clear();
        list.PushBack(ptr);
        ptr = nullptr;
    }
    delete ptr;
}

} // namespace serialization


void TestSerialization() {
    std::cout << "TEST List Serialization and Deserialization" << std::endl;
    Shape* ptr1 = new Circle(1);
    Shape* ptr2 = new Circle(10);
    Shape* ptr3 = new Square(1);
    Shape* ptr4 = new Square(10);
    DoubleLinkedList<Shape*> list{ ptr1, ptr2, ptr3, ptr4};
    assert(list.GetSize() == 4);
    std::cout << "List elements before serialization:" << std::endl;
    for (auto& shape : list) {
        shape->printArea();
    }
    std::cout << std::endl;
    // Сериализуем контейнер list в файл serialize.txt
    serialization::SerializeList(list);
    DoubleLinkedList<Shape*> list2;
    // Десериализуем: должны получить то, что было в list
    serialization::DeserializeList(list2);
    assert(list2.GetSize() == list.GetSize());
    //вывод элементов контейнера после десериализации для сравнения с источником
    std::cout << "List elements after deserialization:" << std::endl;
    for (auto& shape : list2) {
        shape->printArea();
    }
    delete ptr1, ptr2, ptr3, ptr4;
    std::cout << "TEST List Serialization and Deserialization DONE" << std::endl << std::endl;
}

void TestListMethods() {
    std::cout << "TEST List Methods" << std::endl;
    DoubleLinkedList<int> list{ 1, 2, 3, 4, 5, 6 };
    list.PopFront();
    assert(list.GetSize() == 5);

    list.PushBack(7);
    
    auto iter = list.Insert(list.end(), 8);
    assert(iter == list.end());
    
    iter = ++list.begin();
    list.Insert(iter, 9);
    
    iter = list.Insert(list.begin(), 10);
    assert(iter == list.begin());
    
    list.Erase(list.begin());
    iter = ++list.begin();
    list.Erase(++iter);
    
    assert((list == DoubleLinkedList<int>{2, 9, 4, 5, 6, 7, 8}));
    std::cout << "TEST List Methods DONE" << std::endl << std::endl;
}

void TestFactory() {
    std::cout << "TEST FACTORY" << std::endl;
    Factory* ptr1 = new CircleFactory;
    Factory* ptr2 = new SquareFactory;
    shapes_factory::createShapesAndPrintArea(ptr1, 1);
    shapes_factory::createShapesAndPrintArea(ptr2, 5);
    delete ptr1;
    delete ptr2;
    std::cout << "TEST FACTORY DONE" << std::endl;
}

int main() {
    TestSerialization();
    TestListMethods();
    TestFactory();
    return 0;
}