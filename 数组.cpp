
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct data {
	string ID;//编号
	string name;//姓名
	string link;//联系方式
	string position;//所属部门
};
struct data *lb = new struct data[100];
int index;

class Manage {
protected:
public:
	void read_data() {//读取文件内容
		int i = 0;
		ifstream fin("D:\\Manager_sisterm.dat", ios::in | ios::binary);//二进制方式打开文件
		if (!fin.is_open()) {
			cout << "不能打开文件：D:\\Manager_sisterm.dat\n";
			exit(1);
		}
		while (!fin.eof()){
			fin >> lb[i].ID >> lb[i].name;
			fin >> lb[i].link >> lb[i].position;
			i++;
		} 
		index = i-1;
		fin.close();
	}

	void save_data() {//保存内容到文件
		int i;
		ofstream fout("D:\\Manager_sisterm.dat", ios::out | ios::binary|ios::trunc);
		if (!fout) {//创建并打开文件
			cout << "不能打开文件：D:\\Manager_sisterm.dat\n";
			exit(1);
		}
		for (i = 0; i < index; i++) {
			fout << lb[i].ID << "	" << lb[i].name << "	";
			fout << lb[i].link << " 	  " << lb[i].position << "\r\n";
		}
		fout << '\0';
		fout.close();
	}
	void delete_data() {//根据编号删除人员信息
	//	system("cls");
		read_data();
		char c;
	
		do {
			string del;
			cout << "请输入要删除人员的编号：" << endl;
			cin >> del;
			int i = 0;
			while (lb[i].ID != del&&i < index) //查找要删除的人员；
				i++;
			if (lb[i].ID == del) {
				for (int j = i; j < index - 1; j++) {
					lb[j].ID = lb[j + 1].ID;
					lb[j].name = lb[j + 1].name;
					lb[j].link = lb[j + 1].link;
					lb[j].position = lb[j + 1].position;

				}
				cout << "删除成功!" << endl;
				index = index - 1;
			}
			else if (i == index) {
				cout << "查无此人，请检查输入是否正确！" << endl;
			}
			cout << "是否继续删除？（y/n）" << endl;
			cin >> c;
		} while (c=='y'||c=='Y');
		save_data();//删除后的内容保存到文件
	}
	void add_data() {//添加人员信息
	//	system("cls");
		read_data();
		char c;
		int i = 0;
		do {
			string ad;
			cout << "请添加新的人员信息" << endl;
			cout << "请输入人员编号:" << endl;
			cin >> ad;
			while (lb[i].ID != ad&&i < index) { //查看要添加的人员是否存在
				i++;
			}
			if (lb[i].ID == ad) {
				cout << "该人员信息已存在";
				
			}
			else {
				//index++;//可以添加则向数组中继续添加
				lb[index].ID = ad;
				cout << "请输入人员姓名:" << endl;
				cin >> lb[index].name;
				cout << "请输入联系方式:" << endl;
				cin >> lb[index].link;
				cout << "请输入所属部门:" << endl;
				cin >> lb[index].position;
				index++;
			}
			cout << "(是否继续操作？(y/n))" << endl; 
			cin >> c;

		} while (c == 'y' || c == 'Y');
		save_data();
	}
	void change_data() {//修改人员信息
	//	system("cls");
		read_data();
		string id;
		int i = 0;
		char c;
		do {
			cout << "请输入要修改的人员编号:" << endl;
			cin >> id;
			while (lb[i].ID != id&&i < index) //查找要修改的人员；
				i++;
			if (i == index) {
				cout << "查无此人，请检查输入是否正确！" << endl;
			}
			else if (lb[i].ID == id) {
				cout << "请输入修改后的编号：" << endl;
				cin >> lb[i].ID;
				cout << "请输入修改后的姓名：" << endl;
				cin >> lb[i].name;
				cout << "请输入修改后的联系方式：" << endl;
				cin >> lb[i].link;
				cout << "请输入修改后的部门名称：" << endl;
				cin >> lb[i].position;
			}
			cout << "是否继续修改？（y/n）" << endl;
			cin >> c;
		} while (c == 'y' || c == 'Y');
		save_data();
	}
	void print_data() {//打印全部人员信息
		 //从文件读取
	//	system("cls");
		ifstream infile("D:\\Manager_sisterm.dat", ios::in | ios::binary);
		if (!infile) {
			cout << "不能打开输入文件：D:\\Manager_sisterm.dat\n";
			exit(1);
		}
		//得到文件长度；
		infile.seekg(0, ios::end);
		int length = infile.tellg();//返回读指针的位置；
		infile.seekg(0, ios::beg);
		char *r;
		r = new char[length];

		cout << "文件读取结果：" << endl;
		cout << "编号" << '	' << "姓名" << '	' << "联系方式" << '	' << "所属部门" << endl;
		infile.read(r, length);
		cout << r;
		infile.close();
	}
	void find_data() {//根据姓名，编号，联系方式进行查询
	//	system("cls");
		read_data();
		string find;
		char c;
		do{
			cout << "请输入要查找人员的姓名，编号或联系方式)" << endl;
			cin >> find;
			int flag = 0;
			for (int i = 0; i < index; i++) {
				if (lb[i].ID == find) {
					flag = 1;
					cout << "该人员的有关信息如下：" << endl;
					cout << "编号：	" << lb[i].ID << endl;
					cout << "姓名：	" << lb[i].name << endl;
					cout << "联系方式：" << lb[i].link << endl;
					cout << "所属部门：" << lb[i].position << endl;
					break;
				}else if (lb[i].name == find) {
					flag = 1;
					cout << "该人员的有关信息如下：" << endl;
					cout << "编号：	" << lb[i].ID << endl;
					cout << "姓名：	" << lb[i].name << endl;
					cout << "联系方式：" << lb[i].link << endl;
					cout << "所属部门：" << lb[i].position << endl;
					break;
				}
				else if (lb[i].link == find) {
					flag = 1;
					cout << "该人员的有关信息如下：" << endl;
					cout << "编号：	" << lb[i].ID << endl;
					cout << "姓名：	" << lb[i].name << endl;
					cout << "联系方式：" << lb[i].link << endl;
					cout << "所属部门：" << lb[i].position << endl;
					break;
				}				
			}
			if (flag == 0) {
				cout << "未找到该人员信息！" << endl;
			}			
			cout << "是否继续查询？(y/n)" << endl;
			cin >> c;
		}while(c == 'y' || c == 'Y');
	}
	void count_data() {//统计公司人数以及各部门人数
	//	system("cls");
		read_data();
		string find;
		int n;
		cout << "请输入要统计人数的部门数量：" << endl;
		cin >> n;
		for (int j = 0; j < n; j++) {
			cout << "请输入要统计人数的部门名称：" << endl;
			cin >> find;
			int num = 0;
			for (int i = 0; i < index; i++) {
				if (lb[i].position == find) {
					num++;
				}
			}
			cout << find << "共有" << num << "人" << endl;
		}		
		cout << "公司总人数：" << index << endl;
	}
	void rank_data() {//各部门排序
	//	system("cls");
		read_data();
		string rank;
		int n = 0;
		char c;
		do {
			struct data *ran = new struct data[50];
			cout << "请输入要排序的部门名称：" << endl;
			cin >> rank;
			for (int i = 0; i < index; i++) {
				if (lb[i].position == rank) {
					ran[n].ID = lb[i].ID;
					ran[n].name = lb[i].name;
					ran[n].link = lb[i].link;
					ran[n].position = lb[i].position;
					n++;
				}
			}
			for (int j = 0; j < n - 1; j++) {//每一个人跟所有人都比一遍
				for (int i = 0; i < n - 1 - j; i++) {
					if (ran[i].ID > ran[i + 1].ID) {
						swap(ran[i].ID, ran[i + 1].ID);
						swap(ran[i].name, ran[i + 1].name);
						swap(ran[i].link, ran[i + 1].link);
					}
				}
			}
			cout << "按编号排序结果：" << endl;
			cout << "编号" << '	' << "姓名" << '	' << "联系方式" << '	' << "所属部门" << endl;
			for (int i = 0; i < n ; i++) {
				cout << ran[i].ID << "	"
					<< ran[i].name << "	"
					<< ran[i].link << "	        "
					<< ran[i].position << endl;
			}
			cout << "是否继续操作？(y/n)" << endl;
			cin >> c;
		}while (c == 'y' || c == 'Y');

	}

};


int main() {
	int k;	
	Manage A;
	
	while (1) {
		cout << "           欢迎使用公司人员管理系统         " << endl;
		cout << "                                        " << endl;
		cout << "              1.添加人员信息              " << endl;
		cout << "              2.修改人员信息              " << endl;
		cout << "              3.删除人员信息              " << endl;
		cout << "              4.查询人员信息              " << endl;
		cout << "              5.打印人员信息              " << endl;
		cout << "              6.部门人员排序              " << endl;
		cout << "              7.统计人员信息              " << endl;
		cout << "              8.退出程序                 " << endl;
		cout << "	   请输入要执行的操作:" << ' ';
		cin >> k;
			switch (k) {
			case 1: A.add_data(); break;
			case 2: A.change_data(); break;
			case 3: A.delete_data(); break;
			case 4: A.find_data(); break;
			case 5: A.print_data(); break;
			case 6:	A.rank_data(); break;
			case 7: A.count_data(); break;
			case 8:exit(2); break;
			default:cout << "\t\t\t        输入错误,返回" << endl; break;
			}
	}
	system("pause");
	return 0;
}
