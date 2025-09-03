#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <string>

using namespace std;

void createFile() {
    ofstream outf("zam.txt");
    if (!outf) {
        cout << "Error creating" << endl;
        exit(1);
    }
    int n;
    cout << "Сколько записей?" << endl;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string s;
        cout << "Запись " << i + 1 << ": ";
        getline(cin, s);
        outf << s << ";" << endl;

        cout << "Дата: ";
        getline(cin, s);
        outf << s << ";" << endl;

        cout << "Теги: ";
        getline(cin, s);
        outf << s << ";" << endl;
    }
    outf.close();
}

void readFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error reading" << endl;
        exit(1);
    }
    string s;
    while (getline(inf, s)) {
        cout << s << endl;
    }
    inf.close();
}

void editFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    vector<string> records;
    string line;
    while (getline(inf, line)) {
        records.push_back(line);
    }
    inf.close();

    int recordNumber;
    cout << "Введите номер записи для редактирования: ";
    cin >> recordNumber;
    cin.ignore();

    int index = (recordNumber - 1) * 3;

    if (index < 0 || index + 2 >= records.size()) {
        cout << "Неверный номер записи." << endl;
        return;
    }

    cout << "Текущая запись:\n";
    cout << records[index] << "\n" << records[index + 1] << "\n" << records[index + 2] << endl;

    string s;
    cout << "Новая запись: ";
    getline(cin, s);
    records[index] = s + ";";

    cout << "Новая дата: ";
    getline(cin, s);
    records[index + 1] = s + ";";

    cout << "Новые теги: ";
    getline(cin, s);
    records[index + 2] = s + ";";

    ofstream outf("zam.txt");
    for (const auto& rec : records) {
        outf << rec << endl;
    }
    outf.close();

    cout << "Запись обновлена." << endl;
}

void deleteFile() {
    if (remove("zam.txt") != 0) {
        cout << "Error deleting file" << endl;
        exit(1);
    }
    else {
        cout << "File deleted successfully" << endl;
    }
}

void searchFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error reading" << endl;
        exit(1);
    }
    string s;
    cout << "Введите ключевое слово для поиска: ";
    string keyword;
    cin >> keyword;
    bool found = false;
    while (getline(inf, s)) {
        if (s.find(keyword) != string::npos) {
            cout << s << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Запись не найдена." << endl;
    }
    inf.close();
}

void sortFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error reading" << endl;
        exit(1);
    }
    vector<string> records;
    string s;
    while (getline(inf, s)) {
        records.push_back(s);
    }
    inf.close();
    sort(records.begin(), records.end());
    ofstream outf("zam.txt");
    if (!outf) {
        cout << "Error writing" << endl;
        exit(1);
    }
    for (const auto& record : records) {
        outf << record << endl;
    }
    outf.close();
}

void filterFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error reading" << endl;
        exit(1);
    }
    string s;
    cout << "Введите тег для фильтрации: ";
    string tag;
    cin >> tag;
    bool found = false;
    while (getline(inf, s)) {
        if (s.find(tag) != string::npos) {
            cout << s << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Запись не найдена." << endl;
    }
    inf.close();
}

void backupFile() {
    ifstream inf("zam.txt");
    if (!inf) {
        cout << "Error reading" << endl;
        exit(1);
    }
    ofstream outf("zam_backup.txt");
    if (!outf) {
        cout << "Error creating backup" << endl;
        exit(1);
    }
    string s;
    while (getline(inf, s)) {
        outf << s << endl;
    }
    inf.close();
    outf.close();
    cout << "Backup created successfully." << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int a = -1;

    while (a != 0) {
        cout << "\nЧто запишем сегодня?\n"
            << "1 - создать файл\n"
            << "2 - редактировать файл\n"
            << "3 - читать файл\n"
            << "4 - удалить файл\n"
            << "5 - найти в файле\n"
            << "6 - сортировать файл\n"
            << "7 - отфильтровать\n"
            << "8 - создать бэкап\n"
            << "0 - выход из программы" << endl;
        cin >> a;

        switch (a) {
        case 1: createFile(); break;
        case 2: editFile(); break;
        case 3: readFile(); break;
        case 4: deleteFile(); break;
        case 5: searchFile(); break;
        case 6: sortFile(); break;
        case 7: filterFile(); break;
        case 8: backupFile(); break;
        case 0: cout << "Выход из программы." << endl; break;
        default: cout << "Что-то не то." << endl;
        }
    }

    return 0;
}
