#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/*
* Daniel Bamidele UIN 651044450
*10/12/2024
*
* This program helps users access a value from a Maternal
* Mortality dataset. The program asks the user for a file
* name. Then it asks the user to choose whether to display
* dataset or analyze a factor.
* 
*
*/

// FUNCTION DECLARATIONS
void displayData(vector<string>& factorNames, vector<vector<string>>& value, string filename);
void fillData(vector<string>& factorNames, vector<vector<string>>& value, string filename);
void printRow(vector<string>& factorNames, vector<vector<string>>& value, const string& filename);
void singleFactorAnalysis(vector<string>& factorNames, vector<vector<string>>& value, const string& filename);
void twoFactorAnalysis(vector<string>& factorNames, vector<vector<string>>& value, const string& filename);


//FUNCTION TO FILL THE DATA INTO 2D ARRAY/VECTOR
void fillData(vector<string>& factorNames, vector<vector<string>>& value, string filename) {
    /*
        this function takes the filename provided by the user,
        then it searches for the file and opens it. it then reads
        content of the file word by word, then line by line and it 
        stores the content in new vectors.
    */
    factorNames.clear();
    value.clear();
    
    ifstream file(filename);
    string line;
    // if file couldn't be found, return an error.
    if (!file.is_open()) {
        cout << "Couldn't open file! Check file name.";
        return;
    }

    
    // add the factor names to the vector factorName
    if (getline(file, line)) 
    {
        stringstream ss(line);
        string factorName;
        while (getline(ss, factorName, ',')) {
            factorNames.push_back(factorName);
        }  
    }
    
    // add the values of corresponding factor names to 
    // the vector valueStr
    while(getline(file, line)){
        stringstream ss(line);
        string valueStr;
        vector<string> row;

        while(getline(ss, valueStr, ',')) {
            row.push_back(valueStr);
        }

        value.push_back(row);
    }
    file.close();

    
}

// FUNCTION TO DISPLAY THE DATA BASED ON FILE SIZE
void displayData(vector<string>& factorNames, vector<vector<string>>& value, string filename) {
    /*
        this function displays the dataset based on the choice the 
        user makes. it takes in a filename and then calls the fill
        data function to fill the vectors with the factor names and
        values. then it prints the dataset.
    */
    if (filename == "small_data.csv") {
        fillData(factorNames, value, filename);
        for (size_t i = 0; i < factorNames.size(); i++) {
            cout << factorNames.at(i) << ",";
        }
        cout << endl;
        for (size_t i = 0; i < value.size(); i++) {
            for (size_t j = 0; j < value[i].size(); j++) {
                cout << value[i][j] << ",";
            }
            cout << endl;
        }
    } else if (filename == "medium_data.csv") {
        fillData(factorNames, value, filename);
        for (size_t i = 0; i < factorNames.size(); i++) {
            cout << factorNames.at(i) << ",";
        }
        cout << endl;
        for (size_t i = 0; i < value.size(); i++) {
            for (size_t j = 0; j < value[i].size(); j++) {
                cout << value[i][j] << ",";
            }
            cout << endl;
        }
    } else if (filename == "large_data.csv") {
        fillData(factorNames, value, filename);
        for (size_t i = 0; i < factorNames.size(); i++) {
            cout << factorNames.at(i) << ",";
        }
        cout << endl;
        for (size_t i = 0; i < value.size(); i++) {
            for (size_t j = 0; j < value[i].size(); j++) {
                cout << value[i][j] << ",";
            }
            cout << endl;
        }
    } else {
        cout << "Enter correct file" << endl;
    }
    
}

// FUNCTION TO DISPLAY SELECTED ROW
void printRow(vector<string>& factorNames, vector<vector<string>>& value, const string& filename) {
    /*
        this function calls the fill data function to fill the
        vectors with the factor names and the corresponding values.
        it then asks the user to enter a row, and then prints all the
        factor names and corresponding values on that row.
    */
    cout << "Enter a row number: ";
    int rowNumber;
    cin >> rowNumber;
    fillData(factorNames, value, filename);
    for (size_t i = 0; i < factorNames.size(); i++) {
        cout << factorNames.at(i) << ": " << value[rowNumber - 1][i] << endl;
    }
    
}

