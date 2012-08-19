/*! \file host_multiarray.h
 *  \brief A dynamically-sizable structure of arrays of elements which reside in the "host" memory space.
 */
#pragma once

#include <muse/multiarray/detail/common.h>
#include <muse/multiarray/detail/host_multiarray.inl>


namespace muse
{


	/*!
	 *   Getter function that returns reference to N-th container
	 *   of \p host_multiarray
	 *   
	 *   \tparam N container id within \p host_multiarray structure of containers
	 *   \tparam HT head type
	 *   \tparam TT tail type
	 *   
	 *   \param  t reference to \p host_multiarray instance
	 *   \return reference to N-th container
	 *
	 *   The following code snippet demonstrates how to use \p get to access particular
	 *   container within \p host_multiarray
	 *
	 *   \code
	 *   #include <muse/multiarray/host_multiarray.h>
	 *   
	 *   muse::host_multiarray<float, int, bool> x(10000);
	 *
	 *   thrust::host_vector<float> & v0 = muse::get<0>(x);
	 *   thrust::host_vector<int>   & v1 = muse::get<1>(x);
	 *   thrust::host_vector<bool>  & v2 = muse::get<2>(x);
	 *
	 *   \endcode
	 */
	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename multiarray_element<N, muse::detail::cons_host<HT, TT> >::type >::reference_type
			get(muse::detail::cons_host<HT, TT>& t);


	/*!
	 *   Getter function that returns const reference to N-th container
	 *   of \p host_multiarray
	 *   
	 *   \tparam N container id within \p host_multiarray structure of containers
	 *   \tparam HT head type
	 *   \tparam TT tail type
	 *   
	 *   \param  t const reference to \p host_multiarray instance
	 *   \return const reference to N-th container
	 *
	 *   The following code snippet demonstrates how to use \p get to access particular
	 *   container within \p host_multiarray
	 *
	 *   \code
	 *   #include <muse/multiarray/host_multiarray.h>
	 *   
	 *   muse::host_multiarray<float, int, bool> x(10000);
	 *
	 *   const thrust::host_vector<float> & v0 = muse::get<0>(x);
	 *   const thrust::host_vector<int>   & v1 = muse::get<1>(x);
	 *   const thrust::host_vector<bool>  & v2 = muse::get<2>(x);
	 *
	 *   \endcode
	 */
	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename multiarray_element<N, muse::detail::cons_host<HT, TT> >::type >::const_reference_type
			get(const muse::detail::cons_host<HT, TT>& t);


	/*!
	 *   Structure of arrays basing on thrust::host_vector.
	 *   Max number of arrays reduced to 10
	 *   
	 *   The following code snippet demonstrates how to create and use \p host_multiarray
	 *
	 *   \code
	 *   #include <muse/multiarray/host_multiarray.h>
	 *   #include <thrust/sort.h>
	 *   #include <cstdlib>
	 *   
	 *   typedef muse::host_multiarray<float, int, float, float> ExtendedSiteArray;
	 *
	 *   int main()
	 *   {
	 *     // create instance
	 *     ExtendedSiteArray array;
	 * 
	 *     // resize all arrays uniformly
	 *     array.resize(10000);
	 *
	 *     // generate first host_multiarray's container elements using thrust::generate
	 *     thrust::generate(muse::get<0>(array).begin(), muse::get<0>(array).end(), rand);
	 *
	 *     // sort first host_multiarray's container using thrust::sort
	 *     thrust::sort(muse::get<0>(array).begin(), muse::get<0>(array).end());
	 *   }
	 *
	 *   \endcode
	 */
	template<typename T0, typename T1, typename T2, typename T3, typename T4,
	         typename T5, typename T6, typename T7, typename T8, typename T9>
	class host_multiarray 
		: public muse::detail::map_multiarray_to_cons_host<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
	{

	private:
		typedef typename muse::detail::map_multiarray_to_cons_host<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type inherited;
		typedef typename inherited::size_type size_type;

	public:

		/*!
		 *  This constructor creates an empty \p host_multiarray 
		 */
		host_multiarray(void)
			: inherited() {};

		/*!
		 *  This constructor creates a \p host_multiarray with n elements 
		 *  \param n number of elements to initially create
		 */
		explicit host_multiarray(size_type n)
			: inherited(n) {};

		/*!
		 *  Default destructor
		 */
		~host_multiarray(void) {};

		/*!
		 *  Resizes each of the \p host_multiarray component uniformly to contain n elements
		 *  \param n new \p host_multiarray size expressed in elements
		 *  \return none
		 */
		void resize(size_type n) { inherited::resize(n); }

		/*!
		 *  Returns the number of elements
		 *  \return number of elements
		 */
		size_type size(void) const { return inherited::size(); }

	private:
		host_multiarray(const host_multiarray&);
		host_multiarray& operator=(const host_multiarray&);

	}; // end class host_multiarray


	/*! \cond
	 */
	template<>
	class host_multiarray<null_type, null_type, null_type, null_type, null_type,
	                      null_type, null_type, null_type, null_type, null_type>
	{
	public:
		typedef null_type inherited;
	};
	/*! \endcond
	 */


} // end namespace muse
