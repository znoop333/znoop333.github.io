//mxWrapper.cpp
#include "stdafx.h"

#include "mxWrapper.h"
#include "matrix.h"
#include "mat.h"

#include "engine.h"
#include "log.h"

#include <stdarg.h>
#include <math.h>

#include <algorithm>
using std::transform;
#include <functional>
using std::modulus;
using std::pointer_to_unary_function;
using std::pointer_to_binary_function;
using std::bind2nd;
using std::fill_n;

#include <iterator>
using std::back_inserter;

#include <complex>
using std::complex;

#include <climits>
#include <cfloat>

// these libraries are required regardless of what matlab version is used
#if defined(Matlab6p1)
#pragma		comment(lib, "libmx")
#pragma		comment(lib, "libeng")
#else
#pragma		comment(lib, "libut")
#pragma		comment(lib, "libmx")
#pragma		comment(lib, "libeng")
#endif

// the usage of std::copy in this file is correct, but the VSC++ compiler complains about it a lot
// it doesn't like implicitely casting one datatype to another when using copy().
// this is a known problem in MSVC 2008 and newer (see "Cannot suppress warning in template function" Bug 442051 on Microsoft Connect).  the only solution is to use transform instead of copy with the following helper functions which perform an explicit cast.

template <typename T>
inline double castToDouble (T i) { return static_cast<double> (i); }

template <typename T>
inline float castToFloat (T i) { return static_cast<float> (i); }




// not intended for use outside this file

static signed long int numMxArraysAllocated=0;
static signed long int numMxArraysDeletedNotOwned=0;
CCriticalSection mxWrapperNS::mxWrapper::ccEngine;

using mxWrapperNS::mxWrapper;
using mxWrapperNS::mxWrapperEngEvalString;
using mxWrapperNS::GetEnginePtr;
using mxWrapperNS::mxWrapperSubArray;
using mxWrapperNS::ones;
using mxWrapperNS::zeros;
using mxWrapperNS::sum;
using mxWrapperNS::transpose;
using mxWrapperNS::empty;
using mxWrapperNS::linspace;
using mxWrapperNS::mxWrapperEnd;
using mxWrapperNS::mxWrapperColon;
using mxWrapperNS::ramp;
using mxWrapperNS::cat;

mxWrapper::mxWrapper()
{
	m_bIsCOLON=false;
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
}

mxWrapper::~mxWrapper()
{
}


// this constructor DOES create a deep copy
mxWrapper::mxWrapper(const mxWrapper &m1)
{
	m_bIsCOLON=false;
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	*this = m1;  // call operator=()
}

mxWrapper::mxWrapper(const mxWrapperSubArray &m1)
{
	m_bIsCOLON=false;
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	*this = m1;  // call operator=()
}

mxWrapper::mxWrapper(unsigned long long initVal)
{
	Mx=vDouble(1,(double)initVal);
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
	m_bIsCOLON=false;
}

mxWrapper::mxWrapper(unsigned int initVal)
{
	Mx=vDouble(1,(double)initVal);
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
	m_bIsCOLON=false;
}

mxWrapper::mxWrapper(signed int initVal)
{
	Mx=vDouble(1,(double)initVal);
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
	m_bIsCOLON=false;
}

mxWrapper::mxWrapper(double initVal)
{
	Mx=vDouble(1,initVal);
	m_bIsCOLON=false;
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
}

mxWrapper::mxWrapper(double lb, double step, double ub)
{
	m_bIsCOLON=false;
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	*this = ramp(lb, step, ub);
}

mxWrapper::mxWrapper(float initVal)
{
	Mx=vDouble(1,(double)initVal);
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
	m_bIsCOLON=false;
}

mxWrapper::mxWrapper(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex)
{
	m_bIsCOLON=false;
	nDim=5;Dim1=d1;Dim2=d2;Dim3=d3;Dim4=d4;Dim5=d5;
	Mx=vDouble(d1*d2*d3*d4*d5,0);
	if (bComplex)
		MxI=vDouble(d1*d2*d3*d4*d5,0);
}

mxWrapper::mxWrapper(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex)
{
	m_bIsCOLON=false;
	nDim=4;Dim1=d1;Dim2=d2;Dim3=d3;Dim4=d4;Dim5=0;
	Mx=vDouble(d1*d2*d3*d4,0);
	if (bComplex)
		MxI=vDouble(d1*d2*d3*d4,0);
}
mxWrapper::mxWrapper(mwSize d1, mwSize d2, mwSize d3, bool bComplex)
{
	m_bIsCOLON=false;
	nDim=3;Dim1=d1;Dim2=d2;Dim3=d3;Dim4=0;Dim5=0;
	Mx=vDouble(d1*d2*d3,0);
	if (bComplex)
		MxI=vDouble(d1*d2*d3,0);
}
mxWrapper::mxWrapper(mwSize d1, mwSize d2, bool bComplex)
{
	m_bIsCOLON=false;
	nDim=2;Dim1=d1;Dim2=d2;Dim3=Dim4=0;Dim5=0;
	Mx=vDouble(d1*d2,0);
	if (bComplex)
		MxI=vDouble(d1*d2,0);
}

mxWrapper::mxWrapper(const mxWrapper &m1, mwSize md, mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5)
{
	m_bIsCOLON=false;
	Mx=m1.Mx;
	MxI=m1.MxI;
	nDim=md;Dim1=d1;Dim2=d2;Dim3=d3;Dim4=d4;Dim5=d5;
	switch (md)
	{
	case 2:
		ASSERT( d1 > 0 );
		ASSERT( d2 > 0 );
		ASSERT( m1.getNumberElements() == d1*d2 );
		break;
	case 3:
		ASSERT( d1 > 0 );
		ASSERT( d2 > 0 );
		ASSERT( d3 > 0 );
		ASSERT( m1.getNumberElements() == d1*d2*d3 );
		break;
	case 4:
		ASSERT( d1 > 0 );
		ASSERT( d2 > 0 );
		ASSERT( d3 > 0 );
		ASSERT( d4 > 0 );
		ASSERT( m1.getNumberElements() == d1*d2*d3*d4 );
		break;
	case 5:
		ASSERT( d1 > 0 );
		ASSERT( d2 > 0 );
		ASSERT( d3 > 0 );
		ASSERT( d4 > 0 );
		ASSERT( d5 > 0 );
		ASSERT( m1.getNumberElements() == d1*d2*d3*d4*d5 );
		break;
	default:
		ASSERT( false );
		break;
	}
}

mxWrapper::mxWrapper(bool initVal, bool isColon)
{
	Mx=vDouble(1,(double)initVal);
	nDim=2;Dim1=1;Dim2=1;Dim3=Dim4=Dim5=0;
	m_bIsCOLON=isColon;
}

mxWrapper::mxWrapper(const char* name)
{
	MxName=name;
	Mx.clear();
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	m_bIsCOLON=false;
}


// engine retrieval constructor
mxWrapper::mxWrapper(Engine *ep, const char* name)
{
	Mx.clear();
	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	get(ep, name);
	m_bIsCOLON=false;
}

//mxArray constructor: copies data from existing C-style arrays
mxWrapper::mxWrapper(mwSize rows, mwSize cols, const double *dataReal, const double *dataImag)
{
	ASSERT( dataReal != NULL );
	nDim=2;Dim1=rows;Dim2=cols;Dim3=Dim4=Dim5=0;
	Mx.assign(dataReal, dataReal+rows*cols);

	if (dataImag != NULL)
	{
		MxI.assign(dataImag, dataImag+rows*cols);
	}
	else
	{
		MxI.clear();
	}

	m_bIsCOLON=false;
}

//mxArray constructor, special exception: copies data from existing C-style arrays and casts it as doubles
mxWrapper::mxWrapper(mwSize rows, mwSize cols, const unsigned short *dataReal)
{
	ASSERT( dataReal != NULL );
	mwSize N = rows*cols;
	ASSERT( N != 0 );

	Mx.clear();
	transform(dataReal, dataReal+N, back_inserter(Mx), castToDouble<unsigned short>);
	nDim=2;Dim1=rows;Dim2=cols;Dim3=Dim4=Dim5=0;

	m_bIsCOLON=false;
}

//mxArray constructor, special exception: copies data from existing C-style arrays and casts it as doubles
mxWrapper::mxWrapper(mwSize rows, mwSize cols, const float *dataReal)
{
	ASSERT( dataReal != NULL );
	mwSize N = rows*cols;
	ASSERT( N != 0 );

	Mx.clear();
	transform(dataReal, dataReal+N, back_inserter(Mx), castToDouble<float>);
	nDim=2;Dim1=rows;Dim2=cols;Dim3=Dim4=Dim5=0;

	m_bIsCOLON=false;
}

double* mxWrapper::getPr() 
{
	if(Mx.empty())
		return NULL;

	return &Mx[0];
}

const double* mxWrapper::getPr() const 
{
	if(Mx.empty())
		return NULL;

	return &Mx[0];
}

double* mxWrapper::getPi()
{
	if(MxI.empty())
		return NULL;

	return &MxI[0];
}

const double* mxWrapper::getPi() const
{
	if(MxI.empty())
		return NULL;

	return &MxI[0];
}



CStringA mxWrapperNS::MakeMxEngineSafeString(const CStringA& cs)
{
	// Sanitize string -- engEvalString won't work right if any special characters appear.
	// MakeMxEngineSafeString fixes the string by removing unsafe characters.  

	// e.g., if you wanted to run something like: engEvalString("mystring = '%s';");
	// and you replaced %s by a string containing: "mouse's left leg"
	// engEvalString will silently fail because the apostrophy makes the matlab command parses wrong

	CStringA result=cs;
	result.Remove('\'');
	result.Remove('\"');
	result.Replace(';',' ');
	result.Replace('\n',' ');
	result.Replace('\r',' ');
	result.Replace('\t',' ');
	return result;
}


void mxWrapperNS::mxWrapperEngEvalString(Engine *ep, LPCTSTR cmd)
{
	int result=0;
	FILE_LOG(logDEBUG4)<<"Executing Matlab Engine command: " << cmd;

	CSingleLock sLock(&mxWrapper::ccEngine);
	sLock.Lock();    
	if (sLock.IsLocked())
	{
		result = engEvalString(ep,cmd);
    sLock.Unlock();
	}
	else
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	if( result != 0 )
		throw( runtime_error("Matlab Engine mxWrapperEngEvalString FAILED") );
}

mxArray* mxWrapper::CreateMxArray(mxClassID classid) const
{
	mxArray *pMx = NULL;

	if( IsEmpty() && MxName.IsEmpty() )
	{
		FILE_LOG(logWARNING) << "mxWrapper::put can't put an empty matrix into Matlab";
		return NULL; 
	}

// 1. allocate mxArray pointer
	mwSize dims[5] = {0,0,0,0,0}; 
	if( classid == mxDOUBLE_CLASS || classid == mxSINGLE_CLASS )
	{
		ASSERT( getNumberElements() > 0 );

		ASSERT(Dim1>0);
		dims[0] = Dim1; 

		ASSERT(Dim2>0);
		dims[1] = Dim2; 

		if(Dim3>0)
			dims[2] = Dim3; 

		if(Dim4>0)
			dims[3] = Dim4; 

		if(Dim5>0)
			dims[4] = Dim5; 

		CSingleLock sLock(&ccEngine);
		sLock.Lock();    
		if (!sLock.IsLocked())
			throw( runtime_error("Failed to enter the Matlab Engine critical section") );

		pMx=mxCreateNumericArray(nDim,&dims[0],classid, IsComplex() ? mxCOMPLEX : mxREAL);
		if(pMx == NULL)
		{
			FILE_LOG(logERROR)<<"mxWrapper::mxCreateNumericArray() failed. Out of memory?";
			sLock.Unlock();    
			return NULL;
		}

		sLock.Unlock();    
	}
	else if (classid == mxCHAR_CLASS )
	{
		CSingleLock sLock(&ccEngine);
		sLock.Lock();    		
		if (!sLock.IsLocked())
			throw( runtime_error("Failed to enter the Matlab Engine critical section") );

		pMx=mxCreateString(MxName);
		if(pMx == NULL)
		{
			FILE_LOG(logERROR)<<"mxWrapper::mxCreateString() failed. Out of memory?";
			sLock.Unlock();    
			return NULL;
		}

		sLock.Unlock();
	}
	else
	{
		// unsupported Matlab data type
		ASSERT(FALSE);
	}

	// 2. copy data into mxArray pointer

	ASSERT(pMx != NULL);

	CSingleLock sLock(&ccEngine);
	sLock.Lock(); 		
	if (!sLock.IsLocked())
	{
		mxDestroyArray(pMx);
		sLock.Unlock();
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );
		return NULL;
	}

	if( classid == mxDOUBLE_CLASS )
	{
		double *pR=mxGetPr(pMx);
		ASSERT(pR != NULL);
		copy(Mx.begin(),Mx.end(), pR);

		if(IsComplex())
		{
			double *pI=mxGetPi(pMx);
			ASSERT(pI != NULL);
			copy(MxI.begin(),MxI.end(), pI);
		}
	}
	else if( classid == mxSINGLE_CLASS )
	{
		float *pR=(float *)mxGetData(pMx);
		ASSERT(pR != NULL);
		transform(Mx.begin(),Mx.end(), pR, castToFloat<double>);

		if(IsComplex())
		{
			float *pI=(float *)mxGetImagData(pMx);
			ASSERT(pI != NULL);
			transform(MxI.begin(),MxI.end(), pI, castToFloat<double>);
		}
	}
	else if( classid == mxCHAR_CLASS )
	{
		// nothing to do, mxCreateString already copied the string
		;
	}
	else 
	{
		// unsupported Matlab data type
		ASSERT(FALSE);
	}

	sLock.Unlock();

	// 3. if we reached this point, pMx should be a valid mxArray
	return pMx;
}

