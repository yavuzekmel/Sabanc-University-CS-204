

#include <stdio.h>
#include <iostream>
#include "sparse_matrix_2d_linked_list.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


row_node* read_matrix(const string& filename, int& num_rows, int& num_columns)  {
    
    // Open File
    
    ifstream inputMatrix;
    
    inputMatrix.open(filename.c_str());
    string line;
    int matrixOneRowNumber, matrixOneColumnNumber;
    int lineCounter= 0, columnCounter = 0;
    int inputCounter= 0;
    row_node *head;
    head = new row_node;
    int mainCounter = 0;
    bool bug = false;
    
    
    // tempIntroCol: My first column of designed matrix. It does not store values. They are row node of my each row.
    // I will read text line by line
    // inputCounter: When inputCounter == 0 then I understand that it is the first element of the text and I store it to num_rows.
    //               When inputCounter == 1 then I undertant that it is the second element of the text and I store it to column_rows.
    //               When inputCounter == 2 then I start to create new row node but when it is equal to 2 then ı know that the prev node == head
    //               When inputCounter  >2   then I do not have to increment it because ı already know that there is no more head.
    // tempIntroCol: It is temprorary row_node. It helps me to connect prev row_node with new initialized one.
    
    row_node * tempIntroCol;
    while(!inputMatrix.eof()) {
        if (bug == true) {
            break;
        }
        int matrixColumnCounter = 0;
        getline(inputMatrix, line);
        stringstream ss(line);
        int num;
        cell_node * firstColElement;
        cell_node * prev;
        row_node  *introductionCol;
        cell_node * nextColElement;
        
        
        
        if (inputCounter >2) {
            
            introductionCol = new row_node();
            tempIntroCol -> down = introductionCol;
            columnCounter = 0;
            tempIntroCol = introductionCol;
            lineCounter += 1;
            
        }
        if (inputCounter == 2) {
            introductionCol = new row_node();
            head -> down = introductionCol ;
            tempIntroCol = introductionCol;
            lineCounter += 1;
            columnCounter = 0;
            inputCounter +=1;
            
        }
        
      // firstColElement: It is always my first initialized row_node. The importance of first row_node, it's left must be null always.
      // matrixColumnCounter: It helps to understand whether the next initialized node should be firstColElement or not.
      // prev: It is always stores my prev node. After creating new node, thanks to prev I can point to new node from previous node.
      // nextColElement: It inditaces the new initalized row node. It never works for the first initialized row_node.
        
        while (ss >> num) {

            if (inputCounter == 0) {
                matrixOneRowNumber  = num;
                inputCounter +=1;
            }
            
            else if (inputCounter == 1) {
                matrixOneColumnNumber = num;
                inputCounter +=1;
            }
        
            else {
        
                if (num == 0){
                    columnCounter  += 1;
                }
        
                else {
                        
                    if (matrixColumnCounter == 0) {
                        
                        firstColElement = new cell_node;
                        firstColElement-> column = columnCounter;
                        firstColElement -> value = num;
                        columnCounter += 1;
                        introductionCol-> cell = firstColElement;
                        matrixColumnCounter +=1;
                        prev = firstColElement;

                    }
                    
                    else {
                        
                        cell_node * nextColElement;
                        nextColElement = new cell_node;
                        prev -> right  = nextColElement;
                        nextColElement -> left = prev;
                        nextColElement -> column = columnCounter;
                        columnCounter +=1;
                        nextColElement -> value = num;
                        prev = nextColElement;
                    }
                    
                }
            }
            
        }
        
        
        if (mainCounter ==  matrixOneRowNumber) {
            
            bug = true;
        }
        mainCounter +=1;
            
//        if (matrixColumnCounter == 0) {
//
//            firstColElement = new cell_node;
//            prev = firstColElement;
            
    }

    num_rows = matrixOneRowNumber ;
    num_columns = matrixOneColumnNumber ;
    
    row_node *lastDeletion;
    lastDeletion = head;
    head = head-> down;
    
    delete lastDeletion;

    return head;
}
    


