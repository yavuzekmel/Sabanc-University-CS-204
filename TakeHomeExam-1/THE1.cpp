#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// loc: [ [0,2] [1,0] [1,1] [2,1] [2,2] [3,2] [4,0] ]
// answers: [ [4] , [2, 4], [9, 8], [2], [8] ]

void combineVectors(vector<vector<int> > & loc, vector<vector<int> > & answers, ofstream & output){
    int counter = 0;
    for (int i = 0; i < answers.size(); i++){
        for (int j = 0; j < answers[i].size(); j++){
            output << "[" << loc[counter][0] << "," << loc[counter][1] << "] = " << answers[i][j] << endl;
            counter++;
        }
    }
}


void PrintVector(const vector<vector<int> > & LHS) {                 // For printing 2D vectors
  for (int x=0; x < LHS.size(); x++)
    {
      for (int y=0; y < LHS[x].size(); y++)
        {
      cout << setw(2) << LHS[x][y];
        }
    cout << endl;;
    }
    cout << endl;
}

void PrintVector2(vector<int> & RHS) {                        // For printing 1D vectors
  for (int x=0; x < RHS.size(); x++)
    {
        cout <<  RHS[x] << " ";
    }
    cout << endl;
}

void PrintVector3(const vector<vector<int> > & LHS) {                 // For printing 2D vectors
  for (int x=0; x < LHS.size(); x++)
    {
      for (int y=0; y < LHS[x].size(); y++)
        {
            cout << setw(2) << LHS[x][y];
        }
        cout << endl;
    }
    cout << endl;
}

void PrintDoubleVector(const vector<vector<int> > &Loc, vector<int> &Answers) {
    
    for (int b = 0; b< Loc.size(); b++) {
        
        for (int c =0 ; c<=1 ; c++) {
            cout << Loc[b][c];
        }
        cout << Answers[b] << endl;
    }
}


int sumation(vector<int> & coeff, vector<int> & vars){
    int sum = 0;
    for (int i = 0; i < coeff.size(); i++){
        sum += coeff[i] * vars[i];
    }
    return sum;
}


vector<int> solution (int varsSize ,vector<int> & coeff, int target){
  
    //vars all init to 1
    vector<int> vars(varsSize, 1);

    // 1 1 1
    // 8 9 8 
    // sumation = çarpım
    // target = 161

    int sum = sumation(coeff, vars);
    int k;
    vector<bool> converted(varsSize, false);
    int count = 0;
    while(sum != target){ 
        /*PrintVector2(vars);
        count++;
        if (count == 18){
            cout << "-----------" << endl;
            break;
        }
        */
        for (k = vars.size()-1; k >= 0; k--){
            
            if (!converted[k] && vars[k] == 1){
                converted[k] = true;
                vars[k] = 9;
                sum += 8*coeff[k];
                // break;
            }

            else if (vars[k] != 9){
                vars[k]++;
                sum += coeff[k];
                break;
            }
            if (vars[k] == 9){
                if (sum < target){
                    continue;
                }
                else if (sum > target){
                    vars[k] = 2;
                    sum -= 7*coeff[k];

                    if (k == vars.size()-1){
                        vars[k] = 1;
                        sum -= coeff[k];
                    }
                    // sumdan çıkart
                    // sağındaki her şeyi 1 yap
                    // en sağdan başla
                    for (int j = k+1; j < vars.size(); j++) {
                        vars[j] = 1;
                        sum -= 8*coeff[j];
                    }
                    // break;

                    //cout << "whiledan onceki: " << endl;
                    //PrintVector2(vars);
                    while(sum != target){
                        for(int t = vars.size()-1; t >= 0; t--){
                            if (vars[t] != 9){
                                vars[t]++;
                                sum += coeff[t];
                                break;
                            }
                            else{
                                vars[t] = 1;
                                sum -= 8*coeff[t];
                            }
                        }
                    }
                    break;
                }
                else{
                    break;
                }
                
                // vars[k] = 1;
                // sum -= 8*coeff[k];
            }
        }

        
    }
    return vars;
}



