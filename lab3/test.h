#include <cassert>
#include "Tree.h"
#include "Person.h"


#ifndef LAB3_TEST_H
#define LAB3_TEST_H

bool f(int a) {
    if (a > 10) {
        return true;
    }
    return false;
}
int f2(int h) {
    return h * 2;
}

class UnitTestsBinaryTree {
private:
    void FindElement() {
        BinaryTree<int> TreeInt = BinaryTree<int>("|1 ||3 ||2 ||8 ||9 ||33 |");
        assert(TreeInt.FindElement(2) == 1);
        assert(TreeInt.FindElement(22) == 0);
        BinaryTree<Person> TreePerson = BinaryTree<Person>("|Alex ivanov petrov 12 33 4444 ||Alex ivanov petrov 12 33 4444 ||Alex ivanov petrov 18 33 44447 ||Alex ivanov Secons 14 33 3444 ||Ivan ivanov petrov 42 323 444334 |");
        assert(TreePerson.FindElement(Person(Person_ID(33, 4444), "Alex", "ivanov", "petrov", 12)) == 1);
        assert(TreePerson.FindElement(Person(Person_ID(33, 4444), "Pert", "ivanov", "petrov", 32)) == 0);
        BinaryTree<string> TreeString = BinaryTree<string>("|hello ||mu ||name ||is ||Alex ||Petrov |");
        assert(TreeString.FindElement("name") == 1);
        assert(TreeString.FindElement("gg") == 0);
    }

    void AddNode() {
        BinaryTree<int> b1("|1 ||2 ||7 ||4 |");
        assert(b1.FindElement(5) == 0);
        b1.add_node(5);
        assert(b1.FindElement(5) == 1);
    }

    void Where() {
        vector<int> Good = {11, 14, 16, 13, 19, 32};
        vector<int> Bad = {4, 7, 2, 9, 1, 3};
        BinaryTree<int> bt;
        for (auto h : Good) {
            bt.add_node(h);
        }
        for (auto h : Bad) {
            bt.add_node(h);
        }
        auto bt2 = bt.Where(f);
        for (auto h : Good) {
            assert(bt2->FindElement(h) == 1);
        }
        for (auto h : Bad) {
            assert(bt2->FindElement(h) == 0);
        }
    }

    void Merger() {
        vector<int> FT1 = {11, 14, 16, 13, 19, 32};
        vector<int> FT2 = {4, 7, 2, 9, 1, 3, 13};
        BinaryTree<int> bt1;
        BinaryTree<int> bt2;
        for (auto h : FT1) {
            bt1.add_node(h);
        }
        for (auto h : FT2) {
            bt2.add_node(h);
        }
        auto tree = bt1.Merger(&bt2);
        for (auto h : FT1) {
            assert(tree->FindElement(h) == 1);
        }
        for (auto h : FT2) {
            assert(tree->FindElement(h) == 1);
        }
    }

    void IsSubTrea() {
        BinaryTree<int> T1("|7 ||6 ||4 ||5 || 9|");
        BinaryTree<int> T2("|6 ||4 ||5 |");
        BinaryTree<int> T3("|6 ||4 ||5 ||9 |");
        assert(T1.isSubtree(&T2) == 1);
        assert(T1.isSubtree(&T3) == 0);
    }

    void UnderTree() {
        BinaryTree<int> T1("|7 ||6 ||4 ||5 || 9|");
        auto tree = T1.UnderTree(6);;
        assert(T1.isSubtree(tree) == 1);
    }

    void FindElementByWay() {
        BinaryTree<int> T1("|7 ||6 ||4 ||5 || 9|");
        assert(*(T1.FindElementByWay("LLR")) == 5);
        assert(*(T1.FindElementByWay("LL")) == 4);
        assert(T1.FindElementByWay("LLLLLR") == NULL);
    }

    void FindElementByWayFromPeak() {
        BinaryTree<int> T1("|8 ||7 ||6 ||4 ||5 || 9|");
        assert(*(T1.FindElementByWayFromPeak(7, "LLR")) == 5);
        assert(*(T1.FindElementByWayFromPeak(7, "LL")) == 4);
        assert(T1.FindElementByWayFromPeak(7, "LLLLLR") == NULL);
    }