BOOL mxWrapper::putHelper(Engine *ep, const char* name, mxArray *pMx) const
{
	// putHelper takes ownership of pMx and frees it
	VERIFY(ep != NULL);
	VERIFY(name != NULL);
	VERIFY(pMx != NULL);

	CSingleLock sLock(&ccEngine);
	sLock.Lock();    
	if (!sLock.IsLocked())
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	try 
	{
#if defined(Matlab6p1)
		mxSetName(pMx, name);
		if( engPutArray(ep, pMx) )
#else
		if( engPutVariable(ep, name, pMx) )
#endif
		{
			FILE_LOG(logERROR)<<"engPutVariable failed. Bad Matlab Engine pointer?";
			mxDestroyArray(pMx);
			sLock.Unlock();
			return FALSE;
		}
	}
	catch (...)
	{
		// if the array is too big, Matlab will throw a MathWorks::System::SimpleException here
		mxDestroyArray(pMx);
		sLock.Unlock();    
		return FALSE;
	}

	mxDestroyArray(pMx);
	sLock.Unlock();    
	return TRUE;
}

BOOL mxWrapper::put(Engine *ep, const char* name) const
{
	ASSERT(ep!=NULL);
	BOOL isString = !MxName.IsEmpty();

	if( IsEmpty() && !isString )
	{
		// attempting to put an empty mxWrapper into Matlab. rather than attempt and fail to allocate memory for it, just create it as an empty variable in the current workspace.
		CStringA temp;
		temp.Format("%s = [];", MakeMxEngineSafeString(name));
		mxWrapperEngEvalString(ep, temp);
		return TRUE;
	}


	mxArray *pMx = CreateMxArray( isString ? mxCHAR_CLASS : mxDOUBLE_CLASS );
	if( pMx == NULL )
	{
		FILE_LOG(logERROR)<<"CreateMxArray failed. Out of memory?";
		return FALSE;
	}

	if(putHelper(ep, name, pMx))
		return TRUE;

	if(!isString)
	{
		FILE_LOG(logERROR)<<"mxWrapper::put() failed as doubles. Array size too big? Trying again as float instead of double.";
		pMx = CreateMxArray(mxSINGLE_CLASS);

		if(putHelper(ep, name, pMx))
			return TRUE;

		FILE_LOG(logERROR)<<"mxWrapper::put() failed as floats. Array must be too big to fit into memory!";
	}

	// if we reach this point, either a long string or large data array failed to transfer to the Matlab Engine
	// final attempt: write the data into a .mat file in a temporary directory, 
	// then use the load command in matlab to read it.  this can work around the size limitations of Windows COM.

	std::string filename("c:\\mxWrapper_put.mat" );
	if (save(filename,name,*this))
	{
		std::string cmd ("load \'" + filename + "\' " + name);
		mxWrapperEngEvalString(ep, cmd.c_str());

		// delete the temporary .mat file
		DeleteFile(filename.c_str());

		return TRUE;
	}

	FILE_LOG(logERROR)<<"mxWrapper::put() completely failed. Is Matlab installed incorrectly?";

	return FALSE;
}

BOOL mxWrapper::LoadFromMxArray(mxArray* pMx)
{
	VERIFY( pMx != NULL );

	CSingleLock sLock(&ccEngine);
	sLock.Lock(); 
	if (!sLock.IsLocked())
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	empty();

	if (mxGetClassID(pMx) == mxCHAR_CLASS) 
	{
		nDim=2;
		Dim1=1;
		Dim2=mxGetM(pMx)*mxGetN(pMx)*sizeof(mxChar)+1;

		LPTSTR p = MxName.GetBuffer( Dim2 );
		int status = mxGetString(pMx, p, Dim2); 
		ASSERT( !status );
		MxName.ReleaseBuffer( );
	}
	else if ( (mxGetClassID(pMx) == mxDOUBLE_CLASS) || (mxGetClassID(pMx) == mxSINGLE_CLASS) )
	{
		nDim = mxGetNumberOfDimensions(pMx);
		const mwSize *m_dims = mxGetDimensions(pMx);

		if(nDim>=1)
			Dim1=m_dims[0];
		else
			Dim1=0;

		if(nDim>=2)
			Dim2=m_dims[1];
		else
			Dim2=0;

		if(nDim>=3)
			Dim3=m_dims[2];
		else
			Dim3=0;

		if(nDim>=4)
			Dim4=m_dims[3];
		else
			Dim4=0;

		if(nDim>=5)
			Dim5=m_dims[4];
		else
			Dim5=0;

		if (mxGetClassID(pMx) == mxDOUBLE_CLASS) 
		{
			Mx.assign(mxGetPr(pMx), mxGetPr(pMx)+mxGetNumberOfElements(pMx));

			if(mxIsComplex(pMx))
				MxI.assign(mxGetPi(pMx), mxGetPi(pMx)+mxGetNumberOfElements(pMx));
		}
		else if (mxGetClassID(pMx) == mxSINGLE_CLASS) 
		{
			float *pR=(float *)mxGetData(pMx);
			Mx.assign(pR, pR+mxGetNumberOfElements(pMx));

			if(mxIsComplex(pMx))
			{
				float *pI=(float *)mxGetImagData(pMx);
				MxI.assign(pI, pI+mxGetNumberOfElements(pMx));
			}
		}

		mwSize M = mxGetNumberOfElements(pMx);
		mwSize P = getNumberElements();
		ASSERT( M == P );

	}
	else
	{
		// unsupported Matlab data type
		ASSERT(false);
	}

	mxDestroyArray(pMx);

	sLock.Unlock(); 
	return TRUE;
}

BOOL mxWrapper::get(Engine *ep, const char* name)
{
	if(ep==NULL)
		return FALSE;

	CSingleLock sLock(&ccEngine);
	sLock.Lock(); 
	if (!sLock.IsLocked())
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	mxArray *pMx;
#if defined(Matlab6p1)
	pMx=engGetArray(ep, name); 
#else
	pMx=engGetVariable(ep, name); 
#endif
	if (pMx == NULL)
	{
		FILE_LOG(logERROR)<<"Engine variable not found: "<< name;
		sLock.Unlock();
		empty();
		return FALSE;
	}

	sLock.Unlock();

	return LoadFromMxArray(pMx);
}



void mxWrapper::AssignConstant(double c, bool assignImag)
{
	Mx.assign( Mx.size(), c );
	if (assignImag)
		MxI.assign( Mx.size(), c );
}

void mxWrapper::AssignAt(mwSize idx, double d, bool assignImag)
{
	if (!assignImag)
		Mx[idx-1]=d;
	else
		MxI[idx-1]=d;
}



// at most n elements will be written into destReal.
void mxWrapper::ExtractData(double* destReal, mwSize n)
{
	ASSERT( destReal != NULL );

	mwSize srcElements = getNumberElements();
	if (n == 0)
		n = srcElements;
	else if( n > srcElements )
		n = srcElements;

	ASSERT( Mx.size() >= n );

	copy(Mx.begin(), Mx.begin()+n, destReal);
}

void mxWrapper::ExtractData(double* destReal, double* destImag, mwSize n)
{
	ASSERT( destReal != NULL );
	ASSERT( destImag != NULL );

	mwSize srcElements = getNumberElements();
	if (n == 0)
		n = srcElements;
	else if( n > srcElements )
		n = srcElements;

	ASSERT( Mx.size() >= n );
	ASSERT( MxI.size() >= n );

	copy(Mx.begin(), Mx.begin()+n, destReal);
	copy(MxI.begin(), MxI.begin()+n, destImag);
}




bool mxWrapper::IsEmpty() const
{
	return ( Mx.empty() );
}

mwSize mxWrapper::Size() const
{
	if(IsEmpty())
		return 0;
	return nDim;
}

mwSize mxWrapper::Size(mwSize dim) const
{
	if( dim > nDim )
		return 1;

	switch (dim)
	{
	case 1:
		return Dim1;
		break;
	case 2:
		return Dim2;
		break;
	case 3:
		return Dim3;
		break;
	case 4:
		return Dim4;
		break;
	case 5:
		return Dim5;
		break;
	default:
		ASSERT( false );
		return 0;
		break;
	}
}

mwSize mxWrapper::Size(mwSize* dims, mwSize maxdims) const
{
	ASSERT( dims != NULL );

	// matlab defines the size of any higher order dimensions to be 1
	fill_n(dims, maxdims, 1);

	if( IsEmpty() )
		return 0;

	switch (maxdims)
	{
	case 5:
		dims[4]=Dim5;
		// intentional fall-through
	case 4:
		dims[3]=Dim4;
	case 3:
		dims[2]=Dim3;
	case 2:
		dims[1]=Dim2;
		dims[0]=Dim1;
		break;
	default:
		ASSERT( false );
		return 0;
		break;
	}
	return nDim;
}

mwSize mxWrapper::Size(mxWrapper& dims) const
{
	ASSERT( nDim > 0 );

	dims = ones(1,nDim);
	switch (nDim)
	{
	case 5:
		dims.Mx[4]=Dim5;
		// intentional fall-through
	case 4:
		dims.Mx[3]=Dim4;
	case 3:
		dims.Mx[2]=Dim3;
	case 2:
		dims.Mx[1]=Dim2;
		dims.Mx[0]=Dim1;
		break;
	default:
		ASSERT( false );
		return 0;
		break;
	}

	return nDim;
}

void mxWrapper::empty()
{
	if(!Mx.empty())
		Mx.clear();

	if(!MxI.empty())
		MxI.clear();

	nDim=0;Dim1=Dim2=Dim3=Dim4=Dim5=0;
	MxName.Empty();
}


double mxWrapper::ExtractScalar(mwSize i) const
{
	// note that the Matlab indexing starts at 1 (not zero!)
	// however, C indexing starts from zero.  thus, subtract 1 from the index.
	return Mx[i-1];
}

double mxWrapper::ExtractScalar(double &c, mwSize i) const
{
	ASSERT(i > 0);
	ASSERT(i <= getNumberElements());
	mwSize numEl = getNumberElements();

	if( IsComplex() )
		c = MxI[i-1];
	else
		c = 0;

	return Mx[i-1];
}

double mxWrapper::ExtractScalarImag(mwSize i) const
{
	return MxI[i-1];
}

void mxWrapper::ReallocImag()
{
	// don't do anything if we already have an imaginary component
	if ( IsComplex() )
		return;

	MxI = vDouble( getNumberElements(), 0 );
}

void mxWrapper::ReallocReal()
{
	// don't do anything if we do not have an imaginary component
	if (! IsComplex() )
		return;

	MxI.clear();
}

/// returns number of data elements in the array
// @see mxGetDimensions
mwSize mxWrapper::getNumberElements() const
{
	if (IsEmpty())
		return 0;
	int nElem=0;
	switch (nDim)
	{
	case 2:
		nElem=Dim1*Dim2;
		break;
	case 3:
		nElem=Dim1*Dim2*Dim3;
		break;
	case 4:
		nElem=Dim1*Dim2*Dim3*Dim4;
		break;
	case 5:
		nElem=Dim1*Dim2*Dim3*Dim4*Dim5;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return nElem;
}

//finds the minimum from mxArray 
double mxWrapper::minElement()	const
{
	if (IsEmpty())
		return -DBL_MAX;
	return *min_element(Mx.begin(), Mx.end());
}

double mxWrapperNS::min(mxWrapper const &A)
{
	return A.minElement();
}

mxWrapper mxWrapperNS::min(mxWrapper const &A, mxWrapper const &B)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"min";
		result = A;
	}
	else
	{
		A.put(ep, "mxWrapper_min_A");
		B.put(ep, "mxWrapper_min_B");
		mxWrapperEngEvalString(ep,"mxWrapper_min_result=min(mxWrapper_min_A, mxWrapper_min_B);");
		result.get(ep, "mxWrapper_min_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_min_result mxWrapper_min_A mxWrapper_min_B");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_min=mxWrapper_min+1; catch, mxWrapper_min=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::min(mxWrapper *IND, mxWrapper const &A)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"min";
		result = A;
	}
	else
	{
		A.put(ep, "mxWrapper_min_A");
		mxWrapperEngEvalString(ep,"[mxWrapper_min_result, mxWrapper_min_result_IND]=min(mxWrapper_min_A);");
		result.get(ep, "mxWrapper_min_result");
		IND->get(ep, "mxWrapper_min_result_IND");
		mxWrapperEngEvalString(ep,"clear mxWrapper_min_result mxWrapper_min_result_IND mxWrapper_min_A");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_min2=mxWrapper_min2+1; catch, mxWrapper_min2=1; end");
#endif
	}

	return result;
}

