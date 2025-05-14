#include <iostream>
#include <sstream>
#include "2105128_SymbolTable.cpp"
using namespace std;

int countWords(string str)
{
    int count = 0;
    bool inWord = false;

    for (char ch : str)
    {
        if (ch != ' ')
        {
            if (!inWord)
            {
                count++;
                inWord = true;
            }
        }
        else
        {
            inWord = false;
        }
    }

    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        cout << "Number of command line arguments do not match" << endl;
        return 0;
    }

    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    int num_buckets;
    cin >> num_buckets;
    SymbolTable *symbolTable;
    if (argv[3] == NULL || strcmp(argv[3], "SDBMHash") == 0)
    {
        symbolTable = new SymbolTable(num_buckets, &HashFunction::SDBMHash);
    }
    else if (strcmp(argv[3], "count_unique_substrings") == 0)
    {
        symbolTable = new SymbolTable(num_buckets, &HashFunction::count_unique_substrings);
    }
    else if (strcmp(argv[3], "JOAAT") == 0)
    {
        symbolTable = new SymbolTable(num_buckets, &HashFunction::joaat);
    }
    else if (strcmp(argv[3], "DJB2") == 0)
    {
        symbolTable = new SymbolTable(num_buckets, &HashFunction::djb2);
    }
    else
    {
        cout << "No such hash function" << endl;
        return 0;
    }
    string command;
    int cmd_number = 1;
    getline(cin, command);
    while (getline(cin, command))
    {
        cout << "Cmd " << cmd_number << ": " << command << endl;
        stringstream ss(command);
        string operation, name, type, extra_info;
        ss >> operation;
        ss >> name;
        ss >> type;
        getline(ss, extra_info);

        // cout<<operation<<endl<<name<<endl<<type<<endl<<extra_info<<endl;
        if (operation == " ")
        {
            continue;
        }

        else if (operation == "I")
        {
            if (type == "STRUCT" || type == "UNION")
            {
                int number_of_words = countWords(extra_info);
                if (number_of_words % 2 == 1)
                {
                    cout << "\tNumber of parameters mismatch for the command I" << endl;
                }
                else
                {
                    symbolTable->insert(name, type, extra_info);
                }
            }
            else if (type == "FUNCTION")
            {
                if (extra_info.empty())
                {
                    cout << "\tNumber of parameters mismatch for the command I" << endl;
                }
                else
                {
                    symbolTable->insert(name, type, extra_info);
                }
            }
            else
            {
                if (extra_info.empty())
                {
                    symbolTable->insert(name, type, extra_info);
                }
                else
                {
                    cout << "\tNumber of parameters mismatch for the command I" << endl;
                }
            }
        }

        else if (operation == "L")
        {
            if (!type.empty() || name.empty())
            {
                cout << "\tNumber of parameters mismatch for the command L" << endl;
            }
            else
            {
                symbolTable->LookUp(name);
            }
        }

        else if (operation == "D")
        {
            if (!type.empty() || name.empty())
            {
                cout << "\tNumber of parameters mismatch for the command D" << endl;
            }
            else
            {
                symbolTable->remove(name);
            }
        }

        else if (operation == "P")
        {
            if (!type.empty() || name.empty())
            {
                cout << "\tNumber of parameters mismatch for the command P" << endl;
            }
            else
            {
                if (name == "C")
                {
                    symbolTable->print_current_scope();
                }
                else
                {
                    symbolTable->print_all_scope();
                }
            }
        }

        else if (operation == "S")
        {
            if (!name.empty())
            {
                cout << "\tNumber of parameters mismatch for the command S" << endl;
            }
            else
            {
                symbolTable->EnterScope();
            }
        }

        else if (operation == "E")
        {
            if (!name.empty())
            {
                cout << "\tNumber of parameters mismatch for the command E" << endl;
            }
            else
            {
                symbolTable->ExitScope();
            }
        }

        else if (operation == "Q")
        {
            delete symbolTable;
            break;
        }

        else
        {
            cout << "\tWrong command" << endl;
        }

        cmd_number++;
    }

    return 0;
}