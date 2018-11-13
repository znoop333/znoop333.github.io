#include "stdafx.h"
#include "mxWrapper.h"
#include "log.h"

// This file contains all of the mxWrapper operator functions (+, -, etc.)
// Visual Studio Intellisense can't parse a file containing them operator functions, so they are all here
// to make the majority of the mxWrapper code parse correctly in mxWrapper.cpp



using mxWrapperNS::mxWrapper;
using mxWrapperNS::mxWrapperSubArray;

#include <algorithm>
using std::transform;
#include <functional>

template <typename T>
inline double castToDouble (T i) { return static_cast<double> (i); }

template <typename T>
inline float castToFloat (T i) { return static_cast<float> (i); }

mxWrapper mxWrapperNS::operator+ (const mxWrapper& A, const mxWrapper& B)
{
	ASSERT(!A.IsEmpty()); 
	ASSERT(!B.IsEmpty()); 
	mxWrapper result;

	if (A.getNumberElements() == 1)
	{
		result = B;
		result += A;
	}
	else
	{
		result = A;
		result += B;
	}

	return result;
}


mxWrapper &mxWrapper::operator+= (const mxWrapper &m1)
{
	ASSERT(!m1.IsEmpty());  // 2nd array must not be empty
	double *temp1 = getPr();
	const double *temp2 = m1.getPr();
	double d=0;	
	ASSERT(temp2!=NULL);
	mwSize M = getNumberElements();
	mwSize N = m1.getNumberElements();

	// but it could have only one element.
	if ( N == 1 )
	{
		d = m1.ExtractScalar(1);	

		for(mwSize i=0; i<M; i++)
			temp1[i] += d;

		if (m1.IsComplex())
		{
			ReallocImag();
			double di = m1.ExtractScalarImag(1);	
			for(mwSize i=1; i<=M; i++)
				AssignAt(i, ExtractScalarImag(i) + di, true);
		}
	}
	else
	{
		// multiple elements: 2nd array must be the same number of elements as this
		ASSERT(M==N);  

		for(mwSize i=0; i<N; i++)
			temp1[i] += temp2[i];

		if (m1.IsComplex())
		{
			ReallocImag();
			for(mwSize i=1; i<=M; i++)
				AssignAt(i, ExtractScalarImag(i) + m1.ExtractScalarImag(i), true);
		}
	}

	return *this;
}


mxWrapper mxWrapperNS::operator- (const mxWrapper& A, const mxWrapper& B)
{
	ASSERT(!A.IsEmpty()); 
	ASSERT(!B.IsEmpty()); 
	mxWrapper result;

	if (A.getNumberElements() == 1)
	{
		result = zeros(B);
		result.AssignConstant( A.ExtractScalar(1), false);
		if (A.IsComplex())
			result.AssignConstant( A.ExtractScalarImag(1), true);
	}
	else
	{
		result = A;
	}

	result -= B;
	return result;
}

mxWrapper &mxWrapper::operator-= (const mxWrapper &m1)
{
	ASSERT(!m1.IsEmpty());  // 2nd array must not be empty
	double *temp1 = getPr();
	const double *temp2 = m1.getPr();
	double d=0;	
	ASSERT(temp2!=NULL);
	mwSize M = getNumberElements();
	mwSize N = m1.getNumberElements();

	// but it could have only one element.
	if ( N == 1 )
	{
		d = m1.ExtractScalar(1);	

		for(mwSize i=0; i<M; i++)
			temp1[i] -= d;

		if (m1.IsComplex())
		{
			ReallocImag();
			double di = m1.ExtractScalarImag(1);	
			for(mwSize i=1; i<=M; i++)
				AssignAt(i, ExtractScalarImag(i) - di, true);
		}
	}
	else
	{
		// multiple elements: 2nd array must be the same number of elements as this
		ASSERT(M==N);  

		for(mwSize i=0; i<N; i++)
			temp1[i] -= temp2[i];

		if (m1.IsComplex())
		{
			ReallocImag();
			for(mwSize i=1; i<=M; i++)
				AssignAt(i, ExtractScalarImag(i) - m1.ExtractScalarImag(i), true);
		}
	}

	return *this;
}

