#pragma once
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<string.h>
/*
目录：
   1.常用函数；
   2.补充数字类型：;
   3.
   4.
   5.
   6.
   7.
   8.
   9.
*/

template<typename T>
inline T gcd(T a, T b) {//define(x,0)=x;
	if (a == 0 || b == 0)return a+b;
	if (a == 1 || b == 1)return 1;
	if (a < b)std::swap(a, b);
	if (a % b == 0)return b;
	else return gcd(b, a % b);
}

class hp {//10000进制;400位
public:
	int num[101];//num[0]为数字位数,可存储400位数：
	//初始化部分
	hp& operator=(std::string c) {
		int fh = 1;
		std::memset(num, 0, sizeof(num));
		int n = c.length(), j = 1, k = 1; int cnt = 0;
		while (c[cnt] == ' ' || c[cnt] == '\n')cnt++;
		while (c[cnt] > '9' || c[cnt] < '0') { 
			if (c[cnt] == '-')fh *= -1, cnt++; else if (c[cnt] == '+')cnt++; else return *this; 
		}

		for (int i = n-1; i >= cnt; i--) {
			if (k == 10000)j++, k = 1;
			num[j] += k * (c[i] - '0');
			k *= 10;
		}
		num[0] = j;
		while (num[num[0]] == 0&&num[0]>0)num[0]--;//去除前导0;
		num[num[0]] *= fh;
		return *this;
	}
	hp& operator=(int a) { return *this = std::to_string(a); }
	hp& operator=(long long a) { return *this = std::to_string(a); }
	hp& operator=(unsigned long long a) { return *this = std::to_string(a); }
	hp(){ std::memset(num, 0, sizeof(num)); num[0] = 0; }
	hp(int a) { *this = a; }
	hp(long long a) { *this = a; }
	hp(unsigned long long a) { *this = a; }
	//大小比较部分
	bool operator >(const hp& b)const {
		if (num[0] == 0) { if (b.num[b.num[0]] < 0)return true; else return false; }
		if (b.num[0] == 0) { if (num[num[0]] > 0)return true; else return false; }
		if (num[num[0]] * b.num[b.num[0]] < 0)return num[num[0]] > b.num[b.num[0]];
		if (num[num[0]] > 0) {
			if (num[0] != b.num[0]) return num[0] > b.num[0];
			for (int i = num[0]; i >= 1; i--)
				if (num[i] != b.num[i])
					return (num[i] > b.num[i]);
			return false;
		}
		else if(num[num[0]]<0) {
			if (num[0] != b.num[0]) return num[0] < b.num[0];
			for (int i = num[0]; i >= 1; i--)
				if (num[i] != b.num[i])
					return (num[i] < b.num[i]);
			return false;
		}
	}
	bool operator<(const hp& b)const { return b > *this; }
	bool operator<=(const hp& b)const { return !(*this > b); }
	bool operator>=(const hp& b)const { return !(b > *this); }
	bool operator!=(const hp& b)const { return (b > *this) || (*this > b); }
	bool operator==(const hp& b)const { return !(b > *this) && !(*this > b); }
	//四则运算部分
	hp operator+(const hp& b)const {
		hp c; 
		hp a = *this; hp bb = b;
		if (a.num[0] == 0)return b; if (b.num[0] == 0)return *this;
		c.num[0] = std::max(num[0], b.num[0]);
		if (a.num[a.num[0]] > 0 && b.num[b.num[0]] < 0) {
			bb.num[bb.num[0]] *= -1; c = a - bb;
		}
		else if (a.num[a.num[0]] < 0 && b.num[b.num[0]] < 0) {
			a.num[a.num[0]] *= -1; c = bb - a;
		}
		else if (a.num[a.num[0]] < 0 && b.num[b.num[0]] < 0) {
			a.num[a.num[0]] *= -1; bb.num[bb.num[0]] *= -1; c = a + bb; c.num[c.num[0]] *= -1;
		}
		else {
			for (int i = 1; i <= c.num[0]; i++) {
				c.num[i] += num[i] + b.num[i];
				while (c.num[i] >= 10000) {// 进位
					c.num[i] -= 10000;
					c.num[i + 1]++;
				}
			}
			c.num[0]++;
			while (c.num[c.num[0]] == 0)c.num[0]--;
		}
		return c;
	}
	hp operator-(const hp& b)const {
		hp c;
		hp a = *this; hp bb = b;
		if (a.num[0] == 0) {
			bb.num[bb.num[0]] *= -1; return bb;
		} 
		if (b.num[0] == 0)return *this;
		c.num[0] = std::max(num[0], b.num[0]);
		if (a.num[a.num[0]] > 0 && b.num[b.num[0]] < 0) {
			bb.num[bb.num[0]] *= -1; c = a + bb;
		}
		else if (a.num[a.num[0]] < 0 && b.num[b.num[0]] > 0) {
			a.num[a.num[0]] *= -1; c = bb + a; c.num[c.num[0]] *= -1;
		}
		else if (a.num[a.num[0]] < 0 && b.num[b.num[0]] < 0) {
			a.num[a.num[0]] *= -1; bb.num[bb.num[0]] *= -1; c = bb-a; 
		}
		else {
			if (a == bb) { memset(c.num, 0, sizeof(c.num)); return c; }
			else if (bb > a) { c = bb-a; c.num[num[0]] *= -1; }
			else {
				for (int i = 1; i <= c.num[0]; i++) {
					c.num[i] += a.num[i] - bb.num[i];
					while (c.num[i] >= 10000) {// 进位
						c.num[i] -= 10000;
						c.num[i + 1]++;
					}
					while (c.num[i] < 0) { c.num[i] += 10000; c.num[i + 1]--; }
				}
				c.num[0]++;
				while (c.num[c.num[0]] == 0)c.num[0]--;
			}
		}
		return c;
	}
	hp operator*(const hp& b)const {
		hp c; hp a = *this; hp bb = b; int fh = 1;
		if (num[0] == 0 || b.num[0] == 0)return c;
		if (a.num[a.num[0]] < 0)fh *= -1, a.num[a.num[0]] *= -1;
		if (bb.num[bb.num[0]] < 0)fh *= -1, bb.num[bb.num[0]] *= -1;
		c.num[0] = a.num[0] + bb.num[0] + 1;
		for (int i = 1; i <= a.num[0]; i++) {
			for (int j = 1; j <= bb.num[0]; j++) {
				c.num[i + j - 1] += a.num[i] * bb.num[j];            // 和小学竖式的算法一模一样
				c.num[i + j] += c.num[i + j - 1] / 10000;            // 进位
				c.num[i + j - 1] %= 10000;
			}
		}
		while (c.num[c.num[0]] == 0 && c.num[0] >= 1) c.num[0]--;    // 99999999*0
		c.num[c.num[0]] *= fh;
		return c;
	}
	hp operator/(const hp& b)const {
		hp c, d;
		hp aa = *this; hp bb = b; int fh = 1;
		if (bb.num[num[0]] < 0)bb.num[num[0]] *= -1;
		if (aa.num[num[0]] < 0)aa.num[num[0]] *= -1, fh *= -1;
		c.num[0] = aa.num[0] - bb.num[0] + 1; if (c.num[0] <= 0) { c.num[0] = 0; return c; }
		d.num[0] = 0;
		for (int i = aa.num[0]; i >= 1; i--) {
			// 以下三行的含义是：d=d*10000+num[i];
			memmove(d.num + 2, d.num + 1, sizeof(d.num) - sizeof(int) * 2);
			d.num[0]++;
			d.num[1] = aa.num[i];

			// 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
			// 注意，这里是二分优化后除法和朴素除法的区别！
			int left = 0, right = 9999, mid;
			while (left < right) {
				mid = (left + right) / 2;
				if (bb * hp(mid) <= d) left = mid + 1;
				else right = mid;
			}
			c.num[i] = right - 1;
			d = d - bb * hp(right - 1);
		}
		while (c.num[c.num[0]] == 0 && c.num[0] >= 1) c.num[0]--;    // 99999999/99999999
		while (d.num[d.num[0]] == 0 && d.num[0] >= 1) d.num[0]--;
		if (d.num[0] != 0 && fh == -1) { d = bb - d; c.num[c.num[0]] *= -1; c -= 1; }
		return c;
	}
	hp operator%(const hp& b)const {
		hp c, d;
		hp aa = *this; hp bb = b; int fh = 1;
		if (bb.num[num[0]] < 0)bb.num[num[0]] *= -1;
		if (aa.num[num[0]] < 0)aa.num[num[0]] *= -1, fh *= -1;
		c.num[0] = aa.num[0] - bb.num[0] + 1; if (c.num[0] <= 0) { c.num[0] = 0; return c; }
		d.num[0] = 0;
		for (int i = aa.num[0]; i >= 1; i--) {
			// 以下三行的含义是：d=d*10000+num[i];
			memmove(d.num + 2, d.num + 1, sizeof(d.num) - sizeof(int) * 2);
			d.num[0]++;
			d.num[1] = aa.num[i];

			// 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
			// 注意，这里是二分优化后除法和朴素除法的区别！
			int left = 0, right = 9999, mid;
			while (left < right) {
				mid = (left + right) / 2;
				if (bb * hp(mid) <= d) left = mid + 1;
				else right = mid;
			}
			c.num[i] = right - 1;
			d = d - bb * hp(right - 1);
		}
		while (c.num[c.num[0]] == 0 && c.num[0] >= 1) c.num[0]--;    // 99999999/99999999
		while (d.num[d.num[0]] == 0 && d.num[0] >= 1) d.num[0]--;
		if (d.num[0] != 0 && fh == -1) { d = bb - d; c.num[c.num[0]] *= -1; c -= 1; }
		return d;
	}
	hp& operator+=(const hp& b) { return *this = *this + b; }
	hp& operator-=(const hp& b) { return *this = *this - b; }
	hp& operator*=(const hp& b) { return *this = *this * b; }
	hp& operator/=(const hp& b) { return *this = *this / b; }
	hp& operator%=(const hp& b) { return *this = *this % b; }
	//输入输出
	void hp_cout() {
		std::cout << num[num[0]];
		for (int i = num[0] - 1; i >= 1; i--) {
			std::cout.width(4);
			std::cout.fill('0');
			std::cout << num[i];
		}
	}
	hp& hp_cin() {
		std::string s; std::cin >> s;
		return *this = s;
	}
	
};
std::ostream& operator<<(std::ostream& o, hp& n) {
	o << n.num[n.num[0]];
	for (int i = n.num[0] - 1; i >= 1; i--) {
		o.width(4);
		o.fill('0');
		o << n.num[i];
	}
	return o;
}
std::istream& operator>>(std::istream& in, hp& n) {
	std::string s;
	in >> s;
	n = s;
	return in;
}  
const hp hp_0;

