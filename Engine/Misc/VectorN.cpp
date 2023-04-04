﻿#include "VectorN.h"



VectorN::VectorN(): N(0), data(nullptr) {}

VectorN::VectorN(int N): N(N) {
	data = new double[N];
}

VectorN::VectorN(const VectorN& v) {
	N = v.N;
	data = new double[N];
	for (int i = 0; i < N; i++)
		data[i] = v.data[i];
}

VectorN::~VectorN() {
	delete[] data;
}

void VectorN::Zero() {
	for (int i = 0; i < N; i++)
		data[i] = 0.0f;
}

double VectorN::Dot(const VectorN& v) const {
	double sum = 0.0f;
	for (int i = 0; i < N; i++)
		sum += data[i] * v.data[i];
	return sum;
}

VectorN& VectorN::operator = (const VectorN& v) {
	delete[] data;
	N = v.N;
	data = new double[N];
	for (int i = 0; i < N; i++)
		data[i] = v.data[i];
	return *this;
}

VectorN VectorN::operator * (double n) const {
	VectorN result = *this;
	result *= n;
	return result;
}

VectorN VectorN::operator + (const VectorN& v) const {
	VectorN result = *this;
	for (int i = 0; i < N; i++)
		result.data[i] += v.data[i];
	return result;
}

VectorN VectorN::operator - (const VectorN& v) const {
	VectorN result = *this;
	for (int i = 0; i < N; i++)
		result.data[i] -= v.data[i];
	return result;
}

const VectorN& VectorN::operator *= (double n) {
	for (int i = 0; i < N; i++)
		data[i] *= n;
	return *this;
}

const VectorN & VectorN::operator += (const VectorN& v) {
	for (int i = 0; i < N; i++)
		data[i] += v.data[i];
	return *this;
}

const VectorN& VectorN::operator -= (const VectorN& v) {
	for (int i = 0; i < N; i++)
		data[i] -= v.data[i];
	return *this;
}

double VectorN::operator [] (const int index) const {
	return data[index];
}

double& VectorN::operator [] (const int index) {
	return data[index];
}
