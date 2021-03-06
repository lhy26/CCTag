/*
 * Copyright 2016, Simula Research Laboratory
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _CCTAG_NUMERICAL_MATRIX_HPP_
#define	_CCTAG_NUMERICAL_MATRIX_HPP_

#include <cctag/utils/Allocator.hpp>

#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace cctag {
namespace numerical {

typedef boost::numeric::ublas::row_major DefaultStorageOrder;


/*
//-----------------------------
// C++-1x solution
template<typename BaseType>
typedef boost::numeric::ublas::matrix<BaseType, StorageOrder, boost::numeric::ublas::unbounded_array<BaseType, cctag::AlignedAllocator<BaseType> > > Matrix;

template<typename T>
void f( Matrix<T> & m );

Matrixd m;
f(m);

//-----------------------------
// struct to simulate a template alias
// but doesn't allows automatic template
template<typename T>
void f( typename Matrix<T>::Type m, typename BoundedMatrix<T, 3,4>::Type& mm );

Matrixd m;
f<float>(m);

//-----------------------------
// define solution
// not really clear
template<typename T>
void f( CCTAG_Matrix(T) & m, CCTAG_BoundedMatrix(T, 3, 4) & mm );

Matrixd m;
f(m);

//-----------------------------
*/
template<typename T, typename SO = DefaultStorageOrder>
struct Matrix
{
	typedef T BaseType;
	typedef boost::numeric::ublas::unbounded_array<BaseType, cctag::AlignedAllocator<BaseType> > StorageType;
	typedef boost::numeric::ublas::matrix<BaseType, SO, StorageType> Type;

	typedef boost::numeric::ublas::shallow_array_adaptor<BaseType>        ShallowStorageType;
	typedef boost::numeric::ublas::matrix<BaseType, SO, ShallowStorageType>   ShallowType;

private:
	Matrix(){}
};

template<class T, std::size_t M, std::size_t N, typename SO = DefaultStorageOrder>
struct BoundedMatrix
{
	typedef T BaseType;
//	typedef boost::numeric::ublas::bounded_array<BaseType, M*N, cctag::AlignedAllocator<BaseType> > StorageType;
	typedef boost::numeric::ublas::bounded_matrix<BaseType, M, N, SO> Type;

private:
	BoundedMatrix(){}
};

template<typename T>
struct Vector
{
	typedef T BaseType;
	typedef boost::numeric::ublas::unbounded_array<BaseType, cctag::AlignedAllocator<BaseType> > StorageType;
	typedef boost::numeric::ublas::vector<BaseType, StorageType> Type;

	typedef boost::numeric::ublas::shallow_array_adaptor<BaseType>        ShallowStorageType;
	typedef boost::numeric::ublas::vector<BaseType, ShallowStorageType>   ShallowType;

private:
	Vector(){}
};

template<typename T, std::size_t S>
struct BoundedVector
{
	typedef T BaseType;
//	typedef boost::numeric::ublas::bounded_array<BaseType, cctag::AlignedAllocator<BaseType> > StorageType;
	typedef boost::numeric::ublas::bounded_vector<BaseType, S> Type;

//	typedef boost::numeric::ublas::shallow_array_adaptor<BaseType>              ShallowStorageType;
//	typedef boost::numeric::ublas::bounded_vector<BaseType, ShallowStorageType> ShallowType;

private:
	BoundedVector(){}
};





#define CCTAG_DEFINE_NUMERICAL_MATRIX_TYPES( TYPE, ORDER, ORDERSTR, POST ) \
	\
	typedef Matrix<TYPE,ORDER>::Type Matrix##ORDERSTR##POST; \
	typedef Matrix<TYPE,ORDER>::ShallowType MatrixView##ORDERSTR##POST; \
	typedef Matrix<TYPE,ORDER>::ShallowStorageType MatrixViewInit##ORDERSTR##POST; \
	\
	typedef BoundedMatrix<TYPE, 2, 2, ORDER>::Type BoundedMatrix2x2##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 2, 3, ORDER>::Type BoundedMatrix2x3##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 2, 4, ORDER>::Type BoundedMatrix2x4##ORDERSTR##POST; \
	\
	typedef BoundedMatrix<TYPE, 3, 2, ORDER>::Type BoundedMatrix3x2##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 3, 3, ORDER>::Type BoundedMatrix3x3##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 3, 4, ORDER>::Type BoundedMatrix3x4##ORDERSTR##POST; \
	\
	typedef BoundedMatrix<TYPE, 4, 2, ORDER>::Type BoundedMatrix4x2##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 4, 3, ORDER>::Type BoundedMatrix4x3##ORDERSTR##POST; \
	typedef BoundedMatrix<TYPE, 4, 4, ORDER>::Type BoundedMatrix4x4##ORDERSTR##POST; \
//

#define CCTAG_DEFINE_NUMERICAL_TYPES( TYPE, POST ) \
	\
	CCTAG_DEFINE_NUMERICAL_MATRIX_TYPES( TYPE, boost::numeric::ublas::row_major, , POST ) \
	CCTAG_DEFINE_NUMERICAL_MATRIX_TYPES( TYPE, boost::numeric::ublas::column_major, C, POST ) \
	CCTAG_DEFINE_NUMERICAL_MATRIX_TYPES( TYPE, boost::numeric::ublas::row_major, R, POST ) \
	\
	typedef Vector<TYPE>::Type Vector##POST; \
	typedef Vector<TYPE>::ShallowType VectorView##POST; \
	\
	typedef boost::numeric::ublas::shallow_array_adaptor<TYPE> ArrayViewInit##POST; \
	\
	typedef BoundedVector<TYPE, 2>::Type BoundedVector2##POST; \
	typedef BoundedVector<TYPE, 3>::Type BoundedVector3##POST; \
	typedef BoundedVector<TYPE, 4>::Type BoundedVector4##POST; \
//


CCTAG_DEFINE_NUMERICAL_TYPES( float, d )
CCTAG_DEFINE_NUMERICAL_TYPES( float, f )
//CCTAG_DEFINE_NUMERICAL_TYPES( int, i )
//CCTAG_DEFINE_NUMERICAL_TYPES( char, c )


}
}

#endif

