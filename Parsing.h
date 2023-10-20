#pragma once
#include "AVL.h"
#include "regex"

string GenerateRandomString(int length) {
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int max_index = (sizeof(letters) - 1);
    std::string word;
    for (int i = 0; i < length; ++i) {
        word += letters[rand() % max_index];
    }
    return word;
}

bool IsNameValid(string name) {
    regex valid_name("^([a-zA-Z\\s]+(\\s[a-zA-Z\\s]+)*)$");
    return regex_match(name, valid_name);
}

bool IsUFIDValid(string ufid) {
    regex valid_ufid("^\\d{8}$");
    return regex_match(ufid, valid_ufid);
}

void HandleUserInput(AVLTree& tree) {
    string command;
    string command_number;
    string name;
    string ufid;

    // Regex Patterns
    regex insert_pattern(R"(insert\s+\"(.*?)\"\s+(\d+))");
    regex remove_ufid_pattern(R"(remove\s+(\d{8}))");
    regex search_ufid_pattern(R"(search\s+(\d{8}))");
    regex search_name_pattern(R"(search\s+\"(.*?)\")");
    regex print_inorder_pattern("^printInorder$");
    regex print_preorder_pattern("^printPreorder$");
    regex print_postorder_pattern("^printPostorder$");
    regex print_levelcount_pattern("^printLevelCount$");
    regex remove_inorder_pattern(R"(^removeInorder\s+(-?\d+)$)");

    getline(cin, command_number);

    for (int i = 0; i < stoi(command_number); i++) {
        getline(cin, command);
        smatch match_results;

        if (command.find("insert") == 0) {
            if (regex_match(command, match_results, insert_pattern)) {
                name = match_results[1].str();
                ufid = match_results[2].str();

                if (IsNameValid(name) && IsUFIDValid(ufid)) {
                    tree.Insert(name, ufid);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("remove") == 0) {
            if (regex_match(command, match_results, remove_ufid_pattern)) {
                ufid = match_results[1].str();
                if (IsUFIDValid(ufid)) {
                    tree.RemoveUFID(ufid);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else if (regex_match(command, match_results, remove_inorder_pattern)) {
                int n = stoi(match_results[1].str());
                tree.RemoveInorder(n);
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("search") == 0) {
            if (regex_match(command, match_results, search_ufid_pattern)) {
                ufid = match_results[1].str();
                if (IsUFIDValid(ufid)) {
                    tree.SearchUFID(ufid);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else if (regex_match(command, match_results, search_name_pattern)) {
                name = match_results[1].str();
                if (IsNameValid(name)) {
                    tree.SearchNAME(name);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("printInorder") == 0 && regex_match(command, match_results, print_inorder_pattern)) {
            tree.PrintInorder();
        }

        else if (command.find("printPreorder") == 0 && regex_match(command, match_results, print_preorder_pattern)) {
            tree.PrintPreorder();
        }

        else if (command.find("printPostorder") == 0 && regex_match(command, match_results, print_postorder_pattern)) {
            tree.PrintPostorder();
        }

        else if (command.find("printLevelCount") == 0 && regex_match(command, match_results, print_levelcount_pattern)) {
            tree.PrintLevelCount();
        }
    }
}