mxWrapper mxWrapperNS::operator* (const mxWrapper& A, const mxWrapper& B)
{
	mxWrapper result;

	if(A.IsEmpty())
		return result;
	if(A.IsEmpty())
		return result;

	if (A.getNumberElements() == 1)
	{
		result = B;
		result *= A;
	}
	else
	{
		result = A;
		result *= B;
	}
	return result;
}

mxWrapper &mxWrapper::operator*= (const mxWrapper &m1)
{
	ASSERT(!m1.IsEmpty());  // 2nd array must not be empty
	double *temp1 = getPr();
	const double *temp2 = m1.getPr();	
	ASSERT(temp2!=NULL);
	mwSize M = getNumberElements();
	mwSize N = m1.getNumberElements();

	// but it could have only one element.
	if ( N == 1 )
	{
		if (!m1.IsComplex() && !IsComplex())
		{
			double d = m1.ExtractScalar(1);	

			for(mwSize i=0; i<M; i++)
				temp1[i] *= d;
		}
		else 
		{
			ReallocImag();
			double a, b, c, d;
			c = m1.ExtractScalar(d,1);	
			for(mwSize i=1; i<=M; i++)
			{
				a = ExtractScalar(b,i);	
				AssignAt(i, a*c - b*d, false);
				AssignAt(i, a*d + b*c, true);
			}
		}
	}
	else
	{
		// multiple elements: 2nd array must be the same number of elements as this
		ASSERT(M == N);  

		if (!m1.IsComplex() && !IsComplex())
		{
			for(mwSize i=0; i<N; i++)
				temp1[i] *= temp2[i];
		}
		else
		{
			ReallocImag();
			double a, b, c, d;
			for(mwSize i=1; i<=M; i++)
			{
				a = ExtractScalar(b,i);	
				c = m1.ExtractScalar(d,i);	
				AssignAt(i, a*c - b*d, false);
				AssignAt(i, a*d + b*c, true);
			}
		}

	}

	return *this;
}

mxWrapper mxWrapperNS::operator/ (const mxWrapper& A, const mxWrapper& B)
{
	ASSERT(!A.IsEmpty()); 
	ASSERT(!B.IsEmpty()); 
	mxWrapper result;

	if (A.getNumberElements() == 1)
	{
		result = zeros(B);
		result.AssignConstant( A.ExtractScalar(1), false);
		if (A.IsComplex())
			result.AssignConstant( A.ExtractScalarImag(1), true);
	}
	else
	{
		result = A;
	}

	result /= B;
	return result;
}

mxWrapper mxWrapperNS::rdivide (const mxWrapper& A, const mxWrapper& B)
{
	ASSERT(!A.IsEmpty()); 
	ASSERT(!B.IsEmpty()); 
	return A/B;
}

