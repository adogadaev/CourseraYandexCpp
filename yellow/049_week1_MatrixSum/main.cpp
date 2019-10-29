/*
 * main.cpp
 *
 *  Created on: Oct 27, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Matrix {
public:
	Matrix() {
		mMtx.resize(0);
		mRows = 0;
		mColumns = 0;
	}
	Matrix(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Matrix(int,int)");
		}
		mMtx.resize(num_rows);
		for (int i = 0; i < num_rows; i++) {
			mMtx[i].resize(num_cols, 0);
		}
		mRows = num_rows;
		mColumns = num_cols;
	}

	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Reset()");
		}
		mMtx.resize(num_rows);
		for (int i = 0; i < num_rows; i++) {
			mMtx[i].resize(num_cols, 0);
			fill(mMtx[i].begin(), mMtx[i].end(), 0);
		}
		mRows = num_rows;
		mColumns = num_cols;
	}
	int At(int r, int c) const {
		if (r < 0 || c < 0 ||
				r >= GetNumRows() || c >= GetNumColumns()) {
			string err_msg = "const At(): r=";
			err_msg += to_string(r);
			err_msg += "/";
			err_msg += to_string(GetNumRows());
			err_msg +=" c=";
			err_msg += to_string(c);
			err_msg += "/";
			err_msg += to_string(GetNumColumns());
			throw out_of_range(err_msg);
		}
		return mMtx[r][c];
	}
	int& At(int r, int c) {
		if (r < 0 || c < 0 ||
				r >= GetNumRows() || c >= GetNumColumns()) {
			string err_msg = "int& At(): r=";
			err_msg += to_string(r);
			err_msg += "/";
			err_msg += to_string(GetNumRows());
			err_msg +=" c=";
			err_msg += to_string(c);
			err_msg += "/";
			err_msg += to_string(GetNumColumns());
			throw out_of_range(err_msg);
		}
		return mMtx[r][c];
	}
	int GetNumRows() const {
		return mRows;
	}
	int GetNumColumns() const {
		return mColumns;
	}
private:
	vector<vector<int>> mMtx;
	int mRows;
	int mColumns;
};

istream& operator>>(istream& in, Matrix& mtx) {
	int r, c;
	in >> r >> c;
	mtx.Reset(r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			in >> mtx.At(i, j);
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const Matrix& mtx) {
	out << mtx.GetNumRows() << ' ' << mtx.GetNumColumns() << endl;
	for (int i = 0; i < mtx.GetNumRows(); i++) {
		for (int j = 0; j < mtx.GetNumColumns(); j++) {
			out << mtx.At(i, j) << ' ';
		}
		out << endl;
	}
	return out;
}

bool operator==(const Matrix& rhs, const Matrix& lhs) {
	if (rhs.GetNumRows() != lhs.GetNumRows() ||
			rhs.GetNumColumns() != lhs.GetNumColumns()) {
		return false;
	}
	for (int i = 0; i < rhs.GetNumRows(); i++) {
		for (int j = 0; j < rhs.GetNumColumns(); j++) {
			if (rhs.At(i, j) != lhs.At(i,j)) {
				return false;
			}
		}
	}
	return true;
}

Matrix operator+(const Matrix& rhs, const Matrix& lhs) {
	if (rhs.GetNumRows() != lhs.GetNumRows() ||
			rhs.GetNumColumns() != lhs.GetNumColumns()) {
		string err_msg = "Matrices should have the same size to sum them (";
		err_msg += to_string(rhs.GetNumRows());
		err_msg += ",";
		err_msg += to_string(rhs.GetNumColumns());
		err_msg += ",";
		err_msg += to_string(lhs.GetNumRows());
		err_msg += ",";
		err_msg += to_string(lhs.GetNumColumns());
		err_msg += ")";
		throw invalid_argument(err_msg);
	}
	Matrix res(rhs.GetNumRows(), rhs.GetNumColumns());
	for (int i = 0; i < rhs.GetNumRows(); i++) {
		for (int j = 0; j < rhs.GetNumColumns(); j++) {
			res.At(i, j) = rhs.At(i, j) + lhs.At(i, j);
		}
	}
	return res;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one+two << endl;

	Matrix three;
	cin >> three;
	cout << (one == three) << endl;

	two.Reset(2, 3);
	cout << two << endl;

	//three.At(100,500);

	return 0;
}


