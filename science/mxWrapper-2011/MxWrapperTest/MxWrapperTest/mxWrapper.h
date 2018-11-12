#pragma once

// if using very old version of matlab, define this
//#define Matlab6p1
// if using Matlab R14 or newer, undefine it
#undef Matlab6p1

//typedef int mwSize;

// VS C++ 2010 already defines char16_t in yvals.h, which conflicts with matrix.h unless __STDC_UTF_16__ is defined
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif


#if defined(Matlab6p1)
//#include "C:\Program Files\MATLAB6p1\extern\include\engine.h"
//#include "engine.h"
#else
//#include "D:\Program Files (x86)\MATLAB\R2009a\extern\include\engine.h"
#include "engine.h"
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <afxmt.h>
typedef std::exception mwException ;
typedef mwException mxException ;
using std::bad_alloc;
using std::runtime_error;
using std::ostream;
using std::endl;
using std::string;

#include <vector>
using std::vector;
typedef vector<double>  vDouble;


namespace mxWrapperNS
{

class mxWrapperSubArray;

class mxWrapper
{
	// non-member functions which access the mxArray* pMx directly must be friends of this class
	friend mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B);
	friend mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C);
	friend mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D);
	friend mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E);
	friend mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E, const mxWrapper& F);
	friend bool IsCOLON(const mxWrapper &m1);
	friend mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4);
	friend mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3);
	friend mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2);
	friend mwSize mxWrapperEnd(const mxWrapper& A, const mxWrapper& dim, const mxWrapper& nSubscriptIdx);
	friend void safeSizeOf(const mxWrapper& w, mwSize &nd, mwSize &n1, mwSize &n2, mwSize &n3, mwSize &n4, mwSize &n5);
	friend class mxWrapperSubArray;
	friend void mxWrapperEngEvalString(Engine *ep, LPCTSTR cmd);
	friend mxWrapper mod(const mxWrapper& X, const mxWrapper& Y);
	friend mxWrapper floor(mxWrapper const&A);
	friend mxWrapper cos (const mxWrapper& A);
	friend mxWrapper acos (const mxWrapper& A);
	friend mxWrapper sin (const mxWrapper& A);
	friend mxWrapper power(const mxWrapper& X, const mxWrapper& N);
	friend mxWrapper squeeze(mxWrapper const& X);
	friend mxWrapper sqrt(mxWrapper const &A);
	friend mxWrapper abs(mxWrapper const &A);
	friend mxWrapper sign(mxWrapper const &A);
	friend BOOL save(const string& fName, const string& s1, mxWrapper const& v1);
	friend BOOL load(const string& fName, const string& s1, mxWrapper *v1);

public:

	mxWrapper();
	mxWrapper(const mxWrapper &m1);
	mxWrapper(const mxWrapperSubArray &m1);
	mxWrapper(mwSize rows, mwSize cols, const double *dataReal, const double *dataImag=NULL);
	mxWrapper(mwSize rows, mwSize cols, const unsigned short *dataReal);
	mxWrapper(mwSize rows, mwSize cols, const float *dataReal);
	mxWrapper(Engine *ep, const char* name);
	mxWrapper(unsigned long long initVal);
	mxWrapper(unsigned int initVal);
	mxWrapper(signed int initVal);
	mxWrapper(double initVal);
	mxWrapper(float initVal);
	mxWrapper(bool initVal, bool isColon=false);
	mxWrapper(const char* name);
	mxWrapper(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex);
	mxWrapper(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex);
	mxWrapper(mwSize d1, mwSize d2, mwSize d3, bool bComplex);
	mxWrapper(mwSize d1, mwSize d2, bool bComplex);
	mxWrapper(const mxWrapper &m1, mwSize md, mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5);

	// ramp
	mxWrapper(double lb, double step, double ub);

	~mxWrapper();

	BOOL put(Engine *ep, const char* name) const;
	BOOL get(Engine *ep, const char* name);
private:
	BOOL putHelper(Engine *ep, const char* name, mxArray *pMx) const;
