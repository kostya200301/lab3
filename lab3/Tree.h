//
// Created by user on 04.05.2022.
//

#ifndef LAB3_TREE_H
#define LAB3_TREE_H

#include <iostream>
#include<sstream>
#include<vector>
#include<string>
//#include <commctrl.h>

using namespace std;

template <typename T>
struct Node{
    T element;
    Node *left;
    Node *right;
    bool ltag;
    bool rtag;

};

template <typename T>
class BinaryTree {
private:
    Node<T> *root; // голова дерева
    int stitching; // 0 - если дерево не прошито и 1 если прошито


    Node<T>* FindEl(Node<T>* tree, T element) { // Поиск элемента в дереве
        if ((tree == NULL) || (element == tree->element)){
            return tree;
        }
        if (element < tree->element) {
            return FindEl(tree->left, element);
        }
        else {
            return FindEl(tree->right, element);
        }
    }

    void del(Node<T> *&Tree){ // Удаление дерева
        if (Tree != NULL)
        {
            del(Tree->left);
            del(Tree->right);
            delete Tree;
            Tree = NULL;
        }

    }

    void add_node_local(T el, Node<T> *&MyTree) //Функция добавления звена в дерево
    {
        if (NULL == MyTree)
        {
            MyTree = new Node<T>;
            //MyTree = (Node<T>*)malloc(5000);
            MyTree->element = el;
            MyTree->left = NULL;
            MyTree->right = NULL;
            return;
        }
        if (el < MyTree->element)                   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
        {
            if (MyTree->left != NULL) add_node_local(el, MyTree->left);
            else
            {
                MyTree->left = new Node<T>;
                //MyTree->left = (Node<T>*)malloc(sizeof(Node<T>));
                MyTree->left->right = NULL;
                MyTree->left->left = NULL;
                MyTree->left->element = el;
                return;
            }
        }
        if (el > MyTree->element){
            if (MyTree->right != NULL) add_node_local(el, MyTree->right);
            else{
                MyTree->right = new Node<T>;
                //MyTree->right = (Node<T>*)malloc(sizeof(Node<T>));
                MyTree->right->right = NULL;
                MyTree->right->left = NULL;
                MyTree->right->element = el;
                return;
            }
        }
    }


    Node<T>* minValueNode(Node<T>* node) //return node with minimum key value found in that tree
    {
        Node<T>* current = node;

        // loop down to find the leftmost leaf
        while (current && current->left != NULL)
            current = current->left;

        return current;
    }