//finds the maximum from mxArray,
double mxWrapper::maxElement()	const
{
	if (IsEmpty())
		return DBL_MAX;
	return *max_element(Mx.begin(), Mx.end());
}

double mxWrapperNS::max(mxWrapper const &A)
{
	return A.maxElement();
}

mxWrapper mxWrapperNS::max(mxWrapper const &A, mxWrapper const &B)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"max";
		result = A;
	}
	else
	{
		A.put(ep, "mxWrapper_max_A");
		B.put(ep, "mxWrapper_max_B");
		mxWrapperEngEvalString(ep,"mxWrapper_max_result=max(mxWrapper_max_A, mxWrapper_max_B);");
		result.get(ep, "mxWrapper_max_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_max_result mxWrapper_max_A mxWrapper_max_B");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_max=mxWrapper_max+1; catch, mxWrapper_max=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::max(mxWrapper *IND, mxWrapper const &A)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"max";
		result = A;
	}
	else
	{
		A.put(ep, "mxWrapper_max_A");
		mxWrapperEngEvalString(ep,"[mxWrapper_max_result, mxWrapper_max_result_IND]=max(mxWrapper_max_A);");
		result.get(ep, "mxWrapper_max_result");
		IND->get(ep, "mxWrapper_max_result_IND");
		mxWrapperEngEvalString(ep,"clear mxWrapper_max_result mxWrapper_max_result_IND mxWrapper_max_A");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_max2=mxWrapper_max2+1; catch, mxWrapper_max2=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::randn(const mxWrapper& sz)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL || sz.IsEmpty() )
	{
		FILE_LOG(logDEBUG4)<<"randn";
		return result;
	}

	sz.put(ep, "mxWrapper_randn_sz");
	mxWrapperEngEvalString(ep,"mxWrapper_randn_result=randn(mxWrapper_randn_sz);");
	result.get(ep, "mxWrapper_randn_result");

#ifdef _DEBUG
	mxWrapperEngEvalString(ep,"try, mxWrapper_randn=mxWrapper_randn+1; catch, mxWrapper_randn=1; end");
#else
	mxWrapperEngEvalString(ep,"clear mxWrapper_randn_result mxWrapper_randn_sz ");
#endif

	return result;
}

const char *mxWrapper::GetClassName() const
{
	if (MxName.IsEmpty())
		return _T("MxDOUBLE");
	else
		return _T("String");
}

CString mxWrapper::GetString() const
{
	return MxName;
}

void mxWrapperNS::safeSizeOf(const mxWrapper& w, mwSize &nd, mwSize &n1, mwSize &n2, mwSize &n3, mwSize &n4, mwSize &n5)
{
	nd = w.nDim;
	n1 = w.Dim1;
	n2 = w.Dim2;
	n3 = w.Dim3;
	n4 = w.Dim4;
	n5 = w.Dim5;
	ASSERT( nd >= 2 );
}

mxWrapper mxWrapperNS::zeros_c(const mxWrapper& m1, bool bComplex)
{
	if( m1.IsEmpty() )
		return mxWrapper();

	mwSize nd, n1, n2, n3, n4, n5;
	safeSizeOf(m1, nd, n1, n2, n3, n4, n5);

	mxWrapper result;
	switch ( nd )
	{
		case 2:
			ASSERT ( n1 > 0 );
			ASSERT ( n2 > 0 );
			result = zeros_c(n1,n2, bComplex);
			break;
		case 3:
			ASSERT ( n1 > 0 );
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			result = zeros_c(n1,n2,n3, bComplex);
			break;
		case 4:
			ASSERT ( n1 > 0 );
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			ASSERT ( n4 > 0 );
			result = zeros_c(n1,n2,n3,n4, bComplex);
			break;
		case 5:
			ASSERT ( n1 > 0 );
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			ASSERT ( n4 > 0 );
			ASSERT ( n5 > 0 );
			result = zeros_c(n1,n2,n3,n4,n5, bComplex);
			break;
		default:
			ASSERT ( FALSE );
			break;
	}

	return result;
}

mxWrapper mxWrapperNS::zeros_c(mwSize d1, bool bComplex)
{
	return zeros_c(d1,d1, bComplex);
}

inline mxWrapper mxWrapperNS::zeros_c(mwSize d1, mwSize d2, bool bComplex)
{
	return mxWrapper(d1, d2, bComplex);
}

inline mxWrapper mxWrapperNS::zeros_c(mwSize d1, mwSize d2, mwSize d3, bool bComplex)
{
	return mxWrapper(d1, d2, d3, bComplex);
}

inline mxWrapper mxWrapperNS::zeros_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex)
{
	return mxWrapper(d1, d2, d3, d4, bComplex);
}

inline mxWrapper mxWrapperNS::zeros_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex)
{
	return mxWrapper(d1, d2, d3, d4, d5, bComplex);
}

inline mxWrapper mxWrapperNS::ones_c(mwSize d1, bool bComplex)
{
	return ones(d1,d1,bComplex);
}

inline mxWrapper mxWrapperNS::ones_c(mwSize d1, mwSize d2, bool bComplex)
{
	mxWrapper w1 = zeros_c(d1,d2,bComplex);
	w1.AssignConstant(1);
	return w1;
}

inline mxWrapper mxWrapperNS::ones_c(mwSize d1, mwSize d2, mwSize d3, bool bComplex)
{
	mxWrapper w1 = zeros_c(d1,d2,d3,bComplex);
	w1.AssignConstant(1);
	return w1;
}

inline mxWrapper mxWrapperNS::ones_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, bool bComplex)
{
	mxWrapper w1 = zeros_c(d1,d2,d3,d4,bComplex);
	w1.AssignConstant(1);
	return w1;
}

inline mxWrapper mxWrapperNS::ones_c(mwSize d1, mwSize d2, mwSize d3, mwSize d4, mwSize d5, bool bComplex)
{
	mxWrapper w1 = zeros_c(d1,d2,d3,d4,d5,bComplex);
	w1.AssignConstant(1);
	return w1;
}

mxWrapper mxWrapperNS::linspace(const mxWrapper& lb, const mxWrapper& ub, const mxWrapper& N)
{
	return mxWrapper( linspace(lb.ExtractScalar(1), ub.ExtractScalar(1), static_cast<mwSize>(N.ExtractScalar(1))) );
}

mxWrapper mxWrapperNS::linspace(double lb, double ub, mwSize N)
{
	if ( N == 0 ) 
		return mxWrapper(ub);

	ASSERT( N > 0 );
	mxWrapper w1 = zeros(1,N);

	if (N==1)
	{
		w1.AssignAt(1, lb);
	}
	else
	{
		double *temp1 = w1.getPr();	
		for(mwSize i=0; i<N; i++)
			temp1[i]=(ub-lb)/static_cast<double>(N-1)*static_cast<double>(i)  +  lb;
	}

	return w1;
}

inline const mxWrapper& mxWrapperNS::empty()
{
	// an existing mxWrapper can be freed using this syntax:
	//		mxWrapper A = linspace(1, 10, 1);
	//		A = empty();
	static mxWrapper w1;  // w1.mPx will be NULL, and the receiving mxWrapper will free its memory
	//w1.empty();
	return w1;
}

inline mxWrapper mxWrapperNS::ramp(double lb, double step, double ub)
{
	// this function is only an approximation of the true matlab colon operator, which has very complicated logic to deal with round-off errors.  
	// @see "How does the COLON operator work?" Mathworks Solution ID: 1-4FLI96
	// http://www.mathworks.com/support/solutions/en/data/1-4FLI96/index.html?solution=1-4FLI96

	ASSERT( step != 0 );
	//ASSERT( lb != ub );

	mwSize N = static_cast<mwSize>( (ub-lb) / step ) + 1;
	ASSERT( N>0 );

	mxWrapper w1 = zeros(1,N);
	double *temp1 = w1.getPr();	

	for(mwSize i=0; i< N; i++)
		temp1[i]= lb + step*static_cast<double>(i) ;

	return w1;
}

mxWrapper mxWrapperNS::reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5)
{
	int D1,D2,D3,D4,D5;

	if(d1.IsEmpty())
	{
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D5=(int)d5.ExtractScalar(1);
		D1= A.getNumberElements() / (D2*D3*D4*D5);
	} else if(d2.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D5=(int)d5.ExtractScalar(1);
		D2= A.getNumberElements() / (D1*D3*D4*D5);
	} else if(d3.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D5=(int)d5.ExtractScalar(1);
		D3= A.getNumberElements() / (D1*D2*D4*D5);
	} else if(d4.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D5=(int)d5.ExtractScalar(1);
		D4= A.getNumberElements() / (D1*D2*D3*D5);
	} else if(d5.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D5= A.getNumberElements() / (D1*D2*D3*D4);
	} else {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D5=(int)d5.ExtractScalar(1);
	}

	ASSERT( A.getNumberElements() == D1*D2*D3*D4*D5 );
	return mxWrapper (A, 5, D1, D2, D3, D4, D5); 
}

mxWrapper mxWrapperNS::reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4)
{
	int D1,D2,D3,D4,D5=0;

	if(d1.IsEmpty())
	{
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D1= A.getNumberElements() / (D2*D3*D4);
	} else if(d2.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D2= A.getNumberElements() / (D1*D3*D4);
	} else if(d3.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
		D3= A.getNumberElements() / (D1*D2*D4);
	} else if(d4.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4= A.getNumberElements() / (D1*D2*D3);
	} else {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D4=(int)d4.ExtractScalar(1);
	}

	ASSERT( A.getNumberElements() == D1*D2*D3*D4 );
	return mxWrapper (A, 4, D1, D2, D3, D4, D5); 
}

mxWrapper mxWrapperNS::reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3)
{
	int D1,D2,D3,D4=0,D5=0;

	if(d1.IsEmpty())
	{
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D1= A.getNumberElements() / (D2*D3);
	} else if(d2.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
		D2= A.getNumberElements() / (D1*D3);
	} else if(d3.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3= A.getNumberElements() / (D1*D2);
	} else {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
		D3=(int)d3.ExtractScalar(1);
	}

	ASSERT( A.getNumberElements() == D1*D2*D3 );
	return mxWrapper (A, 3, D1, D2, D3, D4, D5); 
}

mxWrapper mxWrapperNS::reshape(const mxWrapper& A, const mxWrapper& d1, const mxWrapper& d2)
{
	int D1,D2,D3=0,D4=0,D5=0;

	if(d1.IsEmpty())
	{
		D2=(int)d2.ExtractScalar(1);
		D1= A.getNumberElements() / D2;
	} else if(d2.IsEmpty()) {
		D1=(int)d1.ExtractScalar(1);
		D2= A.getNumberElements() / D1;
	} else {
		D1=(int)d1.ExtractScalar(1);
		D2=(int)d2.ExtractScalar(1);
	}

	ASSERT( A.getNumberElements() == D1*D2 );
	return mxWrapper (A, 2, D1, D2, D3, D4, D5); 
}

mxWrapper mxWrapperNS::sum(const mxWrapper& w, mwSize d1)
{
	mxWrapper result;

	if ((w.Size() == 2) && (d1 == 2) && (w.Size(2) == 1))
		// sum of columns along 2D array with only 1 column: no summation needed
		result = w;
	else if ((w.Size() == 2) && (d1 == 1) || ( (w.Size() == 3) && (w.Size(3) == 1) && (d1 == 1) ) )
	{
		// optimize this common case
		mwSize M = w.Size(1);
		mwSize N = w.Size(2);

		result = zeros_c( 1, N, w.IsComplex() );
		double summed, *pR=result.getPr();
		const double *pW=w.getPr();
		for (mwSize i=1; i<=N; i++)
		{
			summed=0;
			for (mwSize j=1; j<=M; j++)
				summed+=pW[ j + (i-1)*N -1];
			pR[i-1] = summed;
		}

		if (w.IsComplex())
		{
			pR=result.getPi(); pW=w.getPi();
			for (mwSize i=1; i<=N; i++)
			{
				summed=0;
				for (mwSize j=1; j<=M; j++)
					summed+=pW[ j + (i-1)*N -1];
				pR[i-1] = summed;
			}
		}

	}
	else if ((w.Size() == 2) && (d1 == 2))
	{
		// optimize another common case
		mwSize M = w.Size(1);
		mwSize N = w.Size(2);

		result = zeros_c( M, 1, w.IsComplex() );
		double summed, *pR=result.getPr();
		const double *pW=w.getPr();
		for (mwSize i=1; i<=M; i++)
		{
			summed=0;
			for (mwSize j=1; j<=N; j++)
				summed += pW[ i + (j-1)*M -1];
			pR[i-1] = summed;
		}

		if (w.IsComplex())
		{
			pR=result.getPi(); pW=w.getPi();
			for (mwSize i=1; i<=M; i++)
			{
				summed=0;
				for (mwSize j=1; j<=N; j++)
					summed += pW[ i + (j-1)*M -1];
				pR[i-1] = summed;
			}
		}
	}
	else 
	{
		// general case: amazingly, it is faster to do the sum in Matlab!
		Engine *ep = GetEnginePtr();

		w.put(ep, "mxWrapper_sum_w");
		mxWrapper d(d1);
		d.put(ep, "mxWrapper_sum_d");
		mxWrapperEngEvalString(ep,"mxWrapper_sum_result=sum(mxWrapper_sum_w, mxWrapper_sum_d);");
		result.get(ep, "mxWrapper_sum_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_sum_result mxWrapper_sum_w mxWrapper_sum_d;");

#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_sum=mxWrapper_sum+1; catch, mxWrapper_sum=1; end");
#endif

	}

	return result;
}

