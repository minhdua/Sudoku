#include "sudoku.cpp"
void Process(char choose,Sudoku &s){
	Sudoku s1=s;
	switch (choose){
			case '0'://Thoat
				break;
			case '1'://Hien thi
				clrscr();
				s1.Display();
				break;
			case '2'://Do kho
				clrscr();
				s.Clear();
				s.SetLevel();
				s.Generate();
				s.Display();
				break;
			case '3'://Sinh Sudoku
				s.Clear();
				s.Generate();
				s.Display();
				break;
			case '4'://Nguoi choi
				s1.Display();
				if(s1.Player()) cout<<"Chuc mung ban da hoan thanh! "<<endl;
				else cout<<"Ban da khong hoan thanh !"<<endl;
				break;
			case '5'://May choi
				if(s1.Computer(0,0)) s1.Display();
				else cout<<"Khong tim thay ket qua !"<<endl;
				break;
			case '6'://Nhap sudoku
				cout<<"Nhap sudoku cua ban !"<<endl;
				s.Clear();
				cin>>s;
				clrscr();
				cout<<"Sudoku vua nhap! "<<endl;
				s.Display();
				break;
			case '7'://Xuat sudoku
				if(s1.Computer(0,0)) {
					cout<<"Cac buoc thuc hien la: "<<endl;
					cout<<s1;
				}
				else cout<<"Khong the thuc hien: "<<endl;
				break;
		}
}
void Menu(Sudoku s){
	char choose;
	do{
		cout<<"===== CHUONG TRINH DEMO - TRI TUE NHAN TAO ======"<<endl<<endl;
		cout<<"	0. Thoat !"<<endl;
		cout<<"	1. Hien Thi !"<<endl;
		cout<<"	2. Thiet Lap Do Kho !"<<endl;
		cout<<"	3. Sinh moi Sudoku! "<<endl;
		cout<<"	4. Nguoi Giai Sudoku !"<<endl;
		cout<<"	5. May Giai Sudoku !"<<endl;
		cout<<"	6. Nhap Sudoku !"<<endl;
		cout<<"	7. Xuat Sudoku !"<<endl<<endl;
		cout<<"Lua cho cua ban: ";
		choose=getch();
		clrscr();
		Process(choose,s);
	}while(choose!='0');
	
}
int main(){
	Sudoku s;
	Menu(s);
		
}
