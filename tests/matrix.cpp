#include <catch.hpp>
#include <sstream>
#include "matrix.hpp"

TEST_CASE("creating matrix")
{
	matrix_t<float> matrix;
	REQUIRE(matrix.rows() == 0);
	REQUIRE(matrix.collumns() == 0);
}

TEST_CASE("reading matrix")
{
	std::string input{
		"3, 3\n"
		"1 1 1\n"
		"2 2 2\n"
		"3 3 3" };
	matrix_t<float> matrix;
	std::istringstream istream{ input };

	REQUIRE(matrix.read(istream));
	REQUIRE(matrix.rows() == 3);
	REQUIRE(matrix.collumns() == 3);

	std::ostringstream ostream;
	matrix.write(ostream);

	REQUIRE(input == ostream.str());
}


TEST_CASE("add matrix")
{
	std::string stroka1{
		"2, 3\n"
		"1 1 1\n"
		"1 1 1" };
	std::string stroka2{
		"2, 3\n"
		"2 2 2\n"
		"2 2 2" };
	std::string res_stroka{
		"2, 3\n"
		"3 3 3\n"
		"3 3 3" };

	matrix_t<float> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	result_matrix = matrix1 + matrix2;

	std::ostringstream ostream;
	result_matrix.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error add matrix")
{
	std::string stroka1{
		"2, 2\n"
		"1 1 \n"
		"1 1 " };
	std::string stroka2{
		"2, 3\n"
		"2 2 2\n"
		"2 2 2" };
	matrix_t<float> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	REQUIRE_THROWS_AS((matrix1 + matrix2), std::invalid_argument);
}


TEST_CASE("sub matrix")
{
	std::string stroka1{
		"2, 3\n"
		"1 2 3\n"
		"4 5 6" };
	std::string stroka2{
		"2, 3\n"
		"1 1 1\n"
		"1 1 1" };
	std::string res_stroka{
		"2, 3\n"
		"0 1 2\n"
		"3 4 5" };

	matrix_t<int> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	result_matrix = matrix1 - matrix2;

	std::ostringstream ostream;
	result_matrix.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error sub matrix")
{
	std::string stroka1{
		"2, 2\n"
		"1 2 \n"
		"4 5" };
	std::string stroka2{
		"2, 3\n"
		"1 1 1\n"
		"1 1 1" };
	matrix_t<int> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	REQUIRE_THROWS_AS((matrix1 - matrix2), std::invalid_argument);
}

TEST_CASE("mul matrix")
{
	std::string stroka1{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string stroka2{
		"3, 3\n"
		"1 1 1 \n"
		"1 1 1 \n"
		"1 1 1" };
	std::string res_stroka{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };

	matrix_t<float> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	result_matrix = matrix1 * matrix2;

	std::ostringstream ostream;
	result_matrix.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error mul matrix")
{
	std::string stroka1{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string stroka2{
		"2, 2\n"
		"1 1 \n"
		"1 1" };

	matrix_t<float> matrix1, matrix2, result_matrix;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);


	REQUIRE_THROWS_AS((matrix1 * matrix2), std::invalid_argument);
}

TEST_CASE("sub= matrix")
{
	std::string stroka1{
		"3, 4\n"
		"6 6 6 6\n"
		"6 6 6 6\n"
		"6 6 6 6" };
	std::string stroka2{
		"3, 4\n"
		"4 4 4 4\n"
		"4 4 4 4\n"
		"4 4 4 4" };
	std::string res_stroka{
		"3, 4\n"
		"2 2 2 2\n"
		"2 2 2 2\n"
		"2 2 2 2" };

	matrix_t<float> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	matrix1 -= matrix2;

	std::ostringstream ostream;
	matrix1.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error sub= matrix")
{
	std::string stroka1{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };
	std::string stroka2{
		"3, 4\n"
		"4 4 4 4\n"
		"4 4 4 4\n"
		"4 4 4 4" };

	matrix_t<float> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);


	REQUIRE_THROWS_AS((matrix1 -= matrix2), std::invalid_argument);
}

TEST_CASE("add= matrix")
{
	std::string stroka1{
		"2, 3\n"
		"3 3 3\n"
		"3 3 3" };

	std::string stroka2{
		"2, 3\n"
		"1 1 1\n"
		"1 1 1" };
	std::string res_stroka{
		"2, 3\n"
		"4 4 4\n"
		"4 4 4" };

	matrix_t<float> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	matrix1 += matrix2;

	std::ostringstream ostream;
	matrix1.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error add= matrix")
{
	std::string stroka1{
		"2, 2\n"
		"3 3\n"
		"3 3 " };

	std::string stroka2{
		"2, 3\n"
		"1 1 1\n"
		"1 1 1" };
	matrix_t<float> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	REQUIRE_THROWS_AS((matrix1 += matrix2), std::invalid_argument);
}

TEST_CASE("mul= matrix")
{
	std::string stroka1{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string stroka2{
		"3, 3\n"
		"1 1 1\n"
		"1 1 1\n"
		"1 1 1" };
	std::string res_stroka{
		"3, 3\n"
		"6 6 6\n"
		"6 6 6\n"
		"6 6 6" };

	matrix_t<double> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	matrix1 *= matrix2;

	std::ostringstream ostream;
	matrix1.write(ostream);

	REQUIRE(res_stroka == ostream.str());
}

TEST_CASE("error mul= matrix")
{
	std::string stroka1{
		"3, 3\n"
		"2 2 2\n"
		"2 2 2\n"
		"2 2 2" };
	std::string stroka2{
		"2, 2\n"
		"1 1\n"
		"1 1" };
	
	matrix_t<float> matrix1, matrix2;
	std::istringstream istream1{ stroka1 };
	std::istringstream istream2{ stroka2 };

	matrix1.read(istream1);
	matrix2.read(istream2);

	REQUIRE_THROWS_AS((matrix1 *= matrix2), std::invalid_argument);
}