mxWrapper mxWrapperNS::mean(const mxWrapper& w, mwSize d1)
{
	return sum(w,d1)/w.Size(d1);	
}

mxWrapper mxWrapperNS::repmat(mxWrapper& A, mwSize M, mwSize N)
{
	mwSize nd, U, V, n3, n4, n5;
	safeSizeOf(A, nd, U, V, n3, n4, n5);

	ASSERT(M && N); // must be greater than 0

	mwSize UM = U*M;
	mwSize VN = V*N;
	mxWrapper w1 = zeros(UM,VN);
	double *temp1 = w1.getPr(), *p_A = A.getPr();	

	// warning: matlab indexes by rows (u) then by columns (v)
	for(mwSize u=0; u<UM; u++)
		for(mwSize v=0; v<VN; v++)
			temp1[ u + v*UM ] = p_A[ (u % U) + (v % V) * U  ];

	return w1;
}

mxWrapper mxWrapperNS::times(mxWrapper const &A, mxWrapper const &B)
{
	mxWrapper w1( A );
	return w1 *= B;
}

mxWrapper mxWrapperNS::abs(mxWrapper const &A)
{
	mxWrapper result(A);

	if (!A.IsComplex())
		transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::fabs));
	else
	{
		UINT N = A.getNumberElements();
		for(UINT i=0; i<N; ++i)
		{
			complex<double> c( A.Mx[i], A.MxI[i] );
			complex<double> r = abs(c);
			result.Mx[i] = r.real();
			result.MxI[i] = r.imag();
		}
	}

	return result;
}

mxWrapper mxWrapperNS::sign(mxWrapper const &A)
{
	mxWrapper result(A);
	UINT N = A.getNumberElements();

	if (!A.IsComplex())
		for(UINT i=0; i<N; ++i)
		{
			if(A.Mx[i] > 0)
				result.Mx[i] = 1;
			else if(A.Mx[i] < 0)
				result.Mx[i] = -1;
			else 
				result.Mx[i] = 0;
		}
	else
	{
		// matlab definition of complex signum: sign(A) = A/abs(A) if A~=0; 0 otherwise
		mxWrapper B = abs(A);
		for(UINT i=0; i<N; ++i)
		{
			if(B.Mx[i] > 0)
			{
				result.Mx[i] = A.Mx[i]/B.Mx[i];
				result.MxI[i] = A.MxI[i]/B.Mx[i];
			}
			else 
			{
				result.Mx[i] = 0;
				result.MxI[i] = 0;
			}
		}
	}

	return result;
}

inline mxWrapper mxWrapperNS::gt (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 > m2;
}

inline mxWrapper mxWrapperNS::ge (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 >= m2;
}

inline mxWrapper mxWrapperNS::lt (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 < m2;
}

inline mxWrapper mxWrapperNS::le (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 <= m2;
}

inline mxWrapper mxWrapperNS::eq (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 == m2;
}

inline mxWrapper mxWrapperNS::neq (const mxWrapper &m1, const mxWrapper &m2)  
{
	return m1 != m2;
}

mxWrapper mxWrapperNS::any(const mxWrapper &m1, const mxWrapper &dim)
{
	mwSize d1 = 0;
	mwSize nd, n1, n2, n3, n4, n5;
	safeSizeOf(m1, nd, n1, n2, n3, n4, n5);

	if ( dim.IsEmpty() ) // default dimension requested
	{
		if ( n1 == 1 && n2 != 1 && n3 == 1 && n4 == 1 && n5 == 1)
		// special case: a vector should be applied across rows
			d1 = 2;
		else
		// general case: apply down columns
			d1 = 1;
	}
	else
		d1 = static_cast<mwSize> (dim.ExtractScalar(1));

	// sum() will only be non-zero where the condition is true
	mxWrapper result = sum( m1 != 0, d1 );

	// replace the values above 1 with 1 so that all the outputs will be 0 or 1
	result( find(result > 1) ) = 1;

	return result;
}

mxWrapper mxWrapperNS::all(const mxWrapper &m1, const mxWrapper &dim)
{
	mwSize d1 = 0;
	mwSize nd, n1, n2, n3, n4, n5;
	safeSizeOf(m1, nd, n1, n2, n3, n4, n5);

	if ( dim.IsEmpty() ) // default dimension requested
	{
		if ( n1 == 1 && n2 != 1 && n3 == 1 && n4 == 1 && n5 == 1)
		// special case: a vector should be applied across rows
			d1 = 2;
		else
		// general case: apply down columns
			d1 = 1;
	}
	else
		d1 = static_cast<mwSize> (dim.ExtractScalar(1));

	// sum() will be N in each column where all of the elements are non-zero (N is the number of elements in the column)
	mxWrapper result = sum( m1 != 0, d1 );

	switch ( d1 )
	{
	case 1:
		result =  result == n1;
		break;
	case 2:
		result =  result == n2;
		break;
	case 3:
		result =  result == n3;
		break;
	}

	return result;
}

mxWrapper mxWrapperNS::find(mxWrapper const &A)
{
	if( A.getNumberElements() == 0 )
		return mxWrapper();

	mxWrapper result; 
	mwSize numElementsUsed=0;

	const double *pA=A.getPr();
	mwSize N = A.getNumberElements();
	for(mwSize i=1; i<=N; i++)
		if ( pA[i-1] != 0 )
			numElementsUsed++;
		//if ( A.ExtractScalar(i) != 0 )
		//	numElementsUsed++;

	// possible that none are true: return an empty mxWrapper
	if ( numElementsUsed == 0 )
		return mxWrapper();

	// at least one true element
	result = zeros(1, (int)numElementsUsed);

	// reuse numElementsUsed as a counter
	numElementsUsed=0;

	double *pResult=result.getPr();
	for(mwSize i=1; i<=N; i++)
		if ( pA[i-1] != 0 )
			pResult[numElementsUsed++]=i;

	return result;
}

mxWrapper mxWrapperNS::real(mxWrapper const &A)
{
	mxWrapper result( A );
	result.ReallocReal();
	return result;
}

mxWrapper mxWrapperNS::imag(mxWrapper const &A)
{
	if (!A.IsComplex())
		return zeros_c(A,false);

	mxWrapper result( zeros_c(A, false) );
	double *pr = result.getPr();
	const double *pA = A.getPi();
	memcpy_s( pr, sizeof(double)*result.getNumberElements(), pA, sizeof(double)*A.getNumberElements() );
	return result;
}

mxWrapper mxWrapperNS::cat(const mxWrapper& d1, const mxWrapper& A, const mxWrapper& B)
{
	mwSize dim1 = static_cast<mwSize> (d1.ExtractScalar(1));
	mxWrapper result;

	if ( dim1 == 1 )
	{
		result = vertcat(A,B);
	}
	else if ( dim1 == 2 )
	{
		result = transpose(vertcat(transpose(A),transpose(B)));
	}
	else
	{
		Engine *ep = GetEnginePtr();

		A.put(ep, "mxWrapper_cat_A");
		B.put(ep, "mxWrapper_cat_B");
		d1.put(ep, "mxWrapper_cat_d1");

		mxWrapperEngEvalString(ep,"mxWrapper_cat_result=cat(mxWrapper_cat_d1, mxWrapper_cat_A, mxWrapper_cat_B);");

		result.get(ep, "mxWrapper_cat_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_cat_result mxWrapper_cat_d1 mxWrapper_cat_A mxWrapper_cat_B;");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_cat=mxWrapper_cat+1; catch, mxWrapper_cat=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::horzcat(const mxWrapper& A, const mxWrapper& B)
{
	return transpose(vertcat(transpose(A),transpose(B)));
}

mxWrapper mxWrapperNS::length(const mxWrapper& A)
{
	mxWrapper siz;
	A.Size(siz);
	return mxWrapper(siz.maxElement());
}

mxWrapper mxWrapperNS::vertcat(const mxWrapper& A, const mxWrapper& B)
{
	if (A.IsEmpty())
		return B;
	if (B.IsEmpty())
		return A;

	mwSize nd, U, V, n3, n4, n5;
	safeSizeOf(A, nd, U, V, n3, n4, n5);

	mwSize M, N;
	safeSizeOf(B, nd, M, N, n3, n4, n5);
	ASSERT(V == N);  // must have the same number of columns

	mxWrapper w1 = zeros((int)(U+M),(int)V);
	double *temp1 = w1.getPr();
	const double *p_A = A.getPr(), *p_B = B.getPr();	

	for(mwSize v=0; v<V; v++)
	{
		for(mwSize u=0; u<U; u++)
				temp1[ u + v*(U+M) ] = p_A[ u + v*U  ];

		for(mwSize u=U; u<U+M; u++)
				temp1[ u + v*(U+M) ] = p_B[ (u-U) + v*M  ];
	}

	if( A.IsComplex() )
	{
		p_A = A.getPi();

		w1.ReallocImag();
		temp1 = w1.getPi();
		if( B.IsComplex() )
		{
			// both are complex: simply cat the imaginary numbers
			p_B = B.getPi();	

			for(mwSize v=0; v<V; v++)
			{
				for(mwSize u=0; u<U; u++)
					temp1[ u + v*(U+M) ] = p_A[ u + v*U  ];

				for(mwSize u=U; u<U+M; u++)
					temp1[ u + v*(U+M) ] = p_B[ (u-U) + v*M  ];
			}
		}
		else
		{
			// only A is complex; B is not
			for(mwSize v=0; v<V; v++)
			{
				for(mwSize u=0; u<U; u++)
					temp1[ u + v*(U+M) ] = p_A[ u + v*U  ];
			}
		}
	}
	else
	{
		if( B.IsComplex() )
		{
			// only B is complex; A is not
			w1.ReallocImag();

			temp1 = w1.getPi();
			p_B = B.getPi();	

			for(mwSize v=0; v<V; v++)
			{
				for(mwSize u=U; u<U+M; u++)
					temp1[ u + v*(U+M) ] = p_B[ (u-U) + v*M  ];
			}
		}
	}

	return w1;
}

mxWrapper mxWrapperNS::vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C)
{
	return vertcat(vertcat(A,B),C);
}

mxWrapper mxWrapperNS::vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D)
{
	return vertcat(vertcat(A,B,C),D);
}

mxWrapper mxWrapperNS::vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E)
{
	return vertcat(vertcat(A,B,C,D),E);
}

mxWrapper mxWrapperNS::vertcat(const mxWrapper& A, const mxWrapper& B, const mxWrapper& C, const mxWrapper& D, const mxWrapper& E, const mxWrapper& F)
{
	return vertcat(vertcat(A,B,C,D,E),F);
}

mxWrapper mxWrapperNS::transpose(mxWrapper const& A)
{
	if (A.IsEmpty())
		return A;

	// 2D only!!!
	mwSize nd, U, V, n3, n4, n5;
	safeSizeOf(A, nd, U, V, n3, n4, n5);
	if (nd > 2)
		if ( ( n3 > 1 ) || ( n4 > 1 ) || ( n5 > 1 ) )
			throw( runtime_error("transpose undefined for 3D or 4D") );

	mxWrapper B = zeros(V,U);

	const double *pA=A.getPr();
	double *pB=B.getPr();
	for(mwSize v=1; v<=V; v++)
		for(mwSize u=1; u<=U; u++)
			pB[(u-1)*V + v -1] = pA[(v-1)*U + u -1];

	if (A.IsComplex())
	{
		B.ReallocImag();
		const double *iA=A.getPi();
		double *iB=B.getPi();
		for(mwSize v=1; v<=V; v++)
			for(mwSize u=1; u<=U; u++)
				iB[(u-1)*V + v -1] = iA[(v-1)*U + u -1];
	}

	return B;
}


// each thread has exactly one engine pointer 
__declspec(thread) Engine *InternalEP = NULL;

// these functions use the Matlab Engine
Engine *mxWrapperNS::GetEnginePtr(bool requireNewEnginePtr)
{

	if (requireNewEnginePtr || InternalEP == NULL)
		InternalEP = engOpen("\0");

	if (!InternalEP ) {
		AfxMessageBox(_T("Can't start MATLAB engine\n"), MB_OK);
		return NULL;
	}
	return InternalEP;
}

void mxWrapperNS::CloseEngine()
{
	Engine *ep = GetEnginePtr();
	if ( ep != NULL ) {
		engClose(ep);
		ep = NULL;
	}
}

const mxWrapper& mxWrapperNS::mxWrapperColon()
{
	// the singleton COLON is supposed to be unique within the runtime of the program
	static mxWrapper COLON(false, true);
	return COLON;
	// when is COLON destroyed?  when all other static variables are destroyed at the exit of the program
	// warning: other destructors should not use COLON because the order of destructor calls cannot be known
}
	
/// this version of colon does not actually use COLON at all: instead, it means to generate indices
mxWrapper mxWrapperNS::mxWrapperColon(const mxWrapper& lb, const mxWrapper& step, const mxWrapper&ub )
{
	return ramp( lb.ExtractScalar(1), step.ExtractScalar(1), ub.ExtractScalar(1) );
}
	
