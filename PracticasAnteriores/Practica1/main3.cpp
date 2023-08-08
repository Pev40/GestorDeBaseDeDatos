#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int main() {
    string input;
    regex select_regex("^&\\s*SELECT\\s+((?:\\w+|\\*)\\s*(?:,(?:\\s*(?:\\w+|\\*)\\s*))*)FROM\\s+(\\w+)\\s*#$");
    regex create_table_regex("^&\\s*CREATE\\s+TABLE\\s+(\\w+)\\s*\\((\\s*(?:\\w+\\s+\\w+\\s*(?:,|$))+)\\)\\s*#$");
    smatch match;

    while (true) {
        cout << "Ingrese una sentencia SQL: ";
        getline(cin, input);

        if (input == "exit") break;

        if (regex_match(input, match, select_regex)) {
            string table_name = match[2].str();
            vector<string> field_names;
            string fields_str = match[1].str();
            regex fields_regex("\\s*(\\w+)\\s*(?:,|$)");
            sregex_iterator it(fields_str.begin(), fields_str.end(), fields_regex);
            sregex_iterator end;

            while (it != end) {
                field_names.push_back((*it)[1].str());
                it++;
            }

            cout << "Sentencia SELECT encontrada." << endl;
            cout << "Tabla: " << table_name << endl;
            cout << "Campos: ";

            if (field_names.size() == 0) {
                cout << "*";
            } else {
                for (size_t i = 0; i < field_names.size(); i++) {
                    cout << field_names[i];

                    if (i != field_names.size() - 1) {
                        cout << ", ";
                    }
                }
            }

            cout << endl;
        } else if (regex_match(input, match, create_table_regex)) {
            std::cout<<match[1].str();
            string table_name = match[1].str();
            vector<string> field_names;
            string fields_str = match[2].str();
            regex fields_regex("\\s*(\\w+)\\s+(\\w+)\\s*(?:,|$)");
            sregex_iterator it(fields_str.begin(), fields_str.end(), fields_regex);
            sregex_iterator end;

            while (it != end) {
                field_names.push_back((*it)[1].str());
                it++;
            }

            cout << "Sentencia CREATE TABLE encontrada." << endl;
            cout << "Tabla: " << table_name << endl;
            cout << "Campos: ";

            for (size_t i = 0; i < field_names.size(); i++) {
                cout << field_names[i];

                if (i != field_names.size() - 1) {
                    cout << ", ";
                }
            }

            cout << endl;
        } else {
            cout << "Sentencia inválida." << endl;
        }
    }

    return 0;
}
