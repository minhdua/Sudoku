#include "sudoku.h"
#include "console.cpp"
#define FIXED 4
#define DEFAULT 7
#define LEVEL 0
/*
  * tao mot bang Sudoku 9x9 voi cac gia tri la 0
  * mau mat dinh cua moi o la mau trang 15
  * level mat dinh la de = 35
  * dat ta ca cac bit trong hang,cot,lo la 0
*/
Sudoku::Sudoku(){
	Clear();
}
/*
	* sao chep so va mau tu bang s
  	* sao chep level
  	* sao chep tap ca gia tri cua cac nhom
*/
Sudoku::Sudoku(Sudoku &other){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			SetNum(i,j,other.GetNum(i,j));
			SetColor(i,j,other.GetColor(i,j));
		}
	}
	level=other.level;
	for(int i=0;i<9;i++){
		SetMarkRow(i,other.GetMarkRow(i));
		SetMarkRow(i,other.GetMarkCol(i));
		SetMarkRow(i,other.GetMarkBlock(i));
	}
}
/*
  * tao mot bang Sudoku 9x9 voi cac gia tri la 0
  * mau mat dinh cua moi o la mau trang 15
  * level mat dinh la de = 35
  * dat ta ca cac bit trong hang,cot,lo la 0
*/
void Sudoku::Clear(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			SetNum(i,j,0);
			SetColor(i,j,DEFAULT);
		}
	}
	SetLevel(LEVEL);
	for(int i=0;i<9;i++){
		SetMarkRow(i,0);
		SetMarkCol(i,0);
		SetMarkBlock(i,0);
	}
}
/*
	*kiem tra gia tri z trong hang x, cot y va lo x/3*y+y/3
	*tra ve true neu gia tri z chua co trong hang x,cot y, lo x/3*3+y/3
	*tra ve false trong truong hop nguoc lai
*/
bool Sudoku::Check(int x,int y,int z){
	return (!CheckRow(x,z) && !CheckCol(y,z) && !CheckBlock(x,y,z));
}
/*
	*Danh dau gia tri z da co trong hang x,cot y, lo x/3*3+y
*/
void Sudoku::OnBit(int x,int y,int z){
	OnBitRow(x,z);
	OnBitCol(y,z);
	OnBitBlock(x,y,z);
}
/*
	*Danh dau gia tri z da co trong hang x,cot y, lo x/3*3+y
*/
void Sudoku::OffBit(int x,int y,int z){
	OffBitRow(x,z);
	OffBitCol(y,z);
	OffBitBlock(x,y,z);
}
/*
	*Xoa gia tri trong o x y
	*Tat cac bit co gia tri tai o x,y
*/
void Sudoku::Erase(int x,int y){
	int z=GetNum(x,y);
	SetNum(x,y,0);
	OffBit(x,y,z);
}
/*
	*sinh ngau nhien hang x, cot y voi gia tri z
	*kiem tra gia tri z khi them vao o x,y
	*danh dau hang, cot, lo voi gia tri z
	*thay doi mau trang sang mau do
*/
void Sudoku::GenerateBoard(){
	srand(time(0));
	int x,y,z;
	int i=0;
	while(i<level){
		x=rand()%9;		//x la chi so hang co gia tri tu 0 den 8
		y=rand()%9;		//y la chi so cot co gia tri tu 0 den 8
		z=1+rand()%9;	//z la so trong o gia tri tu 1 den 9
		//neu o trong va vi tri an toan thi them vao
		cout<<x<<" "<<y<<" "<<z<<endl;
		if(GetNum(x,y)==0&&Check(x,y,z)){
			SetNum(x,y,z);
			SetColor(x,y,FIXED);
			OnBit(x,y,z);
			i++;
		}
	}
}
/*
	*nhap -1 de thoat
 	*Nhap toa do x,y,z
 	*Thiet lap rang buoc cho gia tri nhap vao, toa do 0-8, gia tri 1-9
 	*Kiem tra gia tri z khi nhap vao o x,y
 	*Neu khong hop le thi bao loi
 	*Neu o nhap vao co mau do thi bao loi
 	*Neu o nhap vao khong co mau do thi xoa gia tri o do roi them gia tri moi vao
 	*Neu z = 0 thi xoa o do
 	
*/
void Sudoku::NewDisplay(){
	clrscr();
	DisplaySudoku();
}
void Sudoku::PlayerSolveSudoku(){
	int x,y,z;
	DisplaySudoku();
	do{
		cout<<"nhap toa do x y va z , nhap  -1 de thoat !"<<endl;
		cout<<"lua chon cua ban: ";
		cin>>x;
		if(x>-1){
			cin>>y>>z;
			if(x>=0 && y>=0 && z>=0 && x<9 && y<9 && x<=9){
				if(GetColor(x,y)==DEFAULT){
					if(z==0){
						Erase(x,y);
						NewDisplay();
					} 
					else 
					if(Check(x,y,z))
					{
						Erase(x,y);
						SetNum(x,y,z);
						OnBit(x,y,z);
						NewDisplay();
					}else cout<<"Gia tri da ton tai! "<<endl;//Kiem tra tinh hop le cua so nhap vao
				}else cout<<"Vi tri khong cho phep! "<<endl;//Kiem tra o nhap co hop le khong
			}else cout<<"Toa do hoac gia tri khong hop le! "<<endl;//Kiem tra toa do nhap vao
		}
	}while(x!=-1);
}
/*
	*Tap cac bien: cac o trong (Khong co dinh)
	*Tap mien gia tri: tu 1 den 9
	*Tap cac rang buoc: thoa man trong nhom khong cung
*/
bool Sudoku::NextBlank (int &x, int &y){
	 while(x<9&& GetNum(x,y)!=0){
	 	x= x+(y+1)/9;
	 	y= (y+1)%9;
	 }
	 if(x<9) return true;
	 else return false;
}

