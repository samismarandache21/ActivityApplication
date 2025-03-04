#pragma once
#include <map>
#include "DTOObject.h"
using std::map;
class Report
{
private:
	map<string, DTOObject> tipuri;

public:
	Report() noexcept;
	int size() const noexcept;
	void add(const string& elem);

	string to_str() const;

	~Report();
};

