#include <iostream>
#include <cmath> // /usr/include/c++/4.8
#include <fstream>


using namespace std;

#define PI 3.14

int main()
{
   	  ofstream myfile;
   	  myfile.open ("result.txt");

    int option;
    double x, y, param, result;
    char A;
    cout << "Choose an option \n" << endl;

    cout << "1 - cos Compute cosine (function )     \n" << endl;
    cout << "2 - sin Compute sine (function )       \n" << endl;
    cout << "3 - tan Compute tangent (function )    \n" << endl;
    cout << "4 - acos Compute arc cosine (function )\n" << endl;
    cout << "5 - asin Compute arc sine (function )  \n" << endl;
    cout << "6 - atan Compute arc tangent (function ) \n" << endl;
    cout << "7 - atan2 Compute arc tangent with two parameters (function ) \n" << endl;
    cout << "8 - pow Raise to power (function ) \n" << endl;
    cout << "9 - sqrt Compute square root (function ) \n" << endl;
    cout << "10 - cbrt Compute cubic root (function ) \n" << endl;
    cout << "11 - hypot Compute hypotenuse (function ) \n" << endl;
    cout << "12 - add Add 2 numbers (function ) \n" << endl;
    cout << "13 - subtract Subtract 2 numbers \n" << endl;
    cout << "14 - div divide 2 numbers \n" << endl;
    cout << "15 - mult Multiply 2 numbers \n" << endl;
    cout << "16 - exp Compute exponential function (function )\n" << endl;
    cout << "17 - log Compute natural logarithm (function ) \n" << endl;
    cout << "18 - log10 Compute common logarithm (function ) \n" << endl;
    cout << "19 - log1p Compute logarithm plus one (function ) \n" << endl;
    cout << "20 - log2 Compute binary logarithm (function ) \n" << endl;
    cout << "Q/q to quit \n" << endl;
    cin >> option;


    if ( (option >=12 && option <= 15) || option == 11){
        cout << "Enter x: \n";
        cin >> x;
        cout << "Enter y: \n";
        cin >> y;
    }
    else if( option >= 1 && option <= 6){
            cout << "Enter the angle in degrees: \n";
            cin >> param;
    }
    else if(option ==8 ){
            cout << "Enter the base: \n";
            cin >> x;
            cout << "Enter the exponent:n";
            cin >> y;
    }
    else if( option == 9 || option == 10 || ( option >= 16 && option <= 20 ) ){
        cout << "Enter the value: \n";
        cin >> x;
    }

        switch(option){
                case 1:
                    result = cos ( param * PI / 180.0 );
                    cout << "The cosine of " << param <<" is : " << result << endl;
                    cin >> option;
                     myfile << result;
                     myfile.close();
                    break;

                case 2: result = sin ( param * PI / 180.0 );
                    cout << "The sine of " << param <<" is : " << result << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 3: result = tan ( param * PI / 180.0 );
                    cout << "The tan of " << param <<" is : " << result << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 4: result = acos (param) * 180.0 / PI;
                    cout << "The acosine of " << param <<" is : " << result << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 5: result = asin (param) * 180.0 / PI;
                     cout << "The asine of " << param <<" is : " << result << endl;
                     myfile << result;
                    myfile.close();
                    break;

                case 6: result = atan (param) * 180.0 / PI;
                     cout << "The atan of " << param <<" is : " << result << endl;
                     myfile << result;
                    myfile.close();
                    break;

                case 7:
                    break;

                case 8: result  =  pow(x,y);
                    cout << "The " << x << " to the " << y << " power is " << result << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 9: cout << "The sqrt of " << x << " is " << sqrt(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 10: cout << "The cbrt of " << x << " is " << cbrt(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 11: cout << "The hypot of x: " << x << "and is y: " << y << " is " << hypot(x , y) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 12: cout << x << " + " << y << " = " << x+ y<< endl;
                    myfile << result;
                    myfile.close();
                    break;

                 case 13: cout << x << " - " << y << " = " << x - y << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 14: cout << x << " / " << y << " = " << x / y << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 15: cout << x << " * " << y << " = " << x * y << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 16: cout << "The exponential value of " << x << " is " << exp(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 17:  cout << "The log value of " << x << " is " << log(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 18:  cout << "The log10 value of " << x << " is " << log10(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 19: cout << "The log1p value of " << x << " is " << log1p(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                case 20: cout << "The log2 value of " << x << " is " << log2(x) << endl;
                    myfile << result;
                    myfile.close();
                    break;

                default: cout << "Please choose an option \n" <<endl;
                    break;
            }
          return 0;
}
