/*
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <catch2/catch_test_macros.hpp>

namespace {

    static bool itDoesThis() { return true; }

    static bool itDoesThat() { return true; }

    // a trivial fixture example to support SCENARIO_METHOD tests
    struct Fixture {
        Fixture(): d_counter( 0 ) {}

        int counter() { return d_counter++; }

        int d_counter;
    };

}


SCENARIO("Do that thing with the thing", "[Tags]") {
    GIVEN("This stuff exists") {
        // make stuff exist
        AND_GIVEN("And some assumption") {
            // Validate assumption
            WHEN("I do this") {
                // do this
                THEN("it should do this") {
                    REQUIRE(itDoesThis());
                    AND_THEN("do that") {
                        REQUIRE(itDoesThat());
                    }
                }
            }
        }
    }
}

SCENARIO( "Vector resizing affects size and capacity",
          "[vector][bdd][size][capacity]" ) {
    GIVEN( "an empty vector" ) {
        std::vector<int> v;
        REQUIRE( v.size() == 0 );

        WHEN( "it is made larger" ) {
            v.resize( 10 );
            
            THEN_REQUIRE( "the size goes up", v.size() == 10 );
            THEN_REQUIRE( "the capacity goes up", v.capacity() >= 10 );
            
            AND_WHEN( "it is made smaller again" ) {
                v.resize( 5 );
                
                THEN_REQUIRE( "the size goes down", v.size() == 5 );
                THEN_REQUIRE( "the capacity stays the same", v.capacity() >= 10 );
            }
        }

        WHEN( "we reserve more space" ) {
            v.reserve( 10 );
            
            THEN_REQUIRE ( "the capacity goes up", v.capacity() >= 10 );
            THEN_REQUIRE ( "the size stays the same", v.size() == 0 );
        }
    }
}

SCENARIO("This is a really long scenario name to see how the list command deals with wrapping",
         "[very long tags][lots][long][tags][verbose]"
                 "[one very long tag name that should cause line wrapping writing out using the list command]"
                 "[anotherReallyLongTagNameButThisOneHasNoObviousWrapPointsSoShouldSplitWithinAWordUsingADashCharacter]") {
    GIVEN("A section name that is so long that it cannot fit in a single console width") {
        WHEN("The test headers are printed as part of the normal running of the scenario") {
            THEN("The, deliberately very long and overly verbose (you see what I did there?) section names must wrap, along with an indent") {
                SUCCEED("boo!");
            }
        }
    }
}

SCENARIO_METHOD(Fixture,
                "BDD tests requiring Fixtures to provide commonly-accessed data or methods",
                "[bdd][fixtures]") {
    const int before(counter());
    GIVEN("No operations precede me") {
        REQUIRE(before == 0);
        WHEN("We get the count") {
            const int after(counter());
            THEN("Subsequently values are higher") {
                REQUIRE(after > before);
            }
        }
    }
}

SCENARIO( "Use BDD style require and check macros", "[bdd][rquire][check]" )
{
    GIVEN( "some conditions to check" )
    {
        const auto returnTrue = [](){ return true; };
        const auto returnFalse = [](){ return false; };
        const auto throwRuntimeError = [](){ throw std::runtime_error{""}; };
        const auto doNothing = [](){ };
        
        WHEN( "they need to be checked using a BDD style" )
        {
            THEN_REQUIRE( "you can use THEN_REQUIRE", returnTrue() );
            THEN_REQUIRE_FALSE( "you can use THEN_REQUIRE_FALSE", returnFalse() );
            THEN_REQUIRE_THROWS( "you can use THEN_REQUIRE_THROWS", throwRuntimeError() );
            THEN_REQUIRE_THROWS_AS( "you can use THEN_REQUIRE_THROWS_AS", throwRuntimeError(), std::runtime_error );
            THEN_REQUIRE_NOTHROW( "you can use THEN_REQUIRE_NOTHROW", doNothing() );
            THEN_STATIC_REQUIRE( "you can use THEN_STATIC_REQUIRE", true );
            THEN_STATIC_REQUIRE_FALSE( "you can use THEN_STATIC_REQUIRE_FALSE", false );
            THEN_CHECK( "you can use THEN_CHECK", returnTrue() );
            THEN_CHECK_FALSE( "you can use THEN_CHECK_FALSE", returnFalse() );
            THEN_CHECK_NOFAIL( "you can use THEN_CHECK_NOFAIL", returnTrue() );
            THEN_CHECK_THROWS( "you can use THEN_CHECK_THROWS", throwRuntimeError() );
            THEN_CHECK_THROWS_AS( "you can use THEN_CHECK_THROWS_AS", throwRuntimeError(), std::runtime_error );
            THEN_CHECK_NOTHROW( "you can use THEN_CHECK_NOTHROW", doNothing() );
            
            THEN( "some some condition is checked" )
            {
                AND_REQUIRE( "you can use AND_REQUIRE", returnTrue() );
                AND_REQUIRE_FALSE( "you can use AND_REQUIRE_FALSE", returnFalse() );
                AND_REQUIRE_THROWS( "you can use AND_REQUIRE_THROWS", throwRuntimeError() );
                AND_REQUIRE_THROWS_AS( "you can use AND_REQUIRE_THROWS_AS", throwRuntimeError(), std::runtime_error );
                AND_REQUIRE_NOTHROW( "you can use AND_REQUIRE_NOTHROW", doNothing() );
                AND_STATIC_REQUIRE( "can use AND_STATIC_REQUIRE", true );
                AND_STATIC_REQUIRE_FALSE( "can use AND_STATIC_REQUIRE_FALSE", false );
                AND_CHECK( "you can use AND_CHECK", returnTrue() );
                AND_CHECK_FALSE( "you can use AND_CHECK_FALSE", returnFalse() );
                AND_CHECK_NOFAIL( "you can use AND_CHECK_NOFAIL", returnTrue() );
                AND_CHECK_THROWS( "you can use AND_CHECK_THROWS", throwRuntimeError() );
                AND_CHECK_THROWS_AS( "you can use AND_CHECK_THROWS_AS", throwRuntimeError(), std::runtime_error );
                AND_CHECK_NOTHROW( "you can use AND_CHECK_NOTHROW", doNothing() );
            }
        }
    }
}
