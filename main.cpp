#include <iostream>
#include <fstream>
#include "BST4.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }


    int numValue;
    string command;
    string value;
    string userInput;

    BinaryTree<string> add;
    BinaryTree<int> addTree;


    while (in >> userInput) {
        if (userInput == "STRING") {
            command = "String";
            out << "STRING true" << endl;
        } else if (userInput == "INT") {
            command = "INT";
            out << "INT true" << endl;
        }
        if (userInput == "add") {
            if(command == "String") {

                in >> value;
                if(add.addNode(value) == 1) {
                    out << userInput << " " << value << " " << "true" << endl;
                }
                else {
                    out << userInput << " " << value << " " << "false" << endl;
                }
            }
            else {
                in >> value;
                if(addTree.addNode(stoi(value)) == 1) {
                    out << userInput << " " << value << " " << "true" << endl;
                }
                else {
                    out << userInput << " " << value << " " << "false" << endl;
                }
            }
        }
        else if (userInput == "print") {
            if(command == "String") {

                out << userInput << ":";
                out << add.toString() << endl;
            }
            else {
                out << userInput << ":";
                out << addTree.toString() << endl;
            }

        } else if (userInput == "size") {
            if(command == "String") {

                out << userInput << " " << add.Size() << endl;
            }
            else {
                out << userInput << " " << addTree.Size() << endl;
            }

        } else if (userInput == "clear") {
            if(command == "String") {
                if(add.clearTree()) {
                    out << userInput << " true" << endl;
                }
                else {
                    out << userInput << " false" << endl;
                }
            }
            else {
                if(addTree.clearTree()) {
                    out << userInput << " true" << endl;
                }
                else {
                    out << userInput << " false" <<  endl;
                }
            }

        } else if (userInput == "remove") {
            if(command == "String") {
                in >> value;
                if(add.removeNode(value)) {
                    out << userInput << " " << value << " true" << endl;
                }
                else {
                    out << userInput << " " << value << " false" << endl;
                }
            }
            else {
                in >> value;
                if(addTree.removeNode(stoi(value))) {
                    out << userInput << " " << value << " true" << endl;
                }
                else {
                    out << userInput << " " << value << " false" << endl;
                }

            }

        } else if (userInput == "find") {
            if(command == "String") {
                in >> value;
                if(add.Find(value)) {
                    out << userInput << " " << value << " found" << endl;
                }
                else {
                    out << userInput << " " << value << " not found" << endl;
                }

            }
            else {
                in >> numValue;
                if(addTree.Find(numValue)) {
                    out << userInput << " " << numValue << " found" << endl;
                }
                else {
                    out << userInput << " " << numValue << " not found" << endl;
                }
            }

        }
    }










    return 0;
}


