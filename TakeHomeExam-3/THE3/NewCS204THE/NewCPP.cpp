#include "activity_bst.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>


string fill_with_zeros(int num_zeros, const string& input){
   int zeros_to_add = num_zeros - input.length();
   if (zeros_to_add < 0) zeros_to_add = 0;
   return string(zeros_to_add, '0') + input;
}
string number_to_time(int number){
   return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,to_string(number%100));
}



bool time_checker(int time) {    // This function indicates whether the time input is valid or not.
    
    bool verified = true;
    
    if (time < 0) {
        
        verified = false;
        return verified;
    }
    if ( time > 2359) {
        
        verified = false;
        return verified;
    }
    
    int minuteChecker = time % 100;
    
    if (minuteChecker > 59) {
        
        verified = false;
        return verified;
    }
    
    return verified;
}



void add_activity(tree_node *&root, int time, const string &activity) {
 
    bool startPoint;
    
    startPoint = time_checker(time);
    
    if (startPoint == false) { // The int value is not valid so I should not add anything into my tree.
        
        cout << "ERROR! Could not add activity '" << activity << "' due to illegal time value" << endl;
    }
    
    else {
    
        tree_node  *traverserNode = nullptr;            // First I need to start with empty tree and I need to initialize two different pointers.
        tree_node  *prevtraverseNode = nullptr;         // First pointer helps me to traverse in tree and help me to understand which location should pick for my new activity.
        if (root == nullptr) {                          // Second pointer helps me to connect childs with their parents.
    
        
            root = new tree_node(time,activity);        // This if for the first activity of my tree.
        
        }
        else {
            traverserNode = root;
            
            
            while (traverserNode) {                     // I need to traverse until find my location.
                
                if (time < traverserNode->time) {
                    
                    if(traverserNode -> left) {
                    
                        traverserNode = traverserNode -> left;
                    
                    }   else {                          // When I could not find any node in that location I understand that I can put my activty here.
                        
                        prevtraverseNode = traverserNode;
                        traverserNode -> left = new tree_node(time, activity);
                        traverserNode = traverserNode -> left;
                        traverserNode -> parent = prevtraverseNode;
                        break;
                        
                    }
                }
                
                if (time > traverserNode -> time) {
                    
                    if (traverserNode ->right) {
                        
                        traverserNode = traverserNode -> right;
                        
                    }  else  {                          // When I could not find any node in that location I understand that I can put my activty here.
                        
                        prevtraverseNode = traverserNode;
                        traverserNode -> right = new tree_node(time,activity);
                        traverserNode = traverserNode -> right;
                        traverserNode -> parent = prevtraverseNode;
                        break;
                        
                    }
                }
            }
        }
        cout << "Added activity '" << activity << "' at " << number_to_time(time) << endl;
    }
}


void print_all_activities(tree_node *root) {            // Recursion function that traverse all nodes from min time value to max time value and print them in order.
    
    tree_node  *traverserNode = root;
    //tree_node  *prevtraverseNode = root;

    if (traverserNode) {
        
        print_all_activities(traverserNode ->left);
        cout << "[" << number_to_time(traverserNode ->time) << "] - " << traverserNode-> activity <<   endl;
        print_all_activities(traverserNode ->right);
        
    }
}



void print_activity(tree_node *root, int time) {            // I need to find the specific time range to understand which activity in that time range.
    
    tree_node  *traverserNode = root;
    
    bool notNull = true;
    if (root == nullptr) {                                  // If the tree is empty than I understand that all day is free.
        
        cout << "Time: "<< number_to_time(time) << ", Activity: Free" << endl;
        notNull = false;
    }
    while(traverserNode && notNull == true) {
        
        if ( time == traverserNode->time) {  // They are equal , I found an activity that starts on that specific time value.
            
            cout << "Time:" <<  number_to_time(time) << ", " << traverserNode-> activity << endl;
            break;
        }
        
        else if(time < traverserNode-> time){  // time < traverserNode -> time
            
            if (traverserNode-> left) {
                
                traverserNode = traverserNode-> left;
                
            }
            
            else {
                cout << "Time: " << number_to_time(time) << ",  Activity: free" << endl;
                break;
            }
        }
        
        else {  // time > traversNode -> time
            
            if (traverserNode -> right) {
                
                if(traverserNode->right->time > time) {             // I found a range that includes my specific time value and I found that activity in that range
                    cout << "Time: " << number_to_time(time) << ", Activity: " << traverserNode-> activity << endl;
                    break;
                }
                else {
                    traverserNode = traverserNode-> right;
                    
                }
            }
            
            else {
                cout << "Time: " << number_to_time(time) << ", Activity: " << traverserNode-> activity << endl;
                break;
            }
        }
    }
}


