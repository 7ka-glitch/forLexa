#pragma once
#include <cstring>
#include <stdexcept>
#include <iostream>

// Ограничения
#define DICTNAMEMAXSIZE 20    // максимальный размер имени словаря
#define DICTMAXSIZE 100       // максимальная емкость словаря
#define ENTRYNAMEMAXSIZE 30   // максимальная длина имени элемента словаря

// Макросы исключений
#define THROW01 "Create: превышен размер имени словаря"          // если длина имени >= DICTNAMEMAXSIZE
#define THROW02 "Create: превышена максимальная емкость словаря"    // если size > DICTMAXSIZE
#define THROW03 "AddEntry: переполнение словаря"                   // если количество элементов >= maxsize
#define THROW04 "AddEntry: дублирование идентификатора"           // если уже есть элемент с таким id
#define THROW05 "GetEntry: не найден элемент"                      // если элемент не найден
#define THROW06 "DelEntry: не найден элемент"                      // если удаляемый элемент не найден
#define THROW07 "UpdEntry: не найден элемент"                      // если элемент для обновления не найден
#define THROW08 "UpdEntry: дублирование идентификатора"           // если при обновлении id дублируется

namespace Dictionary {

    // Структура элемента словаря
    struct Entry {
        int id;                            // уникальный идентификатор
        char name[ENTRYNAMEMAXSIZE];       // строковое представление информации
    };

    // Структура словаря
    struct Instance {
        char name[DICTNAMEMAXSIZE];        // имя словаря
        int maxsize;                       // максимальное количество элементов
        int size;                          // текущее количество элементов
        Entry* dictionary;                 // динамический массив элементов
    };

    // Объявления функций:
    Instance Create(const char name[DICTNAMEMAXSIZE], int size);
    void AddEntry(Instance& inst, Entry ed);
    void DelEntry(Instance& inst, int id);
    void UpdEntry(Instance& inst, int id, Entry new_ed);
    Entry GetEntry(Instance& inst, int id);
    void Print(const Instance& d);
    void Delete(Instance& d);
}
