#include <iostream>
#include <string>
#include <sstream>

#include "Tree.h"
#include "Complex.h"
#include "Person.h"

#include "test.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream &out, vector<T> vec)
{
    for (int i = 0; i < vec.size(); i++) {
        out << vec[i] << " ";
    }
    out << "\n";
    return out;
}

string operator * (string str, int k){
    string str2 = "";
    for (int i = 0; i < k; i++){
        str2 += str;
    }
    return str2;
}


template <typename T>
T funck(T el) {
    return el * 2;
}



template <typename T>
void Func(BinaryTree<T>* tree, int stitching = 0) {
    int action;
    if (stitching == 0) {
        cout << "0 - exit\n";
        cout << "1 - tree traversal\n";
        cout << "2 - Save to string\n";
        cout << "3 - insert\n";
        cout << "4 - element search\n";
        cout << "5 - deleting an element\n";
        cout << "6 - map\n";
        cout << "7 - where\n";
        cout << "8 - Merging Trees\n";
        cout << "9 - Extracting a subtree\n";
        cout << "10 - Search for an entry subtree\n";
        cout << "11 - Reading from a string\n";
        cout << "12 - Node search by given path from root\n";
        cout << "13 - Node search by given path from given vertex\n";
        cout << "14 - balancing tree\n";
        cout << "15 - Firmware tree\n";
        cin >> action;
        if (action == 0) {
            exit(0);
        }
        if (action == 1) {
            cout << "Write LNR or LRN or NRL and ...\n";
            string traversal;
            cin >> traversal;
            tree->Bypass(traversal);
            cout << endl;
            Func(tree);
        }
        if (action == 2) {
            cout << "Write LNR or LRN or NRL and ...\n";
            string traversal;
            string result;
            cin >> traversal;
            result = tree->Bypass_string(traversal);
            cout << result;
            cout << endl;
            Func(tree);
        }
        if (action == 3) {
            cout << "write element to insert: \n";
            T el;
            cin >> el;
            tree->add_node(el);
            Func(tree);
        }
        if (action == 4) {
            cout << "write element to search: \n";
            T el;
            cin >> el;
            if (tree->FindElement(el)) {
                cout << "Element in TREE\n";
            }
            else {
                cout << "Element not in TREE\n";
            }
            Func(tree);
        }
        if (action == 5) {
            cout << "write element to delete: \n";
            T el;
            cin >> el;
            tree->DeleteElement(el);
            Func(tree);
        }
        if (action == 6) {
            cout << "Map func n->2n\n";
            tree->Map(funck);
            Func(tree);
        }
        if (action == 7) {
            cout << "It definitely works, but it's difficult to prescribe here for all types:))\n";
        }
        if (action == 8) {
            auto tr2 = new BinaryTree<T>;
            int count;
            cout << "count elements of second tree: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                cout << "Write element:\n";
                T el;
                cin >> el;
                tr2->add_node(el);
            }
            tree = tree->Merger(tr2);
            Func(tree);
        }
        if (action == 9) {
            cout << "White element to extracting a subtree:\n";
            T el;
            cin >> el;
            tree = tree->UnderTree(el);
            if (tree == NULL) {
                cout << "empty tree!!!";
                exit(0);
            }
            Func(tree);
        }
        if (action == 10) {
            auto tr2 = new BinaryTree<T>;
            int count;
            cout << "count elements of second tree: ";
            cin >> count;
            for (int i = 0; i < count; i++) {
                cout << "Write element:\n";
                T el;
                cin >> el;
                tr2->add_node(el);
            }
            if (tree->isSubtree(tr2)){
                cout << "new tree is subtree\n";
            }
            else {
                cout << "new tree is not subtree\n";
            }
            Func(tree);
        }
        if (action == 11) {
            cout << "white string in format |obj ||obj ||obj |\n";
            cout << "for example |1 ||2 ||6 ||3 ||9 |\n";
            string str1;
            getline(cin, str1);
            getline(cin, str1);
            tree = new BinaryTree<T>(str1);
            Func(tree);
        }
        if (action == 12) {
            cout << "write path. (ex: 'LRRL')\n";
            string path;
            cin >> path;
            auto el = tree->FindElementByWay(path);
            if (el != NULL) {
                cout << *el << endl;
            }
            else {
                cout << "Incorrect path\n";
            }
            Func(tree);
        }
        if (action == 13) {
            cout << "write element (start search/start path):\n";
            T elem;
            cin >> elem;
            cout << "write path. (ex: 'LRRL')\n";
            string path;
            cin >> path;
            auto el = tree->FindElementByWayFromPeak(elem, path);
            if (el != NULL) {
                cout << *el << endl;
            }
            else {
                cout << "Incorrect path\n";
            }
            Func(tree);
        }
        if (action == 14) {
            tree->Balancing();
            Func(tree);
        }
        if (action == 15) {
            tree->FirmwareTree();
            Func(tree, 1);
        }
    }
    else {
        cout << "0 - exit\n";
        cout << "1 - LNR tree traversal (Firmware tree)\n";
        cout << "2 - LNR tree traversal to String (Firmware tree)\n";
        cin >> action;
        if (action == 0) {
            exit(0);
        }
        if (action == 1) {
            tree->LNR_Fir();
            cout << endl;
            Func(tree, 1);
        }
        if (action == 2) {
            string str = tree->LNR_Fir_String();
            cout << str << endl;
            Func(tree, 1);
        }
    }


}