mxWrapper &mxWrapper::operator/= (const mxWrapper &m1)
{
	ASSERT(!m1.IsEmpty());  // 2nd array must not be empty
	double *temp1 = getPr();
	const double *temp2 = m1.getPr();	
	ASSERT(temp2!=NULL);
	mwSize M = getNumberElements();
	mwSize N = m1.getNumberElements();

	// but it could have only one element.
	if ( N == 1 )
	{
		if (!m1.IsComplex() && !IsComplex())
		{
			double d1 = m1.ExtractScalar(1);	
			ASSERT( d1 != 0 );

			for(mwSize i=0; i<M; i++)
				temp1[i] /= d1;
		}
		else
		{
			ReallocImag();
			double a, b, c, d;
			c = m1.ExtractScalar(d,1);	
			if ( (c*c + d*d) == 0 )
				throw( runtime_error("Divide by 0") );

			for(mwSize i=1; i<=M; i++)
			{
				a = ExtractScalar(b,i);	
				AssignAt(i, (a*c + b*d)/(c*c + d*d), false);
				AssignAt(i, (b*c - a*d)/(c*c + d*d), true);
			}
		}
	}
	else
	{
		// multiple elements: 2nd array must be the same number of elements as this
		ASSERT( M == N );  

		if (!m1.IsComplex() && !IsComplex())
		{
			for(mwSize i=0; i<N; i++)
				if (temp2[i] != 0)
					temp1[i] /= temp2[i];
		}
		else
		{
			ReallocImag();
			double a, b, c, d;

			for(mwSize i=1; i<=M; i++)
			{
				a = ExtractScalar(b,i);	
				c = m1.ExtractScalar(d,i);	
				if ( (c*c + d*d) == 0 )
					throw( runtime_error("Divide by 0") );

				AssignAt(i, (a*c + b*d)/(c*c + d*d), false);
				AssignAt(i, (b*c - a*d)/(c*c + d*d), true);
			}
		}
	}

	return *this;
}

mxWrapper mxWrapper::operator> (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		const double *pR=getPr();
		mwSize N = getNumberElements();
		for(mwSize i=1; i<=N; i++)
			if ( pR[i-1] > d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		const double *pR=getPr(), *pM1R = m1.getPr();
		mwSize N = getNumberElements();
		for(mwSize i=1; i<=N; i++)
			if ( pR[i-1] > pM1R[i-1] )
				result.AssignAt(i, 1);
	}
	return result;
}

mxWrapper mxWrapper::operator>= (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) >= d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) >= m1.ExtractScalar(i))
				result.AssignAt(i, 1);
	}
	return result;
}

mxWrapper mxWrapper::operator< (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		const double *pR=getPr();
		mwSize N = getNumberElements();
		for(mwSize i=1; i<=N; i++)
			if ( pR[i-1] < d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		const double *pR=getPr(), *pM1R = m1.getPr();
		mwSize N = getNumberElements();
		for(mwSize i=1; i<=N; i++)
			if ( pR[i-1] < pM1R[i-1] )
				result.AssignAt(i, 1);
	}
	return result;
}

mxWrapper mxWrapper::operator<= (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) <= d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) <= m1.ExtractScalar(i))
				result.AssignAt(i, 1);
	}
	return result;
}

mxWrapper mxWrapper::operator== (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) == d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) == m1.ExtractScalar(i))
				result.AssignAt(i, 1);
	}
	return result;
}
	
mxWrapper mxWrapper::operator!= (const mxWrapper &m1) const
{
	ASSERT(!m1.IsEmpty()); 
	mxWrapper result = zeros(*this);
	if ( m1.getNumberElements() == 1 )
	{
		double d = m1.ExtractScalar(1);
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) != d )
				result.AssignAt(i, 1);
	}
	else
	{
		ASSERT( m1.getNumberElements() == getNumberElements() );
		for(mwSize i=1; i<=getNumberElements(); i++)
			if ( ExtractScalar(i) != m1.ExtractScalar(i))
				result.AssignAt(i, 1);
	}
	return result;
}


mxWrapperSubArray mxWrapper::operator() (const mxWrapper &m1, const mxWrapper &m2, const mxWrapper &m3, const mxWrapper &m4, const mxWrapper &m5)
{
	// find() may return an empty array, which could then be indexed as a(find( 0 ) ) 
	// then it could be written to!!!!  a(find( 0 ) ) = 5
	if (IsEmpty() || m1.IsEmpty() )
		return mxWrapperSubArray();

	mxWrapperSubArray idx = indexGenerator(m1, m2, m3, m4, m5); // convert to indices
	return idx;
}



