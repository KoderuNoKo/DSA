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

bool isPalindrome(const string& str, size_t i = 0, size_t spaceL = 0, size_t spaceR = 0)
{
	if (str[i + spaceL] == ' ') {
		spaceL++;
	}
	if (str[str.length() - i - spaceR - 1] == ' ') {
		spaceR++;
	}

	if (i == str.length() / 2) {
		return (str[i + spaceL] == str[str.length() - i - spaceR - 1]);
	}
	else if (str[i + spaceL] == str[str.length() - i - 1 - spaceR]) {
		return isPalindrome(str, i + 1, spaceL, spaceR);
	}
	else return false;
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

int mininumBracketAdd(const string &s, unsigned int i = 0, int missing_open = 0, int missing_close = 0)
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
    size_t next = s.rfind(' ');
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


void dup_help(string &ans, string s, int time)
{
    if(time == 0) return; 
    ans += s; 
    dup_help(ans,s,time-1); 
}
void smaller(string& s, size_t index = 0)
{
    size_t find_ = s.find(')',index); 
    string sub = s.substr(index + 1,find_ - index - 1);

    int num_of_dup = s[index-1] - '0';
    string ans = "";
    dup_help(ans,sub,num_of_dup); 

    s.replace(index-1,find_ - index + 2,ans);
}

void help(string& s)
{
    size_t find = s.rfind('('); 
    if(find == std::string::npos) return;
    smaller(s,find);
    help(s); 
}

string expand(string s)
{
    help(s); 
    return s; 
}