/// generate indices
mxWrapper mxWrapperNS::mxWrapperColon(const mxWrapper& lb, const mxWrapper&ub )
{
	return ramp( lb.ExtractScalar(1), 1, ub.ExtractScalar(1) );
}

mwSize mxWrapperNS::mxWrapperEnd(const mxWrapper& A, const mxWrapper& dim, const mxWrapper& nSubscriptIdx)
{
	mwSize d = static_cast<mwSize> (dim.ExtractScalar(1));  // The dimension where end() is used. (1 = row , 2 = column, ...)
	ASSERT( d <= A.Size() );
	mwSize i = static_cast<mwSize> (nSubscriptIdx.ExtractScalar(1));  // Number of indices in the subscript (for two-dimensional indexing, always 2; for one-dimensional indexing, always 1).  

	// the number of indices in the subscript is needed to differentiate these two cases:
	//       a = ones(3);  a(end)=2
	// end refers to element 9 with linear indexing of the entire array
	//       a = ones(3);  a(end,1)=2
	// end refers to dimension 1 element 3, which translates to element 3 in linear indexing of the entire array
	// these refer to completely different elements of the matrix despite having very similar syntax!

	// in c++ these would be written as
	//       mxWrapper a = ones(3);  a(mxWrapperEnd(a,1,1))=2
	// and
	//       mxWrapper a = ones(3);  a(mxWrapperEnd(a,1,2),1)=2

	// contrast this to:
	//       a = ones(3);  a(1,end)=2
	//       mxWrapper a = ones(3);  a(1,mxWrapperEnd(a,2,2))=2
	// this refers to dimension 2 element 3.

	// note the slight distinction in the two expressions: mxWrapperEnd() must know the context in which it is being used
	// this ambiguity is even more important when null assignments are made (i.e., empty()):
	//       a = ones(3);  a(end)=[]
	//       a = ones(3);  a(end,:)=[]
	//       a = ones(3);  a(:,end)=[]
	//       a = ones(3);  a(:,2:2:end)=[]
	// these examples above are all legal
	//       a = ones(3);  a(end,1)=[]
	// illegal: null assignments can only be made with one subscripted dimension (end counts!)
	// however, this is legal because it's a sub-array assignment, not a null assignment
	//       a = ones(3);  a(end,1)=2

	mwSize endIdx; 
	if (i == 1)
		endIdx = A.getNumberElements();
	else 
		endIdx = A.Size( d );

	return endIdx;
}

bool mxWrapper::IsCOLON() const
{
	return (m_bIsCOLON); 
}

bool mxWrapper::IsComplex() const
{
	return (!MxI.empty()); 
}


// convert to linear indices, allowing for COLONs
mxWrapperSubArray mxWrapper::indexGenerator(const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5) const
{
	// indexGenerator should not be called outside this class

	// duplicate the input arguments to simplify the logic
	mxWrapper D1(d1), D2(d2), D3(d3), D4(d4), D5(d5);
	
	// sizes of dimensions in the underlying array
	mwSize nd, n1, n2, n3, n4, n5;  // this works even for 1D arrays because dimensions of 1 are collapsed
	mxWrapperNS::safeSizeOf(*this, nd, n1, n2, n3, n4, n5);

	// replace colons with explicit indices, ':' becomes (1,2,...,N)
	// and fix unspecified dimensions (0)
	if (d1.IsCOLON())
		D1 = linspace(1,n1,n1);
	else if (d1.IsEmpty()) 
		// this should never happen because the first dimension must always be specified
		ASSERT( false );
		//D1 = zeros(1,n1);

	if (d2.IsCOLON())
		D2 = linspace(1,n2,n2);
	else if (d2.IsEmpty()) // this is legal: you can create a 3D array and then only access two dimensions. e.g., a=eye(3); b=repmat(a,[1 1 2]); c=b(:,3) .  the third dimension is treated as if it was specified as an index of 1.  e.g., b(:,3)==b(:,3,1)
		D2 = ones(1,1);

	if (d3.IsCOLON())
		D3 = linspace(1,n3,n3);
	else if (d3.IsEmpty())
		D3 = ones(1,1);

	if (d4.IsCOLON())
		D4 = linspace(1,n4,n4);
	else if (d4.IsEmpty())
		D4 = ones(1,1);

	if (d5.IsCOLON())
		D5 = linspace(1,n5,n5);
	else if (d5.IsEmpty())
		D5 = ones(1,1);

	mxWrapper idx;  // the computed linear indices

	// special exception: linear indexing of the form 
	//       a = eye(3);  a([1 2 4]) = 5
	// this occurs when dimensions 2,3,4 are all indexed as 0 (undefined)
	// in this situation, d1 should be interpreted as a linear index, not as an index to dimension 1
	if ( !d1.IsEmpty() && d2.IsEmpty() && d3.IsEmpty() && d4.IsEmpty() && d5.IsEmpty() )
	{
		if (d1.IsCOLON())
			idx = linspace(1,getNumberElements(),getNumberElements());
		else
			idx = d1;
	}
	else
	{
		// more general case: all dimensions are used to compute indices
		//FILE_LOG(logDEBUG4)<<"mxWrapper::indexGenerator: D1" << D1 << "D2" << D2 << "D3" << D3 << "D4" << D4 << "D5" << D5;

		// allocate array to hold indices
		mwSize s1 = D1.Size(2), s2 = D2.Size(2), s3 = D3.Size(2), s4 = D4.Size(2), s5 = D5.Size(2);
		mwSize numIdx = s1 * s2 * s3 * s4 * s5;
		idx = zeros(1,numIdx);

		// compute every index
		mwSize counter = 0;
		double *pr = idx.getPr(), *pD1=D1.getPr(), *pD2=D2.getPr(), *pD3=D3.getPr(), *pD4=D4.getPr(), *pD5=D5.getPr();
		for (mwSize h = 0; h < s5; h++)
			for (mwSize i = 0; i < s4; i++)
				for (mwSize j = 0; j < s3; j++)
					for (mwSize k = 0; k < s2; k++)
						for (mwSize l = 0; l < s1; l++)
						{
							pr[counter++] = pD1[l] + (pD2[k]-1)*n1 + (pD3[j]-1)*n1*n2 + (pD4[i]-1)*n1*n2*n3 + (pD5[h]-1)*n1*n2*n3*n4;
						}

	}

	if(idx.getNumberElements() > 10)
		FILE_LOG(logDEBUG4)<<"mxWrapper::indexGenerator: idx" << idx(mxWrapperColon(1,10));
	else
		FILE_LOG(logDEBUG4)<<"mxWrapper::indexGenerator: idx" << idx;
	mxWrapper* temp = const_cast<mxWrapper*> (this);  // intentionally discard const qualifier on this pointer so that subarray assignments are possible from mxWrapperSubArray -- required for null assignments (i.e. empty()) and allocation of imaginary components
	return mxWrapperSubArray( temp, idx, d1, d2, d3, d4, d5 );
}

void mxWrapperSubArray::safeSizeOf(mwSize &md, mwSize &m1, mwSize &m2, mwSize &m3, mwSize &m4, mwSize &m5) const
{
	ASSERT( baseWrapper != NULL );
	md=0;
	m1=m2=m3=m4=m5=0;

	// sizes of the underlying mxArray*:
	mwSize nDim, Dim1, Dim2, Dim3, Dim4, Dim5;
	mxWrapperNS::safeSizeOf(*baseWrapper, nDim, Dim1, Dim2, Dim3, Dim4, Dim5);

	// count the number of dimensions which were indexed in any way
	if ( D1.IsCOLON() || !D1.IsEmpty() )
		md++;
	if ( D2.IsCOLON() || !D2.IsEmpty() )
		md++;
	if ( D3.IsCOLON() || !D3.IsEmpty() )
		md++;
	if ( D4.IsCOLON() || !D4.IsEmpty() )
		md++;
	if ( D5.IsCOLON() || !D5.IsEmpty() )
		md++;

	ASSERT ( md > 0 );

	if (D1.IsCOLON())
		if (md == 1)
		{
			// special exception: pure linear indexing
			m1=baseWrapper->getNumberElements(); 		
			md = 2;
			m2 = 1;
			return;
		}
		else
			m1=Dim1;
	else if (D1.getNumberElements() > 0)
	{
		ASSERT (!D1.IsEmpty()); // dimension 1 must ALWAYS be specified 
		m1=D1.getNumberElements();
		if (md == 1)
		{
			// special exception: pure linear indexing
			md = 2;
			m2 = 1;
			return;
		}
	}

	if (D2.IsCOLON())
		m2=Dim2;
	else if (D2.getNumberElements() > 0)
	{
		if (!D2.IsEmpty()) // unspecified dimension. does not affect resulting mxArray
			m2=D2.getNumberElements();
	// else: ignore this dimension.
	}

	if (D3.IsCOLON())
		m3=Dim3;
	else if (D3.getNumberElements() > 0)
	{
		if (!D3.IsEmpty()) 
			m3=D3.getNumberElements();
	}

	if (D4.IsCOLON())
		m4=Dim4;
	else if (D4.getNumberElements() > 0)
	{
		if (!D4.IsEmpty()) 
			m4=D4.getNumberElements();
	}

	if (D5.IsCOLON())
		m5=Dim5;
	else if (D5.getNumberElements() > 0)
	{
		if (!D5.IsEmpty()) 
			m5=D5.getNumberElements();
	}

}

// verifies that the two sub-expressions have compatible dimensions
bool mxWrapperSubArray::SizeTest(const mxWrapperSubArray &msa) const
{
	mwSize M = indices.getNumberElements();
	mwSize N = msa.indices.getNumberElements();

	// prevents the error: "??? In an assignment A(I) = B, the number of elements in B and I must be the same."
	if( M != N )
		return false; 

	// determine size of dimensions in resulting mxArray (n) and source mxArray (m)
	mwSize md, m1, m2, m3, m4, m5;
	safeSizeOf(md, m1, m2, m3, m4, m5);

	mwSize nd, n1, n2, n3, n4, n5;
	msa.safeSizeOf(nd, n1, n2, n3, n4, n5);

	// require the assigned non-singleton subarray dimensions to match
	// for each dimension determine if:
	// it is non-singleton (more than one index in the dimension)
	// and it is assigned (0 means unassigned) 
	mwSize mNonSingletons[5]={0, 0, 0, 0, 0};
	mwSize mNonSingletonsCounter=0;
	if (m1 > 1) 
		mNonSingletons[mNonSingletonsCounter++]=m1;
	if (m2 > 1) 
		mNonSingletons[mNonSingletonsCounter++]=m2;
	if (m3 > 1) 
		mNonSingletons[mNonSingletonsCounter++]=m3;
	if (m4 > 1) 
		mNonSingletons[mNonSingletonsCounter++]=m4;
	if (m5 > 1) 
		mNonSingletons[mNonSingletonsCounter++]=m5;

	mwSize nNonSingletons[5]={0, 0, 0, 0, 0};
	mwSize nNonSingletonsCounter=0;
	if (n1 > 1) 
		nNonSingletons[nNonSingletonsCounter++]=n1;
	if (n2 > 1) 
		nNonSingletons[nNonSingletonsCounter++]=n2;
	if (n3 > 1) 
		nNonSingletons[nNonSingletonsCounter++]=n3;
	if (n4 > 1) 
		nNonSingletons[nNonSingletonsCounter++]=n4;
	if (n5 > 1) 
		nNonSingletons[nNonSingletonsCounter++]=n5;

	// require the number of assigned non-singleton dimensions to match exactly
	if ( mNonSingletonsCounter != nNonSingletonsCounter ) 
		return false;

	// require the assigned non-singleton subarray dimensions to match
	if ( (mNonSingletons[0] != nNonSingletons[0]) || 
		(mNonSingletons[1] != nNonSingletons[1]) || 
		(mNonSingletons[2] != nNonSingletons[2]) || 
		(mNonSingletons[3] != nNonSingletons[3]) ||
		(mNonSingletons[4] != nNonSingletons[4]) 
		) 
	{
		// special exception: it's legal for a subarray of two dimensions [1,N] to be assigned to another sub-array of two dimensions [N,1] and vice versa. e.g.,
		// LEGAL:       a=zeros(3); b=1:6; a(1:3,1)=b(1:3)
		// size(a) = [3 3 0 0]
		// size(b) = [1 3 0 0]
		// size(a(1:3,1)) = [3 1 0 0]
		// size(b(1:3)) = [1 3 0 0]
		if ( mNonSingletonsCounter==2 &&  // first sub-array must be 2D
			nNonSingletonsCounter==2 && // second sub-array must be 2D
			((mNonSingletons[0] == nNonSingletons[1]) || (mNonSingletons[1] == nNonSingletons[0])) )
			return true;  
		else
			return false;
	}

	// ILLEGAL:     a=zeros([3 3 3]); b=linspace(1,27,27); a(:,:,:)=b(:) 
	// size(a) = [3 3 3 0]
	// size(b) = [1 27 0 0]
	// size(a(:,:,:)) = [3 3 3 0]
	// size(b(:)) = [27 1 0 0]
	// also ILLEGAL: a(:,:,:)=b

	return true; 
}


