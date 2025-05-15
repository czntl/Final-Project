#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct SymptomTree{
    string symptom;
    string illness;
    SymptomTree* right;
    SymptomTree* left;
};
SymptomTree* createNode (string symptom, string illness);
SymptomTree* inSert (SymptomTree* root, string symptom, string illness);
SymptomTree* search (SymptomTree* root, string symptom);
SymptomTree* deleteNode (SymptomTree* root, string symptom);
SymptomTree* findsmal (SymptomTree* node);
void DisplayInOrder (SymptomTree* root);
void SavetoFile (SymptomTree* root, ofstream & file);
void LoadfromFile(SymptomTree*& root, string filename);
void DisplayMenu ();

SymptomTree* createNode (string symptom, string illness){
    SymptomTree* NewNode = new  SymptomTree;
    (*NewNode).symptom = symptom;
    (*NewNode).illness = illness;
    (*NewNode).left = (*NewNode).right = nullptr;
    return NewNode;
}

SymptomTree* inSert (SymptomTree* root, string symptom, string illness){
    if (root == nullptr){
        return createNode (symptom, illness);
    }
    if (symptom < (*root).symptom){
        (*root).left = inSert((*root).left, symptom, illness);
    }
    else {
        (*root).right = inSert ((*root).right, symptom, illness);
    }
    return root;
}

SymptomTree* search (SymptomTree* root, string symptom){
    if ( root == nullptr || (*root).symptom == symptom)
    return root;
    if ( symptom < (*root).symptom){
        return search ((*root).left, symptom);
    } else {
        return search ((*root).right, symptom);
    }
}

SymptomTree* findsmal (SymptomTree* node){
    while (node && (*node).left != nullptr){
        node = (*node).left;
    }
    return node;
}
SymptomTree* deleteNode(SymptomTree* root, string symptom) {
    if (root == nullptr) {
        return nullptr;
    }
    if (symptom < (*root).symptom) {
        root->left = deleteNode(root->left, symptom);
    }
    else if (symptom > (*root).symptom) {
       (*root).right = deleteNode((*root).right, symptom);
    }
    else {
        if ((*root).left == nullptr) {
            SymptomTree* temp = (*root).right;
            delete root;
            return temp;
        }
        else if ((*root).right == nullptr) {
            SymptomTree* temp = (*root).left;
            delete root;
            return temp;
        }
        else {
            SymptomTree* temp = findsmal((*root).right);
           (*root).symptom = (*temp).symptom;
            (*root).illness = (*temp).illness;
        }
    }
    return root;
}

void DisplayInOrder (SymptomTree* root){
    if (root != nullptr){
        DisplayInOrder ((*root).left);
        cout << "Symptom: " << (*root).symptom << " ,related Illness: " << (*root).illness << endl;
        DisplayInOrder ((*root).right);
    }
}

void SavetoFile (SymptomTree* root, ofstream & file){
    if (root != nullptr){
        SavetoFile((*root).left, file);
        file << root->symptom << "," << root->illness << endl;
        SavetoFile((*root).right, file);
    }
}

void LoadfromFile(SymptomTree*& root, string filename){
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string symptom = line.substr(0, comma);
            string illness = line.substr(comma + 1);
            root = inSert(root, symptom, illness);
        }
    }
    file.close();
}

void DisplayMenu (){
    system("color 8f");
    HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (h, 9);
    cout << "================ SYMPTREE ";
    SetConsoleTextAttribute (h, 2);
    cout << "o0o";
    SetConsoleTextAttribute (h, 9);
    cout << ": SYMPTOM TRACKING SYSTEM ================" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "|                    ";
    SetConsoleTextAttribute (h, 6);
    cout <<"      |";
    SetConsoleTextAttribute (h, 9);
    cout << "                                          |" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "| 1. Add Symptom Record <3                                            |" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "| 2. Search Symptom <3                                                |" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "| 3. Delete Symptom Record <3                                         |" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "| 4. Display All Records <3                                           |" << endl;
    SetConsoleTextAttribute (h, 9);
    cout << "| 5. Save and Exit <3                                                 |" << endl;
    SetConsoleTextAttribute (h, 9); 
    cout << "|__________________________________________________Enter your choice: |";
}                                                 

int main (){

    system("color 8f");
    HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
    SymptomTree* root = nullptr;
    string filename = "symptoms.txt";
    LoadfromFile(root, filename);

    int choice;
    string symptom, illness;

    do {
        DisplayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
            SetConsoleTextAttribute (h, 9);
                cout << "\n Enter Symptom: "; getline(cin, symptom);
            SetConsoleTextAttribute (h, 9);
                cout << "Enter Related Illness: "; getline(cin, illness);
                root = inSert(root, symptom, illness);
                break;
            case 2:
            SetConsoleTextAttribute (h, 9);
                cout << "\n Enter Symptom to Search: "; getline(cin, symptom);
                if (SymptomTree* found = search(root, symptom)){
            SetConsoleTextAttribute (h, 9);
                    cout << "Found: " << (*found).symptom << " → Illness: " << (*found).illness << endl;
                }
                else{
            SetConsoleTextAttribute (h, 9);
                    cout << "Symptom not found.\n";
                }
                break;
            case 3:
            SetConsoleTextAttribute (h, 9);
                cout << "\n Enter Symptom to Delete: "; 
                getline(cin, symptom);
                root = deleteNode(root, symptom);
            SetConsoleTextAttribute (h, 9);
                cout << "Record deleted (if it existed).\n";
                break;
            case 4:
            SetConsoleTextAttribute (h, 9);
                cout << "\n---------- SYMPTOM RECORDS ----------\n";
                DisplayInOrder(root);
                break;
            case 5:
                {
                    ofstream outFile(filename);
                    SavetoFile(root, outFile);
                    outFile.close();
            SetConsoleTextAttribute (h, 9);
                    cout << "\n Data saved. Exiting...\n";
                }
                break;
            default:
            SetConsoleTextAttribute (h, 13);
                cout << "\n Invalid choice. Please try again.\n";
        }
    } while (choice != 5);


    return 0;
}