// this DOES create a deep copy
mxWrapper& mxWrapper::operator= (const mxWrapper& mx1) {
	static mwSize numDeepCopies = 0; // make sure this doesn't get excessive for simple functions like ones()
	if (this != &mx1) // self-assignment not allowed
	{  
		Mx = mx1.Mx;
		MxI = mx1.MxI;
		m_bIsCOLON=mx1.m_bIsCOLON;
		MxName=mx1.MxName;
		nDim=mx1.nDim;Dim1=mx1.Dim1;Dim2=mx1.Dim2;Dim3=mx1.Dim3;Dim4=mx1.Dim4;Dim5=mx1.Dim5;
	}

  return *this;    // Return ref for multiple assignment
}

mxWrapper & mxWrapper::operator= (const mxWrapperSubArray& msa)
{
	if(msa.baseWrapper == NULL)
		return *this; // do nothing

	// duplicate the mxWrapper in the right hand side of the assignment to prevent errors due to self-assignment 
	// this is legal! e.g. this reshapes n from a row vector to a column vector:
	//      n = colon(-nl,nr);  n = n(colon());
	// or
	//      n = ones(2,2);  n = n(colon());
	// or even
	//      n = ones(2,2,2);  n = n(colon(),colon());
	mwSize nd, n1, n2, n3, n4, n5;
	msa.safeSizeOf(nd, n1, n2, n3, n4, n5);
	bool assignImag = msa.baseWrapper->IsComplex();
	vDouble tempArray, tempArrayI;
	mwSize M = msa.baseWrapper->getNumberElements();
	ASSERT ( M > 0 );

	bool selfAssignment = false;
	double *src=msa.baseWrapper->getPr(), *srcI=msa.baseWrapper->getPi();
	
	// the code below assumed the mxArrays are different, but this assumption has been relaxed by 
	//    1. detecting when the two objects are holding the same vector
	//    2. duplicating the vector if needed to avoid read over-writing errors
	if( !Mx.empty() )
		if ( msa.baseWrapper == this )
		{
			selfAssignment = true;
			tempArray=Mx;
			src = &tempArray[0];

			if (assignImag)
			{
				tempArrayI=MxI;
				srcI = &tempArrayI[0];
			}
		}

	// allocate new memory to copy sub-array into
	switch (nd)
	{
	case 1:
		ASSERT ( n1 > 0 );
		*this = zeros_c(1,n1,assignImag);
		break;
	case 2:
		ASSERT ( n1 > 0 );
		ASSERT ( n2 > 0 );
		*this = zeros_c(n1,n2,assignImag);
		break;
	case 3:
		ASSERT ( n1 > 0 );
		ASSERT ( n2 > 0 );
		ASSERT ( n3 > 0 );
		*this = zeros_c(n1,n2,n3,assignImag);
		break;
	case 4:
		ASSERT ( n1 > 0 );
		ASSERT ( n2 > 0 );
		ASSERT ( n3 > 0 );
		ASSERT ( n4 > 0 );
		*this = zeros_c(n1,n2,n3,n4,assignImag);
		break;
	case 5:
		ASSERT ( n1 > 0 );
		ASSERT ( n2 > 0 );
		ASSERT ( n3 > 0 );
		ASSERT ( n4 > 0 );
		ASSERT ( n5 > 0 );
		*this = zeros_c(n1,n2,n3,n4,n5,assignImag);
		break;
	}

	double *pr=getPr();
	const double *pIdx = msa.indices.getPr();
	mwSize N = getNumberElements();
	mwSize P = msa.indices.getNumberElements();
	ASSERT ( N == P );
	for (mwSize i=1; i <= P; i++)
	{
		mwSize idx = static_cast<mwSize> (pIdx[i-1] );
		ASSERT ( idx >= 1 );
		ASSERT ( idx <= M );

		pr[i-1] = src[ idx - 1 ];
	}

	if (assignImag)
	{
		ReallocImag();
		double *pd=getPi();
		ASSERT(srcI != NULL);
		for (mwSize i=1; i <= P; i++)
		{
			mwSize idx = static_cast<mwSize> (pIdx[i-1] );
			ASSERT ( idx >= 1 );
			ASSERT ( idx <= M );
			pd[i-1] = srcI[ idx - 1 ];
		}
	}

	return *this;
}

