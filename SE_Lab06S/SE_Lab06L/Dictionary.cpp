#include "Dictionary.h"
#include <iostream>
using std::cout;
using std::endl;

namespace Dictionary {

    Instance Create(const char name[DICTNAMEMAXSIZE], int size) {
        // Если длина имени слишком велика (? DICTNAMEMAXSIZE), выбрасываем исключение
        if (strlen(name) >= DICTNAMEMAXSIZE) {
            throw THROW01;
        }
        // Если запрошенный размер превышает допустимое значение, выбрасываем исключение
        if (size > DICTMAXSIZE) {
            throw THROW02;
        }
        Instance inst;
        strcpy_s(inst.name, DICTNAMEMAXSIZE, name);
        inst.maxsize = size;
        inst.size = 0;
        inst.dictionary = new Entry[size];
        return inst;
    }

    void AddEntry(Instance& inst, Entry ed) {
        if (inst.size >= inst.maxsize) {
            throw THROW03;
        }
        // Проверяем на дублирование идентификатора
        for (int i = 0; i < inst.size; i++) {
            if (inst.dictionary[i].id == ed.id) {
                throw THROW04;
            }
        }
        inst.dictionary[inst.size] = ed;
        inst.size++;
    }

    void DelEntry(Instance& inst, int id) {
        bool found = false;
        for (int i = 0; i < inst.size; i++) {
            if (inst.dictionary[i].id == id) {
                // Сдвигаем последующие элементы влево
                for (int j = i; j < inst.size - 1; j++) {
                    inst.dictionary[j] = inst.dictionary[j + 1];
                }
                inst.size--;
                found = true;
                break;
            }
        }
        if (!found) {
            throw THROW06;
        }
    }

    void UpdEntry(Instance& inst, int id, Entry new_ed) {
        bool found = false;
        for (int i = 0; i < inst.size; i++) {
            if (inst.dictionary[i].id == id) {
                // Если меняется идентификатор, надо проверить, что новый id не занят другим элементом
                if (new_ed.id != id) {
                    for (int j = 0; j < inst.size; j++) {
                        if (j != i && inst.dictionary[j].id == new_ed.id) {
                            throw THROW08;
                        }
                    }
                }
                inst.dictionary[i] = new_ed;
                found = true;
                break;
            }
        }
        if (!found) {
            throw THROW07;
        }
    }

    Entry GetEntry(Instance& inst, int id) {
        for (int i = 0; i < inst.size; i++) {
            if (inst.dictionary[i].id == id) {
                return inst.dictionary[i];
            }
        }
        throw THROW05;
    }

    void Print(const Instance& d) {
        cout << "--------- " << d.name << " ---------" << endl;
        for (int i = 0; i < d.size; i++) {
            cout << d.dictionary[i].id << " " << d.dictionary[i].name << endl;
        }
    }

    void Delete(Instance& d) {
        delete[] d.dictionary;
        d.dictionary = nullptr;
        d.size = 0;
        d.maxsize = 0;
    }
}
