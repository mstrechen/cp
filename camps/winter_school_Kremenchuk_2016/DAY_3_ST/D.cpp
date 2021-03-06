#include<iostream>
#include<cmath>
#include<map>

using namespace std;

const double g = 10;

bool isGood(double x, double y, double Vx, double Vy, double L, double h, double l, double d)
{

    double dT1 = (L-x)/Vx;
    double dT2 = (L+l-x)/Vx;
    double dT3 = Vy/g;

    double Y_1 = y + dT1*(Vy+Vy-g*dT1)/2;
    double Y_2 = y + dT2*(Vy+Vy-g*dT2)/2;

    if(dT1 < dT3 && dT3 < dT2)
    {

        double Y_3 = y  + dT3*(Vy+Vy-g*dT3)/2;

        if(h<=Y_3 && Y_3 <=h+d &&
           h<=Y_2 && Y_2 <=h+d &&
           h<=Y_1 && Y_1 <=h+d)
        {
            return 1;
        }
        else
            return 0;
    }
    else
    {
        if(h<=Y_2 && Y_2 <=h+d &&
           h<=Y_1 && Y_1 <=h+d)
        {
            return 1;
        }
        else
            return 0;
    }

}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);



    double L, h, l, d;

    double Vx,Vy, Ux, Uy;

    cin >> L >> h >> l >> d;
    cin >> Vx >> Vy >> Ux >> Uy;

    double maxT = min(L/Vx, 2*Vy/g);


    double x = 0, y = 0;

    cout.precision(6);
    cout << (fixed);

    int N = 1000000;
    for(int i = 0; i<=N; i++)
    {
        double t = maxT*i/N;
        if(t>1e-6&&isGood(x + Vx*t, y + Vy*t + g*t*t/2, Vx+Ux, Vy+Uy-g*t, L, h, l, d))
        {
            cout << t << '\n';
            return 0;
        }

    }

    cout << -1;



    return 0;
}
