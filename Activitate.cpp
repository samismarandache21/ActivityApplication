#include "Activitate.h"

bool cmp_title_asc(const Activitate& a1, const Activitate& a2) {
	return a1.get_titlu() < a2.get_titlu();
}

bool cmp_title_desc(const Activitate& a1, const Activitate& a2) {
	return a1.get_titlu() > a2.get_titlu();
}

bool cmp_desc_asc(const Activitate& a1, const Activitate& a2) {
	return a1.get_descriere() < a2.get_descriere();
}

bool cmp_desc_desc(const Activitate& a1, const Activitate& a2) {
	return a1.get_descriere() > a2.get_descriere();
}

bool cmp_type_dur_asc(const Activitate& a1, const Activitate& a2) {
	if (a1.get_tip() < a2.get_tip())
		return true;
	if (a1.get_tip() == a2.get_tip())
		if (a1.get_durata() < a2.get_durata())
			return true;
	return false;
}

bool cmp_type_dur_desc(const Activitate& a1, const Activitate& a2) {
	if (a1.get_tip() > a2.get_tip())
		return true;
	if (a1.get_tip() == a2.get_tip())
		if (a1.get_durata() > a2.get_durata())
			return true;
	return false;
}

string Activitate::compressed_str() const {
	string s{ this->titlu +
		"|" + this->descriere +
		"|" + this->tip +
		"|" + to_string(durata) };
	return s;
}