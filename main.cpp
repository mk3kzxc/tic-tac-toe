#include <iostream>

using namespace std;

//#define DEBUG

class GArray {
private:
	int SIZE = 3;
	int** arr;

public:
	GArray() {
		int SIZE = this->SIZE;
		arr = new int* [SIZE];

		for (int i = 0; i < SIZE; i++) {
			arr[i] = new int[SIZE] {};
		}
#ifdef DEBUG
		cout << "����������� ������ GArray �������� ���� ������" << endl;
#endif
	}

	~GArray() {
		int SIZE = this->SIZE;

		for (int i = 0; i < SIZE; i++) {
			delete[] arr[i];
		}
		delete[] arr;
#ifdef DEBUG
		cout << "���������� ������ GArray �������� ���� ������" << endl;
#endif
	}

	int GetElement(int row, int col) {
		return this->arr[row][col];
	}

	int GetSize() {
		return this->SIZE;
	}

	bool SetElement(int row, int col, int el) {
		this->arr[row][col] = el;
#ifdef DEBUG
		cout << "�������� �� ������� � �������� ����� " << row << " " << col << " ������ �������� " << el << endl;
#endif
		return true;
	}

	/*void Print() {
		int SIZE = this->SIZE;

		for (int i = 0; i < SIZE; i++) {
			cout << " ";
			for (int j = 0; j < SIZE; j++) {
				cout << this->arr[i][j] << " " ;
			}
			cout << endl;
		}
	}*/
};

class Game : public GArray {
private:
	const int nth = 0;
	const int null = 1;
	const int cross = 2;
	GArray arr;

public:
	Game() {
#ifdef DEBUG
		cout << "����������� ������ Game �������� ���� ������" << endl;
#endif
	}

	~Game() {
#ifdef DEBUG
		cout << "���������� ������ Game �������� ���� ������" << endl;
#endif
	}

	int CheckWin() { // FIXME
		int SIZE = this->GetSize();

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				int el = this->GetElement(i, j);

				if (el == 0) {
					continue;
				}

				if ((el == null) || (el == cross)) {

					if (j < SIZE - 1) {
						if ((this->GetElement(i, j + 1) == el) && (this->GetElement(i, j + 2) == el)) {

							if (el == null) {
								return 1;
							}
							if (el == cross) {
								return 2;
							}

						}
					}

					if (i < SIZE - 1) {
						if ((this->GetElement(i + 1, j) == el) && (this->GetElement(i + 2, j) == el)) {

							if (el == null) {
								return 1;
							}
							if (el == cross) {
								return 2;
							}

						}
					}

					if ((i < SIZE - 2) && (j < SIZE - 2)) {
						if ((this->GetElement(i + 1, j + 1) == el) && (this->GetElement(i + 2, j + 2) == el)) {

							if (el == null) {
								return 1;
							}
							if (el == cross) {
								return 2;
							}

						}
					}


					if ((i < SIZE - 2) && (j > 1)) {
						if ((j == 2) && (this->GetElement(i + 1, j - 1) == el) && (this->GetElement(i + 2, j - 2) == el)) {

							if (el == null) {
								return 1;
							}
							if (el == cross) {
								return 2;
							}

						}
					}
				}


			}
		}
	}

	bool MakeMove(int row, int col, bool who) {
		int el;

		switch (who) {
		case 0:
			el = null;
			break;
		case 1:
			el = cross;
			break;
		default:
			return false;
			break;
		};


		if (this->GetElement(row, col) == 0) {
			this->SetElement(row, col, el);
			return true;
		}
		return false;
	}

	void Print() {
		int SIZE = this->GetSize();

		for (int i = 0; i < SIZE; i++) {
			cout << " ";
			for (int j = 0; j < SIZE; j++) {
				char symb;
				switch (this->GetElement(i,j)) {
				case 1:
					symb = 'O';
					break;
				case 2:
					symb = 'X';
					break;
				default:
					symb = ' ';
					break;
				}
				cout << symb << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Rus");

	Game arr;
	int winner{}, move{};

	while (!winner) {
		system("cls");

		char xod;
		int i,j;
		if ((move == 0) || (move == 1)) {
			move = 1;
			xod = 'O';
		}
		else {
			move = 2;
			xod = 'X';
		}

		cout << "+------------------------------+" << endl;
		cout << "��������-������\n�����: " << xod << endl;
		cout << "+------+-----------------------+" << endl;

		arr.Print();
		cout << "+------+" << endl;
		int win = arr.CheckWin();
		if (win == 1) {
			winner = 1;
			cout << "������� �����! ���� ��������." << endl;
			break;
			system("pause");
		}
		else if (win == 2) {
			winner = 2;
			cout << "������� �������! ���� ��������." << endl;
			break;
			system("pause");
		}
		cout << "������� ����� ������� � ������ ��������������, ��� �� ������ ������� (�� 1 �� 3)" << endl;
		cin >> i >> j;
		if ((i >= 1) && (i <= 3) && (j >= 1) && (j <= 3)) {
			bool movv;
			if (move == 1) {
				movv = false;
			}
			else {
				movv = true;
			}
			int res = arr.MakeMove(j - 1, i - 1, movv);

			if (res == false) {
				cout << "���� ��� ��� �� ������! ���������� ��� ���" << endl;
				if (move == 1) {
					move = 0;
				}
				else {
					move = 2;
				}
				system("pause");
			} 
			if (res == true) {
				if (move == 1) {
					move = 2;
				}
				else if (move==2) {
					move = 1;
				}
			}
		}

		else {
			cout << "�� ����������� ����� ������� ��� ������. ���������� ��� ���" << endl;
			if (move == 1) {
				move = 0;
			}
			else {
				move = 2;
			}
			system("pause");
		}

		
	}
}