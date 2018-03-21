#include <cassert>
#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t<int> matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix;
    std::istringstream stream{ input };
    
    REQUIRE( matrix.read( stream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream stream1;
    matrix.write( stream1 );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("addings matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1.1 1.1 1.1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1.1 1.1 1.1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<float> first_matrix; 
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<float> second_matrix;
    second_matrix.read( stream );
    
    matrix_t<float> result_matrix = first_matrix + second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "2.2 2.2 2.2\n"
    };
    
    std::ostringstream stream1;
    result_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("subtracting matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1.5 1.5 1.5\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<float> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<float> second_matrix;
    second_matrix.read( stream );
    
    matrix_t<float> result_matrix = first_matrix - second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "0.5 0.5 0.5\n"
    };
    
    std::ostringstream stream;
    result_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("multiplying matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    matrix_t<int> result_matrix = first_matrix * second_matrix;

    std::string expected_result_matrix_representation{
        "1, 1\n"
        "3"
    };
    
    std::ostringstream stream1;
    result_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("addings_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    first_matrix += second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "2 2 2\n"
    };
    
    std::ostringstream stream1;
    first_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("subtracting_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    first_matrix -= second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "0 0 0\n"
    };
    
    std::ostringstream stream1;
    first_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("multiplying_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    first_matrix *= second_matrix;

    std::string expected_result_matrix_representation{
        "1, 1\n"
        "3"
    };
    
    std::ostringstream stream1;
    first_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("addings matrixs 3x1")
{
    std::string first_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    matrix_t<int> result_matrix = first_matrix + second_matrix;

    std::string expected_result_matrix_representation{
        "3, 1\n"
        "2\n"
        "2\n"
        "2\n"
    };
    
    std::ostringstream stream1;
    result_matrix.write (stream1);
    
    REQUIRE( ostream.str() == expected_result_matrix_representation );
}

TEST_CASE("Good")
{
    std::string first_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    char op = '+';
    bool str_ = first_matrix.success (second_matrix, op);
    bool expect = true;
    
    REQUIRE( str_ == expect );
}

TEST_CASE("You can`t make this action")
{
    std::string first_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    std::string second_matrix_representation{
        "2, 1\n"
        "1\n"
        "1\n"
    };
    
    std::istringstream stream{ first_matrix_representation };
    matrix_t<int> first_matrix;
    first_matrix.read( stream );
    
    std::istringstream stream{ second_matrix_representation };
    matrix_t<int> second_matrix;
    second_matrix.read( stream );
    
    char op = '-';
    bool str_ = first_matrix.success (second_matrix, op);
    bool expect = false;
    
    REQUIRE( str_ == expect );
}