int main() {
    
    string fileNameLHS, fileNameRHS, fileNameRES, fileNameOUT;
    
    cout << "Enter LHS matrix filename: " << endl;                  // Taking LHS Filename
    cin >> fileNameLHS;
    
    cout << "Enter RHS matrix filename: " << endl;                  // Taking RHS Filename
    cin >> fileNameRHS;
    
    cout << "Enter RES matrix filename: " << endl;                  // Taking RES Filename
    cin >> fileNameRES;
    
    cout << "Enter OUT matrix filename: " << endl;                  // Taking OUT Filename
    cin >> fileNameOUT;
    
    ifstream inputLHS, inputRHS, inputRES, inputOUT;
    ofstream outfile;
    
    outfile.open(fileNameOUT.c_str());
    inputLHS.open(fileNameLHS.c_str());                             // Opening LHS File
    
    if (inputLHS.fail()) {
        outfile << "Error" << endl;
        return 0;
    }
    
    inputRHS.open(fileNameRHS.c_str());                             // Opening RHS File
    
    if (inputRHS.fail()) {
        outfile << "Error" << endl;
        return 0;
    }
    
    inputRES.open(fileNameRES.c_str());                             // Opening RES File
    
    if (inputRES.fail()) {
        outfile << "Error" << endl;
        return 0;
    }
    

    // Creating Vectors for Matrixes
    
    vector<vector<int> > LHS;                                       // LHS
    vector<int> LHSCol;                                            // LHS Columns
    vector<int> RHS;
    vector<int> RES;
    vector<vector<int> > Loc;
    vector<vector<int> > SummationVector;
    vector<int> InSum;
    vector<int> DeficentValueVector;
    vector<int> HugeResult;
    vector<int> PartialResult;
    vector<int> Variables;
    vector<int> Answers;
    
    
    
    // Creating LHS Matrixs
    
    string line;
    int counter = 0, controlCounter=0, rowControlCounter, columnControlCounter;
    while(!inputLHS.eof()) {
        long long int num;
        getline(inputLHS, line);
        stringstream ss(line);
        //cout << line<< endl;
        LHSCol.clear();
        while (ss >> num){
            controlCounter +=1;
            if (controlCounter == 1) {
                
                rowControlCounter = num;                                // I will use this while looking for are there same number of rows with the given value in text
            }
            else if (controlCounter == 2) {
                
                columnControlCounter = num;                            // I will use this while looking for are there same number of columns with the given value in text
            }
            else if ((num != -1 ) && !(1 <= num && num<= 9)){               // Checking the validation of matrix values.
                outfile << "Error";
                return 0;  //Unutmaaaaa
            }
            else if (counter == 0) {                                        // Skipping the first line which for defining our matrix size
            }
            else {
                LHSCol.push_back(num);                                 // Creating rows of LHS  matrix
            }
        }
        if (counter != 0) {
            LHS.push_back(LHSCol);                                     // Adding rows into our LHS matrix
        }
        counter +=1;
    }
    
    
    if (rowControlCounter != LHS.size()) {
        outfile << "Error" << endl;
        return 0;
    }
    
    
    for (int i=0 ; i< LHS.size(); i++) {
        if (columnControlCounter != LHS[i].size()) {
            outfile << "Error" << endl;
            return 0;
        }
    }
    
 
    // Creating RHS Matrixs
    string line2;
    int counter2= 0, checkCounterTry= 0, controlCounter2=0;
    while(!inputRHS.eof()) {
        long long int num2;
        getline(inputRHS,line2);
        stringstream ss2(line2);
        while (ss2 >> num2) {
            if (counter2 == 0) {
                
            }
            else if ((num2 != -1 ) && !(1 <= num2 && num2<= 9)){               // Checking the validation of matrix values.
                outfile << "Error" ;
                return 0;}
            
            else {
                RHS.push_back(num2);
                checkCounterTry += 1;
            }
            
        }
        counter2 +=1;
        
    }
    if (counter2-1 !=  checkCounterTry) {
        outfile << "Error" << endl;
        return 0;
    }
    
   
    // Creating RES Matrixs
    string line3;
    int counter3= 0, controlCounter3=0;
    while(!inputRES.eof()) {
        long long int num3;
        getline(inputRES,line3);
        stringstream ss3(line3);
        while(ss3 >> num3) {
            if (counter3 == 0) {
                
            }
            else if (!(1 <= num3)){               // Checking the validation of matrix values.
                outfile << "Error" << endl;
                return 0; }
            else {
                RES.push_back(num3);
            }
        
        }
        counter3 +=1;
    }
    
    
    // After creating vectors I need to calculate missing values
    int variableNameIdentifier = 0;
    for (int t=0; t<LHS.size() ; t++) {
        
        int summation = 0;
        InSum.clear();
        for (int u=0; u<LHS[t].size(); u++) {
    
            if (LHS[t][u] == -1) {
                
                vector<int> temp;
                temp.push_back(t);
                temp.push_back(u);
                Loc.push_back(temp);
                temp.clear();
                InSum.push_back(RHS[u]);
                //Loc.push_back(LHS[t][u]);
            }
            
            else {
                summation += LHS[t][u] * RHS[u];
            }
            if (u+1 == LHS[t].size()) {
                SummationVector.push_back(InSum);
                InSum.clear();
            }
            
            
            
            // Finding missing values
        }
        int deficentValue;
            
        deficentValue = RES[t] - summation ;
        DeficentValueVector.push_back(deficentValue) ;           //for (int d = 0; d < InSum.size() ; d++) {
            
            //}
             
    }
    
    vector<vector<int> > answers;
    for (int i = 0; i < SummationVector.size(); i++){
        vector<int> answer = solution(SummationVector[i].size(), SummationVector[i], DeficentValueVector[i]);
        answers.push_back(answer);
    }

    




//-----------------------

 
//    PrintVector(LHS);
//    cout << endl;
//    PrintVector2(RHS);
//    cout << endl;
//    PrintVector2(RES);
//    cout << endl;
    // PrintVector3(answers);
    combineVectors(Loc, answers, outfile);
//    cout << endl;
//    PrintVector2(DeficentValueVector);
//    cout << endl;
//    vector<int> temp;
    
/*
    for (int x=0; x < Answers.size(); x++)
    {
        while(Answers[x] > 0)
        {
            int m = Answers[x] % 10;
            Answers[x] = Answers[x] / 10;
            temp.push_back(m);
        }
    }
    
    
    for (int x=0; x < Loc.size(); x++)
    {
        for (int y=0; y < Loc[x].size(); y++)
        {
            outfile << Loc[x][y] << setw(2);
        }
        outfile << temp[x];
        outfile << endl;
    }
    outfile << endl;
*/    

    
 
    
    return 0;
        
}