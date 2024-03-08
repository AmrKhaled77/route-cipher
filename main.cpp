#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// make a function to remove every thing from the text exapt
vector<char> handle_message( string  arr) {
    vector<char> clean_message;

    for (char i : arr) {
        if (isalpha(i)) {
            clean_message.push_back(toupper(i));
        }
    }
    return clean_message;
}



void route_cipher_encryption(vector<vector<char>> matrix) {


    int number_of_rows, number_of_cols, currnt_row, currnt_col, direction;
    // get the size and of the matrix
    number_of_rows = matrix.size();
    number_of_cols = matrix[0].size();


// start from top right element in the matrix
    currnt_row = 0;
    currnt_col = number_of_cols - 1;


// dirctuins ro move in matrix in clockwise movement   {Right, Down, Left, Up}
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  //  Start with moving down
    direction = 1;

    // empaty array to store the text after encryption
    vector<char> encryptedARR;

//  Iterate through each element in the matrix
    for (int i = 0; i < (number_of_rows * number_of_cols); ++i) {

        // add currnt char to the encrypted array
        encryptedARR.push_back(matrix[currnt_row][currnt_col]);

        // remove the add char from tha matrix and add defoult val = '0'
        matrix[currnt_row][currnt_col] = '0';


// change val of next row
        int valdition_on_row = currnt_row + directions[direction][0];
        int valdition_on_col = currnt_col + directions[direction][1];


// check if the val of next row and next col are s within bounds of 0 and row , 0 and number_of_cols , and not equal '0'
        if (0 <= valdition_on_row && valdition_on_row < number_of_rows && 0 <= valdition_on_col && valdition_on_col < number_of_cols && matrix[valdition_on_row][valdition_on_col] != '0') {
            currnt_row = valdition_on_row;
            currnt_col = valdition_on_col;
        } else {
            //Change direction with 1   in range [0,1,2,3]
            direction = (direction + 1) % 4;



            //change the val with the new dirction
            currnt_row += directions[direction][0];
            currnt_col += directions[direction][1];
        }
    }
cout<< "encrypted text is : ";
    for (char c : encryptedARR) {

            cout << c;


    }
}

void route_cipher_decryption(vector<char> encrypted_arr , int rows , int cols  ) {






    // Initialize an empty matrix with the given number of rows and columns
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    // Define initial position (top-left corner)
    int row = 0, col = 0;

    // Define direction deltas for counter-clockwise movement
    vector<vector<int>> deltas = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; // Left, Down, Right, Up
    int direction = 0; // Start with moving left

    // Iterate through the encrypted array and fill the matrix in a counter-clockwise manner
    for (char val : encrypted_arr) {
        // Assign the current value to the current position in the matrix
        matrix[row][col] = val;

        // Calculate next position
        int next_row = row + deltas[direction][0];
        int next_col = col + deltas[direction][1];

        // Check if next position is within bounds and not visited
        if (0 <= next_row && next_row < rows && 0 <= next_col && next_col < cols && matrix[next_row][next_col] == ' ') {
            row = next_row;
            col = next_col;
        } else {
            // Change direction if next position is out of bounds or visited
            direction = (direction + 1) % 4;
            row += deltas[direction][0];
            col += deltas[direction][1];
        }
    }
cout<<"decrypted text is : ";
    // Output the decrypted message
    for (vector<char>& row : matrix) {
        for (int i =row.size()-1;i>=0;--i) {
            cout << row[i];
        }
    }
}

string  Start_App(){
    string user_input;
    cout<<endl;
    cout<<" (a) for encryption "<<endl <<" (b) for decryption"<<endl <<"  (z) to exit"<< endl<<"please chose: ";
    cin>> user_input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return user_input;
}


int main() {




    while (true){
        string user_input;
        user_input= Start_App();

    if (user_input== "z"|| user_input=="Z"){
        cout<<"app end";
        break;
    }






        string  massge;
        int key,cols,rows;
        vector<char> clean_arr_massge;
        cout << "please enter your massge : " << endl;
        getline(cin,massge);
        // delet all spaces and sspecial characters from string and add it to array
        clean_arr_massge = handle_message(massge);




        int error;
        do
        {
            error = 0;
            cout<<" please enter your key";
            cin>>key;
            if (cin.fail())
            {
                cout << "Please enter a valid integer ," << endl;
                error = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        }while(error == 1);

        cols =key;
        rows= ceil((double(clean_arr_massge.size()) /cols));


        vector<vector<char>> arr(rows, vector<char>(cols, 'X'));


        int temp,colsNum,rowsNum;
        temp=0;
        colsNum=0;
        rowsNum=0;

        for(char elemnt : clean_arr_massge){
            if(temp<key){
                arr[rowsNum][colsNum]=elemnt;
                colsNum+=1;
                temp+=1;
            } else{
                temp=0;
                colsNum=0;
                rowsNum+=1;
                arr[rowsNum][colsNum]=elemnt;
                colsNum+=1;
                temp+=1;
            }
        }
        if (user_input== "a"|| user_input=="A"){
            route_cipher_encryption(arr);

        }if (user_input== "b"|| user_input=="B"){
            route_cipher_decryption(clean_arr_massge, rows, cols);

    }}







    return 0;
}
