/*tao mot class sudoku*/
#ifndef  SUDO_H
#define SUDO_H
#include <bits/stdc++.h>
#define MASH(x,y) ((1<<x)+(1<<(y+9))+(1<<(x/3*3+y/3+18)))
using namespace std;
typedef struct Cell {
	int num;
	int color;
};
class Sudoku {
	public:
		Sudoku();//xay dung mac nhien
		Sudoku(Sudoku &s);//xay dung sao chep
		~Sudoku(){};//phuong thuc huy
		int GetLevel(){return level;}//lay level
		int SetLevel(int newlevel) {level=newlevel;}//Dat level
		int GetNum(int x,int y) {return s[x][y].num;}//lay gia tri tai o x,y
		int SetNum(int x,int y,int z);//Dat gia tri tai o x,y
		int GetColor(int x, int y){return s[x][y].color;}//Lay mau tai o x,y
		int SetColor(int x,int y,int c){s[x][y].color=c;}//dat may tai o x,y
		int GetMark(int i){ return mark[i];} // lay phan thu danh dau thu i
		void Erase(int x,int y);// xoa gia tri trong bang tai o x,y
		void Clear();//xoa tat ca cac phan tu trong o
		bool Check(int x,int y,int z) {return ((mark[z]& (~MASH(x,y)))==mark[z]);}//z co the them vao hang x cot y hay khong
		void OnBit(int x,int y,int z) {mark[z]|= MASH(x,y);}//Bat gia tri z 
		void OffBit(int x,int y,int z){mark[z] &= ~MASH(x,y);};//Tat gia tri z 
		void Generate();//Sinh ngay nhien mot bang sudoku
		void PlayerSolveSudoku();//Nguoi choi giai quyet Sudoku
		bool ComputerSolveSudoku(int x,int y);//May giai quyet sudoku
		void RawRowSudoku(int i);
		void Display();//Hien thi sudoku
		bool NextBlank(int &x,int &y);
		void NewDisplay();
	public:
		Cell s[9][9];//bang sudoku
		int mark[10];
		int level;// do kho cua sudoku
};
#endif // SUDO_H
