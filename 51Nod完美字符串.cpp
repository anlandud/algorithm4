#include<string>
#include<algorithm>
#include<functional>	//升降
#include<iostream>
#include<queue>
using namespace std;

string s;
string t;
int c[26];
long result;
priority_queue<int> que;
struct myclass {
	bool operator() (char i, char j) { return (i>j); }
} myobject;
int main() {
	while (cin >> s) {
		result = 0;
		int co = 0;
		for (int i = 0; i < 26; i++) {
			c[i] = 0;
		}
		transform(s.begin(), s.end(),s.begin(), tolower);//转换为小写
		sort(s.begin(),s.end(),myobject);	//对字符串中元素排序
		//将相同的字符串放在一起
		for (int i = 0; i < s.size()-1; i++) {
			if (s[i] != s[i + 1]) {
				c[co]++;
				co++;
			}
			else {
				c[co]++;
			}
		}
		c[co]++;
		sort(c, c + 26,greater<int>());//对数组进行排序
		for (int i = 0; i < 26; i++) {
			result += (26-i)*c[i];
		}
		cout << result << endl;
	}
} 