class fraction {//分子numerator;分母denominator;符号sign
public:
	long long numerator, denominator, sign;
	//初始化部分
	fraction(long long a, long long b, long long c) :numerator(a), denominator(b), sign(c) {
		long long tmp = gcd(numerator, denominator);
		numerator /= tmp; denominator /= tmp;
	};
	fraction& operator=(std::string ss) {
		numerator = 0; denominator = 1; sign = 1;
		int c = ss.length();
		int cnt = 0;
		for (cnt = 0; cnt < c; cnt++) {
			if (ss[cnt] == '/') break;
		}
		numerator = std::stoll(ss.substr(0,cnt));
		denominator = std::stoll(ss.substr(cnt + 1, c - cnt - 1));
		if (numerator < 0){ numerator *= -1; sign *= -1; }
		if(denominator < 0){ denominator *= -1; sign *= -1; }
		long long tmp = gcd(numerator, denominator);
		numerator /= tmp; denominator /= tmp;
		return *this;
	}
	fraction() { numerator = 0; denominator = 1; sign = 1; }
	//大小比较部分
	bool operator >(const fraction& b)const {
		if (sign* b.sign < 0)return sign > 0;
		else if (sign > 0) { return numerator * b.denominator > denominator * b.numerator; }
		else if(sign<0){ return numerator * b.denominator < denominator * b.numerator; }
	}
	bool operator<(const fraction& b)const { return b > *this; }
	bool operator<=(const fraction& b)const { return !(*this > b); }
	bool operator>=(const fraction& b)const { return !(b > *this); }
	bool operator!=(const fraction& b)const { return (b > *this) || (*this > b); }
	bool operator==(const fraction& b)const { return !(b > *this) && !(*this > b); }
	//四则运算部分
	fraction operator+(const fraction& b)const {
		fraction c; c.numerator = numerator * b.denominator * sign + denominator * b.numerator * b.sign;
		c.denominator = b.denominator * denominator;
		if (c.numerator < 0) { c.numerator *= -1; c.sign = -1; }
		else c.sign = 1;
		long long tmp = gcd(c.numerator, c.denominator);
		c.numerator /= tmp; c.denominator /= tmp;
		return c;
	}
	fraction operator-(const fraction& b)const {
		fraction c = b; c.sign *= -1; return *this + c;
	}
	fraction operator*(const fraction& b)const {
		fraction c; c.sign = sign * b.sign;
		c.numerator = numerator * b.numerator; c.denominator = denominator * b.denominator;
		long long tmp = gcd(c.numerator, c.denominator);
		c.numerator /= tmp; c.denominator /= tmp;
		return c;
	}
	fraction operator/(const fraction& b)const {
		fraction c = b; std::swap(c.denominator, c.numerator); return *this * c;
	}
	fraction operator+=(const fraction& b)const { return *this + b; }
	fraction operator-=(const fraction& b)const { return *this - b; }
	fraction operator*=(const fraction& b)const { return *this * b; }
	fraction operator/=(const fraction& b)const { return *this / b; }
	//输入输出
	double fraction_value() {
		double A = numerator*1.0*sign / denominator; return A;
	}
	void fraction_cout() {
		if (sign == -1)std::cout << '-';
		std::cout << numerator<<'/'<<denominator;
	}
	fraction& fraction_cin() {
		std::string s; std::cin >> s;
		return *this = s;
	}
};
const fraction fraction_0(0, 1, 1);