// this is difficult: any of these could be colon() or arbitrary sub-arrays
mxWrapper mxWrapper::operator() (const mxWrapper &m1, const mxWrapper &m2, const mxWrapper &m3, const mxWrapper &m4, const mxWrapper &m5) const
{
	return subsref(m1, m2, m3, m4, m5);
}

mxWrapper mxWrapper::subsref(const mxWrapper& d1, const mxWrapper& d2, const mxWrapper& d3, const mxWrapper& d4, const mxWrapper& d5) const
{
	mxWrapperSubArray idx = indexGenerator(d1, d2, d3, d4, d5); // convert to indices
	//FILE_LOG(logDEBUG4)<<"mxWrapper::subsref: idx " << idx;
	return this->operator() (idx); // calls mxWrapper mxWrapper::operator()(const mxWrapperSubArray &msa) const
}

mxWrapper mxWrapper::operator() (const mxWrapperSubArray &msa) const
{
	mxWrapper a1;
	// mxWrapperSubArray in this context must use explicit linear indices
	ASSERT ( msa.indices.getNumberElements() > 0 );
	if (msa.indices.getNumberElements() == 1) 
	{	
		a1 = mxWrapper( ExtractScalar(static_cast<mwSize> (msa.indices.ExtractScalar(1))) );
	}
	else
	{
		// first use linear indices to get the data, then reshape it to the correct dimensions
		a1 = zeros( msa.indices.getNumberElements(), 1 );
		for( mwSize i = 1; i <= msa.indices.getNumberElements() ; i++)
			a1.AssignAt(i, ExtractScalar( static_cast<mwSize> (msa.indices.ExtractScalar(i)) ));

		mwSize nd, n1, n2, n3, n4, n5;
		msa.safeSizeOf(nd, n1, n2, n3, n4, n5);

		// at the very least, the first dimension must be defined
		ASSERT ( n1 != 0 );

		// for 2D or higher matrices, reshape appropriately.  dimensions of size 0 are ignored.  
		// if the size of dimension 3 is 0 then the size of dimension 4 must be zero as well 
		switch (nd)
		{
		case 1:
			// no changes needed: the array is already 1D
			break;
		case 2:
			ASSERT ( n2 > 0 );
			a1 = reshape( a1, n1, n2 );
			break;
		case 3:
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			a1 = reshape( a1, n1, n2, n3 );
			break;
		case 4:
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			ASSERT ( n4 > 0 );
			a1 = reshape( a1, n1, n2, n3, n4 );
			break;
		case 5:
			ASSERT ( n2 > 0 );
			ASSERT ( n3 > 0 );
			ASSERT ( n4 > 0 );
			ASSERT ( n5 > 0 );
			a1 = reshape( a1, n1, n2, n3, n4, n5 );
			break;
		}

	}
	return a1;
}