public:
	const double* getPr() const;
	const double* getPi() const;
	double* getPr();
	double* getPi();

	bool IsEmpty() const;
	void empty();

	mwSize Size() const;
	mwSize Size(mwSize dim) const;
	mwSize Size(mwSize* dims, mwSize maxdims=2) const;
	mwSize Size(mxWrapper& dims) const; // puts the size into dims

	double minElement() const;	//finds min in the mxArray	
	double maxElement() const;	//finds max in the mxArray	

	mwSize getNumberElements() const;

// indexing operations  (CONST: do not change any data members. used on right of assignment statement)

	// simple scalar data indexing: accesses exactly 1 element
	double ExtractScalar(mwSize i) const;
	double ExtractScalar(double &c, mwSize i) const;
	double ExtractScalarImag(mwSize i) const;

	// multi-dimensional, non-scalar indexing: accesses more than 1 element. construct a mxWrapperSubArray to provide indexing
	mxWrapper subsref(const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5) const;
	mxWrapper operator() (const mxWrapper &m1, const mxWrapper &m2=mxWrapper(), const mxWrapper &m3=mxWrapper(), const mxWrapper &m4=mxWrapper(), const mxWrapper &m5=mxWrapper()) const;
	mxWrapper operator() (const mxWrapperSubArray &msa) const;

private:
	// indexGenerator should not be called outside this class
	mxWrapperSubArray mxWrapper::indexGenerator(const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5) const;

	// NOT thread-safe! callers of the functions below must use the CCriticalSection very carefully
	mxArray* CreateMxArray(mxClassID classid) const;  // constructs an mxArray out of an mxWrapper instance
	BOOL LoadFromMxArray(mxArray* pMx); // loads the data from the pointer and deletes it
	// NOT thread-safe! 

public:

// indexing operations  (NON-CONST: changes data. used on left of assignment statement)
	// simple scalar data indexing: accesses exactly 1 element
	//double& operator() (unsigned int d1=1, unsigned int d2=1, unsigned int d3=1, unsigned int d4=1);

	// multi-dimensional, non-scalar indexing: accesses more than 1 element
	void AssignConstant(double c, bool assignImag=false);  // overwrites every element with d
	//mxWrapper& operator= (double d); // @see AssignConstant
	void AssignAt(mwSize idx, double d, bool assignImag=false); // if assignImag==true, the imaginary component is assigned, else the real component is assigned

	void ReallocImag(); // the mxArray* is re-created with an imaginary component (same size as the real component)
	void ReallocReal(); // the mxArray* is re-created without an imaginary component 

	// WARNING: these functions should be used with care!
	void ExtractData(double* destReal, mwSize n=0);
	void ExtractData(double* destReal, double* destImag, mwSize n=0);

	// NON-CONST indexing
	mxWrapperSubArray operator() (const mxWrapperSubArray &msa);
	mxWrapperSubArray operator() (const mxWrapper &m1, const mxWrapper &m2=mxWrapper(), const mxWrapper &m3=mxWrapper(), const mxWrapper &m4=mxWrapper(), const mxWrapper &m5=mxWrapper()) ;

	// operator()(const mxWrapperSubArray &msa) non-const is NOT DEFINED

	// notice that operator=() is NOT DEFINED in the mxWrapper class except as a constructor or to copy an entire mxWrapper.  
	// instead, mxWrapperSubArray must be used instead for copying indexed parts of an mxWrapper.
	// using mxWrapperSubArray prevents function argument ambiguities and reduces potential indexing errors.  

	mxWrapper & operator= (const mxWrapper& mx1);
	mxWrapper & operator= (const mxWrapperSubArray& msa1);  // copies contents of msa into new mxWrapper

