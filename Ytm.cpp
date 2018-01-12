//Elyess 
// This line represents the preprocesseur directive. Its role is to load C ++ features to do certain actions
#include <iostream>
#include <cmath>
#include <iomanip>

/* This line is very important it permits to create our work space. The names space "std" is one of the most in C++.
It corresponds to the "std" library.*/
using namespace std;

// Computate the present value
// N is the number of full years until maturity
// d is the year fraction until next coupon payment
double PV(double futureValue, double couponRate, double r, int N,double d)
{
    double temp_PV=0;
    double coupon=couponRate*futureValue;
// The loop "for" is usefull to group the initialisation, the condition and the incrementaiton process
    for(int i=0;i<=N;i++)
    {
        temp_PV += coupon*pow(1+r,-i-d);
    }

    temp_PV += + futureValue*pow(1+r,-N-d);

    return temp_PV;
}
// Compute Yield-to-Maturity: Zero Coupon Bond
double zeroCouponYTM(double faceValue,double priceValue,double N,double d)
{
    double YTM=0;
    YTM=pow((faceValue/priceValue),1/N+d)-1;
    return YTM;
}

// Compute the Yield-to-Maturity(YTM) by iteration : Secant method
double iterationYTM(double futureValue,double couponRate,double priceValue,int N,double d,double i0=0.00001, double i1= 10)
{
    //number of iteration
    const int MaxIter=50000;
    //error limit
    double epsilon = 0.0000001;
    //temporary iterative values
    double midP=0.0,midCdif;
    //Algorithm interval
    double lowCdif=priceValue- PV(futureValue, couponRate, i0, N,d);
    double highCdif=priceValue- PV(futureValue, couponRate, i1, N,d);

    if(priceValue == futureValue)
    {
        return couponRate;
    }

    else if(couponRate == 0)
    {
        return  zeroCouponYTM(futureValue, priceValue,N,d);
    }
    if (lowCdif*highCdif>0)
        return -1;
    else
        for(int i=0;i<=MaxIter;i++){
            midP=(i0+i1)/2.0;
            midCdif=priceValue- PV(futureValue, couponRate, midP, N,d);
            if(abs(midCdif)<epsilon) return midP;
            else
            {
                if (midCdif>0) i1=midP;
                else i0=midP;
            }

        }

    return midP;
}


int main() {

    double couponRate, d, futureValue, priceValue,N,coupon;

    cout << "**************************Hello and welcome to your financial management automat**************************" << endl;
    //First requirements to manage your investment
    cout << " ************Please, enter your bond characteristics (enter one value then press enter)************" << endl;

    cout << " The coupon rate" << "=> next coupon payment" << "=> future value" << "=> present value" << " => the number of Year before maturity" << endl;
    //The user presents his bond
    cin >> couponRate >> d >> futureValue >> priceValue >> N;
    //With these information, we compute the coupon value that the user receive each year
    coupon=couponRate*futureValue;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
    //We summarize all the information we have on this bond
    cout <<"Finally, we have a coupon rate = "<< couponRate <<", a coupon value = "<< coupon <<", the next coupon payment in "<< d <<" years"<<", a future value = "<< futureValue <<", a price value = "<< priceValue <<" and your bond comes to maturity in "<< N << " years" << endl;

// Here, we program a Yield-to-Maturity for each different case. For example, in the Zero Coupon bond case or future = price valueuble i1= 10;
    double YTM=iterationYTM(futureValue,couponRate,priceValue,N,d);
    YTM = YTM*100;
    cout<<"To conclude, your YTM="<<YTM<<"%"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;

    return 0;

}
