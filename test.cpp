#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "select.hpp"

TEST(Select_Contains, ReturnTrue) {
	std::stringstream s;
	
	Spreadsheet sheet;

  	sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});
	
	sheet.set_selection(new Select_Contains(&sheet, "fruit", "apple"));
	sheet.print_selection(s);
        EXPECT_EQ("apple \n", s.str());

}

TEST(Select_Contains, EmptyString) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});

        sheet.set_selection(new Select_Contains(&sheet, "fruit", ""));
        sheet.print_selection(s);
        EXPECT_EQ("apple \ngrapes \npeach \n", s.str());

}

TEST(Select_Contains, OneLetter) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"Name"});
        sheet.add_row({"mike"});
        sheet.add_row({"tony"});
        sheet.add_row({"tom"});

        sheet.set_selection(new Select_Contains(&sheet, "Name", "t"));
        sheet.print_selection(s);
        EXPECT_EQ("tony \ntom \n", s.str());

}

TEST(Select_Contains, NonExistingColumn) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});

        sheet.set_selection(new Select_Contains(&sheet, "food", "apple"));
        sheet.print_selection(s);
        EXPECT_EQ("\n", s.str());

}

TEST(Select_Contains, TwoColumnWithSameName) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit", "fruit"});
        sheet.add_row({"apple", "dragon fruit"});
        sheet.add_row({"grapes", "orange"});
        sheet.add_row({"peach", "avocado"});

        sheet.set_selection(new Select_Contains(&sheet, "fruit", "s"));
        sheet.print_selection(s);
        EXPECT_EQ("grapes orange \n", s.str());

}








int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
