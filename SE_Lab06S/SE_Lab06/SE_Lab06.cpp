#include <tchar.h>

// Определяем тестовые макросы (их можно также задать в настройках проекта)
//#define TEST_CREATE_01
//#define TEST_CREATE_02
//#define TEST_ADDENTRY_03
//#define TEST_ADDENTRY_04
//#define TEST_GETENTRY_05
//#define TEST_GETENTRY_06
//#define TEST_UPDENTRY_07
//#define TEST_UPDENTRY_08
#define TEST_DICTIONARY

// Если у вас проект создан с использованием precompiled headers, обязательно включите stdafx.h
#include <locale>
#include <iostream>
#include "../SE_Lab06L/Dictionary.h"
#include <cstring>
#include <string>

#if defined(TEST_CREATE_01) + defined(TEST_CREATE_02) + defined(TEST_ADDENTRY_03) + \
    defined(TEST_ADDENTRY_04) + defined(TEST_GETENTRY_05) + defined(TEST_GETENTRY_06) + \
    defined(TEST_UPDENTRY_07) + defined(TEST_UPDENTRY_08) + defined(TEST_DICTIONARY) > 1
#error "Нельзя устанавливать более одного тестового макроса!"
#endif

using namespace std;
using namespace Dictionary;

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");

    try {
#ifdef TEST_CREATE_01
        {
            // TEST_CREATE_01: проверка функции Create на слишком длинное имя
            try {
                // Передаём имя, длина которого не должна быть допустимой
                Instance testInst = Create("ИмяКотороеСлишкомДлинное", 5);
                cout << "TEST_CREATE_01 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW01) == 0)
                    cout << "TEST_CREATE_01 passed." << endl;
                else
                    cout << "TEST_CREATE_01 failed: неожиданная ошибка: " << e << endl;
            }
        }
#endif

#ifdef TEST_CREATE_02
        {
            // TEST_CREATE_02: проверка функции Create на недопустимый размер словаря
            try {
                Instance testInst = Create("Преподаватели", DICTMAXSIZE + 1);
                cout << "TEST_CREATE_02 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW02) == 0)
                    cout << "TEST_CREATE_02 passed." << endl;
                else
                    cout << "TEST_CREATE_02 failed: неожиданная ошибка: " << e << endl;
            }
        }
#endif

#ifdef TEST_ADDENTRY_03
        {
            // TEST_ADDENTRY_03: проверка переполнения словаря при добавлении элемента
            Instance testInst = Create("Тест", 1);
            Entry entry1 = { 1, "Первый" };
            AddEntry(testInst, entry1);
            Entry entry2 = { 2, "Второй" };
            try {
                AddEntry(testInst, entry2);
                cout << "TEST_ADDENTRY_03 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW03) == 0)
                    cout << "TEST_ADDENTRY_03 passed." << endl;
                else
                    cout << "TEST_ADDENTRY_03 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_ADDENTRY_04
        {
            // TEST_ADDENTRY_04: проверка дублирования идентификатора при добавлении
            Instance testInst = Create("Тест", 5);
            Entry entry1 = { 1, "Первый" };
            Entry entry2 = { 1, "Дубликат" };
            AddEntry(testInst, entry1);
            try {
                AddEntry(testInst, entry2);
                cout << "TEST_ADDENTRY_04 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW04) == 0)
                    cout << "TEST_ADDENTRY_04 passed." << endl;
                else
                    cout << "TEST_ADDENTRY_04 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_GETENTRY_05
        {
            // TEST_GETENTRY_05: проверка GetEntry для несуществующего элемента
            Instance testInst = Create("Тест", 5);
            Entry entry1 = { 1, "Первый" };
            AddEntry(testInst, entry1);
            try {
                Entry res = GetEntry(testInst, 999);
                cout << "TEST_GETENTRY_05 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW05) == 0)
                    cout << "TEST_GETENTRY_05 passed." << endl;
                else
                    cout << "TEST_GETENTRY_05 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_GETENTRY_06
        {
            // TEST_GETENTRY_06: проверка DelEntry для несуществующего элемента
            Instance testInst = Create("Тест", 5);
            Entry entry1 = { 1, "Первый" };
            AddEntry(testInst, entry1);
            try {
                DelEntry(testInst, 999);
                cout << "TEST_GETENTRY_06 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW06) == 0)
                    cout << "TEST_GETENTRY_06 passed." << endl;
                else
                    cout << "TEST_GETENTRY_06 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_UPDENTRY_07
        {
            // TEST_UPDENTRY_07: проверка UpdEntry для отсутствующего элемента
            Instance testInst = Create("Тест", 5);
            Entry entry1 = { 1, "Первый" };
            AddEntry(testInst, entry1);
            Entry updateEntry = { 3, "Обновленный" };
            try {
                UpdEntry(testInst, 999, updateEntry);
                cout << "TEST_UPDENTRY_07 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW07) == 0)
                    cout << "TEST_UPDENTRY_07 passed." << endl;
                else
                    cout << "TEST_UPDENTRY_07 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_UPDENTRY_08
        {
            // TEST_UPDENTRY_08: проверка попытки обновления с дублированием идентификатора
            Instance testInst = Create("Тест", 5);
            Entry entry1 = { 1, "Первый" };
            Entry entry2 = { 2, "Второй" };
            AddEntry(testInst, entry1);
            AddEntry(testInst, entry2);
            // Попытаемся обновить entry1, установив его id равным 2, что уже используется entry2
            Entry updateEntry = { 2, "Измененный" };
            try {
                UpdEntry(testInst, 1, updateEntry);
                cout << "TEST_UPDENTRY_08 failed: исключение не выброшено." << endl;
            }
            catch (const char* e) {
                if (strcmp(e, THROW08) == 0)
                    cout << "TEST_UPDENTRY_08 passed." << endl;
                else
                    cout << "TEST_UPDENTRY_08 failed: неожиданная ошибка: " << e << endl;
            }
            Delete(testInst);
        }
#endif

#ifdef TEST_DICTIONARY
        {
            // TEST_DICTIONARY: демонстрационный тест для всех функций
            Instance d1 = Create("Преподаватели", 5);
            Entry e1 = { 1, "Гладкий" };
            Entry e2 = { 2, "Великин" };
            Entry e3 = { 3, "Смелов" };
            Entry e4 = { 4, "Урбанович" };
            Entry e5 = { 5, "Пащей" }; // изменён, чтобы не было дублирования
            AddEntry(d1, e1);
            AddEntry(d1, e2);
            AddEntry(d1, e3);
            AddEntry(d1, e4);
            AddEntry(d1, e5);

            // Получаем элемент с id = 4 и удаляем элемент с id = 2
            Entry ex2 = GetEntry(d1, 4);
            DelEntry(d1, 2);

            // Обновляем элемент (id 3 заменяем на новый элемент с id 6)
            Entry newentry1 = { 6, "Гурин" };
            UpdEntry(d1, 3, newentry1);
            Print(d1);

            Instance d2 = Create("Студенты", 5);
            Entry s1 = { 1, "Иванов" };
            Entry s2 = { 2, "Петров" };
            Entry s3 = { 3, "Сидоров" };
            AddEntry(d2, s1);
            AddEntry(d2, s2);
            AddEntry(d2, s3);

            Entry newentry3 = { 3, "Николаев" };
            UpdEntry(d2, 3, newentry3);
            Print(d2);

            Delete(d1);
            Delete(d2);
            cout << "TEST_DICTIONARY passed: Все функции выполнены корректно." << endl;
        }
#endif

    }
    // Обработка исключений по типу выбранных макросов (строковые литералы)
    catch (const char* e) {
        std::cerr << "Ошибка: " << e << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Стандартное исключение: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Неизвестное исключение." << std::endl;
    }

    system("pause");
    return 0;
}
