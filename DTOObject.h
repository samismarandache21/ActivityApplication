#pragma once
#include <string>
using std::string;
using std::to_string;
class DTOObject
{
private:
	string tip;
	int numar;
public:
	DTOObject() noexcept : tip{ "" }, numar{ -1 } {}
	DTOObject(const string& str, const int& n) : tip{ str }, numar{ n } {}
	string Tip() const noexcept { return tip; }
	int Numar() const noexcept { return numar; }

	void increment() noexcept {
		numar++;
	}
};

