#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
//#include "spreadsheet.hpp"

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column{
private:
	std::string substr;
public:
	Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& keyword): Select_Column(sheet, name){
		substr = keyword;
	}
	virtual bool select(const std::string& s) const{
		if(s.find(substr) != std::string::npos){
			return true;
		}
		return false;	
	}
};


class Select_Not: public Select{
private:
	Select* s;
public:
	Select_Not(Select* a){
		s = a;
	}
	~Select_Not(){
		delete s;
	}
	bool select(const Spreadsheet* sheet, int row) const{
		if(s->select(sheet, row)){
			return false;
		}
		return true;
	}
};

class Select_And : public Select 
{
private:
	Select* s1;
	Select* s2;

public:
	Select_And(Select* a, Select* b) {
		s1 = a; s2 = b;
	}
	
	virtual bool select(const Spreadsheet* sheet, int row) const {
		if((s1->select(sheet, row)) && (s2->select(sheet, row))) {
			return true;
		}
		return false;
	}

	 ~Select_And() {
		delete s1;
		delete s2;
	}
};


class Select_Or : public Select {
private:
        Select* s1;
        Select* s2;

public:
	Select_Or(Select* a, Select* b) {
		s1 = a; s2 = b; 
	}
	
	virtual bool select(const Spreadsheet* sheet, int row) const {
		if((s1->select(sheet,row)) || (s2->select(sheet,row))) {
			return true;
		}
		return false;
	}

	~Select_Or() {
		delete s1;
		delete s2;

	}
};

#endif //__SELECT_HPP__
