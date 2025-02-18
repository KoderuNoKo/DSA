#include<iostream>

using namespace std;

void printArray(int n)
{
    if (n == 0) {
        cout << n;
    }
    else if (n > 0) {
        printArray(n - 1);
        cout << ", " <<  n;
    } 
    return;
}

void printPattern(int n) 
{
    if (n <= 0) {
        cout << n;
        return;
    }
    cout << n << " ";
    printPattern(n - 5);
    cout << " " << n;
}

int findMax(int* arr, int length)
{
    if (length == 1) {
        return arr[0];
    }
    int temp = findMax(arr, length - 1);
    return (arr[length - 1] > temp) ? arr[length - 1] : temp;
}

bool isPalindromeRec(string str, int n) 
{
    if (n >= str.length() / 2) {
        return true;
    }
    return ((str[n] == str[str.length() - n - 1]) && isPalindromeRec(str, n + 1));
}

bool isPalindrome(string str) 
{
    // remove all spaces
    string nospaceStr = "";
    for (auto ch : str) {
        if (ch != ' ') {
            nospaceStr += ch;
        }
    }
    // call check palindrom recursion function
    return isPalindromeRec(nospaceStr, 0);
}

int findGCD(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return findGCD(b, a % b);
}

void printHailstone(int number)
{
    if (number == 1) {
        cout << number;
    }
    else if (number % 2 == 0) {
        cout << number << " ";
        printHailstone(number / 2);
    }
    else if (number % 2 == 1) {
        cout << number << " ";
        printHailstone(number*3 + 1);
    }
}

int exp(int a, int b)
{
    if (b == 1) {
        return a;
    }
    return a * exp(a, b - 1);
}

int myArrayToInt(char* str, int n, int i = 0)
{
    if (i == n - 1) {
        return str[i] - '0';
    }
    int curr_digit = str[i] - '0';
    return curr_digit * exp(10, n - i - 1) + myArrayToInt(str, n, i + 1);
}

int findLCM(int a, int b)
{
    return (a / findGCD(a, b)) * b;
}

int mininumBracketAdd(string s, int i = 0, int missing_open = 0, int missing_close = 0)
{
    if (i == s.length()) {
        return missing_close + missing_open;
    }
    if (s[i] == '(') {
        return mininumBracketAdd(s, i + 1, missing_open, missing_close + 1);
    }
    if (s[i] == ')') {
        if (missing_close > 0) {
            return mininumBracketAdd(s, i + 1, missing_open, missing_close - 1);
        }
        return mininumBracketAdd(s, i + 1, missing_open + 1, missing_close);
    }
    return 0;   // error case
}

string reverseSentence(string s) 
{
    int next = s.rfind(' ');
    if (next == string::npos) {
        return s;
    }
    return s.substr(next + 1, s.length() - next) + " " + reverseSentence(s.substr(0, next));
}

int strLen(char* str, int count = 0)
{
    if (!str[count]) {
        return count;
    }
    return strLen(str, count + 1);
} 