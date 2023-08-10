#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int size_of_park = 0; //������ ��������� ��������

struct passenger//����� ��������
{
	unsigned place = 0;
	string name;
	string surname;
	unsigned age = 0;
};

struct plane
{
	//�������� ��������������
	string name_of_plane; 
	unsigned place_in_row = 0; //���-�� ���� � ����� ����
	set <int> free_places; // ���-�� ��������� ����
	set <int> occupied_places; //���-�� ������� ����

	//���������������
	vector <passenger> list_of_passangers; // C����� ����������
	string plane_type; //��� ������� 
};

void create_plane(vector<plane>& aircraft_base)//������� ���������� ������� � ���� ������������
{

	cout << "\n�������� ��� �������:";
	cout << "\n1. Airbus A320";
	cout << "\n2. Superjet 100";
	cout << endl;
	cout << "\n����� �����: ";
	int n;
	cin >> n;
	while (cin.fail() || n > 2)//��������� ���������� ����� �������
	{
		cout << "������ ������ ������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> n;
	}

	switch (n)
	{
	case 1://type airbus
	{
		plane Airbus;
		size_of_park += 1;
		cout << "\n �������� �������: Airbus_" << size_of_park;
		Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
		cout << "\n������� ���-�� ����, �� �� ����� 180: ";
		int seats;
		cin >> seats;
		while (cin.fail() || seats > 180 || seats <= 0)//��������� ���������� ����� �������
		{
			cout << "������ ����� ���-�� ����" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "���������� ��� ���: ";
			cin >> seats;
		}
		//������ ���������� �����
		for (int i = 0; i < seats; i++)
		{
			Airbus.free_places.insert(i + 1);
		}
		Airbus.place_in_row = 6;
		Airbus.plane_type = "Airbus";
		Airbus.list_of_passangers.resize(seats);
		aircraft_base.push_back(Airbus);//��������� ������ � ���� ������
		cout << "\n������ ������� ��������!" << endl;
		break;

	}
	case 2://type superjet
		plane SuperJet;
		size_of_park += 1;
		cout << "\n �������� �������: SuperJet_" << size_of_park;
		SuperJet.name_of_plane = "SuperJet" + to_string(size_of_park);
		cout << "\n������� ���-�� ����, �� �� ����� 100: ";
		int seats;
		cin >> seats;
		while (cin.fail() || seats > 100 || seats <= 0)//��������� ���������� ����� �������
		{
			cout << "������ ����� ���-�� ����" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "���������� ��� ���: ";
			cin >> seats;
		}
		//������ ���������� �����
		for (int i = 0; i < seats; i++)
		{
			SuperJet.free_places.insert(i + 1);
		}
		SuperJet.place_in_row = 5;
		SuperJet.plane_type = "SuperJet";
		SuperJet.list_of_passangers.resize(seats);
		aircraft_base.push_back(SuperJet);//��������� ������ � ���� ������
		cout << "\n������ ������� ��������!" << endl;
		break;
	}
}

void planes(vector<plane>& aircraft_base)
{

	if (size_of_park == 0)
	{
		cout << "\n\t�������� �������� � ���� ���� ���." << endl;
	}

	for (int i = 0; i < size_of_park; i++)
	{
		plane local_plane = aircraft_base[i];
		cout << "\n" << i+1 << ". ������: " << local_plane.name_of_plane << ", ���������� c�������� ���� - " << local_plane.free_places.size() << ", ���������� ������� ���� - " << local_plane.occupied_places.size();
	}
	
}

