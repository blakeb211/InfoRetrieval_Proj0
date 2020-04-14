#include "../MapBuilder.h"
#include "../Utility.h"
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MapBuilder_IsNumber) {
  BOOST_CHECK_EQUAL(Utility::IsNumber("245"), true);
  BOOST_CHECK_EQUAL(Utility::IsNumber("18th"), false);
}

BOOST_AUTO_TEST_CASE(MapBuilder_ToLower) {
  const string stopwords_filename = "../stop_words.txt";
  const vector<string> input_files = {"test_input_file.txt"};
  MapBuilder mb(stopwords_filename, input_files);
  string s = "TesTER!";
  string s2 = "AAAA";
  Utility::ToLower(s);
  BOOST_CHECK_EQUAL(s, "tester!");
  Utility::ToLower(s2);
  BOOST_CHECK_EQUAL(s2, "aaaa");
}

BOOST_AUTO_TEST_CASE(MapBuilder_Term_Frequency) {
  const string stopwords_filename = "../stop_words.txt";
  const vector<string> input_files = {"test_input_file.txt"};
  MapBuilder mb(stopwords_filename, input_files);
  mb.LoadStopwords();
  mb.ProcessInputFiles();
  mb.SortMap();
  mb.PrintMap(std::cout);
  BOOST_CHECK_EQUAL(mb.GetFrequency("Person"), 1);
  BOOST_CHECK_EQUAL(mb.GetFrequency("oliver"), 2);
  BOOST_CHECK_EQUAL(mb.GetFrequency("Sophie"), 3);
}