// arithmetic operations
	// scalar operations: just rely on the compiler to allocate a single element mxWrapper automatically
	// per-element array operations

	mxWrapper & operator+= (const mxWrapper &m1);
	mxWrapper & operator-= (const mxWrapper &m1);
	mxWrapper & operator*= (const mxWrapper &m1);
	mxWrapper & operator/= (const mxWrapper &m1);

	// boolean logic operators
	mxWrapper operator> (const mxWrapper &m1) const;
	mxWrapper operator>= (const mxWrapper &m1) const;
	mxWrapper operator< (const mxWrapper &m1) const;
	mxWrapper operator<= (const mxWrapper &m1) const;
	mxWrapper operator== (const mxWrapper &m1) const;
	mxWrapper operator!= (const mxWrapper &m1) const;

	// misc.
	const char *GetClassName() const;
	CString GetString() const;

	bool IsCOLON() const;
	bool IsUNDEFINED() const;
	bool IsComplex() const;  // does the mxArray have an Imaginary component?  by default, it's real-only

private:

	vDouble Mx, MxI;
	CString MxName;
	bool m_bIsCOLON; // does this mxWrapper represent COLON?  (':')
	mwSize nDim, Dim1, Dim2, Dim3, Dim4, Dim5;

	// multi-threaded use of ::get() and ::put() must be exclusive
	static CCriticalSection ccEngine;
};

// this does not implement the full functionality of the [] operator for deleting parts of arrays
const mxWrapper& empty();
const mxWrapper& mxWrapperColon();
mxWrapper mxWrapperColon(const mxWrapper& lb, const mxWrapper&ub );
mxWrapper mxWrapperColon(const mxWrapper& lb, const mxWrapper& step, const mxWrapper&ub );
mwSize mxWrapperEnd(const mxWrapper& A, const mxWrapper& dim, const mxWrapper& nSubscriptIdx);

void mxWrapperEngEvalString(Engine *ep, LPCTSTR cmd);
CStringA MakeMxEngineSafeString(const CStringA& cs);

class mxWrapperSubArray
{
	friend class mxWrapper;
public:
	mxWrapperSubArray() : baseWrapper(NULL), indices(), D1(), D2(), D3(), D4(), D5() {} 
	mxWrapperSubArray(mxWrapper* b, const mxWrapper& idx, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5) : baseWrapper(b), indices(idx), D1(d1), D2(d2), D3(d3), D4(d4), D5(d5) {} 
	mxWrapperSubArray(const mxWrapperSubArray &msa) : baseWrapper(msa.baseWrapper), indices(msa.indices), D1(msa.D1), D2(msa.D2), D3(msa.D3), D4(msa.D4), D5(msa.D5) {} 
	~mxWrapperSubArray() {} 
	mxWrapperSubArray& operator= (const mxWrapperSubArray &msa);
	mxWrapperSubArray& operator= (const mxWrapper &w);
	mxWrapperSubArray& AssignConstant (double d, bool assignImag=false);
	string ToString() const;
	bool SizeTest(const mxWrapperSubArray &msa) const;
	void safeSizeOf(mwSize &md, mwSize &m1, mwSize &m2, mwSize &m3, mwSize &m4, mwSize &m5) const;
private:
	mxWrapper* baseWrapper; // mxWrapperSubArray never frees this array.  it only uses it to do indexing
	mxWrapper indices;  // linear indices into *base
	mxWrapper D1, D2, D3, D4, D5;  // subscripted indices (possibly COLON or empty()) into *base.  used to preserve the shape of the subarray after assignment to a new mxWrapper 
};

// note that these are accessible without an instance of mxWrapper 
// they are in here to avoid namespace conflicts
mxWrapper zeros_c(const mxWrapper& m1, bool bComplex); // creates a new matrix of zeros, same size as m1. if bComplex, include an imaginary component
inline mxWrapper zeros(const mxWrapper& m1) { return zeros_c(m1,false); }

mxWrapper zeros_c(mwSize d1, bool bComplex);
inline mxWrapper zeros(mwSize d1) { return zeros_c(d1,false); }

mxWrapper zeros_c(mwSize d1, mwSize d2, bool bComplex);
inline mxWrapper zeros(mwSize d1, mwSize d2) { return zeros_c(d1,d2,false); }

