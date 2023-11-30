#include <iostream>

using namespace std;

void printArray(int n, int cnt = 0)
{
	if (cnt == n) {
		std::cout << cnt;
		return;
	}
	std::cout << cnt << ", ";
	return printArray(n, ++cnt);
}

void printPattern(int n, int lim = 2147)
{
	if (lim == 2147) {
		lim = n;
	}
	if (lim <= 0)
	{
		return;
	}
	cout << n << " ";
	if (n > 0) {
		printPattern(n - 5, lim);
	}
	else return;
	if (n == lim) {
		cout << n;
	}
	else {
		cout << n << " ";
	}
}

int findMax(int* arr, int length)
{
	static int max = arr[length - 1];
	if (length <= 0)
	{
		int temp = max;
		max = 0;
		return temp;
	}
	if (max < arr[length - 1]) {
		max = arr[length - 1];
	}
	return findMax(arr, length - 1);
}

#include <string>

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
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	if (a == 0 || b == 0) {
		return (a == 0) ? b : a;
	}
	return findGCD(b, a % b);
}

void printHailstone(int number) 
{
	if (number == 1) {
		cout << number;
		return;
	}
	cout << number << " ";
	if (number % 2 == 0) {
		printHailstone(number / 2);
	}
	else {
		printHailstone(number * 3 + 1);
	}
}

/*
int myArrayToInt(char* str, int n, int cnt = 0)
{
	static int res = 0;
	if (n == 0) return res;
	res += str[cnt] * pow(10, --n);
	myArrayToInt(str, n, cnt++);
	return 0;
}
*/

int findLCM(int a, int b)
{
	return (a * b) / findGCD(a, b);
}

int mininumBracketAdd(const string& s, int openCnt = 0, size_t idx = 0, int minAdd = 0)
{
	if (idx == s.length()) return minAdd + openCnt;

	if (s[idx] == '(') {
		openCnt++;
	}
	else if (s[idx] == ')')
	{
		if (openCnt == 0) {
			minAdd++;
		}
		else {
			openCnt--;
		}
	}
	return mininumBracketAdd(s, openCnt, ++idx, minAdd);
}


string reverseSentence(string s)
{
	if (s.find(" ") == string::npos)
		return s + " ";
	
	return reverseSentence(s.substr(s.find(" ") + 1)) + s.substr(0, s.find(" ") + 1);
}

int strLen(char* str)
{
	if (str[0] == 0) return 0;
	return 1 + strLen(str + 1);
}

size_t findDigit(const string& s, size_t idx = 0)
{
	if (isdigit(s[idx]) || idx == s.size() - 1) {
		return idx;
	}
	findDigit(s, ++idx);
}

string repeater(const string& s, size_t repeatCnt)
{
	if (repeatCnt == 0) return "";
	if (repeatCnt == 1) return s;
	return s + repeater(s, --repeatCnt);
}

string expandHelp(const string& s, int repeat)
{
	size_t open = s.find("(");
	string temp = s.substr(open);
	size_t close = open + temp.rfind(")");
	if (open == string::npos) {
		return repeater(s, repeat);
	}
	return repeater(s.substr(0, (open - 1 < 0) ? 0 : open - 1) +
		expandHelp(s.substr(open + 1, close - open - 1), s[open - 1] - '0') +
		((close < s.size() - 1) ? expandHelp(s.substr(close + 1), 1) : 0), repeat);
}

string expand(string s)
{
	return expandHelp(s, 1);
}

