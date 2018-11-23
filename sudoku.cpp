#include "sudoku.h"
#include "console.cpp"
#define RED 4
#define WHITE 7
#define KHO 25
#define TB  20
#define DE  15
	
/* XAY DUNG MAC NHIEN
  * Khoi tao cac gia tri la 0
  * Khoi tao cac mang danh dau la 0
  * Thiet lap level mat dinh
*/
Sudoku::Sudoku(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s[i][j].num=0;
			s[i][j].color=WHITE;
		}
	}
	level=DE;
}
/* 	LAM SACH TAT CAC CAC O SUDOKU
	*
*/
void Sudoku::Clear(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s[i][j].num=0;
			s[i][j].color=WHITE;
		}
	}
}
/* 	DAT LEVEL
	*
*/
void Sudoku::SetLevel(){
	char c;
	int newlevel;
	cout<<"===== THIET LAP DO KHO ======"<<endl<<endl;
	cout<<"	1. De !"<<endl;
	cout<<"	2. Trung binh !"<<endl;
	cout<<"	3. Kho !"<<endl;
	cout<<"	4. Tuy chinh!"<<endl;
	cout<<"	Phim khac de thoat"<<endl<<endl;
	cout<<"nhap Lua cho cua ban: ";
	c=getch();
	clrscr();
	switch (c) {
		case '1':
			newlevel=KHO;
			break;
		case '2':
			newlevel=TB;
			break;
		case '3':
			newlevel=DE;
			break;
		case '4':
			cout<<"Thiet lap so luong duoc sinh ra: ";
			cin>>newlevel;
			break;
		default: return;
	}
	level=newlevel;	
}
/* KIEM TRA HANG
	* Tra ve true neu z chua ton tai trong hang x
	* Tra ve false trong truong hop nguoc lai
*/
bool Sudoku::CheckRow(int x,int z){
	for(int i=0;i<9;i++)
		if(s[x][i].num==z) return false;
	return true;
}
/* KIEM TRA COT
	* Tra ve true neu z chua ton tai trong cot y
	* Tra ve false trong truong hop nguoc lai 
*/
bool Sudoku::CheckCol(int y,int z){
	for(int i=0;i<9;i++)
		if (s[i][y].num==z) return false;
	return true;
}
/* KIEM TRA LO
	* Tra ve true neu trong lo x-x%3, y-y%3 chua ton tai z
	* Tra ve false trong truong truong hop nguoc lai
*/
bool Sudoku::CheckBlock(int x,int y,int z){
	x=x-x%3;
	y=y-y%3;
	for(int i=x;i<x+3;i++)
		for (int j=y;j<y+3;j++)
			if (s[i][j].num==z) return false;
	return true;
}
/*	KIEM TRA HOP LE
	* Tra ve true neu kiem tra hang, cot, lo deu hop le
	* Tra ve false trong truong hop nguoc lai
*/
bool Sudoku::Check(int x,int y,int z){
	return (CheckRow(x,z) && CheckCol(y,z) && CheckBlock(x,y,z));
}
/* KIEM TRA O TRONG
	* Tra ve false neu khong con o nao trong
	* Tra ve true va hang x cot y trong truong hop nguoc lai
*/
bool Sudoku::NextBlank (int &x, int &y){
	 while(x<9&& s[x][y].num!=0){
	 	x= x+(y+1)/9;
	 	y= (y+1)%9;
	 }
	 if(x<9) return true;
	 else return false;
}
/* SINH SUDOKU NGAU NHIEN
	*	Sinh ngau nhien toa do x,y va gia tri z
	*	Neu o(x,y) =0 va gia tri z hop le thi them z vao
	* 	Dat mau o (x,y)= Do
*/
void Sudoku::Generate(){
	srand(time(0));
	int x,y,z;
	int i=0;
	while(i<level){
		x=rand()%9;	//x ngau nhien tu 0 den 8
		y=rand()%9;	//y ngau nhien tu 0 den 8
		z=1+rand()%9;//z ngau nhien tu 1 den 9
		//neu o trong va vi tri an toan thi them vao
		if(s[x][y].num == 0 && Check(x,y,z)){ //neu o chua co gia tri va gia tri z la hop le
			s[x][y].num= z; // dat o(x,y) co gia tri z
			s[x][y].color= RED; // dat o(x,y) co mau do
			i++; // i la so luong phan tu da duoc sinh ra
		}
	}
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

bool Sudoku::Player(){
	int x,y,z,x0=0,y0=0;
	bool exit=false;
	do{
		cout<<"nhap toa do x y va z , nhap  -1 de thoat !"<<endl;
		cout<<"lua chon cua ban: ";
		cin>>x>>y>>z;
		if(x==-1||y==-1||z==-1) exit=true;
		else
			if(x>=0 && y>=0 && z>=0 && x<9 && y<9 && x<=9){
				if(s[x][y].color==WHITE){
					if (z==0) s[x][y].num=0;
					else
					if(Check(x,y,z))
					{
						s[x][y].num=z;
						exit=!NextBlank(x0,y0);
					}else cout<<"Gia tri da ton tai! "<<endl;//Kiem tra tinh hop le cua so nhap vao
					clrscr();
					Display();
				}else cout<<"Vi tri khong cho phep! "<<endl;//Kiem tra o nhap co hop le khong
			}else cout<<"Toa do hoac gia tri khong hop le! "<<endl;//Kiem tra toa do nhap vao
	}while(!exit);
	return !NextBlank(x0,x0);
}
/* MAY CHOI
	*co 2 doi so x,y
	* Neu khong con o trong thi ngung
	* Neu con o trong thi lay 1 gia tri hop le trong mien gia tri 1-9
	* Neu gia tri do hop le thi gan vao o (x,y). thuc hien de quy doi voi o trong tiep theo
	* Neu khong co gia tri hop le thi tra ve false. thuc hien quay lui de thay do phuong an da chon truoc do
*/

bool Sudoku::Computer(int x,int y){
	if(NextBlank(x,y)==false) return true;
	for(int z=1;z<=9;z++){
		if(Check(x,y,z)){
			s[x][y].num=z; // gan gia tri z
			if(Computer(x,y)) return true;
			s[x][y].num=0;// quay lui
		}
	}
	return false;
}
/* HIEN THI HANG THU I TRONG LUOI SUDOKU
  *	Hien thi chi muc cot
  *	Hien thi vung 3x3
*/
void Sudoku::RawRowSudoku(int i){
	cout<<i-1<<" |";
	for(int j=1;j<=9;j++){
		TextColor(s[i-1][j-1].color);
		if(s[i-1][j-1].num==0) cout<<" .";
			else cout<<" "<<s[i-1][j-1].num;
		TextColor(WHITE);
		if (j%3==0) cout<<" |";	
	}
	cout<<endl;
}
/* HIEN THI SUDOKU
	* Chi muc cot
	* Dong phan cach lo
	* Hien thi hang thu i trong luoi sudoku	
*/
void Sudoku::Display(){
	cout<<endl;
	string lineindex="    0 1 2   3 4 5   6 7 8\n"; // chi muc cot
	string lineblock="  +-------+-------+-------+\n"; // dong phan cach lo
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

/* QUA TAI TOAN TU GAN
	* gan gia tri va mau o tuong ung
  	* gan level
*/
void Sudoku::operator = (const Sudoku &other){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s[i][j].num=other.s[i][j].num;
			s[i][j].color=other.s[i][j].color;
		}
	}
	level=other.level;//dat level tuong ung
} 
/* QUA TAI TOAN TU XUAT
	* gia tri cac o trong
  	* moi o trong xuat 3 bo so x,y,z
*/
ostream & operator << (ostream &output,const Sudoku &other){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(other.s[i][j].color==WHITE&& other.s[i][j].num!=0){
					output<<" "<<i<<" "<<j<<" "<<other.s[i][j].num;
			}
	cout<<endl;
} 
/* QUA TAI TOAN TU NHAP
	* gia tri cua o la '.' thi tuong ung voi gia tri 0
  	* nguoc lai thi co gia tri tuong ung
*/
istream &operator >> (istream &input,Sudoku &other){
	char c;
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			cin>>c;
			if (c!='.' && other.Check(i,j,c-48)) {
				other.s[i][j].num=c-48;
				other.s[i][j].color=RED;
			}else {
				other.s[i][j].num=0;
				other.s[i][j].color=WHITE;
			}	
	}
}

