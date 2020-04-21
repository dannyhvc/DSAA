#pragma once
#include <string>
#include <memory>
#define DEF_POINTER(cls) using pointer = std::shared_ptr<cls>

/**
 * int n = 100;
 * new CIO("/{" + n + " }^^[10%,20%]/");
 */

class container_io {
	
public:
	container_io() = default;
	virtual ~container_io() = default;
};

/*This class*/
class Operator : public container_io {	
public:
	//macro and type def
    DEF_POINTER(Operator);

	//function specifier
	virtual void anon_receiver() = 0;
};

class Split_operator : public Operator {
public:
	//macro and typedef
    DEF_POINTER(Split_operator);
	

};