void add_passanger(vector<plane>& aircraft_base)
{
	if (size_of_park == 0)
	{
		cout << "\n� ����� ���� ��� �������� ��� ����������� ����������" << endl;
		return;
	}
	passenger tourist;
	cout << "\n�������� ������: ";//����� ��������� ��������
	planes(aircraft_base);
	int NumPlane = 0;
	cout << "\n�����: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park)//��������� ���������� ����� �������
	{
		cout << "������ ������ �������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane-1];
	int j = 0;
	
	//����������� ���������
	cout << "\n��� ���������: ";
	cin >> tourist.name;//���������� ����� ���������
	cout << "\n������� ���������: ";
	cin>> tourist.surname;//��������� ������� ���������
	cout << "\n������� ���������: ";
	cin >> tourist.age;//���������� �������� ���������
	while (cin.fail())
	{
		cout << "\n������������ ���� ��������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n���������� ��� ���: ";
		cin >> tourist.age;

	}
	
	if (local_plane.plane_type == "Airbus")
	{
		//������ ���������� ����
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0)
				cout << "\t";//������ ��� ����������
			if (j % 6 == 0)
				cout << endl;
			if (local_plane.occupied_places.find(i) != local_plane.occupied_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	else//if type == SuperJet
	{
		int spec_2 = 2;//���� ��� ������ ������� ����� 2 ������� �����
		int spec_5 = 5;//���� ��� �������� ����
		//������ ���������� ����
		for (int i = 1; i <= local_plane.free_places.size() + local_plane.occupied_places.size(); i++)
		{

			if (j == spec_2)
			{
				cout << "\t";//������ ��� ����������
				spec_2 += 5;
			}
			if (j == spec_5)
			{
				cout << endl;
				spec_5 += 5;
			}
			if (local_plane.occupied_places.find(i) != local_plane.occupied_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	cout << "\n�������� �����: ";
	cin >> tourist.place;
	while (cin.fail() || tourist.place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\n������ ����� �����, ���������� ������� ������������ �������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n���������� ��� ���: ";
		cin >> tourist.place;
	}
	if (local_plane.occupied_places.find(tourist.place) != local_plane.occupied_places.end())
	{
		cout << "\n��� ����� ��� ������!";
		return;
	}
	cout << "\n�� �������: " << tourist.place;
	local_plane.list_of_passangers[tourist.place-1] = tourist;
	local_plane.free_places.erase(tourist.place);//������� ��������� ����� � ������ ��������� ������
	local_plane.occupied_places.insert(tourist.place);//���������� � ������ ������� ������ ����� ���������
	aircraft_base[NumPlane - 1] = local_plane;
}

void find_passanger(vector<plane>& aircraft_base)
{
	planes(aircraft_base);
	if (size_of_park == 0)
	{
		return;
	}
	int NumPlane = 0;
	cout << "\n�����: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park || NumPlane <= 0)//��������� ���������� ����� �������
	{
		cout << "������ ������ �������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane - 1];
	
	int j = 0;
	if (local_plane.plane_type == "Airbus")
	{
		if(local_plane.occupied_places.size() == 0)
		{
			cout << "��� ������� ����";
			return;
		}
		//������ ���������� ����
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0 && j != 0)
				cout << "\t";//������ ��� ����������
			if (j % 6 == 0)
				cout << endl;
			if (local_plane.free_places.find(i) != local_plane.free_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	else//if type == SuperJet
	{
		if (local_plane.occupied_places.size() == 0)
		{
			cout << "��� ������� ����";
			return;
		}
		int spec_2 = 2;//���� ��� ������ ������� ����� 2 ������� �����
		int spec_5 = 5;//���� ��� �������� ����
		//������ ���������� ����
		for (int i = 1; i <= local_plane.free_places.size() + local_plane.occupied_places.size(); i++)
		{

			if (j == spec_2)
			{
				cout << "\t";//������ ��� ����������
				spec_2 += 5;
			}
			if (j == spec_5)
			{
				cout << endl;
				spec_5 += 5;
			}
			if (local_plane.free_places.find(i) != local_plane.free_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	cout << "\n�������� �����: ";
	int num_of_place;
	cin >> num_of_place;

	while (cin.fail() || num_of_place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\n������ ����� �����, ���������� ������� ������������ �������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> num_of_place;
	}

	if (local_plane.free_places.find(num_of_place) != local_plane.free_places.end())
	{
		cout << "\n��� ����� ��� ��������!";
			return;
	}
	passenger tourist = local_plane.list_of_passangers[num_of_place-1];
	cout << "\n���: "<< tourist.name;
	cout << "\n�������: " << tourist.surname;
	cout << "\n�������: " << tourist.age;
}

void del_passenger(vector <plane> &aircraft_base)
{
	planes(aircraft_base);
	if (size_of_park == 0)
	{
		return;
	}
	int NumPlane = 0;
	cout << "\n�����: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park || NumPlane <= 0)//��������� ���������� ����� �������
	{
		cout << "������ ������ �������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane - 1];

	int j = 0;
	if (local_plane.plane_type == "Airbus")
	{
		if (local_plane.occupied_places.size() == 0)
		{
			cout << "��� ������� ����";
			return;
		}
		//������ ���������� ����
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0 && j != 0)
				cout << "\t";//������ ��� ����������
			if (j % 6 == 0)
				cout << endl;
			if (local_plane.free_places.find(i) != local_plane.free_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	else//if type == SuperJet
	{
		if (local_plane.occupied_places.size() == 0)
		{
			cout << "��� ������� ����";
			return;
		}
		int spec_2 = 2;//���� ��� ������ ������� ����� 2 ������� �����
		int spec_5 = 5;//���� ��� �������� ����
		//������ ���������� ����
		for (int i = 1; i <= local_plane.free_places.size() + local_plane.occupied_places.size(); i++)
		{

			if (j == spec_2)
			{
				cout << "\t";//������ ��� ����������
				spec_2 += 5;
			}
			if (j == spec_5)
			{
				cout << endl;
				spec_5 += 5;
			}
			if (local_plane.free_places.find(i) != local_plane.free_places.end())
			{
				cout.width(4);
				cout << "x";//���� ����� ������ 
				j++;
				continue;
			}
			cout.width(4);//������ ���� ������ ����������� ����� ����� 
			cout << i;
			j++;
		}
	}
	cout << "\n�������� �����: ";
	int num_of_place;
	cin >> num_of_place;
	while (cin.fail() || num_of_place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\n������ ����� �����, ���������� ������� ������������ �������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "���������� ��� ���: ";
		cin >> num_of_place;
	}

	if (local_plane.free_places.find(num_of_place) != local_plane.free_places.end())
	{
		cout << "\n��� ����� ��� ��������!";
		return;
	}

	local_plane.list_of_passangers.erase(local_plane.list_of_passangers.begin() + num_of_place - 1);
	local_plane.free_places.insert(num_of_place);//������� ��������� ����� � ������ ��������� ������
	local_plane.occupied_places.erase(num_of_place);//���������� � ������ ������� ������ ����� ���������
	aircraft_base[NumPlane - 1] = local_plane;
}


int console(int i, vector<plane>& aircraft_base)
{
	cout << "\n\t������� ���������� ���������" << endl;
	cout << "\n 1. �������� ������";
	cout << "\n 2. C������ ������������";
	cout << "\n 3. ���������������� �������� �� ����";
	cout << "\n 4. ����������� ������� �����";
	cout << "\n 5. �������� ����������� ���������";
	cout << "\n 0. �����";
	//cout << "\n  "
	cout << "\n ������� ����� ������ ����: ";
	unsigned n;
	
	cin >> n;
	while (cin.fail() || n>5)
	{
		cout << "\n������ ������ �������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n���������� ��� ���: ";
		cin >> n;
	}

	//���������� ������ �������
	switch (n)
	{

	case 1:
		create_plane(aircraft_base);
		return 1;

	case 2:
		cout << "\n������� � ����";
		planes(aircraft_base);
		return 1;

	case 3:
		add_passanger(aircraft_base);
		return 1;

	case 4:
		find_passanger(aircraft_base);
		return 1;

	case 5:
		del_passenger(aircraft_base);
		return 1;

	case 0:
		return 0;	
	}
	cout << "������ ������ ���� ���, ���������� ��� ���" << endl;
	return 1;
}

int main()
{
	setlocale(LC_ALL ,"Russian");//���������� ������� ����

	vector<plane> aircraft_base;//������ ������ ��� �������� ��������

	int i = 1;
	while (i == 1)
	{
		i = console(i,aircraft_base);//������� � �������
	}
	
	return 0;

}