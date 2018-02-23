//
// Created by marmus_a on 07/02/18.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE TestCore

#include "ThreadPool.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestBoostCompilation) {
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE(ClassThreadPool)
    BOOST_AUTO_TEST_CASE(execution) {
        ThreadPool pool(4);

        pool.runAsync([] () {
           BOOST_CHECK(true);
        });
    }
 BOOST_AUTO_TEST_SUITE_END()