string mxWrapperSubArray::ToString() const
{
	std::ostringstream os;
	os << indices;
	return os.str();
}


mxWrapperSubArray& mxWrapperSubArray::AssignConstant (double d, bool assignImag)
{
	ASSERT( baseWrapper != NULL );
	ASSERT( indices.getNumberElements() > 0 );

	//FILE_LOG(logDEBUG4)<<"mxWrapperSubArray::operator=(double d): indices" << indices;

	double *a = baseWrapper->getPr(), *pIdx = indices.getPr();
	if (assignImag)
	{
		baseWrapper->ReallocImag();
		a = baseWrapper->getPi();
	}

	mwSize MaxIdx = baseWrapper->getNumberElements();
	ASSERT ( MaxIdx != 0 );
	mwSize NumIdx = indices.getNumberElements();
	for (mwSize i=0; i < NumIdx; i++)
	{
		mwSize idxA = static_cast<mwSize> (pIdx[i] - 1);  // C indexes from 0, not 1
		ASSERT ( idxA >= 0 );
		ASSERT ( idxA < MaxIdx );

		a[ idxA ] = d;
	}

	return *this;
}

mxWrapper mxWrapperNS::fft(const mxWrapper& X, const mxWrapper& N, const mxWrapper& dim)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"fft";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_fft_X");
		mxWrapper N1 = N;
		if ( (N.ExtractScalar(1) == 0) || (N.IsEmpty()) )
			N1 = X.Size( static_cast<mwSize> (dim.ExtractScalar(1)) );
		N1.put(ep, "mxWrapper_fft_N");
		dim.put(ep, "mxWrapper_fft_dim");
		mxWrapperEngEvalString(ep,"mxWrapper_fft_result=fft(mxWrapper_fft_X,mxWrapper_fft_N,mxWrapper_fft_dim);");
		result.get(ep, "mxWrapper_fft_result");
		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_fft_result mxWrapper_fft_X mxWrapper_fft_N mxWrapper_fft_dim");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_fft=mxWrapper_fft+1; catch, mxWrapper_fft=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::ifft(const mxWrapper& X, const mxWrapper& N, const mxWrapper& dim)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"ifft";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_ifft_X");
		mxWrapper N1 = N;
		if ( (N.ExtractScalar(1) == 0) || (N.IsEmpty()) )
			N1 = X.Size( static_cast<mwSize> (dim.ExtractScalar(1)) );
		N1.put(ep, "mxWrapper_ifft_N");
		dim.put(ep, "mxWrapper_ifft_dim");
		mxWrapperEngEvalString(ep,"mxWrapper_ifft_result=ifft(mxWrapper_ifft_X,mxWrapper_ifft_N,mxWrapper_ifft_dim);");
		result.get(ep, "mxWrapper_ifft_result");
		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_ifft_result mxWrapper_ifft_X mxWrapper_ifft_N mxWrapper_ifft_dim");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_ifft=mxWrapper_ifft+1; catch, mxWrapper_ifft=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::cumsum(const mxWrapper& X, const mxWrapper& dim)
{
	if (X.IsEmpty())
		return X;

	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"cumsum";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_cumsum_X");
		dim.put(ep, "mxWrapper_cumsum_dim");
		mxWrapperEngEvalString(ep,"mxWrapper_cumsum_result=cumsum(mxWrapper_cumsum_X,mxWrapper_cumsum_dim);");
		result.get(ep, "mxWrapper_cumsum_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_cumsum_result mxWrapper_cumsum_X mxWrapper_cumsum_dim");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_cumsum=mxWrapper_cumsum+1; catch, mxWrapper_cumsum=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::power(const mxWrapper& X, const mxWrapper& N)
{
	mxWrapper result;
	double n = N.ExtractScalar(1);

	if ( (X.Size()==2) && !X.IsComplex() && !N.IsComplex() && (N.Size()==2) && (N.getNumberElements()==1) && (n>=0) )
	{
		if (n == 0)
		{
			result=zeros(X);
			result.AssignConstant(1);
		}
		else if (n == 1)
			result=X;
		else
		{
			result=zeros(X);
			transform( X.Mx.begin(), X.Mx.end(), result.Mx.begin(), bind2nd( pointer_to_binary_function <double,double,double>(::pow), n) );
		}
	}
	else 
	{
		Engine *ep = GetEnginePtr();
		if ( ep == NULL )
		{
			FILE_LOG(logDEBUG4)<<"power";
			result = X;
			return result;
		}
		X.put(ep, "mxWrapper_power_X");
		N.put(ep, "mxWrapper_power_N");
		mxWrapperEngEvalString(ep,"mxWrapper_power_result=power(mxWrapper_power_X,mxWrapper_power_N);");
		result.get(ep, "mxWrapper_power_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_power_result mxWrapper_power_X mxWrapper_power_N");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_power=mxWrapper_power+1; catch, mxWrapper_power=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::exp(const mxWrapper& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"exp";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_exp_X");
		mxWrapperEngEvalString(ep,"mxWrapper_exp_result=exp(mxWrapper_exp_X);");
		result.get(ep, "mxWrapper_exp_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_exp_result mxWrapper_exp_X ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_exp=mxWrapper_exp+1; catch, mxWrapper_exp=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::conv(const mxWrapper& X, const mxWrapper& Y)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	// special case: conv of real column vectors
	if ( (X.Size() == 2) && (Y.Size() == 2) && (X.Size(2) == 1) && (Y.Size(2) == 1) && !X.IsComplex() && !Y.IsComplex() )
	{
		// The resulting vector is length MAX([LENGTH(X)+LENGTH(Y)-1,LENGTH(X),LENGTH(Y)])
		mwSize nX = X.Size(1);
		mwSize nY = Y.Size(1);
		mwSize newLength=nX+nY-1;
		if ( nY > newLength )
			newLength = nY;
		if ( nX > newLength )
			newLength = nX;

		result = zeros( newLength, 1 );
		double *pR = result.getPr();
		const double *pX = X.getPr(), *pY = Y.getPr();
		for ( mwSize i=0; i < newLength; ++i )
		{
			double d=0;
			for ( mwSize m=0; m < nX; ++m )
			{
				if( (i-m) >= 0  && (i-m) < nY )
					d += pX[m] * pY[i-m];
			}
			pR[ i ] = d;
		}

		//result.put(ep, "mxWrapper_conv_result1");
	}
	else
	{
		ASSERT ( ep != NULL );
		X.put(ep, "mxWrapper_conv_X");
		Y.put(ep, "mxWrapper_conv_Y");
		mxWrapperEngEvalString(ep,"mxWrapper_conv_result=conv(mxWrapper_conv_X,mxWrapper_conv_Y);");
		result.get(ep, "mxWrapper_conv_result");
		//mxWrapperEngEvalString(ep,"clear mxWrapper_conv_result mxWrapper_conv_X mxWrapper_conv_Y");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_conv=mxWrapper_conv+1; catch, mxWrapper_conv=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::mtimes(const mxWrapper& X, const mxWrapper& Y)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"mtimes";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_mtimes_X");
		Y.put(ep, "mxWrapper_mtimes_Y");
		mxWrapperEngEvalString(ep,"mxWrapper_mtimes_result=mtimes(mxWrapper_mtimes_X,mxWrapper_mtimes_Y);");
		result.get(ep, "mxWrapper_mtimes_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_mtimes_result mxWrapper_mtimes_X mxWrapper_mtimes_Y");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_mtimes=mxWrapper_mtimes+1; catch, mxWrapper_mtimes=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::mod(const mxWrapper& X, const mxWrapper& Y)
{
	mxWrapper result;

	if ( (X.getNumberElements()==1) && (Y.Size()<=2) )
	{
		// common case: mod(5,[1 2 3])
		double d = X.ExtractScalar(1);
		result = zeros(Y);
		transform( Y.Mx.begin(), Y.Mx.end(), result.Mx.begin(), bind1st( modulus<int>(), (int)d) );
	}
	else if ( (Y.getNumberElements()==1) && (X.Size()<=2) )
	{
		// common case: mod([10 22 34], 5)
		double d = Y.ExtractScalar(1);
		result = zeros(X);
		transform( X.Mx.begin(), X.Mx.end(), result.Mx.begin(), bind2nd( modulus<int>(), (int)d) );
	}
	else if ( (X.getNumberElements()==Y.getNumberElements()) && (X.Size()==2) && (Y.Size()==2) )
	{
		// common case: mod([10 22 34], [1 2 3])
		result = zeros(X);
		transform( X.Mx.begin(), X.Mx.end(), Y.Mx.begin(), result.Mx.begin(), modulus<int>() );
	}
	else
	{
		Engine *ep = GetEnginePtr();

		if ( ep == NULL )
		{
			FILE_LOG(logDEBUG4)<<"mod";
			result = X;
		}
		else
		{
			X.put(ep, "mxWrapper_mod_X");
			Y.put(ep, "mxWrapper_mod_Y");
			mxWrapperEngEvalString(ep,"mxWrapper_mod_result=mod(mxWrapper_mod_X,mxWrapper_mod_Y);");
			result.get(ep, "mxWrapper_mod_result");
			mxWrapperEngEvalString(ep,"clear mxWrapper_mod_result mxWrapper_mod_X mxWrapper_mod_Y");
#ifdef _DEBUG
			mxWrapperEngEvalString(ep,"try, mxWrapper_mod=mxWrapper_mod+1; catch, mxWrapper_mod=1; end");
#endif
		}
	}

	return result;
}

mxWrapper mxWrapperNS::sqrt(mxWrapper const &A)
{
	mxWrapper result(A);

	if ( !A.IsComplex() )
		transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::sqrt) );
	else
	{
		UINT N = A.getNumberElements();
		for(UINT i=0; i<N; ++i)
		{
			complex<double> c( A.Mx[i], A.MxI[i] );
			complex<double> r = sqrt(c);
			result.Mx[i] = r.real();
			result.MxI[i] = r.imag();
		}
	}

	return result;
}

mxWrapper mxWrapperNS::meshgrid(mxWrapper *out,mxWrapper const&x, mxWrapper const&y)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"meshgrid";
		result = x;
		*out=x;
	}
	else
	{
		x.put(ep, "mxWrapper_meshgrid_x");
		y.put(ep, "mxWrapper_meshgrid_y");
		mxWrapperEngEvalString(ep,"[mxWrapper_meshgrid_resultX, mxWrapper_meshgrid_resultY]=meshgrid(mxWrapper_meshgrid_x,mxWrapper_meshgrid_y);");
		result.get(ep, "mxWrapper_meshgrid_resultX");
		out->get(ep, "mxWrapper_meshgrid_resultY");
		mxWrapperEngEvalString(ep,"clear mxWrapper_meshgrid_resultX mxWrapper_meshgrid_resultY mxWrapper_meshgrid_x mxWrapper_meshgrid_y");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_meshgrid=mxWrapper_meshgrid+1; catch, mxWrapper_meshgrid=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::meshgrid(mxWrapper *outY, mxWrapper *outZ, mxWrapper const&x, mxWrapper const&y, mxWrapper const&z)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"meshgrid";
		result = x;
	}
	else
	{
		x.put(ep, "mxWrapper_meshgrid_x");
		y.put(ep, "mxWrapper_meshgrid_y");
		z.put(ep, "mxWrapper_meshgrid_z");
		mxWrapperEngEvalString(ep,"[mxWrapper_meshgrid_resultX, mxWrapper_meshgrid_resultY, mxWrapper_meshgrid_resultZ]=meshgrid(mxWrapper_meshgrid_x,mxWrapper_meshgrid_y, mxWrapper_meshgrid_z);");
		result.get(ep, "mxWrapper_meshgrid_resultX");
		outY->get(ep, "mxWrapper_meshgrid_resultY");
		outZ->get(ep, "mxWrapper_meshgrid_resultZ");
		mxWrapperEngEvalString(ep,"clear mxWrapper_meshgrid_resultX mxWrapper_meshgrid_resultY mxWrapper_meshgrid_resultZ mxWrapper_meshgrid_x mxWrapper_meshgrid_y mxWrapper_meshgrid_z");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_meshgrid2=mxWrapper_meshgrid2+1; catch, mxWrapper_meshgrid2=1; end");
#endif
	}

	return result;
}



mxWrapper mxWrapperNS::floor(mxWrapper const&A)
{
	mxWrapper result;

	result = zeros(A);
	transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::floor) );

	if (A.IsComplex())
		transform( A.MxI.begin(), A.MxI.end(), result.MxI.begin(), pointer_to_unary_function <double,double>(::floor) );

	return result;
}

