#include "Report.h"

Report::Report() noexcept : tipuri{ map<string, DTOObject>() } {

}

int Report::size() const noexcept {
	return int(tipuri.size());
}

void Report::add(const string& tip) {
	if (tipuri.find(tip) == tipuri.end())
		tipuri[tip] = DTOObject(tip, 1);
	else
		tipuri[tip].increment();
}

string Report::to_str() const {
	string res = "";
	for (const auto& p : tipuri) {
		res += p.second.Tip() + " - " + to_string(p.second.Numar()) + "\n";
	}
	return res;
}

Report::~Report() {

}