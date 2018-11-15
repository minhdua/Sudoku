#include "sudoku.h"
#include "console.cpp"
#define FIXED 4
#define DEFAULT 7
#define LEVEL 20
/* Phuong thuc xay dung mac nhien
  * Khoi tao cac gia tri la 0
  * Khoi tao cac mang danh dau la 0
  * Thiet lap level mat dinh
*/
Sudoku::Sudoku(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s[i][j].num=0;
			s[i][j].color=DEFAULT;
		}
	}
	for(int i=1;i<=9;i++){
		mark[i]=0;
	}
	level=LEVEL;
}
/* PHUONG THUC XAY DUNG SAO CHEP
	* sao chep so va mau tu bang s
  	* sao chep level
  	* sao chep tat ca gia tri cua cac nhom
*/
Sudoku::Sudoku(Sudoku &other){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s[i][j].num=other.GetNum(i,j);
			s[i][j].color=other.GetColor(i,j);
		}
	}
	for(int i=1;i<=9;i++) mark[i]=other.GetMark(i);
	level=other.GetLevel();//dat level tuong ung
}
/* DAT GIA TRI
	*Dat gia tri z vao o x y
	*Bat cac bit o vi tri z tu cac hang, cot va cac lo
*/
int Sudoku::SetNum(int x,int y,int z) {
	s[x][y].num=z;
	OnBit(x,y,z);
}
/* XOA GIA TRI
	*Xoa gia tri trong o x y
	*Tat cac bit co gia tri tai o x,y
*/
void Sudoku::Erase(int x,int y){
	int z=s[x][y].num;
	if (z!=0){
		OffBit(x,y,z);
		s[x][y].num=0;
		s[x][y].color=DEFAULT;
	}
}
/* LAM SACH SUDOKU
  * Xoa cac gia tri trong o x,y
  * Dat gia tri mau mat dinh
*/
void Sudoku::Clear(){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++) Erase(i,j);
}
/* SINH GIA TRI NGAU NHIEN
	*sinh ngau nhien hang x, cot y voi gia tri z
	*kiem tra gia tri z khi them vao o x,y
	*danh dau hang, cot, lo voi gia tri z
	*thay doi mau trang sang mau do
*/
void Sudoku::Generate(){
	srand(time(0));
	int x,y,z;
	int i=0;
	while(i<level){
		x=rand()%9;		//x la chi so hang co gia tri tu 0 den 8
		y=rand()%9;		//y la chi so cot co gia tri tu 0 den 8
		z=1+rand()%9;	//z la so trong o gia tri tu 1 den 9
		//neu o trong va vi tri an toan thi them vao
		if(GetNum(x,y)==0&&Check(x,y,z)){ //neu o chua co gia tri va gia tri z la hop le
			SetNum(x,y,z);//dat gia tri z
			SetColor(x,y,FIXED); // dat mau co dinh
			i++;
		}
	}
}
void Sudoku::NewDisplay(){
	clrscr();
	Display();
}
/* HIEN THI SUDOKU
	*nhap -1 de thoat
 	*Nhap toa do x,y,z
 	*Thiet lap rang buoc cho gia tri nhap vao, toa do 0-8, gia tri 1-9
 	*Kiem tra gia tri z khi nhap vao o x,y
 	*Neu khong hop le thi bao loi
 	*Neu o nhap vao co mau do thi bao loi
 	*Neu o nhap vao khong co mau do thi xoa gia tri o do roi them gia tri moi vao
 	*Neu z = 0 thi xoa o do
 	
*/

void Sudoku::PlayerSolveSudoku(){
	int x,y,z;
	Display();
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
void Sudoku::RawRowSudoku(int i){
	cout<<i-1<<" |";
	for(int j=1;j<=9;j++){
		TextColor(GetColor(i-1,j-1));
		if(GetNum(i-1,j-1)==0) cout<<" .";
			else cout<<" "<<GetNum(i-1,j-1);
		TextColor(DEFAULT);
		if (j%3==0) cout<<" |";	
	}
	cout<<endl;
}
/*
	*ve 	
*/
void Sudoku::Display(){
	string lineindex="    0 1 2   3 4 5   6 7 8\n";
	string lineblock="  +-------+-------+-------+\n";	
	for(int i=0;i<=9;i++){
		if(i%3==0){
			if (i==0){
				cout<<lineindex;
				cout<<lineblock;
			}
			else {
				RawRowSudoku(i);
				cout<<lineblock;
			}
		}else RawRowSudoku(i);
	}
}
int main(){
	Sudoku s;
	s.Generate();
	s.Display();
	Sudoku s1(s);
	s1.PlayerSolveSudoku();
	Sudoku s2(s);
	if (s2.ComputerSolveSudoku(0,0)) s2.Display();
	else cout<<"Khong tim ra giai phap !";
}

