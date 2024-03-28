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
		cout << "Конструктор класса GArray закончил свою работу" << endl;
#endif
	}

	~GArray() {
		int SIZE = this->SIZE;

		for (int i = 0; i < SIZE; i++) {
			delete[] arr[i];
		}
		delete[] arr;
#ifdef DEBUG
		cout << "Деструктор класса GArray закончил свою работу" << endl;
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
		cout << "Элементу со строкой и колонкой соотв " << row << " " << col << " задано значение " << el << endl;
#endif
		return true;
	}

	void Print() {
		int SIZE = this->SIZE;

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << this->arr[i][j] << " " ;
			}
			cout << endl;
		}
	}
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
		cout << "Конструктор класса Game закончил свою работу" << endl;
#endif
	}

	~Game() {
#ifdef DEBUG
		cout << "Деструктор класса Game закончил свою работу" << endl;
#endif
	}

	int CheckWin() { // FIXME
		int SIZE = this->GetSize();

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				int el = arr.GetElement(i, j);

				if (el == 0) {
					continue;
				}

				else if (el == null) {

					if (i == 0) {
						if (arr.GetElement(i, j + 1) == null) {
							if (arr.GetElement(i, j + 2) == null) {
								return 1;
							}
						}

						if (arr.GetElement(i + 1, j) == null) {
							if (arr.GetElement(i + 2, j) == null) {
								return 1;
							}
						}
					}

					if (i == 0 && j == 0) {
						if (arr.GetElement(i + 1, j + 1) == null) {
							if (arr.GetElement(i + 2, j + 2) == null) {
								return 1;
							}
						}
					}

					if (i == 2 && j == 2) {
						if (arr.GetElement(i - 1, j - 1) == null) {
							if (arr.GetElement(i - 2, j - 2) == null) {
								return 1;
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
};

int main() {
	setlocale(LC_ALL, "Rus");

	Game arr;

	arr.Print();

	arr.MakeMove(0, 0, false);
	arr.MakeMove(1, 0, false);
	arr.MakeMove(2, 0, false);

	//cout << arr.GetElement(0, 0) << endl << arr.GetElement(1, 0) << endl << arr.GetElement(2, 0) << endl << endl;;

	cout << endl;
	arr.Print();
	cout << endl << arr.CheckWin();
}