void print_activity_and_duration(tree_node *root, int time) {
    
    tree_node  *traverserNode = root;
   
    tree_node *parentFinder = traverserNode;
    bool parentFinderDetection = false;
    bool isFree = true;             // If there is no activity than I can state that all day is free.
    
    bool startPoint;
    
    startPoint = time_checker(time);
    
    if (startPoint == false) { // The int value is not valid so I should not add anything into my tree.
        
        cout << "ERROR! Could not find the activity due to illegal time value" << endl;
    }
    
    else {
        while(traverserNode) {
            
            if ( time == traverserNode->time) {  // They are equal ,  I found  activity and it starts in my specific time value.
                
                if(traverserNode->right) {       // This if and else part is  understand the time range of that activity
                    
                    cout << "Time period: [" <<  number_to_time(traverserNode->time) << " - " << number_to_time(traverserNode->right->time) << "]: " << traverserNode->activity << endl;
                    isFree = false;
                    break;
                        
                }
                else {
                    
                    parentFinder = traverserNode;
                    while (parentFinder && parentFinderDetection == false) {
                        
                        if (parentFinder->parent){
                            if (parentFinder->parent->time > time) {
                               
                                cout << "Time period: [" <<  number_to_time(traverserNode->time) << " - " << number_to_time(parentFinder->parent->time) << "]: " << traverserNode->activity << endl;
                                isFree = false;
                                parentFinderDetection = true;
                                                       
                            }
                        }
                        parentFinder = parentFinder->parent;
                        
                    }
                                            
                    if (parentFinderDetection == false) {
                        
                        cout << "Time period: [" <<  number_to_time(traverserNode->time) << " - 00:00]: " << traverserNode->activity << endl;
                        isFree = false;
                        break;
                    }
                        
                    break;
                }
            }
            
            
            else if(time < traverserNode-> time){  // time < traverserNode -> time
                
                if (traverserNode-> left) {
                    
                    traverserNode = traverserNode-> left;
                    
                }
                
                else {
                    cout << "Time peripd: [00:00 - " << number_to_time(traverserNode->time) << "]: free" << endl;
                    isFree = false;
                    break;
                }
            }
            
            else {  // time > traversNode -> time
                
                if (traverserNode -> right) {           // This if and else part is understand the time range of that activityt.
                    
                    if(traverserNode->right->time > time) {
                        cout << "Time: [" << number_to_time(traverserNode->time) <<" - "<<  number_to_time(traverserNode->right->time)<< "]:" << traverserNode-> activity << endl;
                        isFree = false;
                        break;
                    }
                    else {
                        traverserNode = traverserNode-> right;
                        
                    }
                }
                
                else {
                    parentFinder = traverserNode;
                    
                    while (parentFinder && parentFinderDetection == false) {
                        
                        if (parentFinder->parent){
                            if (parentFinder->parent->time > time) {
                            
                                cout << "Time period: [" <<  number_to_time(traverserNode->time) << " - " << number_to_time(parentFinder->parent->time) << "]: " << traverserNode->activity << endl;
                                isFree = false;
                                parentFinderDetection = true;
                            }
                        }
                        parentFinder = parentFinder->parent;
                        
                    }
                    if (parentFinderDetection == false) {
                        
                        cout << "Time period: [" <<  number_to_time(traverserNode->time) << " - 00:00]: " << traverserNode->activity << endl;
                        isFree = false;
                        break;
                    
                    }
                    break;
                }
            }
        }
        if (isFree == true) {       // All day is free.
        
            cout << "Time period: [00:00 - 00:00]: free" << endl;
        }
    }
}


void print_single_activity(tree_node *root, const string &activity) {     // Recursion function that visit all nodes and if activity is same with my stated activity then it prints the time range.
    
    tree_node *findSameString = root;
       
    if (findSameString) {
        
        print_single_activity(findSameString->left, activity);
        if (findSameString -> activity == activity){
            print_activity_and_duration(root, findSameString->time);
            
        }
        print_single_activity(findSameString->right, activity);
    
    }
}


void delete_tree(tree_node *root) {         // display post order and delete nodes one by one.
    
    
    tree_node *deletionPointer ;
    deletionPointer = root;
    
    if (deletionPointer) {
        
        delete_tree(deletionPointer -> left);
        delete_tree(deletionPointer -> right);
        
        delete deletionPointer;
    }
        

}

