#include <iostream>
#include <cmath>
using namespace std;
struct Point
{
    float x;
    float y;
};

int modulo(int a, int b)
{
    return (a % b + b) % b;
}

// Function to calculate the inverse of a number
int modInverse(int a, int m)
{
    a = modulo(a, m);

    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;

    return 1;
}

// Function to calculate the GCD of two numbers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Elliptic Curve Function
Point EC_Add(Point p1, Point p2, int a, int b, int p)
{
    Point p3;

    // If both points are same
    if (p1.x == p2.x && p1.y == p2.y)
    {
        int slope = modulo((3 * pow(p1.x, 2) + a), p);
        int inverse = modInverse(2 * p1.y, p);
        int num = modulo((slope * inverse), p);
        int x3 = modulo((pow(num, 2) - p1.x - p2.x), p);
        int y3 = modulo((num * (p1.x - x3) - p1.y), p);

        p3.x = x3;
        p3.y = y3;
    }
    else
    {
        int slope = modulo((p2.y - p1.y), p);
        int inverse = modInverse(p2.x - p1.x, p);
        int num = modulo((slope * inverse), p);
        int x3 = modulo((pow(num, 2) - p1.x - p2.x), p);
        int y3 = modulo((num * (p1.x - x3) - p1.y), p);

        p3.x = x3;
        p3.y = y3;
    }
    return p3;
}

// Function to calculate the point multiplication 
Point EC_Multiplication(Point p1, int k, int a, int b, int p)
{
    Point ans = p1;

    for (int i = 0; i < k - 1; i++)
        ans = EC_Add(ans, p1, a, b, p);
    return ans;
}

// Driver Program
int main()
{
    //Elliptic curve equation : y2 = x3 + ax + b
    // Choose randomly
    int a = 5;
    int b = 25;
    int p = 31;
    Point p1 = {5, 11};

    int k = 5;
    Point p2 = EC_Multiplication(p1, k, a, b, p);
    std::cout << "The result of kP is:(" << p2.x << ", " << p2.y << ")" << std::endl;
    return 0;
}