mxWrapper zeros_c(mwSize d1, mwSize d2, mwSize d3, bool bComplex);
inline mxWrapper zeros(mwSize d1, mwSize d2, mwSize d3) { return zeros_c(d1,d2,d3,false); }

mxWrapper zeros_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex);
inline mxWrapper zeros(mwSize d1, mwSize d2, mwSize d3, mwSize d4) { return zeros_c(d1,d2,d3,d4,false); }

mxWrapper zeros_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex);
inline mxWrapper zeros(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5) { return zeros_c(d1,d2,d3,d4,d5,false); }


mxWrapper ones_c(mwSize d1, bool bComplex);
inline mxWrapper ones(mwSize d1) { return ones_c(d1,false); }

mxWrapper ones_c(mwSize d1, mwSize d2, bool bComplex);
inline mxWrapper ones(mwSize d1, mwSize d2) { return ones_c(d1,d2,false); }

mxWrapper ones_c(mwSize d1, mwSize d2, mwSize d3, bool bComplex);
inline mxWrapper ones(mwSize d1, mwSize d2, mwSize d3) { return ones_c(d1,d2,d3,false); }

mxWrapper ones_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex);
inline mxWrapper ones(mwSize d1, mwSize d2, mwSize d3, mwSize d4) { return ones_c(d1,d2,d3,d4,false); }

mxWrapper ones_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex);
inline mxWrapper ones(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5) { return ones_c(d1,d2,d3,d4,d5,false); }

mxWrapper linspace(const mxWrapper& lb, const mxWrapper& ub, const mxWrapper& N=100);
mxWrapper linspace(double lb, double ub, mwSize N=100);
mxWrapper repmat(mxWrapper& A, mwSize M, mwSize N);
mxWrapper ramp(double lb, double step, double ub);
mxWrapper sum(const mxWrapper& w, mwSize d1=1);	//sums entire mxArray	along a given dimension
mxWrapper mean(const mxWrapper& w, mwSize d1=1);	
mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2);
mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3);
mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4);
mxWrapper reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5);

// additional math operators
mxWrapper operator+ (const mxWrapper& A, const mxWrapper& B);
mxWrapper operator- (const mxWrapper& A, const mxWrapper& B);
mxWrapper operator* (const mxWrapper& A, const mxWrapper& B);
mxWrapper operator/ (const mxWrapper& A, const mxWrapper& B);

mxWrapper cos (const mxWrapper& A);
mxWrapper acos (const mxWrapper& A);
mxWrapper sin (const mxWrapper& A);

// boolean logic operators
mxWrapper gt (const mxWrapper &m1, const mxWrapper &m2);  // >
mxWrapper ge (const mxWrapper &m1, const mxWrapper &m2);  // >=
mxWrapper lt (const mxWrapper &m1, const mxWrapper &m2);  // <
mxWrapper le (const mxWrapper &m1, const mxWrapper &m2);  // <=
mxWrapper eq (const mxWrapper &m1, const mxWrapper &m2);  // ==
mxWrapper neq (const mxWrapper &m1, const mxWrapper &m2);  // !=

mxWrapper any(const mxWrapper &m1, const mxWrapper &dim=mxWrapper());
mxWrapper all(const mxWrapper &m1, const mxWrapper &dim=mxWrapper());

// returns 1 for any undefined dimensions
//void safeSizeOf(const mxWrapper& w, unsigned int &n1, unsigned int &n2, unsigned int &n3, unsigned int &n4);
mwSize Size(const mxArray* ma, mwSize dim);

#undef min
#undef max
double min(mxWrapper const &A);
mxWrapper min(mxWrapper const &A, mxWrapper const &B);
double max(mxWrapper const &A);
mxWrapper max(mxWrapper const &A, mxWrapper const &B);
mxWrapper times(mxWrapper const &A, mxWrapper const &B);
mxWrapper find(mxWrapper const &A);