bool Sudoku::ComputerSolveSudoku(int x,int y){
	if(NextBlank(x,y)==false) return true;
	for(int z=1;z<=9;z++){
		if(Check(x,y,z)){
			SetNum(x,y,z);
			OnBit(x,y,z);
			if(ComputerSolveSudoku(x,y)) return true;
			Erase(x,y);
		}
	}
	return false;
}
/*
  *Hien thi hang chi muc
  *Hien thi cot chi muc
  *Hien thi vung 3x3
*/
void DisplayIndexCol(){
	for(int i=0;i<=9;i++){
		if(i%3==0){
			if(i==0) cout<<"   ";
			else cout<<" "<<i-1<<"  ";
		}
		else cout<<" "<<i-1;
	}
	cout<<endl;
}
void DisplayLineBlock(){
	for(int i=0;i<=9;i++){
		if(i%3==0){
			if(i==0) cout<<"  +";
			else cout<<"---"<<"+";
		}
		else cout<<"--";
	}
	cout<<endl;
}
void Sudoku::DisplayRowSudoku(int i){
	for(int j=0;j<=9;j++){
		if (j%3==0){
			if(j==0) cout<<i-1<<" |";
			else {
				TextColor(GetColor(i-1,j-1));
				if(GetNum(i-1,j-1)==0) cout<<" . ";
				else cout<<" "<<GetNum(i-1,j-1)<<" ";
				TextColor(DEFAULT);
				cout<<"|";
			}
		}else {
			TextColor(GetColor(i-1,j-1));
			if(GetNum(i-1,j-1)==0) cout<<" .";
				else cout<<" "<<GetNum(i-1,j-1);
			TextColor(DEFAULT);
		}
	}
	cout<<endl;
}
/*
	
}*/
void Sudoku::DisplaySudoku(){	
	for(int i=0;i<=9;i++){
		if(i%3==0){
			if (i==0){
				DisplayIndexCol();
				DisplayLineBlock();
			}
			else {
				DisplayRowSudoku(i);
				DisplayLineBlock();
			}
		}else DisplayRowSudoku(i);
	}
}
/*

*/
int main(){
	Sudoku s;
	s.GenerateBoard();
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(s.GetNum(i,j)==0) cout<<". ";
			else
			cout<< s.GetNum(i,j)<<" ";
		}
		cout<<endl;
	}
	cout<<"=============mau: ============"<<endl;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<< s.GetColor(i,j)<<" ";
		}
		cout<<endl;
	}
	for(int i=0;i<9;i++)
	cout<<s.markblock[i]<<endl;	
	//s.PlayerSolveSudoku();
	s.ComputerSolveSudoku(0,0);
	s.NewDisplay();
}

