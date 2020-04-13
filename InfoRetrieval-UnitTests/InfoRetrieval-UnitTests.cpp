#include "../MapBuilder.h"
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MapBuilder_IsNumber) {
  const string stopwords_filename = "../stop_words.txt";
  const vector<string> input_files = {"test_input_file.txt"};
  MapBuilder mb(stopwords_filename, input_files);
  BOOST_CHECK_EQUAL(mb.IsNumber("245"), true);
  BOOST_CHECK_EQUAL(mb.IsNumber("18th"), false);
}

BOOST_AUTO_TEST_CASE(MapBuilder_ToLower) {
  const string stopwords_filename = "../stop_words.txt";
  const vector<string> input_files = {"test_input_file.txt"};
  MapBuilder mb(stopwords_filename, input_files);
  string s = "TesTER!";
  mb.ToLower(s);
  BOOST_CHECK_EQUAL(s, "tester!");
}

BOOST_AUTO_TEST_CASE(MapBuilder_BuildMap) {
  const string stopwords_filename = "../stop_words.txt";
  const vector<string> input_files = {"test_input_file.txt"};
  MapBuilder mb(stopwords_filename, input_files);
  mb.LoadStopwords();
  mb.ProcessInputFiles();
  mb.SortMap();
  mb.PrintMap(std::cout);
}