void print_matrix(row_node* head, int num_rows, int num_columns) {
    
    
    row_node *printStart = head;
    cell_node* printValue;
    
    // printStart = Indicates the first column of the linked list which includes row_node.
    // printValue = Indicates the specific cell node of specific row. It will visit all cell_nodes.
    
    while (printStart) {
        
        int printZero = 0;
        printValue = printStart -> cell;
        
        bool  fullZeroConditon = true; // The role of this bool element is understand whether that row include only 0 element or not.
        
        while (printValue) {
            
            fullZeroConditon = false;
            if (printZero == printValue -> column) {
                
                cout << printValue -> value << " ";
                printValue = printValue -> right;  // Shifting cell node.
                printZero +=1;
            }  else {
    
                cout << "0" << " " ;
                printZero +=1;  // Counting 0's that I have printed.
            }
        
        }
        
        if ( fullZeroConditon == true) { // If printValue is Nullptr than that specific row do not have cell node. So I need to print only 0.
            
            for (int ı=0 ; ı < num_columns; ı++) {
                cout << "0 ";
            }
        }
        
        else if (printZero < num_columns) { // This condition help me to  print 0's between last element of row and last not zero element.
                                            // If the last element of row not 0 then it wont work.
            
            int q = num_columns - printZero;
            
            while (q > 0) {
                cout << "0 ";
                q-- ;
                
            }
            
        }
        
        cout << endl;
        printStart = printStart -> down; // Shifting row.
    }
    cout << endl;
}




row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns) {
    
    
    
    row_node    *sumIntCol;     // First column of Summation matrix linked list that only includes row nodes.
    sumIntCol = new row_node;
    row_node  *prevSumIntCol;   // Helps me to connect previous row node to new one with storing previous row node.
    
    cell_node  *sumColValue;    // Indicates the cell node.
    
    cell_node  *prevSumColValue; // Indicates the previous cell node. I use them while connecting cell nodes.
    
    
    row_node *sumMatrix;        // Indicates the head of Summation Matrix linked list.
    cell_node *leftColValue;    // Indicates the cell node of first matrix that used for summation.
    cell_node *rightColValue;   // Indicates the cell node of second matrix that used for summation.
    
    int helper = 0;             // If helper == 0 then I understand that I should not connect prev node because it is head.
    
    
    
    
    while (left) {              // First row node of first summation matrix. The value of rows are same. It will shift to next row node every time.
        
        bool check = false;     // It helps me to understand whether is there any cell node in specific row in any two matrix that I will sum.
        bool secondCheck = false;    // It helps to understand whether the cell node that I have already visit is last element of that row or not.
        
        leftColValue = nullptr;     // Defensive coding.
        rightColValue = nullptr;    // Defensive coding.
      
        
        if (helper > 0) {
            
            if (helper ==1 ) {              // If helper >0 then I should connect prev  row node  with new one.
                
                sumMatrix = sumIntCol;
            }
            prevSumIntCol = sumIntCol;
            sumIntCol =  new row_node;
            prevSumIntCol -> down = sumIntCol;
            
        }
        
        helper += 1;
        
        
        if (left -> cell) {

            leftColValue = left -> cell;
            check = true;
        }
        
        
        
        if (right -> cell) {
            
            rightColValue = right-> cell;
            check = true;
        }
        
        if (check == true) {
            
            sumColValue = new cell_node;
            sumColValue -> value = 0;
            sumColValue -> column = 0;
            sumIntCol -> cell= sumColValue;
        }
        
        for (int t=0 ; t < num_columns; t++) {
            
            if (check == true) {
                
                secondCheck = false ;
                
                if (leftColValue  && leftColValue -> column == t) {
                    
                    sumColValue -> column = t;
                    sumColValue -> value += leftColValue->value;
                    
                    if (leftColValue -> right) {
                        leftColValue = leftColValue -> right;
                        secondCheck = true;
                    }
                }
                
                if (rightColValue && rightColValue -> column == t ) {
                    
                    sumColValue -> column = t;
                    sumColValue -> value += rightColValue-> value;
                    
                    if (rightColValue -> right) {
                        rightColValue = rightColValue-> right;
                        secondCheck = true;
                    }
                    
                }
                
                if (sumColValue ->value == 0) {     // If the value of the Value still zero than I should not create cell node.
                    
                    sumIntCol -> cell = nullptr;
                    break;
                }
                
                if ( secondCheck == true) {         // If secondCheck is true then I know that I will read other cell node it that row.
                    
                    prevSumColValue = sumColValue;
                    sumColValue = new cell_node;
                    sumColValue -> value = 0;
                    sumColValue -> column = 0;
                    
                    prevSumColValue -> right = sumColValue;
                    sumColValue -> left = prevSumColValue;
                   
                }
            }
           
        }
        left = left->down;
        right = right ->down;
        
    }
    
    cout << "Burası";
    
    return sumMatrix;
}