    Node<T>* deleteNode(Node<T>* root, T key)
    {
        if (root == NULL)
            return root;

        if (key < root->element)
            root->left = deleteNode(root->left, key);


        else if (key > root->element)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then This is the node
        // to be deleted
        else {
            if (root->left == NULL and root->right == NULL)
                return NULL;
                // node with only one child or no child
            else if (root->left == NULL) {
                Node<T> *temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                Node<T> *temp = root->left;
                free(root);
                return temp;
            }
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            Node<T> *temp = minValueNode(root->right);

            // Copy the inorder successor's content to this node
            root->element = temp->element;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->element);
        }
        return root;
    }

    void NLR_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL){
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
            NLR_local(tree->left, data);
            NLR_local(tree->right, data);
        }

    }

    void NRL_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL){
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
            NRL_local(tree->right, data);
            NRL_local(tree->left, data);
        }

    }

    void RLN_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL){
            RLN_local(tree->right, data);
            RLN_local(tree->left, data);
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
        }
    }

    void RNL_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL){
            RNL_local(tree->right, data);
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
            RNL_local(tree->left, data);
        }
    }

    void LNR_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL) {
            LNR_local(tree->left, data);
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
            LNR_local(tree->right, data);
        }
    }

    void LRN_local(Node<T>* tree, vector<T>* data = NULL) {
        if (tree != NULL) {
            LRN_local(tree->left, data);
            LRN_local(tree->right, data);
            if (data != NULL){
                data->push_back(tree->element);
            } else {
                cout << tree->element << " ";
            }
        }
    }

    void Where_local(bool (*fun)(T), Node<T>* temp, BinaryTree<T> &tree) {
        if (temp != NULL)
        {
            if (fun(temp->element))
            {
                tree.add_node(temp->element);
            }
            Where_local(fun, temp->left, tree);
            Where_local(fun, temp->right, tree);
        }
    }

    void Map_local(T (*fun)(T), Node<T>* temp) {
        if (temp != NULL)
        {
            temp->element = fun(temp->element);
            Map_local(fun, temp->left);
            Map_local(fun, temp->right);
        }
    }

    void Merger_local(Node<T>* temp1, BinaryTree<T> &tree) {
        if (temp1 != NULL){
            tree.add_node(temp1->element);
            Merger_local(temp1->right, tree);
            Merger_local(temp1->left, tree);
        }
    }

    bool isEquals(Node<T>* tree, Node<T>* subtree) {

        if (tree == NULL && subtree == NULL)
            return true;
        if (tree == NULL || subtree == NULL)
            return false;
        return tree->element ==
               subtree->element &&
               isEquals(tree->left, subtree->left) &&
               isEquals(tree->right, subtree->right);
    }

    bool isSubtree_local(Node<T>* tree, Node<T>* subtree) {

        return isEquals(tree, subtree) ||
               (tree->left != NULL && isSubtree_local(tree->left, subtree)) ||
               (tree->right != NULL && isSubtree_local(tree->right, subtree));
    }

    void CreateNewTree(Node<T>* tree, BinaryTree<T>* Tr) {
        if (tree != NULL) {
            Tr->add_node(tree->element);
            CreateNewTree(tree->left, Tr);
            CreateNewTree(tree->right, Tr);
        }

    }

    //Функции для охода прошитого дерева
    Node<T>* P1(Node<T>* p, int& action) {
        while (p->ltag) {
            p = p->left;
        }
        action = 3;
        return p;
    }

    Node<T>* P2(Node<T>* p, int& action) {
        if (p->rtag == false) {
            p = p->right;
            action = 3;
            return p;
        }
        p = p->right;
        action = 2;
        return p;
    }

    //Преобразование в строку
    string Vector_to_string(vector<T> vec) {
        ostringstream ss;
        //ss << "|";
        for (int i = 0; i < vec.size(); i++) {
            ss << "|" << vec[i] << " |";
        }
        string s(ss.str());
        return s;
    }

    //Преобразование строки в вектор
    vector<T> String_to_vector(string& str) {
        vector<T> vec;
        stringstream ss;
        ss << str;
        char trash;
        ss >> trash;
        T el;
        while (ss){
            ss >> el;
            ss >> trash;
            ss >> trash;
            vec.push_back(el);
        }
        return vec;
    }

    // Обходы в строку
    vector<T> NLR_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->NLR_local(r, &s);
        return s;
    }

    vector<T> LNR_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->LNR_local(r, &s);
        return s;
    }

    vector<T> LRN_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->LRN_local(r, &s);
        return s;
    }

    vector<T> RLN_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->RLN_local(r, &s);
        return s;
    }

    vector<T> RNL_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->RNL_local(r, &s);
        return s;
    }

    vector<T> NRL_string() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        vector<T> s;
        this->NRL_local(r, &s);
        return s;
    }

    void LNR_Firmware(Node<T>* pold, Node<T>* p) { // прошивка левой части дерева
        if (p != NULL) {
            LNR_Firmware(pold, p->left);
            if (p->left != NULL) {
                p->ltag = true;
            } else {
                p->ltag = false;
                p->left = pold;
            }
            pold = p;
            LNR_Firmware(pold, p->right);
        }
    }

    void RNL_Firmware(Node<T>* pold, Node<T>* p) { //прошивака правой части дерева
        if (p != NULL) {
            RNL_Firmware(pold, p->right);
            if (p->right != NULL) {
                p->rtag = true;
            } else {
                p->rtag = false;
                p->right = pold;
            }
            pold = p;
            if (p->ltag) {
                RNL_Firmware(pold, p->left);
            }
        }
    }


    //Балансировка дерева
    void storeBSTNodes(Node<T>* root, vector<Node<T>*> &nodes)
    {
        if (root==NULL)
            return;

        // Store nodes in Inorder (which is sorted
        // order for BST)
        storeBSTNodes(root->left, nodes);
        nodes.push_back(root);
        storeBSTNodes(root->right, nodes);
    }

    Node<T>* buildTreeUtil(vector<Node<T>*> &nodes, int start,
                        int end)
    {
        // base case
        if (start > end)
            return NULL;

        // Get the middle element and make it root
        int mid = (start + end)/2;
        Node<T> *root = nodes[mid];

        // Using index in Inorder traversal, construct
        //   left and right subtress
        root->left  = buildTreeUtil(nodes, start, mid-1);
        root->right = buildTreeUtil(nodes, mid+1, end);

        return root;
    }

    Node<T>* buildTree(Node<T>* root)
    {
        // Store nodes of given BST in sorted order
        vector<Node<T> *> nodes;
        storeBSTNodes(root, nodes);

        // Constructs BST from nodes[]
        int n = nodes.size();
        return buildTreeUtil(nodes, 0, n-1);
    }