class hp_fraction {//分子numerator;分母denominator;符号sign
public:
	hp numerator, denominator;int sign;
	//初始化部分
	hp_fraction(hp a, hp b, int c) :numerator(a), denominator(b), sign(c) {
		hp tmp = gcd(numerator, denominator);
		numerator /= tmp; denominator /= tmp;
	};
	hp_fraction& operator=(std::string ss) {
		numerator = 0; denominator = 1; sign = 1;
		int c = ss.length();
		int cnt = 0;
		for (cnt = 0; cnt < c; cnt++) {
			if (ss[cnt] == '/') break;
		}
		numerator = std::stoll(ss.substr(0, cnt));
		denominator = std::stoll(ss.substr(cnt + 1, c - cnt - 1));
		if (numerator < hp_0) { numerator *= -1; sign *= -1; }
		if (denominator < hp_0) { denominator *= -1; sign *= -1; }
		hp tmp = gcd(numerator, denominator);
		numerator /= tmp; denominator /= tmp;
		return *this;
	}
	hp_fraction() { numerator = hp_0; denominator = 1; sign = 1; }
	//大小比较部分
	bool operator >(const hp_fraction& b)const {
		if (sign* b.sign < 0)return sign > 0;
		else if (sign > 0) { return numerator * b.denominator > denominator * b.numerator; }
		else if (sign < 0) { return numerator * b.denominator < denominator* b.numerator; }
	}
	bool operator<(const hp_fraction& b)const { return b > *this; }
	bool operator<=(const hp_fraction& b)const { return !(*this > b); }
	bool operator>=(const hp_fraction& b)const { return !(b > *this); }
	bool operator!=(const hp_fraction& b)const { return (b > *this) || (*this > b); }
	bool operator==(const hp_fraction& b)const { return !(b > *this) && !(*this > b); }
	//四则运算部分
	hp_fraction operator+(const hp_fraction& b)const {
		hp_fraction c; c.numerator = numerator * b.denominator * sign + denominator * b.numerator * b.sign;
		c.denominator = b.denominator * denominator;
		if (c.numerator < hp_0) { c.numerator *= -1; c.sign = -1; }
		else c.sign = 1;
		hp tmp = gcd(c.numerator, c.denominator);
		c.numerator /= tmp; c.denominator /= tmp;
		return c;
	}
	hp_fraction operator-(const hp_fraction& b)const {
		hp_fraction c = b; c.sign *= -1; return *this + c;
	}
	hp_fraction operator*(const hp_fraction& b)const {
		hp_fraction c; c.sign = sign * b.sign;
		c.numerator = numerator * b.numerator; c.denominator = denominator * b.denominator;
		hp tmp = gcd(c.numerator, c.denominator);
		c.numerator /= tmp; c.denominator /= tmp;
		return c;
	}
	hp_fraction operator/(const hp_fraction& b)const {
		hp_fraction c = b; std::swap(c.denominator, c.numerator); return *this * c;
	}
	hp_fraction operator+=(const hp_fraction& b)const { return *this + b; }
	hp_fraction operator-=(const hp_fraction& b)const { return *this - b; }
	hp_fraction operator*=(const hp_fraction& b)const { return *this * b; }
	hp_fraction operator/=(const hp_fraction& b)const { return *this / b; }
	//输入输出
	void hp_fraction_cout() {
		if (sign == -1)std::cout << '-';
		numerator.hp_cout(); std::cout << '/'; denominator.hp_cout();
	}
	hp_fraction& hp_fraction_cin() {
		std::string s; std::cin >> s;
		return *this = s;
	}
};
const hp_fraction hp_fraction_0(0, 1, 1);