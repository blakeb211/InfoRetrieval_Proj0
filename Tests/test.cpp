#include "../MapBuilder.h"
#include "pch.h"

TEST(MapBuilder_tests, load_files) {
  MapBuilder mb{"../stop_words.txt", vector<string>{"Test_Input_file.txt"}};

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
