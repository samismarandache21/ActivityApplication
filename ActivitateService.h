#pragma once
#include "ActivitateRepo.h"
#include "UndoAction.h"
#include "Report.h"
#include <random>
#include <chrono>
#include <memory>

class ActivitateService
{
private:
	ActivitateRepo& repo;
	vector<Activitate> activities;
	Report tipuri_raportate;
	vector<unique_ptr<UndoAction>> undo_list;
	
public:
	ActivitateService() = default;
	ActivitateService(ActivitateRepo& given_repo) noexcept;
	const vector<Activitate>& Lista() const noexcept;
	void add_activity(const string& titlu);
	void generate_activities(const string& numar);
	void export_activities(const string& where) const;
	void empty_activities() noexcept;
	/*
	* functia de adaugare din serive
	* primeste ca parametrii titlul, descriere, tipul si durata
	*/
	void add(string titlu, string descriere, string tip, int durata);
	/*
	* functia de stergere din service si sterge activitatea care contine titlul dat
	*/
	void delete_act(string titlu);
	//functia care modifica activitatea care contine titlul dat din lista si primeste ca parametrii noi campuri pentru obiectul activitate
	void modify(string titlu,  string descriere_noua, string tip_nou, int durata_noua);
	// functia returneaza activitatea care contine titlul dat
	Activitate cauta_activitate(string denumire);
	// functia afiseaza obiectele au ca descriere un string dat
	vector<Activitate> filtrare_descriere(const string& descriere);
	// functia afiseaza obiectele au ca tip un string dat
	vector<Activitate> filtrare_tip(const string& tip);
	// se creaza  o copie a listei ordonate in functie de denumire si se afiseaza obiectele din aceasta
	vector<Activitate> ordoneaza_denumire(int ordine);
	// se creaza  o copie a listei ordonate in functie de descriere si se afiseaza obiectele din aceasta
	vector<Activitate> ordoneaza_descriere(int ordine);
	// se creaza  o copie a listei ordonate in functie de tip si durata si se afiseaza obiectele din aceasta
	vector<Activitate> ordoneaza_tipuri_si_durata(int ordine);
	// se returneaza lista de activitati
	const vector<Activitate>& get_all();
	// lungimea listei
	size_t get_size();

	const Report& Report() const noexcept;
	void generate_report();

	void undo();
	
};

