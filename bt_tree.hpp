#pragma once
#include <iostream>
#include <string>
template <class T>
struct bt_tree_node {
    T val;
    bt_tree_node<T>* left = nullptr;
    bt_tree_node<T>* right = nullptr;
    bt_tree_node() {}
    virtual ~bt_tree_node() {}
    bt_tree_node<T>& operator = (const bt_tree_node<T>& node) {
        val = node.val;
    }
    bool operator == (const bt_tree_node<T>& node) {
        return val == node.val;
    }
    virtual bool is_null_node() = 0;
};

struct bt_tree_node_int : bt_tree_node<int> {
    const int NULL_VAL = -999;
    bt_tree_node_int(int v = 0) {
        val = v;
    }
    virtual bool is_null_node() override {
        return NULL_VAL == val;
    }
    friend std::istream& operator >> (std::istream& in, bt_tree_node_int& node) {
        in >> node.val;
        return in;
    }
    friend std::ostream& operator << (std::ostream& os, const bt_tree_node_int& node) {
        os << node.val << " ";
        return os;
    }
};

struct person_type {
    int id = 0;
    std::string name;
    int age = 0;
    person_type() {}
    person_type(int _id, const std::string& _name, int _age) {
        id = _id;
        name = _name;
        age = _age;
    }
    person_type(const person_type& person) {
        id = person.id;
        name = person.name;
        age = person.age;
    }
    inline person_type& operator = (const person_type& person) {
        id = person.id;
        name = person.name;
        age = person.age;
        return *this;
    }
    inline bool operator == (const person_type& person) {
        return (id == person.id) && (name == person.name) && (age == person.age);
    }
};

struct bt_tree_node_person : bt_tree_node<person_type> {
    bt_tree_node_person() {}
    bt_tree_node_person(int _id, const std::string& _name, int _age) {
        val = person_type(_id, _name, _age);
    }
    bt_tree_node_person(const person_type& person) {
        val = person;
    }
    virtual bool is_null_node() override {
        return 0 == val.age;
    }
    friend std::istream& operator >> (std::istream& in, bt_tree_node_person& node) {
        in >> node.val.id >> node.val.name >> node.val.age;
        return in;
    }
    friend std::ostream& operator << (std::ostream& os, const bt_tree_node_person& node) {
        os << node.val.id << " " << node.val.name << " " << node.val.age << std::endl;
        return os;
    }
};


template <class NodeType>
class bt_tree {
private:
    NodeType* bt_root_ = nullptr;
private:
    const char SEP_CHAR = ';';
    const char NULL_CHAR = '#';
private:
    void create(NodeType* &root) {
        NodeType node;
        std::cin >> node;
        if (node.is_null_node()) {
            return;
        }
        if (nullptr == root) {
            root = new NodeType(node.val);
            create((NodeType*&)(root->left));
            create((NodeType*&)(root->right));
        }
    }
    void show(NodeType* root) const {
        if (nullptr == root) {
            return;
        }
        std::cout << *root;
        show((NodeType*)(root->left));
        show((NodeType*)(root->right));
    }
    void destroy(NodeType* &root) {
        if (root) {
            destroy((NodeType*&)(root->left));
            destroy((NodeType*&)(root->right));
            delete root;
            root = nullptr;
        }
    }
public:
    bool init() {
        create(bt_root_);
        if (nullptr == bt_root_) {
            return false;
        }
        return true;
    }
    void show() const {
        show(bt_root_);
    }
    virtual ~bt_tree() {
        if (bt_root_) {
            destroy(bt_root_);
        }
    }
};