//
//  Class_Declaration.cpp
//  204_THE4
//
//  Created by Ekmel Yavuz on 2.12.2022.
//

#include "ActivityBST.hpp"
#include <string>
#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////////////////
///Helper function to number_to_time.

inline string fill_with_zeros(int num_zeros, const string &input) {
    int zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// It helps to create true representation form of time values.

inline string number_to_time(int number) {
    if (number > 2359 || number < 0) return "ERROR";
    return fill_with_zeros(2, to_string(number / 100)) + ":" +
           fill_with_zeros(2, to_string(number % 100));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// It checkes whether the given time value is valid.

inline bool legal_time(int time) {
    if (time > 2359 || time < 0)
        return false;
    if (time % 100 > 59 || time / 100 > 23)
        return false;
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// While creating deep copy, this function works and helps to create same nodes one by one.

void add_activity_internal(tree_node *&root, int time,  string activity) {
    
    if (!legal_time(time)) {
            
        
    }
    else {
        if (root == nullptr) {
            root = new tree_node(time, activity);
        } else {
            tree_node *curr = root;
            tree_node *new_node;
            new_node = new tree_node(time, activity);
            bool added = false;
            while (!added) {
                if (curr->time == time){
                    curr->activity = activity;
                    added = true;
                    delete new_node;
                }
                else if (curr->time > time) {
                    if (curr->left == nullptr) {
                        new_node->parent = curr;
                        curr->left = new_node;
                        added = true;
                    } else {
                        curr = curr->left;
                    }
                } else if (curr->time < time) {
                    if (curr->right == nullptr) {
                        new_node->parent = curr;
                        curr->right = new_node;
                        added = true;
                    } else {
                        curr = curr->right;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default Constructor

ActivityBST::ActivityBST() {
    
    root = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Destructor

ActivityBST::~ActivityBST() {
    
    deleteTree(root);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function to destruct class

void ActivityBST::deleteTree(tree_node* willbeDeleted) {
    
        if (willbeDeleted == nullptr) return;
        // Delete the nodes in the left subtree
        deleteTree(willbeDeleted->left);
        // Delete the nodes in the right subtree
        deleteTree(willbeDeleted->right);
        // Delete `root`
        delete willbeDeleted;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// After root created with default constructor add function helps to create each  new node.
   
void ActivityBST::add(int time , string activity) {
    
    
    if (!legal_time(time)) {

    }
    else {
        if (root == nullptr) {
            root = new tree_node(time, activity);
        } else {
            tree_node *curr = root;
            tree_node *new_node;
            new_node = new tree_node(time, activity);
            bool added = false;
            while (!added) {
                if (curr->time == time){
                    curr->activity = activity;
                    added = true;
                    delete new_node;
                }
                else if (curr->time > time) {
                    if (curr->left == nullptr) {
                        new_node->parent = curr;
                        curr->left = new_node;
                        added = true;
                    } else {
                        curr = curr->left;
                    }
                } else if (curr->time < time) {
                    if (curr->right == nullptr) {
                        new_node->parent = curr;
                        curr->right = new_node;
                        added = true;
                    } else {
                        curr = curr->right;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function to copy constructor. It helps to traverse each node to create deep copy with preOrder strategy.

void preOrderRecursion(tree_node *&clone,  tree_node *&ptr) {
    
    if (ptr) {
        
        add_activity_internal(clone, ptr->time, ptr->activity);
        preOrderRecursion(clone, ptr->left);
        preOrderRecursion(clone, ptr->right);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/// It helps to print ActivityBST tree with traversing each node one by one with inOrder strategy.

void inOrderRecursionPrint(tree_node *ptr)  {
    
    if (ptr) {
        
        inOrderRecursionPrint(ptr->left);
        cout << "[" << number_to_time(ptr->time) << "] - " << ptr->activity << endl;
        inOrderRecursionPrint(ptr->right);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function to create deep copy.

tree_node * ActivityBST::createClone() const {
    
    
    if (root == nullptr) {
        return nullptr;
    }
    
    tree_node * ptr = root;
    tree_node * rootClone = nullptr;
    
    preOrderRecursion(rootClone, ptr);
    
    return rootClone;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copy Constructor which creates deep copy.

ActivityBST::ActivityBST(const ActivityBST & copy) {
    
    root = copy.createClone();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Overloaded = operator

ActivityBST & ActivityBST::operator = (const ActivityBST & rhs) {
    
    if (this != & rhs) {
    
        deleteTree(root);
        root = rhs.createClone();
    
    }
    return * this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Overloaded += operator.

const ActivityBST & ActivityBST::operator+=(const ActivityBST & rhs) {
    
    if (root == nullptr) {
        
        root = rhs.createClone();
    }
    
    else {
        tree_node *lhstraverser = root;
        tree_node *rhstraverser = rhs.root;
        
        preOrderRecursion(lhstraverser , rhstraverser);
    }
    
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Overloaded + operator.

ActivityBST operator + (const ActivityBST &lhs, const ActivityBST & rhs) {
    
    ActivityBST result(lhs);
    
    result += rhs;
    
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Overloaded os operator.

ostream & operator << (ostream & os, const ActivityBST tree) {
    
    tree_node * traverser = tree.root;
    
    inOrderRecursionPrint(traverser);
    
    return os;
}



