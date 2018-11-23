/*tao mot class sudoku*/
#ifndef  SUDO_H
#define SUDO_H
#include <bits/stdc++.h>
using namespace std;
typedef struct Cell {
	int num;
	int color;
};
class Sudoku {
	public:
		Sudoku();//xay dung mac nhien
		~Sudoku(){};//phuong thuc huy
		void SetLevel();//dat level
		void Clear();// lam sach soduku
		bool CheckRow(int x,int z);// kiem tra hang
		bool CheckCol(int y,int z);// kiem tra cot
		bool CheckBlock(int x,int y,int z); // kiem tra khoi
		bool Check(int x,int y,int z);// kiem tra hang hop le
		bool NextBlank(int &x,int &y);// lay o trong ke tiep
		void Generate();//Sinh ngay nhien mot bang sudoku
		bool Player();//Nguoi choi giai quyet Sudoku
		bool Computer(int x,int y);//May giai quyet sudoku
		void RawRowSudoku(int i);//Xuat ra man hinh hang thu i sudoku
		void Display();//Hien thi sudoku`
		void operator = (const Sudoku &s);// Qua tai toan tu gan
		friend ostream & operator << (ostream &output,const Sudoku &s);// Qua tai toan tu nhap
		friend istream & operator >> (istream &input,Sudoku &s);// Qua tai toan tu xuat
	private:
		Cell s[9][9];//luoi sudoku
		int level;// do kho
};
#endif // SUDO_H
