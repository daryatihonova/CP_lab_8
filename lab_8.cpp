#include <iostream>
#include <list>
#include <algorithm>
#include "App.h"
#include <fstream>
#include <unordered_set>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    list<App> appList; // Создаем пустой список программ

    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        App newApp;

        cout << "Введите наименование программы: ";
        cin >> newApp.name;

        // Проверяем, есть ли уже такая программа в списке
        auto it = find_if(appList.begin(), appList.end(), [&newApp](const App& app) {
            return app.name == newApp.name;
            });

        if (it != appList.end()) {
            // Программа уже есть в списке, генерируем исключение и делаем запись в системный файл журнала
            ofstream logFile("log.txt", ios_base::app);
            logFile << "Попытка добавления дубликата программы: " << newApp.name << endl;
            logFile.close();
            throw runtime_error("Программа уже существует в списке!");
        }

        cout << "Введите производителя программы: ";
        cin >> newApp.manufacturer;

        cout << "Введите размер на диске (в МБ): ";
        cin >> newApp.size;

        cout << "Введите цену программы: ";
        cin >> newApp.price;

        if (!appList.empty()) {
            App& prevApp = appList.back();
            prevApp.next = &newApp;
            newApp.prev = &prevApp;
        }
        appList.push_back(newApp);
        // Добавляем новую программу в список

        cout << "Продолжить ввод программы? (y/n): ";
        cin >> choice;
    }

    // Выводим список всех программ
    for (const auto& app : appList) {
        cout << "Название: " << app.name << ", Производитель: " << app.manufacturer << ", Размер на диске: " << app.size << " МБ, Цена: " << app.price << endl;
    }


    // Выбор действия пользователем
    char action;
    cout << "Если вы хотите удалить программу нажмите 'd', если хотите вывести информацию нажмите 'v', если хотите найти программу по названию нажмите 'p', если хотите получить уникальные производителей нажмите 'e': ";
    cin >> action;

    if (action == 'd') {
        // Удаление элемента по номеру позиции
        int position;
        cout << "Введите номер позиции для удаления элемента с головы списка: ";
        cin >> position;

        if (position >= 1 && position <= appList.size()) {
            auto it = appList.begin();
            advance(it, position - 1);

            if (it != appList.begin()) {
                App& prevApp = *prev(it);
                prevApp.next = it->next;
            }

            if (it->next != nullptr) {
                it->next->prev = it->prev;
            }

            appList.erase(it);

            // Выводим список всех программ после удаления
            for (const auto& app : appList) {
                cout << "Название: " << app.name << ", Производитель: " << app.manufacturer << ", Размер на диске: " << app.size << " МБ, Цена: " << app.price << endl;
            }

        }
        else {
            throw out_of_range("Указанная позиция превышает длину списка!");
        }
    }
    else if (action == 'v') {
        // Получение значения элемента по номеру позиции
        int position2;
        cout << "Введите номер позиции для получения элемента с головы списка: ";
        cin >> position2;

        if (position2 >= 1 && position2 <= appList.size()) {
            auto it = appList.begin();
            advance(it, position2 - 1);
            const App* selectedApp = &(*it);

            // Вывод информации о выбранной программе
            cout << "Выбранная программа: Название: " << selectedApp->name << ", Производитель: "
                << selectedApp->manufacturer << ", Размер на диске: " << selectedApp->size
                << " МБ, Цена: " << selectedApp->price << endl;

            // Вывод информации о предыдущем элементе, если таковой имеется
            if (selectedApp->prev != nullptr) {
                cout << "Предыдущая программа: Название: " << selectedApp->prev->name << ", Производитель: "
                    << selectedApp->prev->manufacturer << ", Размер на диске: " << selectedApp->prev->size
                    << " МБ, Цена: " << selectedApp->prev->price << endl;
            }

            // Вывод информации о следующем элементе, если таковой имеется
            if (selectedApp->next != nullptr) {
                cout << "Следующая программа: Название: " << selectedApp->next->name << ", Производитель: "
                    << selectedApp->next->manufacturer << ", Размер на диске: " << selectedApp->next->size
                    << " МБ, Цена: " << selectedApp->next->price << endl;
            }
        }
        else {
            throw out_of_range("Указанная позиция превышает длину списка!");
        }


    }
    else if (action == 'p') {
        // Поиск программы по названию и вывод номеров позиций
        string searchName;
        cout << "Введите название программы для поиска: ";
        cin >> searchName;

        bool found = false;
        int position = 1;
        for (const auto& app : appList) {
            if (app.name == searchName) {
                found = true;
                cout << "Программа '" << searchName << "' найдена на позиции: " << position << endl;

                // Вывод информации о найденной программе
                cout << "Название: " << app.name << ", Производитель: " << app.manufacturer
                    << ", Размер на диске: " << app.size << " МБ, Цена: " << app.price << endl;

                // Вывод информации о предыдущем элементе, если таковой имеется
                if (app.prev != nullptr) {
                    cout << "Предыдущая программа: Название: " << app.prev->name << ", Производитель: "
                        << app.prev->manufacturer << ", Размер на диске: " << app.prev->size
                        << " МБ, Цена: " << app.prev->price << endl;
                }

                // Вывод информации о следующем элементе, если таковой имеется
                if (app.next != nullptr) {
                    cout << "Следующая программа: Название: " << app.next->name << ", Производитель: "
                        << app.next->manufacturer << ", Размер на диске: " << app.next->size
                        << " МБ, Цена: " << app.next->price << endl;
                }

                break; // Выход из цикла после нахождения и вывода информации о программе
            }
            position++;
        }

        if (!found) {
            cout << "Программа '" << searchName << "' не найдена в списке." << endl;
        }


    }
    else if (action == 'e') {
        // Получение всех уникальных производителей
        const int MAX_UNIQUE_MANUFACTURERS = 100;
        vector<string> uniqueManufacturers;

        // Создаем временный список для хранения уже найденных производителей
        unordered_set<string> manufacturersSet;

        for (const auto& app : appList) {
            // Проверяем, был ли уже найден производитель
            if (manufacturersSet.find(app.manufacturer) == manufacturersSet.end()) {
                uniqueManufacturers.push_back(app.manufacturer);
                manufacturersSet.insert(app.manufacturer);

                if (uniqueManufacturers.size() >= MAX_UNIQUE_MANUFACTURERS) {
                    break; // Максимальное количество уникальных производителей достигнуто
                }
            }
        }

        // Вывод уникальных производителей
        cout << "Уникальные производители:" << endl;
        for (const auto& manufacturer : uniqueManufacturers) {
            cout << manufacturer << endl;
        }


        return 0;
    }
}
