/*! \file device_multiarray.inl
 *  \brief Inline file for device_multiarray.h.
 */
#pragma once

#include <thrust/device_vector.h>

namespace muse
{


	// forward declaration for device_multiarray
	template <typename T0 = null_type, typename T1 = null_type, typename T2 = null_type,
	          typename T3 = null_type, typename T4 = null_type, typename T5 = null_type,
	          typename T6 = null_type, typename T7 = null_type, typename T8 = null_type,
	          typename T9 = null_type>
	class device_multiarray;


	template<> struct multiarray_size< device_multiarray<> >
	{
		static const int value = 0;
	};


	namespace detail
	{
		// Forward declaration of cons structure (typelist)
		template<class HT, class TT> struct cons_device;
	}




	/*!
	 *   Forward declaration of get function that returns reference to N-th container
	 *   of multiarray
	 */
	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::reference_type
			get(muse::detail::cons_device<HT, TT>& c);

	/*!
	 *   Forward declaration of get function that returns const reference to N-th container
	 *   of multiarray
	 */
	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::const_reference_type
			get(const muse::detail::cons_device<HT, TT>& c);


	namespace detail
	{

		template<int N>
		struct get_class_device
		{

			template<class RET, class HT, class TT>
			inline static RET get(const cons_device<HT, TT>& t)
			{
				return get_class_device<N-1>::template get<RET>(t.tail);
			}

			template<class RET, class HT, class TT>
			inline static RET get(cons_device<HT, TT>& t)
			{
				return get_class_device<N-1>::template get<RET>(t.tail);
			}
		};

		template<>
		struct get_class_device<0>
		{

			template<class RET, class HT, class TT>
			inline static RET get(const cons_device<HT, TT>& t)
			{
				return t.head;
			}

			template<class RET, class HT, class TT>
			inline static RET get(cons_device<HT, TT>& t)
			{
				return t.head;
			}
		};

	}  // end namespace detail


	namespace detail
	{

		template<class HT, class TT>
		struct cons_device
		{
			typedef HT head_type;
			typedef TT tail_type;

			typedef thrust::device_vector<head_type> container_head_type;
			typedef typename thrust::device_vector<head_type>::size_type size_type;


			// Attributes
			container_head_type head;
			tail_type tail;


			// Constructor
			explicit cons_device(size_type n) 
				: head(n), tail(n) {}

			// Accessors
			inline
				typename access_traits<container_head_type>::reference_type
					get_head() { return head; }

			inline
				typename access_traits<tail_type>::reference_type
					get_tail() { return tail; }

			inline
				typename access_traits<container_head_type>::const_reference_type
					get_head() const { return head; }

			inline
				typename access_traits<tail_type>::const_reference_type
					get_tail() const { return tail; }


			template<int N>
				typename access_traits<typename multiarray_element<N, cons_device<HT, TT> >::type >::reference_type
					get() { return muse::get<N>(*this); }

			template<int N>
				typename access_traits<typename multiarray_element<N, cons_device<HT, TT> >::type >::const_reference_type
					get() const { return muse::get<N>(*this); }

			// Methods
			void resize(size_type n) { head.resize(n); tail.resize(n); }

		};


		template<typename HT>
		struct cons_device<HT, null_type>
		{
			typedef HT head_type;
			typedef null_type tail_type;
			typedef cons_device<HT, null_type> self_type;

			typedef thrust::device_vector<head_type> container_head_type;
			typedef typename thrust::device_vector<head_type>::size_type size_type;


			// Attributes
			container_head_type head;


			// Constructor
			explicit cons_device(size_type n) 
				: head(n) {}

			// Accessors
			inline
				typename muse::access_traits<container_head_type>::reference_type
					get_head() { return head; }

			inline
				null_type get_tail() { return null_type(); }

			inline
				typename muse::access_traits<container_head_type>::const_reference_type
					get_head() const { return head; }

			inline
				null_type get_tail() const { return null_type(); }

			template<int N>
				typename muse::access_traits<typename multiarray_element<N, self_type >::type >::reference_type
					get() { return muse::get<N>(*this); }

			template<int N>
			typename muse::access_traits<typename multiarray_element<N, self_type >::type >::const_reference_type
				get() const { return muse::get<N>(*this); }

			// Methods
			void resize(size_type n) { head.resize(n); }
		};






		template<typename T0, typename T1, typename T2, typename T3, typename T4,
		         typename T5, typename T6, typename T7, typename T8, typename T9>
		struct map_multiarray_to_cons_device
		{
			typedef muse::detail::cons_device<T0,
				typename muse::detail::map_multiarray_to_cons_device<T1, T2, T3, T4, T5, T6, T7, T8, T9, null_type>::type > type;
		};

		template<>
		struct map_multiarray_to_cons_device<null_type, null_type, null_type, null_type, null_type,
		                                     null_type, null_type, null_type, null_type, null_type>
		{
			typedef null_type type;
		};

	} // end namespace detail





	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename muse::multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::reference_type
			get(muse::detail::cons_device<HT, TT>& c)
	{
		return muse::detail::get_class_device<N>::template
			get<typename access_traits<
			        typename muse::multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::reference_type, HT, TT >(c);
	}




	template<int N, class HT, class TT>
	inline 
		typename muse::access_traits<typename muse::multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::const_reference_type
			get(const muse::detail::cons_device<HT, TT>& c)
	{
		return muse::detail::get_class_device<N>::template
			get<typename muse::access_traits<
			        typename muse::multiarray_element<N, muse::detail::cons_device<HT, TT> >::type >::const_reference_type, HT, TT >(c);
	}


} // end namespace muse
