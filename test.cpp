#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "select.hpp"


TEST(Select_Or, Basic) {
	std::stringstream s;
	Spreadsheet sheet; 

	sheet.set_column_names({"fruit"});
	sheet.add_row({"apple"});
	sheet.add_row({"pear"});
	sheet.add_row({"grapes"});
	
	sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "fruit", "apple"), new Select_Contains(&sheet, "fruit", "pea")));
	sheet.print_selection(s);

	EXPECT_EQ("apple \npear \n", s.str());
}

TEST(Select_Or, BasicOne) {
        std::stringstream s;
        Spreadsheet sheet;

        sheet.set_column_names({"fruit", "size"});
        sheet.add_row({"apple", "small"});
        sheet.add_row({"pear"});
        sheet.add_row({"grapes"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "fruit", "app"), new Select_Contains(&sheet, "fruit", "op")));
        sheet.print_selection(s);

        EXPECT_EQ("apple small \n", s.str());
}

TEST(Select_Or, Case) {
        std::stringstream s;
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"pear"});
        sheet.add_row({"grapes"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "fruit", "aPPle"), new Select_Contains(&sheet, "fruit", "gra")));
        sheet.print_selection(s);

        EXPECT_EQ("grapes \n", s.str());
}

TEST(Select_Or, Empty) {
        std::stringstream s;
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"pear"});
        sheet.add_row({"grapes"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "fruit", "pear"), new Select_Contains(&sheet, "fruit", "")));
        sheet.print_selection(s);

        EXPECT_EQ("apple \npear \ngrapes \n", s.str()); //since all of them have empty strings
}

TEST(Select_Or, None) {
        std::stringstream s;
        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"pear"});
        sheet.add_row({"grapes"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "fruit", "orange"), new Select_Contains(&sheet, "fruit", "do")));
        sheet.print_selection(s);

        EXPECT_EQ("", s.str()); //empty string b/c "orange" and "do" do not exist in our sheet
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