//FUNCTION TO ANALYZE A SINGLE FACTOR
void singleFactorAnalysis(vector<string>& factorNames, vector<vector<string>>& value, const string& filename) {
    /* this function asks the user for a factor name, then the column index 
    of the factor name is retrieved. then the function creates a vector and
    stores all the values in the column of that factor name. then it counts
    how many times each value appear and prints it out.
    */
    fillData(factorNames, value, filename);
    vector<string> Column;
    cout << "Enter a factor name: ";
    string varName;
    cin >> varName;

    int index = -1;

 
    // search for the column index of factor provided
    for (size_t i = 0; i < factorNames.size(); i++) {
        if (varName == factorNames.at(i)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Invalid factor name.";
    } else {
        for (size_t i = 0; i < value.size(); i++) {
            // add each value to vector Column
            Column.push_back(value[i][index]);
        } 
    }
    
    for (size_t i = 0; i < Column.size(); i++) {
        string category = Column.at(i);
        bool alreadyPrinted = false;

        // check if category has already been printed
        for (size_t j = 0; j < i; j++) {
            if (category == Column.at(j)) {
                alreadyPrinted = true;
                break;
            }
        }

        if (alreadyPrinted) continue;

        // count how many occurences a category appears in the dataset
        int count = 0;
        for (size_t k = 0; k < Column.size(); k++) {
            if (category == Column.at(k)) {
                count++;
            }
        }

        cout << varName << " " << Column.at(i) << ": " << count << " records" << endl;
       
    }
    
} 

//FUNCTION TO ANALYZE A TWO FACTORS
void twoFactorAnalysis(vector<string>& factorNames, vector<vector<string>>& value, const string& filename) {
    /*
    this function calls the fill data function which fills the array
    with the factor names and values. it then asks the user to enter 
    two factor names and then creates two arrays. it then compares both
    arrays to each other and finds out the number of occurences using a 
    2d array.
    */
    fillData(factorNames, value, filename);
    string firstFactor;
    string secondFactor;
    
    cout << "Enter a factor name: " << endl;
    cin >> firstFactor;
    cout << "Enter a second factor name: " << endl;
    cin >> secondFactor;
    
    int index1 = -1;
    int index2 = -1;

    // find column index for both factors
    for (size_t i = 0; i < factorNames.size(); i++) {
        if (factorNames.at(i) == firstFactor) {
            index1 = i;
        }
        if (factorNames.at(i) == secondFactor) {
            index2 = i;
        }
    }
    
    if (index1 == -1 || index2 == -1) {
        cout << "Invalid factor names. " << endl;
        return;
    }

    // find unique values for each factor
    vector<string> uniqueFactor1;
    vector<string> uniqueFactor2;
    
    // push values of first factor into an erray
    for (size_t i = 0; i < value.size(); i++) {
        string val = value[i][index1];
        bool found = false;
        for(size_t j = 0; j < uniqueFactor1.size(); j++) {
            if (uniqueFactor1.at(j) == val) {
                found = true;
                break;
            }
        }
        if(!found) {
            uniqueFactor1.push_back(val);
        }
    }

    // push values of second factor into an erray
    for (size_t i = 0; i < value.size(); i++) {
        string val = value[i][index2];
        bool found = false;
        for(size_t j = 0; j < uniqueFactor2.size(); j++) {
            if (uniqueFactor2.at(j) == val) {
                found = true;
                break;
            }
        }
        if(!found) {
            uniqueFactor2.push_back(val);
        }
    }

    // count occurences
    for (size_t i = 0; i < uniqueFactor1.size(); i++) {
        cout << firstFactor << " " << uniqueFactor1.at(i) << " :" << endl;
        for (size_t j = 0; j < uniqueFactor2.size(); j++) {
            int count = 0;
            for (size_t k = 0; k < value.size(); k++) {
                if (value[k][index1] == uniqueFactor1.at(i) && value[k][index2] == uniqueFactor2.at(j)) {
                    count++;
                }
            }
            cout << secondFactor << " " << uniqueFactor2.at(j) << " : " << count << " records" << endl;
        }
        cout << "=====================================" << endl;
    }

}

// MAIN FUNCTION TO DISPLAY OPTION CHOSEN
void optionChosen(vector<string>& factorNames, vector<vector<string>>& value, string filename, int choices) {
    /*
    this function is the main function that calls all other
    functions depending on what the user selects. it takes in
    vectors, filename, and the choice the user picks. 
    */
    if (choices == 1) {
        displayData(factorNames, value, filename);
    } else if (choices == 2) {
        printRow(factorNames, value, filename);
    } else if (choices == 3) {
        singleFactorAnalysis(factorNames, value, filename);
    } else if (choices == 4) {
        twoFactorAnalysis(factorNames, value, filename);
    } else {
        cout << "Please select from the options above.";
    }
}

int main() 
{
    string filename;

    vector<string> factorNames;
    vector<vector<string>> value;

    // The menu output. Don't modify this, so that it outputs exactly as expected
    cout << "Project 1: Understanding Maternal Mortality" << endl;
    cout << "Enter a file name you want to use: ";
    cin >> filename;
    cout << "Which option would you like?" << endl;
    cout << "  1. Display data" << endl;
    cout << "  2. Print a selected row" << endl;
    cout << "  3. Single factor analysis" << endl;
    cout << "  4. Two factor analysis" << endl;
    cout << "Your choice: ";

    int choices;
    cin >> choices;

    optionChosen(factorNames, value, filename, choices);
}