    void Bypass_string() {
        auto tree1 = new BinaryTree<int>();
        tree1->add_node(1);
        tree1->add_node(2);
        tree1->add_node(5);
        tree1->add_node(7);
        tree1->add_node(7);
        tree1->add_node(3);
        tree1->add_node(9);
        tree1->add_node(19);
        tree1->add_node(14);
        tree1->add_node(15);
        assert(tree1->Bypass_string("LNR") == "|1 ||2 ||3 ||5 ||7 ||9 ||14 ||15 ||19 |");
        assert(tree1->Bypass_string("LRN") == "|3 ||15 ||14 ||19 ||9 ||7 ||5 ||2 ||1 |");
        assert(tree1->Bypass_string("NRL") == "|1 ||2 ||5 ||7 ||9 ||19 ||14 ||15 ||3 |");
        assert(tree1->Bypass_string("NLR") == "|1 ||2 ||5 ||3 ||7 ||9 ||19 ||14 ||15 |");
        assert(tree1->Bypass_string("RLN") == "|15 ||14 ||19 ||9 ||7 ||3 ||5 ||2 ||1 |");
        assert(tree1->Bypass_string("RNL") == "|19 ||15 ||14 ||9 ||7 ||5 ||3 ||2 ||1 |");
    }

    void LNR_Fir_String() {
        auto tree1 = new BinaryTree<int>();
        tree1->add_node(1);
        tree1->add_node(2);
        tree1->add_node(5);
        tree1->add_node(7);
        tree1->add_node(7);
        tree1->add_node(3);
        tree1->add_node(9);
        tree1->add_node(19);
        tree1->add_node(14);
        tree1->add_node(15);
        tree1->FirmwareTree();
        assert(tree1->LNR_Fir_String() == "|1 ||2 ||3 ||5 ||7 ||9 ||14 ||15 ||19 |");
    }

    void Map() {
        auto tree1 = new BinaryTree<int>();
        tree1->add_node(1);
        tree1->add_node(2);
        tree1->add_node(5);
        tree1->add_node(7);
        tree1->add_node(7);
        tree1->add_node(3);
        tree1->add_node(9);
        tree1->add_node(19);
        tree1->add_node(14);
        tree1->add_node(15);
        tree1->Map(f2);
        assert(tree1->Bypass_string("LNR") == "|2 ||4 ||6 ||10 ||14 ||18 ||28 ||30 ||38 |");
    }

    void Balancing() {
        BinaryTree<int> tree("|1 ||2 ||3 ||4 ||5 ||6 ||7 |");
        BinaryTree<int> tree2("|7 ||6 ||5 ||4 ||3 ||2 ||1 |");
        assert(tree.Bypass_string("NLR") == "|1 ||2 ||3 ||4 ||5 ||6 ||7 |");
        tree.Balancing();
        assert(tree.Bypass_string("NLR") == "|4 ||2 ||1 ||3 ||6 ||5 ||7 |");

        assert(tree2.Bypass_string("NLR") == "|7 ||6 ||5 ||4 ||3 ||2 ||1 |");
        tree2.Balancing();
        assert(tree.Bypass_string("NLR") == "|4 ||2 ||1 ||3 ||6 ||5 ||7 |");
    }

    void DeleteElement() {
        BinaryTree<int> tree("|1 ||3 ||6 ||8 ||2 ||9|");
        tree.DeleteElement(3);
        assert(tree.Bypass_string("LNR") == "|1 ||2 ||6 ||8 ||9 |");
        BinaryTree<int> tree2("|1 ||3 ||6 ||8 ||2 ||9|");
        tree2.DeleteElement(1);
        assert(tree2.Bypass_string("LNR") == "|2 ||3 ||6 ||8 ||9 |");
        BinaryTree<int> tree3("|1 ||3 ||6 ||8 ||2 ||9|");
        tree3.DeleteElement(8);
        assert(tree3.Bypass_string("LNR") == "|1 ||2 ||3 ||6 ||9 |");
    }

public:
    void RUN(){
        FindElement();
        AddNode();
        Where();
        Merger();
        IsSubTrea();
        FindElementByWay();
        FindElementByWayFromPeak();
        Bypass_string();
        LNR_Fir_String();
        Map();
        Balancing();
        DeleteElement();
    }

};


#endif //LAB3_TEST_H
