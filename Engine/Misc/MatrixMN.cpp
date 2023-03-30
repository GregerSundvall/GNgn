#include "MatrixMN.h"



MatrixMN::MatrixMN(): M(0), N(0), rows(nullptr) {}

MatrixMN::MatrixMN(int M, int N): M(M), N(N) {
	rows = new VectorN[M];
	for (int i = 0; i < M; i++)
		rows[i] = VectorN(N);
}

MatrixMN::MatrixMN(const MatrixMN& m) {
	*this = m;
}

MatrixMN::~MatrixMN() {
	delete[] rows;
}

void MatrixMN::Zero() {
	for (int i = 0; i < M; i++)
		rows[i].Zero();
}

MatrixMN MatrixMN::Transpose() const {
	MatrixMN result(N, M);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			result.rows[j][i] = rows[i][j];
	return result;
}

const MatrixMN& MatrixMN::operator = (const MatrixMN& m) {
	M = m.M;
	N = m.N;
	rows = new VectorN[M];
	for (int i = 0; i < M; i++)
		rows[i] = m.rows[i];
	return *this;
}

VectorN MatrixMN::operator * (const VectorN& v) const {
	if (v.N != N)
		return v;
	VectorN result(M);
	for (int i = 0; i < M; i++)
		result[i] = v.Dot(rows[i]);
	return result;
}

MatrixMN MatrixMN::operator * (const MatrixMN& m) const {
	if (m.M != N && m.N != M)
		return m;		
	MatrixMN tranposed = m.Transpose();
	MatrixMN result(M, m.N);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < m.N; j++)
			result.rows[i][j] = rows[i].Dot(tranposed.rows[j]);
	return result;
}

VectorN MatrixMN::SolveGaussSeidel(const MatrixMN& A, const VectorN& b) {
	const int N = b.N;
	VectorN X(N);
	X.Zero();

	// Iterate N times
	for (int iterations = 0; iterations < N; iterations++) {
		for (int i = 0; i < N; i++) {
			float dx = (b[i] / A.rows[i][i]) - (A.rows[i].Dot(X) / A.rows[i][i]);
			if (dx == dx) {
				X[i] += dx;
			}
		}
	}
	return X;
}