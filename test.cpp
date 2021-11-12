#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "select.hpp"


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

TEST(Select_Not, FoundTwo) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "fruit", "apple")));
        sheet.print_selection(s);
        EXPECT_EQ("grapes \npeach \n", s.str());

}

TEST(Select_Not, EmptyString) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"peach"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "fruit", "")));
        sheet.print_selection(s);
        EXPECT_EQ("", s.str());

}

TEST(Select_Not, OneLetter) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit"});
        sheet.add_row({"apple"});
        sheet.add_row({"grapes"});
        sheet.add_row({"orange"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "fruit", "g")));
        sheet.print_selection(s);
        EXPECT_EQ("apple \n", s.str());

}

TEST(Select_Not, ReturnTrue) {
        std::stringstream s;

        Spreadsheet sheet;

        sheet.set_column_names({"fruit", "fruit"});
        sheet.add_row({"apple", "dragon fruit"});
        sheet.add_row({"grapes", "orange"});
        sheet.add_row({"peach", "avocado"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "fruit", "apple")));
        sheet.print_selection(s);
        EXPECT_EQ("grapes orange \npeach avocado \n", s.str());

}

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
