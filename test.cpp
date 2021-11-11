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

TEST(Select_And, Contains) {
	std::stringstream s;

	Spreadsheet sheet;

	sheet.set_column_names({"electronics"});
	sheet.add_row({"laptop"});
	sheet.add_row({"desktop"});
	sheet.add_row({"mouse"});

	sheet.set_selection(new Select_And(new Select_Contains(&sheet, "electronics", "mou"), new Select_Contains(&sheet, "electronics", "se")));
 	sheet.print_selection(s);
	
	EXPECT_EQ("mouse \n", s.str());
} 

TEST(Select_Contains, Basic) {
	std::stringstream s;
	std::string test;

	Spreadsheet sheet;

	sheet.set_column_names({"person"});
	sheet.add_row({"Bob"});
	sheet.add_row({"Mike"});

	sheet.set_selection(new Select_Contains(&sheet, "person", "Mike"));
	sheet.print_selection(s);
	EXPECT_EQ("Mike \n", s.str());
}

TEST(ColumnTest, ColumnNotExists) {
	Spreadsheet sheet;
	bool valid = false;

	sheet.set_column_names({"person"});
	sheet.add_row({"Lee"});;
	sheet.add_row({"Rob"});
	sheet.add_row({"Sara"});

	if(sheet.get_column_by_name("people") != -1) {
		valid = true;
	}
	else {
		valid = false;
	}	

	EXPECT_EQ(false, valid);	

}

TEST(ColumnTest, ColumnExists) {

        Spreadsheet sheet;
        bool valid = false;

        sheet.set_column_names({"person"});
        sheet.add_row({"Lee"});;
        sheet.add_row({"Rob"});
        sheet.add_row({"Sara"});

        if(sheet.get_column_by_name("person") != -1) {
                valid = true;
        }
        else {
                valid = false;
        }

        EXPECT_EQ(true, valid);

}

TEST(Select_And, Empty) {
	std::stringstream s;
	
	Spreadsheet sheet;

	sheet.set_column_names({"fruit"});
	sheet.add_row({"kiwi"});
	sheet.add_row({"pear"});
	sheet.add_row({"plum"});

	sheet.set_selection(new Select_And(new Select_Contains(&sheet, "fruit", "pe"), new Select_Contains(&sheet, "fruit", "")));
	sheet.print_selection(s);

	EXPECT_EQ("pear \n", s.str());
}

TEST(Select_And, Case) {
	std::stringstream s;

	Spreadsheet sheet;

	sheet.set_column_names({"fruit"});
	sheet.add_row({"pear"});
	sheet.add_row({"peach"});
	sheet.add_row({"kiwi"});
	sheet.add_row({"plum"});

	sheet.set_selection(new Select_And(new Select_Contains(&sheet, "fruit", "KI"), new Select_Contains(&sheet, "fruit",  "wi")));
	sheet.print_selection(s);

	EXPECT_EQ("", s.str()); //expect an empty string since "KI" doesn't exist
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
