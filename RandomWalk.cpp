/*
Excercise.8 Random Walk.
 n x m 배열에서 인접한 8방향의 타일로 이동하는 바퀴벌레가
 모든타일을 적어도 한번씩 지나가는데 걸리는 시간은? 
  
  a) 2<  n,m <= 40 
  b) 다음과 같은 경우에 대하여 실험한다
   (1) n =15, m = 15, 시작점 (9,9)
   (2) n = 39, m= 19, 시작점 (0,0)
  c) 반복실행의 한계를 가진다. 50,000 번째 이동시 종료되야함
  d) 각 실험에 대해 다음 결과를 출려한다.
   (1) 바퀴벌레의 총 이동수
   (2) 마지막 count 배열 ( 즉, 이동의 밀도, 어디어디 가장 많이 방문햇는가)
 */

#include <iostream>	
#include <iomanip>	// setw
#include <stdlib.h> // srand, rand 
#include <time.h>	// time 

using namespace std;

const int imove[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
const int jmove[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
// Implement of 8 direction = {↖, ↑,↗, →, ↘, ↓, ↙, ←};

template <typename T>
class Matrix {
	int row; // n
	int col; // m
	T *count; // How many times has the cockroach visited each tile
public:
	Matrix(int n, int m) {
		row = n+2;
		col = m+2;
		count = new int[row*col];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == 0 || i == row - 1 || j == 0 || j == col - 1){
					count[i*col + j] = -1;
				}else {
					count[i*col + j] = 0;
				}
			}
		}
	}

	Matrix(const Matrix<T>& a) {
		row = a.row;
		col = a.col;
		count = new int[row*col];
		for (int i = 0; i < row*col; i++) {
			count[i] = a.count[i];
		}
	}

	Matrix operator = (const Matrix& a) {
		if (this != &a)
		{
			delete[] count;
			row = a.row;
			col = a.col;
			count = new int[row * col];
			for (int i = 0; i < row * col; i++)
				*(count + i) = *(a.count + i);
		}
		return *this;
	}

	~Matrix() {
		delete[] count;
	}

	int getRow() const {
		return row;
	}
	int getCol()const {
		return col;
	}

	int getCount(int i, int j) {
		return count[i*col + j];
	}

	void upCount(int i, int j) {
		count[i*col + j]++;
	}
	
	bool isEnd() {
		for (int i = 0; i < row*col; i++) {
			if (count[i] == 0)
				return false;
		}
		return true;
	}

	T& operator() (int i, int j) const{ // return value of matrix(row,col)
		return count[i*col + j];
	}

	int display() {
		for (int i = 0; i < row; i++)
		{
			cout << endl;
			for (int j = 0; j < col; j++) {
				cout << setw(5) << count[i*col + j];
			}
		}
		cout << endl;
		return 0;
	}

	// display Matrix emphasizing where the last move was made
	int display(int a, int b) {
		for (int i = 0; i < row; i++)
		{
			cout << endl;
			for (int j = 0; j < col; j++) {
				if (i*col + j == a*col+b) {
					cout << setw(3) <<"'"<< count[i*col + j]<< "'"; 
				}
				else {
					cout << setw(5) << count[i*col + j];
				}
			}
		}
		cout << endl;
		return 0;
	}
};


class Cockroach {
private:
	int ibug;
	int jbug;
public:
	Cockroach(int i, int j) {
		ibug = i;
		jbug = j;
	}

	void move(int k) {
		ibug = ibug + imove[k];
		jbug = jbug + jmove[k];
	}

	template <typename T>
	int moveCheck(int k, Matrix<T> m) {
		move(k);
		if ( m.getCount(ibug,jbug) == -1){	// if last move was invalid (has value of '-1') go back.
			move((k + 4) % 8);				// imove and jmove with index(k+4)%8 have opposite direction of index k
			return 0;
		}
		return 1;
	}

	int getIbug() {
		return ibug;
	}
	int getJbug() {
		return jbug;
	}
};

int main() {
	// case (1)
	Matrix<int> matrix1(15, 15);
	Cockroach cockroach1(10,10);
	matrix1.upCount(cockroach1.getIbug(), cockroach1.getJbug()); // set 'count' of starting point 1
	matrix1.display(10,10);
	
	int moveCount = 0;
	srand(time(NULL));
	int k = 0;
	while (moveCount < 50000) {
		k = rand() % 8;
		if (cockroach1.moveCheck(k, matrix1)) {	// if move was valid plus count
			moveCount++;
			matrix1.upCount(cockroach1.getIbug(), cockroach1.getJbug());
		}

		/* Can check the moves step by step. discomment following two lines */

		//matrix1.display(cockroach1.getIbug(), cockroach1.getJbug());  
		//system("pause");

		if (matrix1.isEnd()) {
			cout << "cockroach1 visited all tiles. test end" << endl;
			break;
		}
	}
	matrix1.display(-1,-1);
	cout << "Total " << moveCount << " times moved " << endl;
	
	// case (2)
	Matrix<int> matrix2(39, 19);
	Cockroach cockroach2(1, 1);
	matrix2.upCount(cockroach2.getIbug(), cockroach2.getJbug());
	matrix2.display(1,1);

	moveCount = 0;
	srand(time(NULL));
	k = 0;
	while (moveCount < 50000) {
		k = rand() % 8;
		if (cockroach2.moveCheck(k, matrix2)){
			moveCount++;
			matrix2.upCount(cockroach2.getIbug(), cockroach2.getJbug());
		}
		// matrix2.display(cockroach2.getIbug(), cockroach2.getJbug());
		// system("pause");
		if (matrix2.isEnd()) {
			cout << "cockroach2 visited all tiles. test end" << endl;
			break;
		}
	}
	matrix2.display();
	cout << "Total " << moveCount << " times moved " << endl;

	system("pause");
	return 0;
}
