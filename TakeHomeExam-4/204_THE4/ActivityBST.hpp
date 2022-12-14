//
//  Class_Declaration.hpp
//  204_THE4
//
//  Created by Ekmel Yavuz on 2.12.2022.
//

#ifndef ActivityBST_hpp
#define ActivityBST_hpp

#include <stdio.h>
#include <string>
using namespace std;


struct tree_node {
   int time;
   string activity;
   tree_node *right;
   tree_node *left;
   tree_node *parent;
   tree_node(int t, const string &a) : time(t), activity(a),
                                       right(nullptr), left(nullptr),
                                        parent(nullptr) {}
};
  

class ActivityBST{

    friend void preOrderRecursion(tree_node *clone, tree_node *ptr);
    friend void inOrderRecursionPrint(tree_node * tree) ;
    friend ActivityBST operator + (const ActivityBST &lhs, const ActivityBST & rhs);
    friend ostream & operator << (ostream & os, const ActivityBST tree);
    
    
public:
  
    ActivityBST();                                                  // Constructor
    ActivityBST (const ActivityBST & );                            // Copy Constuctor
    tree_node *  createClone() const ;                            // Deep Copy Element
    ~ActivityBST();                                              // Destructor
    void add(int time, string activity);                        // New Activity Addition
    void deleteTree(tree_node *willbeDeleted);                 // Delete tree
    void print(ActivityBST *tree);                            // Print tree
    ActivityBST & operator = (const ActivityBST & rhs);      // Overloaded = operator
    const ActivityBST & operator += (const ActivityBST & rhs);
    
    
private:
    
    tree_node *root;
    
};
    
ostream & operator << (ostream & os, const ActivityBST tree);
ActivityBST operator + (const ActivityBST &lhs, const ActivityBST & rhs);
void add_activity_internal(tree_node *&root, int time,  string activity);
inline bool legal_time(int time);
inline string number_to_time(int number);
inline string fill_with_zeros(int num_zeros, const string &input);


#endif /* ActivityBST_hpp */
