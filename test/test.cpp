#include "CppUnitTest.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace all_tests
{
	TEST_CLASS(test_v10)
	{
	public:
		TEST_METHOD(test_01)
		{
			std::stringstream ss("14 -78 22");
			std::vector<int> v;
			
			std::istream_iterator<int> in(ss), ends;
			copy(in, ends, back_inserter(v));

			Assert::AreEqual(3ull, v.size());
			Assert::AreEqual(14, v[0]);
			Assert::AreEqual(-78, v[1]);
			Assert::AreEqual(22, v[2]);

		}
		TEST_METHOD(test_02a)
		{
			std::vector<int> v(10);
			// TODO: fill vector with incremental values
			std::iota(std::begin(v), std::end(v), 1);
			Assert::AreEqual(10ull, v.size());
			Assert::IsTrue(std::is_sorted(v.cbegin(), v.cend()));
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(10, v[9]);
		}
		TEST_METHOD(test_02b)
		{
			// generate
			std::vector<int> v(10);
			// TODO: fill vector with incremental values (by 2)
			std::generate(std::begin(v), std::end(v), [n = -1]() mutable { return n+=2; });
			Assert::IsTrue(std::is_sorted(v.cbegin(), v.cend()));
			Assert::IsTrue(v.cend() == std::adjacent_find(v.cbegin(), v.cend(), [](int a, int b) { return b - a != 2;  }));
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(19, v[9]);
		}

		TEST_METHOD(test_03a)
		{
			std::vector<int> v = { 1, 5, 10 };
			// TODO: change all values in a vector
			std::transform(std::begin(v), std::end(v), std::begin(v), [](int n) { return n * n * n; });
			Assert::AreEqual(3ull, v.size());
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(125, v[1]);
			Assert::AreEqual(1000, v[2]);
		}
		TEST_METHOD(test_03b)
		{
			int x[] = { 3, 5, 10 };
			std::vector<int> y = { 4, 12, 10 };
			std::vector<double> d;

			// TODO: calculate distances from origin (from x and y collections) to new vector
			std::transform(y.begin(), y.end(), x, std::back_inserter(d), [](int x, int y) {return std::hypot(x, y); });
			Assert::AreEqual(3ull, d.size());
			Assert::AreEqual(5., d[0]);
			Assert::AreEqual(13., d[1]);
			Assert::AreEqual(sqrt(200), d[2]);
		}
		TEST_METHOD(test_04a)
		{
			std::stringstream ss("1.5 2.5 3.5");
			std::istream_iterator<double> in(ss), ends;
			auto res = std::accumulate(in, ends, 0.); // TODO: sum of all values in input stream
			Assert::AreEqual(7.5, res);
		}
		TEST_METHOD(test_04b)
		{
			std::vector<std::string> v{ "V", "S", "I", "T", "E", "!" };
			auto res = std::accumulate(v.begin(), v.end(), std::string("GO "));
			Assert::AreEqual("GO VSITE!", res.c_str());
		}
		TEST_METHOD(test_04c)
		{
			struct person { std::string name; int age; };
			std::vector<person> v{ {"Pero", 33}, {"Iva", 25} };
			auto total_age = std::accumulate(v.begin(), v.end(), 0, [](int age_sum,  const person& p) {return age_sum += p.age; });
			Assert::AreEqual(58, total_age);
		}

		TEST_METHOD(test_05a)
		{
			std::vector<int> v{ -5, 8, 11, 0, -9, 77, -4 };
			auto number_of_negative = std::count_if(v.begin(), v.end(), [](int n) {return n < 0; }); // TODO: 
			Assert::AreEqual(3ll, number_of_negative);
		}
		TEST_METHOD(test_05b)
		{
			std::vector<double> v{ 1.5, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			auto number_of_invalid = std::count(v.begin(), v.end(), 1e10); // TODO: 
			Assert::AreEqual(3ll, number_of_invalid);
		}
		TEST_METHOD(test_05c)
		{
			struct point { int x, y; };
			std::vector<point> v{ {1,1}, {-5,3}, {2,2}, {-7,-6}, {9,-4} };
			auto number_in_first_quadrant = std::count_if(v.begin(), v.end(), [](const point& p) {return p.x >= 0 && p.y >= 0; }); // TODO: 
			Assert::AreEqual(2ll, number_in_first_quadrant);
		}

		TEST_METHOD(test_06)
		{
			std::vector<int> v{ 33, 16, 24, 41, 25, 19, 9 };
			auto first_prime = std::find_if(v.begin(), v.end(), [](int n) 
				{
					bool flag = true;
					for (int i = 2; i <= n / 2; i++) {
						if (n % i == 0) {
							flag = false;
							break;
						}
					}
					return flag;
				}
			); // TODO: 
			Assert::AreEqual(41, *first_prime);
		}
		TEST_METHOD(test_07a)
		{
			std::vector<double> v{ 1e10, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			// TODO: change every invalid value (1e10) with -1 
			std::replace(v.begin(), v.end(), 1e10, -1.);
			Assert::AreEqual(-1., v[0]);
			Assert::AreEqual(-1., v[4]);
			Assert::AreEqual(-1., v[6]);
		}
		TEST_METHOD(test_07b)
		{
			std::string s("neisporuka");
			// TODO: change every vowel with x 
			std::replace_if(s.begin(), s.end(), [](char& s){return (s == 'a') || (s == 'e') || (s == 'i') || (s == 'o') || (s == 'u');}, 'x');
			Assert::AreEqual("nxxspxrxkx", s.c_str());
		}
		TEST_METHOD(test_08a)
		{
			std::vector<double> v{ 1e10, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			// TODO: delete all invalid values (1e10)
			auto it = std::remove(v.begin(), v.end(), 1e10);
			v.erase(it, v.end());
			Assert::AreEqual(5ull, v.size());
			Assert::AreEqual(8., v[0]);
			Assert::AreEqual(99., v[4]);
		}

		TEST_METHOD(test_08b)
		{
			std::string s("poliuretan");
			// TODO: delete all vowels 
			auto it = std::remove_if(s.begin(), s.end(), [](char c) {
				return (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');
				}
			);
			s.erase(it, s.end());
			Assert::AreEqual("plrtn", s.c_str());
		}

		TEST_METHOD(test_09)
		{
			struct exam { std::string name; int points, grade; };
			std::vector<exam> v{ {"Pero", 55, 2}, {"Iva", 93, 5}, {"Marko", 89, 5} };
			// TODO: sort vector by grade, then by points
			std::sort(v.begin(), v.end(), [](const exam& a, const exam& b) {
				if (a.grade == b.grade)
					return a.points > b.points;
				return a.grade > b.grade;
				}
			);
			Assert::AreEqual("Iva", v[0].name.c_str());
			Assert::AreEqual("Marko", v[1].name.c_str());
			Assert::AreEqual("Pero", v[2].name.c_str());

		}
		TEST_METHOD(test_10)
		{
			std::vector<double> v(2e7);
			// half of the values less than 1000
			std::generate(v.begin(), v.begin() + v.size() / 2, []() { return rand() % 1000; });
			// other half of the values greater than 1000
			std::generate(v.begin() + v.size() / 2, v.end(), []() { return 1001 + rand() % 1000; });
			v.push_back(1000); // to be median

			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(v.begin(), v.end(), g);

			// TODO: put median value in the middle of vector. fast.
			std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
			Assert::AreEqual(1000., v[v.size() / 2]); // median value
		}
		TEST_METHOD(test_11)
		{
			std::vector<double> v{ 11, 0.5, -97.23, -23.11, 48.78, 22.96, -77 };
			auto smallest_value = *std::min_element(v.begin(), v.end());// TODO: 
			Assert::AreEqual(-97.23, smallest_value);
			auto largest_value = *std::max_element(v.begin(), v.end());// TODO: 
			Assert::AreEqual(48.78, largest_value);
		}
		TEST_METHOD(test_12)
		{
			std::vector<int> atp_points{ 8445, 7480, 6220, 6219, 5300, 5290, 5285 };
			// the most interesting match is the one with the smallest difference
			auto smallest_difference = abs(* std::max_element(atp_points.begin() + 1, (std::adjacent_difference(atp_points.begin(), atp_points.end(), atp_points.begin()))));// TODO: 

			Assert::AreEqual(1, smallest_difference);
		}
	};
}
