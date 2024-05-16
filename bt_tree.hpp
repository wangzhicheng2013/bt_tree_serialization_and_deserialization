#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
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
    virtual void serialize(std::string& str) = 0;
    virtual void deserialize(const std::string& str) = 0;
};

struct bt_tree_node_int : bt_tree_node<int> {
    const int NULL_VAL = -999;
    bt_tree_node_int(int v = 0) {
        val = v;
    }
    virtual bool is_null_node() override {
        return NULL_VAL == val;
    }
    virtual void serialize(std::string& str) override {
        str += std::to_string(val);
    }
    virtual void deserialize(const std::string& str) override {
        val = atoi(str.c_str());
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
    inline void serialize(std::string& str) {
        str += std::to_string(id);
        str += " ";
        str += name;
        str += " ";
        str += std::to_string(age);
    }
    void deserialize(const std::string& str) {
        char *p = nullptr;
        static const char* delim = " ";
        char *ptr = strtok_r((char *)(str.c_str()), delim, &p);
        int index = 0;
        while (ptr) {
            switch (index)
            {
            case 0:
                id = atoi(ptr);
                break;
            case 1:
                name = ptr;
                break;
            case 2:
                age = atoi(ptr);
                break;
            default:
                break;
            }
            ++index;
            ptr = strtok_r(nullptr, delim, &p);
        }
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
    virtual void serialize(std::string& str) override {
        val.serialize(str);
    }
    virtual void deserialize(const std::string& str) override {
        val.deserialize(str);
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
    const char* const SEP_CHAR = ";";
    const char* const NULL_CHAR = "#";
private:
    int cur_pos_ = -1;
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
    void serialize(NodeType* root, std::string& str) {
        if (root) {
            root->serialize(str);
        }
        else {
            str += NULL_CHAR;
        }
        str += SEP_CHAR;
        if (root) {
            serialize((NodeType*&)(root->left), str);
            serialize((NodeType*&)(root->right), str);
        }
    }
    void fetch_vals(const std::string& str, std::vector<std::string>&vals) {
        vals.clear();
        char *p = nullptr;
        char *ptr = strtok_r((char *)(str.c_str()), SEP_CHAR, &p);
        while (ptr) {
            vals.emplace_back(ptr);
            ptr = strtok_r(nullptr, SEP_CHAR, &p);
        }
    }
    void deserialize(NodeType*& root, const std::vector<std::string>&vals) {
        ++cur_pos_;
        if (vals[cur_pos_].compare(NULL_CHAR)) {
            root = new NodeType;
            root->deserialize(vals[cur_pos_]);
            deserialize((NodeType*&)(root->left), vals);
            deserialize((NodeType*&)(root->right), vals);
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
    void init(NodeType* root) {
        bt_root_ = root;
    }
    void show() const {
        show(bt_root_);
    }
    void serialize(std::string& str) {
        str.clear();
        if (bt_root_) {
            serialize(bt_root_, str);
        }
    }
    NodeType* deserialize(const std::string& str) {
        NodeType* root = nullptr;
        if (str.empty()) {
            return nullptr;
        }
        std::vector<std::string>vals;
        fetch_vals(str, vals);
        deserialize(root, vals);
        return root;
    }
    virtual ~bt_tree() {
        if (bt_root_) {
            destroy(bt_root_);
        }
    }
};