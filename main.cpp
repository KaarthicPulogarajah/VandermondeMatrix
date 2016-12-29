//Kaarthic Pulogarajah

//cmath is for powers
#include <cmath>
//iostream is for cin and cout
#include <iostream>
//conio.h is for getch() at the end
#include <conio.h>
//iomanip is for setprecision() and setw()
#include <iomanip>
using namespace std;
int main()
{
     //variable declaration
    int poly,row,col;
    //prompt for order
    cout << "Enter order of Polynomial: ";
    cin >> poly;
    //col must must used for the array size, not poly
    col = poly+1;
    cout << "Enter number of data points, min of " << col << ": ";
    cin >> row;
    // make sure user enter correct number of data points
    while (row < col)
    {
        cout <<"Min of " << col << " points\n Enter number of points: ";
        cin >> row;
    }

    //declare v array
    //array has row = num of data points, col = order + 1
    double v[row][col];
    //Y is the solution vector
    // Y is 1d because it is only a column
    double Y[row];
    //fill the first column with 1s
    for (int i = 0 ; i < row ; i++)
        v[i][0] = 1;

    //prompt user for all 8 coordinates and store in v array
    for (int i = 0 ; i < row ; i++)
    {
        cout << "Enter x coordinate "<< i+1 << "\n";
        cin >> v[i][1];
        // fill each column with corresponding powers
        for (int z = 2 ; z <= poly ; z++)
        {
            v[i][z] = pow(v[i][1], z);

        }
        //store solution coordinates in Y array
        cout << "Enter y coordinate "<< i+1 << "\n";
        cin >> Y[i];
        cout << endl;
    }




    //create transpose matrix

    // transpose matrix has the size of v, but inverted col/row
    double vt[col][row];
    //switch the values of v from row to column
    for (int i = 0 ; i < col ; i++)
        for (int j = 0 ;j < row ; j++)
            vt[i][j] = v[j][i];

    //calculate vtv matrix by multiplying vt*v
    //initialize vtv so that it is a square matrix
    // must be a square, or inverse cannot be found
    double vtv [col][col];
    //sum will be the value in vtv after matrix multiplication
    double sum = 0;
    for (int i = 0 ; i < col ; i++)
    {

        for (int j = 0 ;j < col ; j++)
        {
            for (int k = 0 ; k < row ; k++)
            {
                //sum that will correspond to each value in vtv matrix
                sum += v[k][j]* vt[i][k];
            }
            vtv[i][j] = sum;
            //make sum 0 so that each vtv value begins with 0
            sum = 0;
        }
    }

    //used setprecision() for decimal places and setw() for field widths

    //display v matrix
    cout << endl << "This is the V matrix\n";
    for (int i = 0 ; i < row ; i++){
        for (int j = 0 ;j < col ; j++)
        {
            if (v[i][j] == 1)
                cout << fixed << setprecision (0)<< setw (8) << v[i][j];
            else
                cout << fixed << setprecision (2)<< setw (8) << v[i][j];
        }

    cout << endl;
    }
    //display vt matrix
    cout << endl << "This is the Vt matrix\n";
    for (int i = 0 ; i < col ; i++){
        for (int j = 0 ;j < row ; j++)
        {
            if (vt[i][j] == 1)
                cout << fixed << setprecision (0)  << setw (8)<< vt[i][j] ;
            else
                cout << fixed << setprecision (2)<< setw (8) << vt[i][j];
        }
    cout << endl;
    }
    //display vtv matrix
    cout << endl << "This is the VtV matrix\n";
    for (int i = 0 ; i < col ; i++){
        for (int j = 0 ;j < col ; j++)
            cout << fixed << setprecision (2) << setw (12) << vtv[i][j];
    cout << endl;
    }

    //find inverse
    //large is necessary for the augmented matrix (col by 2*col)
    int large = 2*col;
    //work matrix is the large augmented matrix
    //this matrix starts with the identity matrix on the right side

    //fill left side of work with vtv
    double work[col][large];
    for (int i = 0 ; i < col ; i++)
        for (int j = 0 ; j < col ; j++)
            work[i][j] = vtv[i][j];
    //fill right side with identity matrix
    for (int i = 0 ; i < col ; i++)
        for (int j = col ; j < large ; j++)
        {
            if (j == i+col)
                work[i][j] = 1;
            else
                work[i][j] = 0;
        }
    //row operations, find inverse
    //using pivot method to find inverse

    //pivot method: divide top row to make top left 1
        //multiply the 1 by any of the let column,
        //goal is to make the left column 1, then all 0
        //repeat for each column until identity matrix is reached

    for (int k = 0 ; k < col ; k++)
    {
        for (int j = k ; j < large ; j++)
        {
            double n;
            //select coordinate that will become 1
            if (j==k)
                n = work[k][k];
            //divide rest of that row by the selected number
            work[k][j] /= n;
        }
        //repeat for the number of columns in matrix
        for (int i = 0 ; i < col ; i++)
        {
            for (int j = k ; j < large ; j++)
            {
                //condition to avoid accessing the same row containing the 1
                if ( i != k)
                {
                     double n;
                     //select a coordinate to multiply the 1 by
                    if (j==k)
                        n = work[i][k];
                    //multiply 1 by the selected number
                    work[k][j] *= n;
                    //subtract the rows to obtain a 0
                    work[i][j] -= work[k][j];
                    //restore the row with the 1 to its orginal state to be reused
                    work[k][j] /= n;
                }

            }
        }
    }
    //inverse is the right side of the work matrix
    double inverse[col][col];
    int p = col;
    for (int i = 0 ; i < col ; i++)
    {
        p=col;
        for (int j = 0 ; j < col ; j++)
        {
            //remove left hand 4x4 box from the work matrix
            inverse[i][j] = work[i][p];
            p++;
        }
    }

    //display inverse
    cout << endl << "This is (VtV)^-1\n";
    for (int i = 0 ; i < col ; i++){
        for (int j = 0 ;j < col ; j++)
            cout << setw (9) << inverse[i][j];
    cout << endl;
    }

    //initalize (VtV)^-1 * Vt size
    double A [col][row];
    double sum2 = 0;
    for (int i = 0 ; i < col ; i++)
    {
        for (int j = 0 ; j < row ; j++)
        {
            for (int m = 0 ; m < col ; m++)
            {
                //access appropriate row and columns to add
                sum2 += inverse[i][m]*vt[m][j];
            }
            //A will have value of the sum
            A[i][j] = sum2;
            //reset sum to be reused
            sum2 = 0;
        }
    }
    //display matrix
    cout << endl << "This is [(VtV)^-1]*Vt\n";
    for (int i = 0 ; i < col ; i++){
        for (int j = 0 ;j < row ; j++)
            cout << fixed << setprecision (2) << setw (8) << A[i][j];
    cout << endl;
    }
    //initialize solution vector
    double solution [col];
    double total = 0;
    for (int i = 0 ; i < col ; i++)
    {
        for (int k = 0 ; k < row ; k++)
        {
            //multiply corresponding row and column elements to get sum
            total += A[i][k]*Y[k];
        }
        solution[i] = total;
        total = 0;
    }
    //display solution
    cout << endl << "This is the Solution Vector ([(VtV)^-1]*Vt * Y)\n";
    for (int i = 0 ; i < col ; i++){
            cout << fixed << setprecision (2) << solution[i];
    cout << endl;
    }
    //display the function in one line
    cout << "\nf(x) = ";
    for (int i = poly ; i > 1 ; i--)
    {
        //disply each coefficient with the correct power
            cout << "(" << solution[i] << ")x^" << i << " + ";
    }
    //display the last coefficient and the constant term
    cout << "(" << solution[1] << ")x + (" << solution[0] << ")";
    cout << "\n*All values rounded to 2 decimal places";

    getch();
    return 0;
}
