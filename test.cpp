#include "bt_tree.hpp"
int main() {
    bt_tree<bt_tree_node_int> bst_int;
    if (true == bst_int.init()) {
        std::cout << "btree_int init ok!" << std::endl;
        bst_int.show();
    }
    bt_tree<bt_tree_node_person> bst_person;
    if (true == bst_person.init()) {
        std::cout << "btree_int init ok!" << std::endl;
        bst_person.show();
    }
    
    return 0;
}