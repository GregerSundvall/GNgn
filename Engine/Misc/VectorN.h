#pragma once

class VectorN
{
public:
	int N;
	double* data;

	VectorN();
	VectorN(int N);
	VectorN(const VectorN& v);
	~VectorN();

	void Zero(); 
	double Dot(const VectorN& v) const;

	VectorN& operator = (const VectorN& v);
	VectorN operator + (const VectorN& v) const;
	VectorN operator - (const VectorN& v) const;
	VectorN operator * (const double n) const;   
	const VectorN& operator += (const VectorN& v);
	const VectorN& operator -= (const VectorN& v);
	const VectorN& operator *= (const double n);   
	double operator [] (const int index) const; 
	double& operator [] (const int index);      
};
