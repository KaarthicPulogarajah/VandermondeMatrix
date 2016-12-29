//Kaarthic Pulogarajah
#include <cmath>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;
int main()
{
    //variable declaration and initialization
    int row, col;
    col = 4;
    row = 8;
    //declare v array
    double v[row][col];
    double Y[8];
    //fill the first column with 1s
    for (int i = 0 ; i < row ; i++)
        v[i][0] = 1;

    cout << "Enter x,y pairs for a 3rd order polynomial\n";
    //prompt user for all 8 coordinates and store in v array
    for (int i = 0 ; i < row ; i++)
    {
        cout << "Enter x coordinate "<< i+1 << "\n";
        cin >> v[i][1];
        // fill each column with corresponding powers
        v[i][2] = pow(v[i][1], 2);
        v[i][3] = pow(v[i][1], 3);
        cout << "Enter y coordinate "<< i+1 << "\n";
        cin >> Y[i];
        cout << endl;
    }



    //create transpose matrix
    double vt[col][row];
    //switch the values of v from row to column
    for (int i = 0 ; i < col ; i++)
        for (int j = 0 ;j < row ; j++)
            vt[i][j] = v[j][i];

    //calculate vtv matrix by multiplying vt*v
    double vtv [col][col];
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
    double work [4][8];
    //set up augmented matrix
    for (int i = 0 ; i < 4 ; i++)
    {
        //take in values from vtv matrix
        for (int j = 0 ; j < 4 ; j++)
            work[i][j] = vtv[i][j];
    }
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 4 ; j < 8 ; j++)
        {
            // fill right side with the identity matrix for a 4x4
            if (j-i == 4)
                work[i][j] = 1;
            else
                work[i][j] = 0;
        }
    }
    //row operations, find inverse
    //using pivot method to find inverse
    for (int k = 0 ; k <=3 ; k++)
    {
        for (int j = k ; j < 8 ; j++)
        {
            double n;
            //select coordinate that will become 1
            if (j==k)
                n = work[k][k];
            //divide rest of that row by the selected number
            work[k][j] /= n;
        }
        //repeat for the number of columns in matrix
        for (int i = 0 ; i <=3 ; i++)
        {
            for (int j = k ; j < 8 ; j++)
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
                    //restore the row with the 1 to its orginal state so it can be reused
                    work[k][j] /= n;
                }

            }
        }
    }
    //initialize size of mtrix as same as vtv
    double inverse[col][col];
    for (int i = 0 ; i < col ; i++)
        for(int j = 4 ; j < row ; j++)
        {
             //remove left hand 4x4 box from the work matrix
            inverse[i][j-4] = work[i][j];
        }


    //display inverse
    cout << endl << "This is (VtV)^-1\n";
    for (int i = 0 ; i < col ; i++){
        for (int j = 0 ;j < col ; j++)
            cout << fixed << setprecision (2) << setw (12) << inverse[i][j];
    cout << endl;
    }
    //initalize (VtV)^-1 * Vt size
    double A [col][row];
    double sum2 = 0;
    for (int i = 0 ; i < col ; i++)
    {
        for (int j = 0 ; j < row ; j++)
        {
            for (int m = 0 ; m < 4 ; m++)
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
        for (int k = 0 ; k < 8 ; k++)
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

    cout << "\nf(x) = (" << solution[3] << ")x^3 + (" << solution[2] << ")x^2";
    cout << " + (" << solution[1] << ")x + (" << solution[0] << ")";
    cout << "\n*All values rounded to 2 decimal places";
    getch();
    return 0;
}
