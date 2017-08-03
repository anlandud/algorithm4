/*
@author :anlan
time :2017-8-3
*/

//算法4 第一个类c++实现
//有了第一个，第二个就很容易写了

/*
importance ： 我不清楚我是否会意错了题目，
但根据自己的理解与翻译还是写出了这个类，
具体的实现就没写了
*/
#include<iostream>
using namespace std;

#define close 25536 

class percolation {
public:
	percolation(int N);               // create N-by-N grid, with all sites blocked  
	void open(int i, int j);          // open site (row i, column j) if it is not open already  
	bool isOpen(int i, int j);     // is site (row i, column j) open?  
	bool isFull(int i, int j);     // is site (row i, column j) full?  
	bool percolates();             // does the system percolate?  
	int find(int i, int j);		//将此点连接到上一个点的root并返回root
private:
	int n;	//正方形的边长
	int *num;		//一维数组
};

percolation::percolation(int N){
	if (N < 0)
		throw;
	else {
		this->n = N;
		int sum = N*N+1;
		this->num = new int[sum];
		int i = 0;
		while (i < sum) {
			this->num[i] = close;
		}
		this->num[sum] = -1;	//顶部单元
	}		//初始化一维数组
}

//只需要返回该点的开闭状态值
bool percolation::isOpen(int i,int j) {
	if (num[i*this->n + j] == close)
		return 0;
	else
		return 1;
}

int percolation::find(int i, int j) {
	int HelpPoint = close, preHelpPoint = close;
	int CurrentPoint = i*(this->n) + j;
	while (this->num[CurrentPoint - this->n] != (close | this->n)) {
		HelpPoint = this->num[CurrentPoint];
		preHelpPoint = CurrentPoint;
		CurrentPoint = this->num[CurrentPoint];
	}		//找到此时的点的上面的那个点的root
	CurrentPoint = i*(this->n) + j;
	if (HelpPoint == this->n)
		this->num[CurrentPoint] = HelpPoint;
	else
		this->num[CurrentPoint] = preHelpPoint;
	return this->num[CurrentPoint];
}

//判断该点是否打开，如果打开则结束。未打开则与上下左右四个点连接
void percolation::open(int i, int j) {
	if (this->isOpen(i, j) == 1)
		throw;
	else {
		int rootL = close, rootR = close, rootD = close, root = close;
		int CurrentPoint = i*(this->n) + j;
		if (i == 0) {//第一排
			this->num[CurrentPoint] = this->n;
			this->num[CurrentPoint + this->n] = this->n;	//下边
			if (j == 0) {
				this->num[CurrentPoint + 1] = this->n;		//右边
			}
			else if (j == this->n - 1) {
				this->num[CurrentPoint - 1] = this->n;		//左边
			}
			else {
				this->num[CurrentPoint - 1] = this->n;		//左边
				this->num[CurrentPoint + 1] = this->n;		//右边
			}
		}
		else if (i == this->n - 1) {//最后一排
			root = find(i, j);	//上边
			if (j == 0) {
				rootR = find(i, j+1);
				if (rootD < root) {
					this->num[this->num[CurrentPoint]] = rootD;
					root = rootD;
				}
				else 
					this->num[this->num[CurrentPoint + 1]] = root;
			}	//右边
			else if (j == this->n - 1) {
				rootL = find(i, j-1);
				if (rootL < root) {
					this->num[this->num[CurrentPoint]] = rootL;
					root = rootL;
				}
				else
					this->num[this->num[CurrentPoint + 1]] = root;
			}	//左边
		}
		else if (j == 0) {//第一列(除去第一排和最后一排)
			root = find(i, j);	//上边
			this->num[CurrentPoint + this->n] = root;		//下边
			rootR = find(i, j+1);
			if (rootD < root) {
				this->num[this->num[CurrentPoint]] = rootD;
				root = rootD;
			}
			else
				this->num[this->num[CurrentPoint + 1]] = root;	//右边
		}
		else if (j == this->n - 1) {//最后一列(除去第一排和最后一排)
			root = find(i, j);	//上边
			this->num[CurrentPoint + this->n] = root;		//下边
			rootL = find(i, j - 1);
			if (rootL < root) {
				this->num[this->num[CurrentPoint]] = rootL;
				root = rootL;
			}
			else
				this->num[this->num[CurrentPoint - 1]] = root;	//左边
		}
		else{
			root = find(i, j);	//上边
			this->num[CurrentPoint + this->n] = root;		//下边
			rootR = find(i, j + 1);
			if (rootD < root) {
				this->num[this->num[CurrentPoint]] = rootD;
				root = rootD;
			}
			else
				this->num[this->num[CurrentPoint + 1]] = root;	//右边
			rootL = find(i, j - 1);
			if (rootL < root) {
				this->num[this->num[CurrentPoint]] = rootL;
				root = rootL;
			}
			else
				this->num[this->num[CurrentPoint - 1]] = root;	//左边
		}
	}
}

//判断该点是否与顶部联通。
bool percolation::isFull(int i, int j) {
	int judge = close;
	int CurrentPoint = i*n + j;
	while (this->num[CurrentPoint] != (close | this->n - 1)) {
		judge = this->num[CurrentPoint];
		CurrentPoint = this->num[CurrentPoint];
	}
	if (judge == this->n)
		return 1;
	return 0;
}

//判断是否渗漏
bool percolation::percolates()
{
	int judge = close;
	for (int i = this->n - 1; i < this->n; i++) {
		int CurrentPoint = (this->n - 1)*(this->n) + i;
		while (this->num[CurrentPoint] != (close | this->n)) {
			judge = this->num[CurrentPoint];
			CurrentPoint = this->num[CurrentPoint];
		}
		if (judge == this->n)
			return 1;
	}
	return 0;
}