// write into the underlying mxArray at the indices from the mxWrapperSubArray argument
mxWrapperSubArray& mxWrapperSubArray::operator= (const mxWrapperSubArray &msa)
{
	// check for NULL pointers
	if ((baseWrapper == NULL) || (msa.baseWrapper == NULL))
		return *this;  // do nothing

	ASSERT( indices.getNumberElements() > 0 );

	// the two subarrays must be the same size
	if (! SizeTest(msa) )
	{
		ASSERT( false );  // if in DEBUG mode, die here
		return *this; // ignore the assignment
	}

	double *a = baseWrapper->getPr(), *b = msa.baseWrapper->getPr();
	mwSize N = indices.getNumberElements();
	mwSize M = baseWrapper->getNumberElements();
	mwSize P = msa.baseWrapper->getNumberElements();
	for (mwSize i=1; i <= N; i++)
	{
		mwSize idxA = static_cast<mwSize> (indices.ExtractScalar(i) - 1);  // C indexes from 0, not 1
		ASSERT ( idxA >= 0 );
		ASSERT ( idxA < M );

		mwSize idxB = static_cast<mwSize> (msa.indices.ExtractScalar(i) - 1);
		ASSERT ( idxB >= 0 );
		ASSERT ( idxB < P );

		a[ idxA ] = b[ idxB ];
	}

	if (msa.baseWrapper->IsComplex())
	{
		baseWrapper->ReallocImag();
		a = baseWrapper->getPi();
		b = msa.baseWrapper->getPi();
		for (mwSize i=1; i <= indices.getNumberElements(); i++)
		{
			mwSize idxA = static_cast<mwSize> (indices.ExtractScalar(i) - 1);  // C indexes from 0, not 1
			ASSERT ( idxA >= 0 );
			ASSERT ( idxA < baseWrapper->getNumberElements() );

			mwSize idxB = static_cast<mwSize> (msa.indices.ExtractScalar(i) - 1);
			ASSERT ( idxB >= 0 );
			ASSERT ( idxB < msa.baseWrapper->getNumberElements() );

			a[ idxA ] = b[ idxB ];
		}
	}

	return *this;
}