mxWrapper mxWrapperNS::log(mxWrapper const&A)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"log";
		result = A;
	}
	else
	{
		A.put(ep, "mxWrapper_log_A");
		mxWrapperEngEvalString(ep,"mxWrapper_log_result=log(mxWrapper_log_A);");
		result.get(ep, "mxWrapper_log_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_log_result mxWrapper_log_A");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_log=mxWrapper_log+1; catch, mxWrapper_log=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::shiftdim(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"shiftdim";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_shiftdim_X");
		mxWrapperEngEvalString(ep,"mxWrapper_shiftdim_result=shiftdim(mxWrapper_shiftdim_X);");
		result.get(ep, "mxWrapper_shiftdim_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_shiftdim_result mxWrapper_shiftdim_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_shiftdim=mxWrapper_shiftdim+1; catch, mxWrapper_shiftdim=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::shiftdim(mxWrapper const& X, mxWrapper const& N)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"shiftdim";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_shiftdim_X");
		N.put(ep, "mxWrapper_shiftdim_N");
		mxWrapperEngEvalString(ep,"mxWrapper_shiftdim_result=shiftdim(mxWrapper_shiftdim_X, mxWrapper_shiftdim_N);");
		result.get(ep, "mxWrapper_shiftdim_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_shiftdim_result mxWrapper_shiftdim_X mxWrapper_shiftdim_N");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_shiftdim2=mxWrapper_shiftdim2+1; catch, mxWrapper_shiftdim2=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::squeeze(mxWrapper const& X)
{
	// remove singleton dimensions

	if( X.IsEmpty() )
		return mxWrapper();

	// original dimensions: m
	mwSize md, m1, m2, m3, m4, m5;
	safeSizeOf(X, md, m1, m2, m3, m4, m5);

	ASSERT( md >= 1 );

	if( md == 2 )
	{
		// squeezing a 2D matrix which is [1,m] or [m,1] should not change it
		return X;
	}

	// new dimensions: ndims
	mwSize nd=0;
	mwSize ndims[5] = {0,0,0,0,0}; 
	if( m1 > 1 )
		ndims[nd++] = m1;

	if( md >= 2 && m2 > 1 )
		ndims[nd++] = m2;

	if( md >= 3 && m3 > 1 )
		ndims[nd++] = m3;

	if( md >= 4 && m4 > 1 )
		ndims[nd++] = m4;

	if( md >= 5 && m5 > 1 )
		ndims[nd++] = m5;

	if( nd == 1 )
	{
		// if the original matrix had only one non-singleton dimension, 
		// the result of squeeze will still be 2D because 1D matrices are not allowed
		// e.g., squeeze [1 1 3 1] -> [3 1]
		ndims[1] = 1;
		nd++;
	}

	ASSERT( nd > 0 );
	ASSERT( nd <= md );

	// now nd is the number of non-singleton dimensions, and ndims holds a non-zero dimension size for each valid dimension

	mxWrapper result( X, nd, ndims[0], ndims[1], ndims[2], ndims[3], ndims[4] );

	ASSERT( result.getNumberElements() == X.getNumberElements() );
	ASSERT( result.nDim <= X.nDim );

	return result;
}

mxWrapper mxWrapperNS::conj(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"conj";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_conj_X");
		mxWrapperEngEvalString(ep,"mxWrapper_conj_result=conj(mxWrapper_conj_X);");
		result.get(ep, "mxWrapper_conj_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_conj_result mxWrapper_conj_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_conj=mxWrapper_conj+1; catch, mxWrapper_conj=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::pow2(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"pow2";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_pow2_X");
		mxWrapperEngEvalString(ep,"mxWrapper_pow2_result=pow2(mxWrapper_pow2_X);");
		result.get(ep, "mxWrapper_pow2_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_pow2_result mxWrapper_pow2_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_pow2=mxWrapper_pow2+1; catch, mxWrapper_pow2=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::diff(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"diff";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_diff_X");
		mxWrapperEngEvalString(ep,"mxWrapper_diff_result=diff(mxWrapper_diff_X);");
		result.get(ep, "mxWrapper_diff_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_diff_result mxWrapper_diff_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_diff=mxWrapper_diff+1; catch, mxWrapper_diff=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::inv(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"inv";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_inv_X");
		mxWrapperEngEvalString(ep,"mxWrapper_inv_result=inv(mxWrapper_inv_X);");
		result.get(ep, "mxWrapper_inv_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_inv_result mxWrapper_inv_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_inv=mxWrapper_inv+1; catch, mxWrapper_inv=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::nextpow2(mxWrapper const& X)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"nextpow2";
		result = X;
	}
	else
	{
		X.put(ep, "mxWrapper_nextpow2_X");
		mxWrapperEngEvalString(ep,"mxWrapper_nextpow2_result=nextpow2(mxWrapper_nextpow2_X);");
		result.get(ep, "mxWrapper_nextpow2_result");
		mxWrapperEngEvalString(ep,"clear mxWrapper_nextpow2_result mxWrapper_nextpow2_X");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_nextpow2=mxWrapper_nextpow2+1; catch, mxWrapper_nextpow2=1; end");
#endif
	}

	return result;
}

void mxWrapperNS::ind2sub(mxWrapper *o1, mxWrapper *o2, mxWrapper *o3, mxWrapper const& sz, mxWrapper const& IND)
{
	mxWrapper result1, result2, result3;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
		FILE_LOG(logDEBUG4)<<"ind2sub";
	else
	{
		sz.put(ep, "mxWrapper_ind2sub_sz");
		IND.put(ep, "mxWrapper_ind2sub_IND");
		mxWrapperEngEvalString(ep,"[mxWrapper_ind2sub_result1, mxWrapper_ind2sub_result2, mxWrapper_ind2sub_result3]=ind2sub(mxWrapper_ind2sub_sz, mxWrapper_ind2sub_IND);");
		result1.get(ep, "mxWrapper_ind2sub_result1");
		result2.get(ep, "mxWrapper_ind2sub_result2");
		result3.get(ep, "mxWrapper_ind2sub_result3");

		*o1 = result1;
		*o2 = result2;
		*o3 = result3;
		mxWrapperEngEvalString(ep,"clear mxWrapper_ind2sub_result1 mxWrapper_ind2sub_result2 mxWrapper_ind2sub_result3 mxWrapper_ind2sub_sz mxWrapper_ind2sub_IND ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_ind2sub=mxWrapper_ind2sub+1; catch, mxWrapper_ind2sub=1; end");
#endif
	}
}

BOOL mxWrapperNS::save(const string& fName, const string& s1, mxWrapper const& v1)
{
	if (v1.IsEmpty())
		return FALSE;

	CSingleLock sLock(&mxWrapper::ccEngine);
	sLock.Lock();    
	if (!sLock.IsLocked())
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	MATFile *pmatFile = matOpen(fName.c_str(), "w");
	if(pmatFile == NULL) 
	{
		FILE_LOG(logERROR)<<"save failed in file: " << fName;
		sLock.Unlock();
		return FALSE;
	}

	mxArray* pMx = v1.CreateMxArray(mxDOUBLE_CLASS);
	if(pMx == NULL) 
	{
		if(matClose(pmatFile))
			FILE_LOG(logERROR)<<"failed to close file: " << fName;
		sLock.Unlock();
		return FALSE;
	}

	if (matPutVariable(pmatFile, s1.c_str(), pMx))
	{
		FILE_LOG(logERROR)<<"matPutVariable failed to write to file: " << fName;
		mxDestroyArray(pMx);
		if(matClose(pmatFile))
			FILE_LOG(logERROR)<<"failed to close file: " << fName;
		sLock.Unlock();
		return FALSE;
	}

	mxDestroyArray(pMx);

	if(matClose(pmatFile))
		FILE_LOG(logERROR)<<"failed to close file: " << fName;

	sLock.Unlock();

	return TRUE;
}

BOOL mxWrapperNS::load(const string& fName, const string& s1, mxWrapper *v1)
{
	VERIFY( v1 != NULL );

	CSingleLock sLock(&mxWrapper::ccEngine);
	sLock.Lock();    
	if (!sLock.IsLocked())
		throw( runtime_error("Failed to enter the Matlab Engine critical section") );

	MATFile *pmatFile = matOpen(fName.c_str(), "r");
	if(pmatFile == NULL) 
	{
		FILE_LOG(logERROR)<<"load failed to open file: " << fName;
		sLock.Unlock();
		return FALSE;
	}

	mxArray* pMx = matGetVariable(pmatFile, s1.c_str());
	if(pMx == NULL) 
	{
		FILE_LOG(logERROR)<<"variable " << s1 << " not found in file: " << fName;

		if(matClose(pmatFile))
			FILE_LOG(logERROR)<<"failed to close file: " << fName;

		sLock.Unlock();
		return FALSE;
	}
	 
	v1->empty();
	sLock.Unlock();

	if (!v1->LoadFromMxArray(pMx))
	{
		FILE_LOG(logERROR)<<"variable " << s1 << " from file: " << fName << " could not be loaded into memory. Out of memory?";
		return FALSE;
	}

	return TRUE;
}

// "Fast Linear Interpolation" by Umberto Picchini 04 Oct 2005 (Updated 20 Apr 2006) 
// http://www.mathworks.com/matlabcentral/fileexchange/8627-fast-linear-interpolation
double lininterp1f(double *yinterp, const double *xv, const double *yv, const double *x, const double *ydefault, int m, int minterp)
{
	int i, j; 
	int nrowsinterp, nrowsdata;
	nrowsinterp = minterp;
	nrowsdata = m;
	for (i=0; i<nrowsinterp; i++)
	{
		if((x[i] < xv[0]) || (x[i] > xv[nrowsdata-1]))
			yinterp[i] = *ydefault;
		else
		{   
			for(j=1; j<nrowsdata; j++)
			{      
				if(x[i]<=xv[j])
				{		   
					yinterp[i] = (x[i]-xv[j-1]) / (xv[j]-xv[j-1]) * (yv[j]-yv[j-1]) + yv[j-1];
					break;
				}
			}
		}
	}
	return *yinterp;
} 

/*
F = lininterp1f(X,Y,XI,Ydefault) returns the value of the 1-D function Y at the points XI using linear interpolation. Length(F)=length(XI). The vector X specifies the coordinates of the underlying interval. Ydefault is returned for values of XI outside the coordinates in X.

For lininterp1f to work properly:
X must be a monotonically increasing array;
Y must be an array with length(Y)=length(X);
XI must be an array.
Ydefault must be a scalar value or an empty matrix [].

Example:
>> x = [1:1:1000];
>> y =log(sqrt(x+1.001)-1.001);
>> xv =[5:.001:100];
>> yinterp =lininterp1f(x,y,xv,[]);
*/
mxWrapper mxWrapperNS::lininterp1f_wrapper(const mxWrapper& x,const mxWrapper& Y,const mxWrapper& xi, double extrapval)
{
	 mxWrapper yinterp  = zeros( xi );
   lininterp1f(yinterp.getPr(),x.getPr(),Y.getPr(),xi.getPr(),&extrapval,x.getNumberElements(),xi.getNumberElements());

	 //Engine *ep = GetEnginePtr();
	 //yinterp.put(ep,"lininterp1f_wrapper_result");  // debug: make sure it gives the same result as interp1

   return yinterp;
}

mxWrapper mxWrapperNS::interp1(const mxWrapper& x,const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& method, double extrapval)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"interp1";
		result = Y;
	}
	else
	{
		x.put(ep, "mxWrapper_interp1_x");
		Y.put(ep, "mxWrapper_interp1_Y");
		xi.put(ep, "mxWrapper_interp1_xi");

		//mxWrapper mxInterpMethod(method);
		//mxInterpMethod.put(ep, "mxWrapper_interp1_method");
		method.put(ep, "mxWrapper_interp1_method");

		mxWrapper mxExtrapval(extrapval);
		mxExtrapval.put(ep, "mxWrapper_interp1_mxExtrapval");

		mxWrapperEngEvalString(ep,"mxWrapper_interp1_result=interp1(mxWrapper_interp1_x, mxWrapper_interp1_Y, mxWrapper_interp1_xi, mxWrapper_interp1_method, mxWrapper_interp1_mxExtrapval);");

		result.get(ep, "mxWrapper_interp1_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_interp1_result mxWrapper_interp1_x mxWrapper_interp1_Y mxWrapper_interp1_xi mxWrapper_interp1_method mxWrapper_interp1_mxExtrapval ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_interp1=mxWrapper_interp1+1; catch, mxWrapper_interp1=1; end");
#endif
	}

	return result;

	// mxInterpMethod and mxExtrapval are automatically freed when they go out of scope here
	// result is not freed
	// mxWrapper x,mxWrapper Y,mxWrapper xi are not freed (and are unchanged)
}