void init(int gen, int type) {
    int size;
    cout << "Count elements: ";
    cin >> size;
    if (gen == 1) {
        if (type == 1) {
            auto tree = new BinaryTree<int>;
            for (int i = 0; i < size; i++) {
                tree->add_node(rand() % (size * 3) );
            }
            Func(tree);
        }
        if (type == 2) {
            auto tree = new BinaryTree<float>;
            for (int i = 0; i < size; i++) {
                tree->add_node((rand() % (size * 3 * 10)) / 10.0 );
            }
            Func(tree);
        }
        if (type == 3) {
            auto tree = new BinaryTree<ComplexNumber<int>>;
            for (int i = 0; i < size; i++) {
                tree->add_node(GenComplex(size * 3) );
            }
            Func(tree);
        }
        if (type == 4) {
            auto tree = new BinaryTree<string>;
            for (int i = 0; i < size; i++) {
                tree->add_node(GenString(10));
            }
            Func(tree);
        }
        if (type == 5 || type == 6) {
            auto tree = new BinaryTree<Person>;
            for (int i = 0; i < size; i++) {
                tree->add_node(GenPerson());
            }
            Func(tree);
        }
    } else{
        if (type == 1) {
            auto tree = new BinaryTree<int>;
            for (int i = 0; i < size; i++) {
                cout << "Enter element:\n";
                int el;
                cin >> el;
                tree->add_node(el);
            }
            Func(tree);
        }
        if (type == 2) {
            auto tree = new BinaryTree<float>;
            for (int i = 0; i < size; i++) {
                cout << "Enter element:\n";
                float el;
                cin >> el;
                tree->add_node(el);
            }
            Func(tree);
        }
        if (type == 3) {
            auto tree = new BinaryTree<ComplexNumber<int>>;
            for (int i = 0; i < size; i++) {
                cout << "Enter element:\n";
                ComplexNumber<int> el;
                cin >> el;
                tree->add_node(el);
            }
            Func(tree);
        }
        if (type == 4) {
            auto tree = new BinaryTree<string>;
            for (int i = 0; i < size; i++) {
                cout << "Enter element:\n";
                string el;
                cin >> el;
                tree->add_node(el);
            }
            Func(tree);
        }
        if (type == 5 || type == 6) {
            auto tree = new BinaryTree<Person>;
            for (int i = 0; i < size; i++) {
                cout << "Enter element:\n";
                Person el;
                cin >> el;
                tree->add_node(el);
            }
            Func(tree);
        }
    }
}

int main()
{


    

    int f1;
    cout << "1 - create tree\n";
    cout << "2 - start tests\n";
    cin >> f1;
    if (f1 == 1){
        int gen;
        cout << "1 - generate\n";
        cout << "2 - input\n";
        cin >> gen;
        int f2;
        cout << "1 - int\n";
        cout << "2 - float\n";
        cout << "3 - complex\n";
        cout << "4 - strings\n";
        cout << "5 - students\n";
        cout << "6 - teachers\n";
        cin >> f2;
        init(gen, f2);
    }
    else {
        UnitTestsBinaryTree t;
        t.RUN();
        cout << "TESTS. OK!!!";
    }
}