// Principle of function:
// In that function I am trying to visit each column one by one. For that purpose, I visit each row while holding my column same. If I found any cell node in that column then I create a cell node in my transposed matrix and fill that cell node with these variables.
row_node* transpose(row_node* head, int num_rows, int num_columns) {

    row_node *transpose;            // It indicates the head of transposed matrix.

    row_node  *introductionColTranspose;        // It indicates the first Column of tranpose matrix that only includes row nodes.
    introductionColTranspose = new row_node;
    transpose = introductionColTranspose;
    

    row_node *prevIntroductionColTranspose;    // It indicates the prev row node.


    row_node  *firstRowOfHead;                 // It indicates the firstColumn of linked list that I should tranpose.
    firstRowOfHead = head;

    cell_node  *valueTranpose;                  // The cell node of Transposed matrix.


    cell_node *prevValueTranspose;              // The previous cell node of Transposed matrix.



    row_node *introductionColHead;              // It helps me to visit each row node of matrix for transpose.

    cell_node *valueDetecter;                   // Indicates the value of the cell node of the matrix that I should transpose.

    int counterForNewTranposeRow = 0;           // It helps me to understand that I have created enough row or not.
    int columnDetecter = 0;                     // It helps me to decide which column should I select for my new cell node in transposed matrix.

    for (int n= 0; n < num_columns ; n++) {

        columnDetecter = 0;
        int leakCounter = 0;                    // It helps to understand should I connect prev cell node with new one or
                                                //    it is the first cell node of tranposed matrix.

        introductionColHead = firstRowOfHead;

        for ( int m = 0 ; m < num_rows; m ++) {

            if (introductionColHead -> cell) {

                valueDetecter = introductionColHead -> cell;

                while (valueDetecter){

                    if (valueDetecter -> column == n) {

                        valueTranpose = new  cell_node;
                        valueTranpose -> column = 0;
                        valueTranpose -> value = 0;
                        valueTranpose -> column = columnDetecter;
                        valueTranpose -> value = valueDetecter -> value;

                        if (leakCounter > 0) {

                            prevValueTranspose -> right = valueTranpose;
                            valueTranpose -> left = prevValueTranspose;
                        }
                        else {

                            introductionColTranspose -> cell = valueTranpose;

                        }

                        prevValueTranspose = valueTranpose;
                        leakCounter += 1;
                    }
                    valueDetecter = valueDetecter -> right;
                }

            }
            introductionColHead = introductionColHead -> down ;
            columnDetecter += 1;

        }

    
        if ( counterForNewTranposeRow == (num_columns -1) ) {
            
            
            continue;
        }
        else {
            prevIntroductionColTranspose = introductionColTranspose;
            introductionColTranspose = new row_node;
            prevIntroductionColTranspose -> down = introductionColTranspose;
            prevIntroductionColTranspose = introductionColTranspose;
        }
        counterForNewTranposeRow += 1;
    }
    return transpose;

}

// Principle Of Function:
// I already have an tranpose function. I used that function for deciding whether that matrix symmetic or not. First I create the transposed matrix of that matrix. If they are same then I decide that matrix is symmetric. Else, not.
bool is_symmetric(row_node* head, int num_rows, int num_columns) {
    
    row_node *transposeOfHead;
    transposeOfHead = transpose(head , num_rows, num_columns) ;
    
    cell_node *transposeOfHeadCell;
    cell_node *headCell;

    
    while (transposeOfHead) {
        
        transposeOfHeadCell = transposeOfHead -> cell;
        headCell = head -> cell;
        
        while (headCell) {
            
            if ((headCell-> value) != (transposeOfHeadCell-> value)) {
                return false;
            }
            
            headCell = headCell -> right;
            transposeOfHeadCell = transposeOfHeadCell -> right;
            
        }
        
        transposeOfHead = transposeOfHead -> down;
        head = head -> down;
        
    }
    
    
    
    return true;
}




void delete_matrix(row_node* head) {
    
    row_node* row_ptr = head, *row_temp;
    cell_node* cell_ptr, *temp;
    
    while(row_ptr != nullptr){
        
        cell_ptr = row_ptr->cell;
        
        if (cell_ptr == nullptr){
            row_temp = row_ptr;
            row_ptr = row_ptr->down;
            delete row_temp;
            break;
        }
        
 
        while (cell_ptr->right != nullptr){
            cell_ptr = cell_ptr->right;
        }
        
        while(cell_ptr != row_ptr->cell){ // en soldaki cell_node'a gelene kadar sola git
            temp = cell_ptr;
            cell_ptr = cell_ptr->left;
            delete temp;
        }
        delete cell_ptr;
        
       
        row_temp = row_ptr;
        

        row_ptr = row_ptr->down;
        
     
        delete row_temp;
    }
    
    row_node *ptr = head;
 
    ptr->cell = NULL;
    ptr->down = NULL;
    ptr = NULL;
}






































