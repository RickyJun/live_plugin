/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_07172005_0843)
#define FUSION_CONS_07172005_0843

#include "cons_fwd.hpp"
#include "access.hpp"
#include "begin.hpp"
#include "end.hpp"
#include "next.hpp"
#include "deref.hpp"
#include "cons_iterator.hpp"
#include "begin_impl.hpp"
#include "end_impl.hpp"
#include "at_impl.hpp"
#include "value_at_impl.hpp"
#include "empty_impl.hpp"
#include "is_convertible.hpp"
#include "enable_if.hpp"
#include "sequence_base.hpp"
#include "int.hpp"
#include "bool.hpp"
#include "or.hpp"

namespace boost { namespace fusion
{
    struct void_;
    struct cons_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    struct nil : sequence_base<nil>
    {
        typedef mpl::int_<0> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef void_ car_type;
        typedef void_ cdr_type;

        nil() {}

        template <typename Iterator>
        nil(Iterator const& /*iter*/, mpl::true_ /*this_is_an_iterator*/)
        {}

        template <typename Iterator>
        void assign_from_iter(Iterator const& /*iter*/)
        {
        }
    };

    template <typename Car, typename Cdr /*= nil*/>
    struct cons : sequence_base<cons<Car, Cdr> >
    {
        typedef mpl::int_<Cdr::size::value+1> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef Car car_type;
        typedef Cdr cdr_type;

        cons()
            : car(), cdr() {}

        explicit cons(typename detail::call_param<Car>::type in_car)
            : car(in_car), cdr() {}

        cons(
            typename detail::call_param<Car>::type in_car
          , typename detail::call_param<Cdr>::type in_cdr)
            : car(in_car), cdr(in_cdr) {}
        
        template <typename Car2, typename Cdr2>
        cons(cons<Car2, Cdr2> const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}

        cons(cons const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}

        template <typename Sequence>
        cons(
            Sequence const& seq
          , typename boost::disable_if<
                mpl::or_<
                    is_convertible<Sequence, cons> // use copy ctor instead
                  , is_convertible<Sequence, Car>  // use copy to car instead
                > 
            >::type* /*dummy*/ = 0
        )
            : car(*fusion::begin(seq))
            , cdr(fusion::next(fusion::begin(seq)), mpl::true_()) {}

        template <typename Iterator>
        cons(Iterator const& iter, mpl::true_ /*this_is_an_iterator*/)
            : car(*iter)
            , cdr(fusion::next(iter), mpl::true_()) {}

        template <typename Car2, typename Cdr2>
        cons& operator=(cons<Car2, Cdr2> const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }

        cons& operator=(cons const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }

        template <typename Sequence>
        typename boost::disable_if<is_convertible<Sequence, Car>, cons&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type Iterator;
            Iterator iter = fusion::begin(seq);
            this->assign_from_iter(iter);
            return *this;
        }

        template <typename Iterator>
        void assign_from_iter(Iterator const& iter)
        {
            car = *iter;
            cdr.assign_from_iter(fusion::next(iter));
        }

        car_type car;
        cdr_type cdr;
    };
}}

#endif

