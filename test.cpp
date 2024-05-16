#include "bt_tree.hpp"
int main() {
    std::string str;
    bt_tree<bt_tree_node_int> bst_int;
    if (true == bst_int.init()) {
        std::cout << "btree_int init ok!" << std::endl;
        bst_int.show();
        std::cout << std::endl;
        bst_int.serialize(str);
        std::cout << "btree_int serialize:" << str << std::endl;
        bt_tree_node_int* root = bst_int.deserialize(str);
        if (root) {
            bt_tree<bt_tree_node_int> bst_int;
            bst_int.init(root);
            bst_int.show();
            std::cout << std::endl;
        }
    }
    bt_tree<bt_tree_node_person> bst_person;
    if (true == bst_person.init()) {
        std::cout << "btree_int init ok!" << std::endl;
        bst_person.show();
        std::cout << std::endl;
        bst_person.serialize(str);
        std::cout << "bst_person serialize:" << str << std::endl;
        bt_tree_node_person* root = bst_person.deserialize(str);
        if (root) {
            bt_tree<bt_tree_node_person> bst_person;
            bst_person.init(root);
            bst_person.show();
            std::cout << std::endl;
        }
    }
    
    return 0;
}