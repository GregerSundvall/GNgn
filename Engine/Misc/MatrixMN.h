#pragma once
#include "VectorN.h"


class MatrixMN
{
public:
	int M;      // Rows
	int N;      // Columns
	VectorN* rows; 

	MatrixMN();
	MatrixMN(int M, int N);
	MatrixMN(const MatrixMN& m);
	~MatrixMN();

	void Zero();
	MatrixMN Transpose() const;

	const MatrixMN& operator = (const MatrixMN& m);
	VectorN operator * (const VectorN& v) const;
	MatrixMN operator * (const MatrixMN& m) const;

	static VectorN SolveGaussSeidel(const MatrixMN& A, const VectorN& b);
};