public:

    BinaryTree() { //Создание путстого дерева
        this->root = NULL;
        this->stitching = 0;
    }

    BinaryTree(string str) { //Создание дерева по строке
        this->root = NULL;
        this->stitching = 0;
        vector<T> vec = String_to_vector(str);
        for (int i = 0; i < vec.size(); i++) {
            add_node(vec[i]);
        }
    }

    ~BinaryTree() { // очистка памяти и удаление дерева
        this->del(root);
    }

    void add_node(T element) { // добавление элемента в дерево
        this->add_node_local(element, root);
    }

    void DeleteElement(T el) {
        this->root = deleteNode(this->root, el);
    }

    // Обходы
    void NLR() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->NLR_local(r);
    }

    void LNR() {
        if (this->stitching) {
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->LNR_local(r);
    }

    void LRN() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->LRN_local(r);
    }

    void RLN() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->RLN_local(r);
    }

    void RNL() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->RNL_local(r);
    }

    void NRL() {
        if (this->stitching){
            throw "use another bypass for stitched wood";
        }
        Node<T>* r = root;
        this->NRL_local(r);
    }

    void Map(T (*fun)(T)) {  //построить новое дерево поэлементным преобразованием
        Map_local(fun, this->root);
    }

    BinaryTree* Where(bool (*fun)(T)) { // Строит новое дерево в которое входят лишь элементы удовл. условию fun
        auto tree = new BinaryTree<T>;
        Where_local(fun, this->root, *tree);
        return tree;
    }

    BinaryTree* Merger(BinaryTree<T>* tree) { // Слияние двух деревьев
        auto tree2 = new BinaryTree<T>;
        Merger_local(this->root, *tree2);
        Merger_local(tree->root, *tree2);
        return tree2;
    }

    bool isSubtree(BinaryTree<T>* tree) {  // Проверка является ли дерево поддеревом
        return isSubtree_local(this->root, tree->root);
    }

    BinaryTree* UnderTree(T element) { // Возвращает поддерево по вершине
        auto el = FindEl(this->root, element);
        if (el != NULL) {
            auto Tr = new BinaryTree<T>();
            CreateNewTree(el, Tr);
            return Tr;
        }
        return NULL;
    }

    bool FindElement(T el) { // Поиск элемента
        if (FindEl(this->root, el) == NULL) {
            return false;
        }
        return true;
    }


    T* FindElementByWay(string str) {  //Поиск элемента по заданному пути от корня дерева
        Node<T>* node = this->root;
        for (auto i : str) {
            if (node != NULL)
                if (i == 'L') {
                    node = node->left;
                } else {
                    node = node->right;
                }
        }
        if (node != NULL) {
            return &(node->element);
        }
        return NULL;
    }

    T* FindElementByWayFromPeak(T el, string str) { //Поиск элемента по заданному пути от некоторой вершины
        Node<T>* node = this->FindEl(this->root, el);
        for (auto i : str) {
            if (node != NULL)
                if (i == 'L') {
                    node = node->left;
                } else {
                    node = node->right;
                }
        }
        if (node != NULL) {
            return &(node->element);
        }
        return NULL;
    }

    void Balancing() { // Балансировка дерева
        this->root = buildTree(this->root);
    }

    void FirmwareTree() {  //Прошивка дерева
        this->stitching = 1;
        auto head = new Node<T>;
        head->left = this->root;
        head->right = head;
        this->root = head;
        Node<T>* pold = head;
        Node<T>* p = head->left;
        LNR_Firmware(pold, p);
        pold = head;
        p = head->left;
        RNL_Firmware(pold, p);

    }

    void LNR_Fir() {   //обход (прошитого дерева)
        if (this->stitching == 0){
            throw "use another bypass for not stitched wood";
        }
        Node<T>* p = this->root->left;
        int action = 2;
        while (true) {
            if (p == this->root) {
                return;
            }
            if (action == 2) {
                p = P1(p, action);
            }
            if (action == 3) {
                cout << p->element << " ";
                action = 4;
            }
            if (action == 4) {
                p = P2(p, action);
            }
        }
    }

    string LNR_Fir_String() { // Получение строки по обходу (прошитого дерева)
        vector<T> vec;
        if (this->stitching == 0){
            throw "use another bypass for not stitched wood";
        }
        Node<T>* p = this->root->left;
        int action = 2;
        while (true) {
            if (p == this->root) {
                return Vector_to_string(vec);
            }
            if (action == 2) {
                p = P1(p, action);
            }
            if (action == 3) {
                vec.push_back(p->element);
                action = 4;
            }
            if (action == 4) {
                p = P2(p, action);
            }
        }
    }


    void Bypass(string str) { //Обход заданный [R][L][N] форматом
        if (str == "LNR") {
            this->LNR();
        }
        else if (str == "LRN") {
            this->LRN();
        }
        else if (str == "RLN") {
            this->RLN();
        }
        else if (str == "RNL") {
            this->RNL();
        }
        else if (str == "NLR") {
            this->NLR();
        }
        else if (str == "NRL") {
            this->NRL();
        } else {
            throw "Incorrect path";
        }

    }

    string Bypass_string(string str) { // Получение строки по обходу
        if (str == "LNR") {
            return Vector_to_string(this->LNR_string());
        }
        else if (str == "LRN") {
            return Vector_to_string(this->LRN_string());
        }
        else if (str == "RLN") {
            return Vector_to_string(this->RLN_string());
        }
        else if (str == "RNL") {
            return Vector_to_string(this->RNL_string());
        }
        else if (str == "NLR") {
            return Vector_to_string(this->NLR_string());
        }
        else if (str == "NRL") {
            return Vector_to_string(this->NRL_string());
        } else {
            throw "Incorrect path";
        }

    }

};


#endif //LAB3_TREE_H
