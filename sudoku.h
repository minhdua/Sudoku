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
		Sudoku(Sudoku &s);//xay dung sao chep
		~Sudoku(){};//phuong thuc huy
		int GetLevel() {return level;}//lay level
		int GetNum(int x,int y) {return s[x][y].num;}//lay gia tri tai o x,y
		int SetNum(int x,int y,int z) {s[x][y].num=z;}//Dat gia tri tai o x,y
		int SetLevel(int newlevel) {level=newlevel;}//Dat level
		int GetColor(int x, int y){return s[x][y].color;}//Lay mau tai o x,y
		int SetColor(int x,int y,int c){s[x][y].color=c;}//dat may tai o x,y
		void Erase(int x,int y);// xoa gia tri trong bang tai o x,y
		void Clear();//xoa tat ca cac phan tu trong o
		void SetMarkRow(int x,int z){markrow[x]=z;}//Dat gia tri cho hang x
		void SetMarkCol(int y,int z){markcol[y]=z;}//Dat gia tri cho cot y
		void SetMarkBlock(int t,int z){markblock[t]=z;}//Dat gia tri cho lo t
		int GetMarkRow(int x){return markrow[x];}//Lay gia tri cho hang x
		int GetMarkCol(int y){return markcol[y];}//Lay gia tri cho cot y
		int GetMarkBlock(int t){return markblock[t];}//Lay gia tri cho lo t
		bool CheckRow(int x,int z) { return (markrow[x]&(1<<(z-1)));}//kiem tra hang
		bool CheckCol(int y,int z) { return (markcol[y]&(1<<(z-1)));}//kiem tra cot
		bool CheckBlock(int x,int y,int z){ return (markblock[x/3*3+y/3]&(1<<(z-1)));}//kiem tra lo
		bool Check(int x,int y,int z);//kiem tra hang x da co chua gia tri z hay chua
		void OnBitRow(int x,int z){(markrow[x]|=(1<<(z-1)));}//Bat bit thu z cua hang x
		void OnBitCol(int y,int z){(markcol[y]|=(1<<(z-1)));}//Bat bit thu z cua cot y
		void OnBitBlock(int x,int y,int z){(markblock[x/3*3+y/3]|=(1<<(z-1)));}//Bat bit thu z cua lo x/3*3+y
		void OffBitRow(int x,int z){markrow[x]&= (~(1<<(z-1)));}//tat bit thu z cua hang x
		void OffBitCol(int y,int z){markcol[y]&= (~(1<<(z-1)));}//tat bit thu z cua cot y
		void OffBitBlock(int x,int y,int z){markblock[x/3*3+y/3]&= (~(1<<(z-1)));}//tat bit thu z cua lo x/3*3+y/3
		void OnBit(int x,int y,int z);//danh dau gia tri z da co tai o x,y
		void OffBit(int x,int y,int z);//danh dau gia tri z da co tai o x,y
		void GenerateBoard();//Sinh ngay nhien mot bang sudoku
		void PlayerSolveSudoku();//Nguoi choi giai quyet Sudoku
		bool ComputerSolveSudoku(int x,int y);//May giai quyet sudoku
		void NewDisplay();
		void DisplayRowSudoku(int i);
		void DisplaySudoku();//Hien thi sudoku
		bool NextBlank(int &x,int &y);
		const int* operator [] (unsigned int i) const;//qua tai toan tu
		int* operator [] (unsigned int i);//qua tai toan tu
	public:
		Cell s[9][9];//bang sudoku
		int markrow[9];//danh dau 1 so da co trong hang
		int markcol[9];//danh dau 1 so da co trong cot
		int markblock[9];//danh dau 1 so da cos trong lo
		int level;// do kho cua sudoku
};
#endif // SUDO_H
