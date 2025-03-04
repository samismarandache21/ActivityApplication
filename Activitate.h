#pragma once
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::to_string;
using std::cout;
class Activitate
{
	string titlu;
	string descriere;
	string tip;
	int durata;

public:
	Activitate() = default;

	Activitate(string titlu, string descriere, string  tip, int durata) :titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}
	// constructor de copiere
	Activitate(const Activitate& new_act) : titlu{ new_act.titlu }, descriere{ new_act.descriere }, tip{ new_act.tip }, durata{ new_act.durata } {}

	//getter pt titlu, reutrneaza titlul
	string get_titlu() const noexcept
	{
		return this->titlu;
	}
	//getter pt descriere, returneaza descrierea
	string get_descriere() const noexcept
	{
		return this->descriere;
	}
	// getter pt tip, returneaza tipul
	string get_tip() const noexcept
	{
		return this->tip;
	}
	//getter pt durata, returneaza un intreg valoarea duratei
	int get_durata() const noexcept
	{
		return this->durata;
	}
	//setter pt titlu
	void set_titlu(string new_titlu)
	{
		this->titlu = new_titlu;
	}
	//setter pt descriere
	void set_descriere(string new_descriere)
	{
		this->descriere = new_descriere;
	}
	//setter pt tip
	void set_tip(string new_tip)
	{
		this->tip = new_tip;
	}
	//setter pentru durata
	void set_durata(int new_durata) noexcept
	{
		this->durata = new_durata;
	}
	//formatul de afisare
	string format() const
	{
		string to_print = "Titlu: " + this->titlu + " Descriere: " + this->descriere + " Tip: " + this->tip + " Durata: " + to_string(this->durata) + "\n";
		return to_print;
	}


	bool operator!=(Activitate act)
	{
		return this->titlu != act.titlu;
	}

	string to_html() const {
		return "Nume Activitate: " + titlu + "<br>Descriere: " + descriere;
	}

	string compressed_str() const;

};

bool cmp_title_asc(const Activitate& a1, const Activitate& a2);
bool cmp_title_desc(const Activitate& a1, const Activitate& a2);
bool cmp_desc_asc(const Activitate& a1, const Activitate& a2);
bool cmp_desc_desc(const Activitate& a1, const Activitate& a2);
bool cmp_type_dur_asc(const Activitate& a1, const Activitate& a2);
bool cmp_type_dur_desc(const Activitate& a1, const Activitate& a2);