// assign an entire mxWrapper to a sub-array of another mxWrapper 
mxWrapperSubArray& mxWrapperSubArray::operator= (const mxWrapper &w)
{
	if( baseWrapper == NULL )
		return *this;

	mxWrapper d1, d2, d3, d4, d5;

	if (w.IsEmpty())
	{
		// this is a special exception: the following command should reallocate the mxArray with one dimension shrunk ("null assignment"):
		// these commands delete the first row of a.
		// e.g.,   a = eye(3);  a(:,1) = []
		// in c++: mxWrapper a(eye(3));  a(mxWrapperColon(),1) = empty();
		//
		// another example: this command deletes two columns in a 3D matrix:
		// e.g.,   a = zeros([3, 3, 3]);  a(:,[1 2],:) = []
		// in c++: mxWrapper a(zeros(3, 3, 3));  a(mxWrapperColon(),linspace(1,2,2),mxWrapperColon()) = empty();
		//
		// important: only one dimension may be shrunk. if you try this command, you will get the error: "A null assignment can have only one non-colon index."
		//         a = zeros([3, 3, 3]);  a(:,[1 2],1) = []
		// also illegal:
		//         a = zeros([3, 3, 3]);  a(1:3,1:3,1:3) = []

		// the null assignment is accomplished by determining which dimension is not COLON (only one! all others must be COLON), 
		// then identifying which parts of that dimension should be retained. 
		// a new mxArray is created to hold the remaining portion of the matrix

		// create default sub-indexes: by default, every element of every dimension is used as if it was colon.
		//     a = ones([3 3 3]); a(:,:) = []
		// is equivalent to 
		//     a = ones([3 3 3]); a(:,:,:) = []
		if ( baseWrapper->Size() >= 5 )
			d5 = mxWrapperColon(1,baseWrapper->Size(5));
		if ( baseWrapper->Size() >= 4 )
			d4 = mxWrapperColon(1,baseWrapper->Size(4));
		if ( baseWrapper->Size() >= 3 )
			d3 = mxWrapperColon(1,baseWrapper->Size(3));
		if ( baseWrapper->Size() >= 2 )
			d2 = mxWrapperColon(1,baseWrapper->Size(2));
		if ( baseWrapper->Size() >= 1 )
			d1 = mxWrapperColon(1,baseWrapper->Size(1));

		// determine which dimension is not COLON
		mwSize shrunkDim=0; 

		// another special exception: consider this code:
		//       a = eyes(3);  a([1 4 7]) = []
		// according to the Matlab documentation, this should transform the matrix from 2D to 1D, 
		// and then eliminate elements 1, 4, 7 using linear indexing
		// therefore, the resulting array will be equivalent to a([2 3 5 6 8 9]), which creates a 1D matrix!
		// this condition would occur when dimensions 2, 3, and 4 are all indexed as 0 (undefined)
		// which implies only the first dimension is being used.
		if ( !D1.IsEmpty() && D2.IsEmpty() && D3.IsEmpty() && D4.IsEmpty() && D5.IsEmpty() )
		{
			shrunkDim=1;
			if (D1.IsCOLON())
			{
				//     a = ones([3 3 3]); a(:) = []
				// this should delete a entirely disregarding any other conditions
				d1.empty();  // force the deletion (below)
			}
			else
			{
				d1 = ones(1,(int)baseWrapper->getNumberElements());  // by default, all elements in the array will be retained
				d2.empty(); d3.empty(); d4.empty(); d5.empty(); // retain the information that dimensions 2, 3, 4, and 5 are all undefined
				mwSize N = D1.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D1.ExtractScalar(i));
					d1.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d1 = find(d1); // might be empty! in this case, the entire array must be deleted
			}

		}
		else 
		{
			FILE_LOG(logDEBUG4)<<"mxWrapperSubArray::operator= (const mxWrapper &w), d1" << d1 << ", d2" << d2 << ", d3" << d3 << ", d4" << d4 << ", d5" << d5;

			if (!D1.IsCOLON() && !D1.IsEmpty() )
			{
				shrunkDim=1;
				d1 = ones(1,(int)baseWrapper->Size(1));  // by default, all elements in this dimension will be retained
				mwSize N = D1.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D1.ExtractScalar(i));
					d1.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d1 = find(d1); // might be empty! in this case, the entire array must be deleted
				if (d1.IsEmpty())
				{
					baseWrapper->empty();
					return *this;
				}
			}
			else if (!D2.IsCOLON() && !D2.IsEmpty() )
			{
				shrunkDim=2;
				d2 = ones(1,baseWrapper->Size(2));  // by default, all elements in this dimension will be retained
				mwSize N = D2.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D2.ExtractScalar(i));
					d2.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d2 = find(d2); // might be empty! in this case, the entire array must be deleted
				if (d2.IsEmpty())
				{
					baseWrapper->empty();
					return *this;
				}
			}
			else if (!D3.IsCOLON() && !D3.IsEmpty() )
			{
				shrunkDim=3;
				d3 = ones(1,(int)baseWrapper->Size(3));  // by default, all elements in this dimension will be retained
				mwSize N = D3.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D3.ExtractScalar(i));
					d3.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d3 = find(d3); // might be empty! in this case, the entire array must be deleted
				if (d3.IsEmpty())
				{
					baseWrapper->empty();
					return *this;
				}
			}
			else if (!D4.IsCOLON() && !D4.IsEmpty() )
			{
				shrunkDim=4;
				d4 = ones(1,(int)baseWrapper->Size(4));  // by default, all elements in this dimension will be retained
				mwSize N = D4.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D4.ExtractScalar(i));
					d4.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d4 = find(d4); // might be empty! in this case, the entire array must be deleted
				if (d4.IsEmpty())
				{
					baseWrapper->empty();
					return *this;
				}
			}
			else if (!D5.IsCOLON() && !D5.IsEmpty() )
			{
				shrunkDim=5;
				d5 = ones(1,(int)baseWrapper->Size(5));  // by default, all elements in this dimension will be retained
				mwSize N = D5.getNumberElements();
				for(mwSize i=1; i <= N; i++)
				{
					mwSize idx = static_cast<mwSize> (D5.ExtractScalar(i));
					d5.AssignAt(idx, 0); // remove each element specified by the sub-array
				}
				// retain only the elements which were not marked for deletion
				d5 = find(d5); // might be empty! in this case, the entire array must be deleted
				if (d5.IsEmpty())
				{
					baseWrapper->empty();
					return *this;
				}
			}
		}

		FILE_LOG(logDEBUG4)<<"mxWrapperSubArray::operator= (const mxWrapper &w), d1" << d1 << ", d2" << d2 << ", d3" << d3 << ", d4" << d4 << ", d5" << d5;

		ASSERT( shrunkDim != 0 );

		// construct the new sub-array from the elements which should not be deleted
		mxWrapperSubArray result = baseWrapper->operator()(d1,d2,d3,d4,d5);
		// copy it into a new array (to avoid trying to overwrite baseWrapper at the same time as reading it)
		mxWrapper temp = result;
		// change the underlying mxArray* to point to the new sub-array
		*baseWrapper = temp;

	} 
	else if (w.getNumberElements() == 1)
	{
		// first overwrite real component
		AssignConstant( w.ExtractScalar(1), false );

		// if needed, also overwrite imaginary component
		if ( w.IsComplex() )
		{
			double dr,di;
			dr = w.ExtractScalar(di,1);
			AssignConstant( di, true );
		}
		else if ( baseWrapper->IsComplex() )
		{
			//baseWrapper->ReallocReal();
			AssignConstant( 0, true );
		}

	} 
	else 
	{
		// normal subarray assignment: each index in the left hand side is overwritten with consecutive elements of the right hand side

		// by default, each of the dimensions is not indexed at all.  
		// if the dimension exists, all elements should be indexed
		if (( w.Size() >= 5 ) && !D5.IsEmpty() )
			d4 = mxWrapperColon(1,w.Size(5));
		if (( w.Size() >= 4 ) && !D4.IsEmpty() )
			d4 = mxWrapperColon(1,w.Size(4));
		if (( w.Size() >= 3 ) && !D3.IsEmpty() )
			d3 = mxWrapperColon(1,w.Size(3));
		if (( w.Size() >= 2 ) && !D2.IsEmpty() )
			d2 = mxWrapperColon(1,w.Size(2));
		if (( w.Size() >= 1 ) && !D1.IsEmpty() )
			d1 = mxWrapperColon(1,w.Size(1));

		mxWrapper *temp = const_cast<mxWrapper *>(&w); // intentionally discard const qualifier on this pointer so that subarray assignments are possible from mxWrapperSubArray
		mxWrapperSubArray msa1(temp, mxWrapperColon(1,w.getNumberElements()), d1, d2, d3, d4, d5);
		return *this = msa1; // call mxWrapperSubArray::operator= (const mxWrapperSubArray &)
	} 

	return *this;
}



