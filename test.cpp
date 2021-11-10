#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "select.hpp"

TEST(Select_Contains, ReturnTrue) {
	Spreadsheet sheet;

  	sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});
        sheet.add_row({"orange"});

        Select* test = new Select_Contains(&sheet , "fruit", "apple");

        EXPECT_EQ(true, test->select(&sheet, 0));

}

TEST(Select_Contains, EmptyString) {
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});
        sheet.add_row({"orange"});

        Select* test = new Select_Contains(&sheet , "fruit", "");

        EXPECT_EQ(true, test->select(&sheet, 0));

}

TEST(Select_Contains, DifferentCase) {
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});
        sheet.add_row({"orange"});

        Select* test = new Select_Contains(&sheet , "fruit", "Apple");

        EXPECT_EQ(false, test->select(&sheet, 0));

}

TEST(Select_Contains, TwoLetters) {
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});
        sheet.add_row({"orange"});

        Select* test = new Select_Contains(&sheet , "fruit", "pp");

        EXPECT_EQ(true, test->select(&sheet, 0));

}







int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
