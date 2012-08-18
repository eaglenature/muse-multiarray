/*! \file common.h
 *  \brief Common components for device_multiarray and host_multiarray.
 */
#pragma once


namespace muse
{

	struct null_type;


	// forward declaration of multiarray_element metafunction
	template<int i, typename T> struct multiarray_element;


	/*!
	 *  Type of N-th element in multiarray
	 *  The result type is particular container type
	 */
	template<int N, class T> struct multiarray_element
	{
	private:
		typedef typename T::tail_type Next;
	public:
		// The result of this metafunction is returned in type
		typedef typename multiarray_element<N-1, Next>::type type;
	};


	// specializations for multiarray_element metafunction
	template<class T> struct multiarray_element<0,T>
	{
		typedef typename T::container_head_type type;
	};



	// forward declaration of multiarray_size  metafunction
	template<class T> struct multiarray_size;


	/*!
	 *   Number of multiarray attributes
	 */
	template<class T> struct multiarray_size
	{ 
		//The result of this metafunction is returned in value.
		static const int value = 1 + multiarray_size<typename T::tail_type>::value;
	};



	template<> struct multiarray_size<null_type>
	{
		static const int value = 0;
	};



	// define null_type
	struct null_type {};



	template<typename T>
	struct access_traits
	{
		typedef const T& const_reference_type;
		typedef T& reference_type;
	};



} // end namespace muse