ostream &operator<<(ostream &os, const mxException &mx1)
{
	return os << mx1.what();
}


ostream &operator<<(ostream &os, const mxWrapperNS::mxWrapper &mx1)
{
	if (mx1.IsEmpty())  // don't try to print if the array is empty
	{
		os << _T("empty array") << endl;
		return os;
	}

	mwSize nd, U, V, n3, n4, n5;
	safeSizeOf(mx1, nd, U, V, n3, n4, n5);

	os << _T("(") << U << _T(", ") << V << _T("): ") << mx1.getNumberElements() << _T(" elements (") << mx1.GetClassName() << _T(")") << endl;
	os.flush();

	mwSize nPrinted = mx1.getNumberElements();
	if (nPrinted > 20)
		nPrinted = 20;

	os << _T("mx1(1:20) = [");
	for(mwSize idx=1; idx<=nPrinted; idx++)
	{
		os << mx1.ExtractScalar(idx) << ", ";
	}
	os << _T("];")<< endl;

	if (mx1.IsComplex()) 
	{
		os << _T("imag(mx1(1:20)) = [");
		for(mwSize idx=1; idx<=nPrinted; idx++)
		{
			os << mx1.ExtractScalarImag(idx) << ", ";
		}
		os << _T("];")<< endl;
	}

	return os;
}

ostream &operator<<(ostream &os, const mxWrapperNS::mxWrapperSubArray &msa)
{
	os << _T("mxWrapperSubArray with indices");
	os << msa.ToString();
	os.flush();
	return os;
}