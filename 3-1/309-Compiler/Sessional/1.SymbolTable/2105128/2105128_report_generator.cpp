#include <iostream>
#include <random>
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

int main()
{
    freopen("2105128_report_input.txt", "r", stdin);

    int num_buckets;
    cin >> num_buckets;
    SymbolTable *sdbm = new SymbolTable(num_buckets, &HashFunction::SDBMHash);
    SymbolTable *cus = new SymbolTable(num_buckets, &HashFunction::count_unique_substrings);
    SymbolTable *joaat = new SymbolTable(num_buckets, &HashFunction::joaat);
    SymbolTable *djb2 = new SymbolTable(num_buckets, &HashFunction::djb2);

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
                    sdbm->insert(name, type, extra_info);
                    cus->insert(name, type, extra_info);
                    joaat->insert(name, type, extra_info);
                    djb2->insert(name, type, extra_info);
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
                    sdbm->insert(name, type, extra_info);
                    cus->insert(name, type, extra_info);
                    joaat->insert(name, type, extra_info);
                    djb2->insert(name, type, extra_info);
                }
            }
            else
            {
                if (extra_info.empty())
                {
                    sdbm->insert(name, type, extra_info);
                    cus->insert(name, type, extra_info);
                    joaat->insert(name, type, extra_info);
                    djb2->insert(name, type, extra_info);
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
                sdbm->LookUp(name);
                cus->LookUp(name);
                joaat->LookUp(name);
                djb2->LookUp(name);
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
                sdbm->remove(name);
                cus->remove(name);
                joaat->remove(name);
                djb2->remove(name);
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
                    sdbm->print_current_scope();
                    cus->print_current_scope();
                    joaat->print_current_scope();
                    djb2->print_current_scope();
                }
                else
                {
                    sdbm->print_all_scope();
                    cus->print_all_scope();
                    joaat->print_all_scope();
                    djb2->print_all_scope();
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
                sdbm->EnterScope();
                cus->EnterScope();
                joaat->EnterScope();
                djb2->EnterScope();
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
                sdbm->ExitScope();
                cus->ExitScope();
                joaat->ExitScope();
                djb2->ExitScope();
            }
        }

        else if (operation == "Q")
        {
            int collision_sdbm = sdbm->getCollision();
            int collision_cus = cus->getCollision();
            int collision_joaat = joaat->getCollision();
            int collision_djb2 = djb2->getCollision();

            ofstream file("report_output.txt");

            if (file.is_open())
            {
                file << "Collision for SDBMHash function: " << collision_sdbm << "/" << num_buckets << " = " << static_cast<float>(collision_sdbm) / num_buckets << endl;
                file << "Collision for Count Unique Substring function: " << collision_cus << "/" << num_buckets << " = " << static_cast<float>(collision_cus) / num_buckets << " (https://cp-algorithms.com/string/string-hashing.html)" << endl;
                file << "Collision for JOAAT function: " << collision_joaat << "/" << num_buckets << " = " << static_cast<float>(collision_joaat) / num_buckets << " (https://github.com/alessandromrc/JOAAT/blob/main/src/JOAAT.h)" << endl;
                file << "Collision for DJB2 function: " << collision_djb2 << "/" << num_buckets << " = " << static_cast<float>(collision_djb2) / num_buckets << " (https://theartincode.stanis.me/008-djb2/)" << endl;

                file.close();
                cout << "Data written to file successfully." << endl;
            }
            else
            {
                cerr << "Failed to open file for writing." << endl;
            }

            delete sdbm;
            delete cus;
            delete joaat;
            delete djb2;
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