mxWrapper real(mxWrapper const &A);
mxWrapper imag(mxWrapper const &A);
mxWrapper abs(mxWrapper const &A);
mxWrapper sign(mxWrapper const &A);

// 2D only!!!
mxWrapper transpose(mxWrapper const& A);

// yes, this looks annoying but it works
mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B);
mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C);
mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D);
mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E);
mxWrapper vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E, const mxWrapper& F);

mxWrapper horzcat(const mxWrapper& A, const mxWrapper& B);
mxWrapper length(const mxWrapper& A);
mxWrapper rdivide(const mxWrapper& A, const mxWrapper& B);

// these functions use the Matlab Engine -- either too difficult, too Matlab-specific or buggy to implement in C++
Engine *GetEnginePtr(bool requireNewEnginePtr=false);
void CloseEngine(); // must be called when done using these functions
mxWrapper interp1(const mxWrapper& x,const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& method="linear", double extrapval=0);
mxWrapper interp2(const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& yi,const mxWrapper& method="linear", const mxWrapper& extrapval=0);
mxWrapper interp2(const mxWrapper& x,const mxWrapper& y,const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& yi,const mxWrapper& method="linear", const mxWrapper& extrapval=0);
mxWrapper cat(const mxWrapper& d1, const mxWrapper& A, const mxWrapper& B);
mxWrapper fft(const mxWrapper& X, const mxWrapper& N=0, const mxWrapper& dim=1);
mxWrapper ifft(const mxWrapper& X, const mxWrapper& N=0, const mxWrapper& dim=1);
mxWrapper cumsum(const mxWrapper& X, const mxWrapper& dim=1);
mxWrapper power(const mxWrapper& X, const mxWrapper& N);
mxWrapper exp(const mxWrapper& X);
mxWrapper conv(const mxWrapper& X, const mxWrapper& Y);
mxWrapper mtimes(const mxWrapper& X, const mxWrapper& Y);
mxWrapper mod(const mxWrapper& X, const mxWrapper& Y);
mxWrapper sqrt(mxWrapper const &A);
mxWrapper meshgrid(mxWrapper *out, mxWrapper const&x, mxWrapper const&y);
mxWrapper meshgrid(mxWrapper *outY, mxWrapper *outZ, mxWrapper const&x, mxWrapper const&y, mxWrapper const&z);
mxWrapper floor(mxWrapper const& A);
mxWrapper log(mxWrapper const& A);
mxWrapper shiftdim(mxWrapper const& X);
mxWrapper shiftdim(mxWrapper const& X, mxWrapper const& N);
mxWrapper squeeze(mxWrapper const& X);
mxWrapper conj(mxWrapper const& X);
mxWrapper pow2(mxWrapper const& X);
mxWrapper diff(mxWrapper const& X);
mxWrapper inv(mxWrapper const& X);
mxWrapper nextpow2(mxWrapper const& X);
void ind2sub(mxWrapper *o1, mxWrapper *o2, mxWrapper *o3, mxWrapper const& sz, mxWrapper const& IND);
mxWrapper min(mxWrapper *IND, mxWrapper const &A);
mxWrapper max(mxWrapper *IND, mxWrapper const &A);
mxWrapper randn(const mxWrapper& sz);

BOOL save(const string& fName, const string& s1, mxWrapper const& v1);
BOOL load(const string& fName, const string& s1, mxWrapper *v1);

mxWrapper lininterp1f_wrapper(const mxWrapper& x,const mxWrapper& Y,const mxWrapper& xi, double extrapval=0);

// test functions
int mxTestWrappers();
int mxTestEngine();

// fix deficiencies in standard math libraries
//inline double log(int i) { return std::log(static_cast<double>(i)); }
//inline double floor(int i) { return std::floor(static_cast<double>(i)); }

}

ostream &operator<<(ostream &os, const mxException &mx1);
ostream &operator<<(ostream &os, const mxWrapperNS::mxWrapper &mx1);
ostream &operator<<(ostream &os, const mxWrapperNS::mxWrapperSubArray &msa);