mxWrapper mxWrapperNS::interp2(const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& yi,const mxWrapper& method, const mxWrapper& extrapval)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"interp2";
		result = Y;
	}
	else
	{
		Y.put(ep, "mxWrapper_interp2_Y");
		xi.put(ep, "mxWrapper_interp2_xi");
		yi.put(ep, "mxWrapper_interp2_yi");
		method.put(ep, "mxWrapper_interp2_method");
		extrapval.put(ep, "mxWrapper_interp2_mxExtrapval");

		mxWrapperEngEvalString(ep,"mxWrapper_interp2_result=interp2(mxWrapper_interp2_Y, mxWrapper_interp2_xi, mxWrapper_interp2_yi, mxWrapper_interp2_method, mxWrapper_interp2_mxExtrapval);");

		result.get(ep, "mxWrapper_interp2_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		//mxWrapperEngEvalString(ep,"clear mxWrapper_interp2_result mxWrapper_interp2_Y mxWrapper_interp2_xi mxWrapper_interp2_yi mxWrapper_interp2_method mxWrapper_interp2_mxExtrapval ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_interp2=mxWrapper_interp2+1; catch, mxWrapper_interp2=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::interp2(const mxWrapper& x,const mxWrapper& y,const mxWrapper& Y,const mxWrapper& xi,const mxWrapper& yi,const mxWrapper& method, const mxWrapper& extrapval)
{
	mxWrapper result;
	Engine *ep = GetEnginePtr();

	if ( ep == NULL )
	{
		FILE_LOG(logDEBUG4)<<"interp2";
		result = Y;
	}
	else
	{
		x.put(ep, "mxWrapper_interp2_x");
		y.put(ep, "mxWrapper_interp2_y");
		Y.put(ep, "mxWrapper_interp2_Y");
		xi.put(ep, "mxWrapper_interp2_xi");
		yi.put(ep, "mxWrapper_interp2_yi");
		method.put(ep, "mxWrapper_interp2_method");
		extrapval.put(ep, "mxWrapper_interp2_mxExtrapval");

		mxWrapperEngEvalString(ep,"mxWrapper_interp2_result=interp2(mxWrapper_interp2_x, mxWrapper_interp2_y, mxWrapper_interp2_Y, mxWrapper_interp2_xi, mxWrapper_interp2_yi, mxWrapper_interp2_method, mxWrapper_interp2_mxExtrapval);");

		result.get(ep, "mxWrapper_interp2_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_interp2_result mxWrapper_interp2_x mxWrapper_interp2_y mxWrapper_interp2_Y mxWrapper_interp2_xi mxWrapper_interp2_yi mxWrapper_interp2_method mxWrapper_interp2_mxExtrapval ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_interp2=mxWrapper_interp2+1; catch, mxWrapper_interp2=1; end");
#endif
	}

	return result;
}

mxWrapper mxWrapperNS::cos (const mxWrapper& A)
{
	mxWrapper result;

	if (A.IsComplex())
	{
		Engine *ep = GetEnginePtr();
		A.put(ep, "mxWrapper_cos_A");
		mxWrapperEngEvalString(ep,"mxWrapper_cos_result=cos(mxWrapper_cos_A);");

		result.get(ep, "mxWrapper_cos_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_cos_result mxWrapper_cos_A ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_cos=mxWrapper_cos+1; catch, mxWrapper_cos=1; end");
#endif
	}
	else
	{
		result = A;
		transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::cos) );
	}
	return result;
}

mxWrapper mxWrapperNS::acos (const mxWrapper& A)
{
	mxWrapper result;

	if (A.IsComplex())
	{
		Engine *ep = GetEnginePtr();
		A.put(ep, "mxWrapper_acos_A");
		mxWrapperEngEvalString(ep,"mxWrapper_acos_result=acos(mxWrapper_acos_A);");

		result.get(ep, "mxWrapper_acos_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_acos_result mxWrapper_acos_A ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_acos=mxWrapper_acos+1; catch, mxWrapper_acos=1; end");
#endif
	}
	else
	{
		result = zeros(A);
		transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::acos) );
	}
	return result;
}

mxWrapper mxWrapperNS::sin (const mxWrapper& A)
{
	mxWrapper result;

	if (A.IsComplex())
	{
		Engine *ep = GetEnginePtr();
		A.put(ep, "mxWrapper_sin_A");
		mxWrapperEngEvalString(ep,"mxWrapper_sin_result=sin(mxWrapper_sin_A);");

		result.get(ep, "mxWrapper_sin_result");

		// remove temporary variables from the matlab workspace (to avoid polluting the namespace and to reduce memory usage)
		mxWrapperEngEvalString(ep,"clear mxWrapper_sin_result mxWrapper_sin_A ");
#ifdef _DEBUG
		mxWrapperEngEvalString(ep,"try, mxWrapper_sin=mxWrapper_sin+1; catch, mxWrapper_sin=1; end");
#endif
	}
	else
	{
		result = zeros(A);
		transform( A.Mx.begin(), A.Mx.end(), result.Mx.begin(), pointer_to_unary_function <double,double>(::sin) );
	}
	return result;
}


// demonstrate argument passing
// a deep copy should not be created by putting mxWrapper as an argument
void subFunction(mxWrapper &wa1)
{
	mxWrapper wa2;
	wa2=wa1; // this DOES create a deep copy 

	// do some processing with data
	double *data = wa2.getPr();
	// for(i,j,k...)
	// { data[] ... }

	// alternative: do some processing with the mxArray
	CString c1;
	//mxArray *m1=wa2.getPMX();
	//c1.Format(_T("The datatype # (%d) is %s\n"), mxGetClassID(m1), mxGetClassName(m1));
	//AfxMessageBox(c1, MB_OK);

	// wa2's memory will be automatically deleted
	// wa1's memory is not deleted
}

mxWrapper mxTest_DownSampling (mxWrapper data, int nlen)
{  
  FILE_LOG(logDEBUG)<<"CD::DownSampling {";
  mxWrapper x,xi,newdata;
  mwSize i;
  mwSize nsz[2];
  int noff;

  data.Size(nsz,2);
  if(nsz[0]<2)
  {
    AfxMessageBox("Must be a column vector in DownSampling(...)!");
    return data;
  }
  
  FILE_LOG(logDEBUG4)<<"if(nlen == nsz[0])";
  if(nlen == nsz[0])
      return data;
  
  if(nsz[0]>(mwSize)nlen) //low-pass filtering for down-sampling
  {
    noff = nsz[0]-nlen;
    noff = noff/2;

    data = fft(data);
    data(mxWrapperColon(nsz[0]/2-noff,nsz[0]/2+noff),mxWrapperColon()) = 0;
    data = real(ifft(data));
  }
  
  FILE_LOG(logDEBUG4)<<" x  = linspace(1,nsz[0],nsz[0]);";
  x  = linspace(1,nsz[0],nsz[0]);
  x  = transpose(x);

  FILE_LOG(logDEBUG4)<<" xi = linspace(1,nsz[0],nlen+1);";
  xi = linspace(1,nsz[0],nlen+1);
  xi(1) = empty();
  
  xi = xi-(xi(2)-xi(1))/2;

  xi = transpose(xi);

  newdata = zeros(nlen,nsz[1]);

  FILE_LOG(logDEBUG4)<<"for (i=1;i<=nsz[1];i++);";
  for (i=1;i<=nsz[1];i++)  {
    FILE_LOG(logDEBUG4)<<"for (i="<<i;
    newdata(mxWrapperColon(),i) = interp1(x,data(mxWrapperColon(),i),xi,"linear");
  }

  FILE_LOG(logDEBUG)<<"} CD::DownSampling ";
  return newdata;

};

mxWrapper mxTest_designWnd(int nlen, int nmaxfreq, double dcutoff)
{
  BOOL bmark;
  int n;
  double delta_alpha;

  mxWrapper mywnd,tmpary1,tmpary2,myalpha;

  bmark = (nlen%2);
  nlen = nlen+(nlen%2);

  n = int(nmaxfreq*dcutoff)+1;
  n = n<4?4:n;  //keep at least 4 frequency components, not including DC
  n = n>nlen/2?nlen/2:n;
  
	const double PI = 3.14159;

  delta_alpha = PI/2/(n-1);
  
  myalpha = ramp(0,1,nlen-2);
  myalpha = cat(2,0,myalpha);
  myalpha = delta_alpha*myalpha;
  myalpha(find(myalpha>PI/2)) = PI/2;

  mywnd = cos(myalpha);

  mywnd(mxWrapperColon(nlen/2+2,1,nlen)) = mywnd(mxWrapperColon(nlen/2,-1,2));

  mywnd = transpose(mywnd);

  if(bmark)
    mywnd(nlen/2+1) = empty(); //5

	return mywnd;
}



int mxTestComplexWrappers()
{
// mxWrapper can hold imaginary arrays, but it does not implement many functions which use them

	mxWrapper a=zeros(10, 1, true);
	mxWrapper b=ones(10, 1, true);
	mxWrapper c=a+b;
	mxWrapper d=a-b;
	mxWrapper e=a*b;
	mxWrapper f=a/b;
		
	FILE_LOG(logDEBUG3)<<"mxTestComplexWrappers f" << f;
	
	return 0;
}

int mxTestWrappers()
{
	double dSW = 20, m_dSweepFieldGauss2Vol = 1.5;
	int nlen0 = 5, nlen1 = 5, nlen2 = 10, nlen3 = 5, nlen4 = 2; 
  mxWrapper mwtmp0;
	mwtmp0 = ones(nlen0,1)* (-dSW/2);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwtmp0 = " << mwtmp0;

  mxWrapper mwtmp1 = linspace(-dSW/2,dSW/2,nlen1);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwtmp1 = " << mwtmp1;

  mxWrapper mwtmp2 = ones(nlen2,1)*(dSW/2);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwtmp2 = " << mwtmp2;

  mxWrapper mwtmp3 = linspace(dSW/2,-dSW/2,nlen3);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwtmp3 = " << mwtmp3;

	mxWrapper mwSW   = vertcat(mwtmp0,transpose(mwtmp1),mwtmp2,transpose(mwtmp3))*m_dSweepFieldGauss2Vol;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwSW = " << mwSW;

	mwSW   = repmat(mwSW,nlen4,1);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mwSW after repmat = " << mwSW;

	mxTestComplexWrappers();

	mxWrapper a = ones(5,3);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mxWrapperColon() test a" << a;

	// oops, this calls mxWrapper::operator(mxWrapper,mxWrapper) const
	// instead of the non-const version
	a( mxWrapperColon(), 1 ) = 3;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mxWrapperColon() test a" << a;

	a( 1, mxWrapperColon() ) = 0;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mxWrapperColon() test a" << a;

	mxWrapper b(-1.0,1,1.0);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: ramp(-1,1,1) b" << b;
	a( 3, mxWrapperColon() ) = b;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: mxWrapperColon() a( 1, mxWrapperColon() ) = b, " << a;


	a /= 3;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a /= 3" << a;
	a += 0.5;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a += 3.14159" << a;

	b = repmat(mxWrapperColon(1,1,3), 5, 1);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: b = repmat(b, 5, 1) " << b;

	mxWrapper c = a / b;
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: c = a / b" << c;

	mxWrapper d = sum(a, 1);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: d = sum(a, 1)" << d;


	mxWrapper e = mxWrapperColon(3, 7);
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: e = mxWrapperColon(3, 7)" << e;

	mxWrapper f = find( e >= 4 );
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: f = find( e >= 4 )" << f;

	mxWrapper g;
	g = e( f );
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: g = e( f )" << g;

	a = ones(3);  
	FILE_LOG(logDEBUG3)<<"testing mxWrapperEnd(): a" << a;
	a(mxWrapperEnd(a,1,1))=2;
	FILE_LOG(logDEBUG3)<<"testing mxWrapperEnd(): a(mxWrapperEnd(a,1,1))=2; " << a;

	a = ones(3);  
	a(mxWrapperEnd(a,1,2),1)=2;
	FILE_LOG(logDEBUG3)<<"testing mxWrapperEnd(): a(mxWrapperEnd(a,1,2),1)=2; " << a;

	a = ones(3);  
	a(1,mxWrapperEnd(a,2,2))=2;
	FILE_LOG(logDEBUG3)<<"testing mxWrapperEnd(): a(1,mxWrapperEnd(a,2,2))=2; " << a;

	a = b;
	FILE_LOG(logDEBUG3)<<"testing empty(): a" << a;
	a = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a = empty();" << a;

	a = b;
	a(1) = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a(1) = empty();" << a;

	a = b;
	a(mxWrapperEnd(a,1,1)) = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a(mxWrapperEnd(a,1,1)) = empty();" << a;

	a = b;
	a(mxWrapperColon(),1) = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a(mxWrapperColon(),1) = empty();" << a;

	a = b;
	a(1,mxWrapperColon()) = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: a(1,mxWrapperColon()) = empty();" << a;

	FILE_LOG(logDEBUG3)<<"mxTestWrappers: e" << e;
	e( f ) = empty();
	FILE_LOG(logDEBUG3)<<"mxTestWrappers: e( f ) = empty();" << e;

	FILE_LOG(logDEBUG3)<<"mxTest_designWnd" << mxTest_designWnd(1024,100,1);
	FILE_LOG(logDEBUG3)<<"mxTest_DownSampling" << mxTest_DownSampling( ones(1024,1), 1024 );
	
	return 0;
}

int mxTestEngine()
{
	Engine *ep = GetEnginePtr();
	
	AfxMessageBox(_T("Opened MATLAB engine\n"), MB_OK);

	mxWrapper wa1(5.0);
	wa1.put(ep,"qa1");
	
	mxWrapper wa2;
	wa2.get(ep,"qa1");
	
	mxWrapper wa3(ep,"qa1");
	
	mxWrapper wa4 = linspace(1, 3, 3);
	
	mxWrapper wa5 = linspace(-10, -20, 3);
	mxWrapper wa6 = wa4 + wa5;
	subFunction(wa5);


	mxWrapper simulatedProjections(0.0,1.0,1024.0);
	simulatedProjections = repmat(transpose(simulatedProjections),1,5);
	mxTest_DownSampling(simulatedProjections,256);

	AfxMessageBox(_T("Successfully used MATLAB engine\n"), MB_OK);

	//CloseEngine();

	// all mxWrappers and their data should be automatically deleted here
	// when they go out of scope

	return 0;
}

