#include "UI.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;

UI::UI(ActivitateService& given_service) noexcept : service{ given_service } {}

void UI::print_menu()
{
	cout << "0. Afisati lista activitatilor\n";
	cout << "1. Adaugati o activitate la lista de activitatii\n";
	cout << "2. Stergeti o activitate din lista de activitati in functie de titlul acesteia\n";
	cout << "3. Modificati o activitate din lista in functie de titlul acesteia\n";
	cout << "4. Filtrati lista activitatiilor \n";
	cout << "5. Ordonati lista activitatilor\n";
	cout << "6. Cautati o activitate in functie de denumirea acesteia\n";
	cout << "7. Generati un raport\n\n";
	cout << "Itinerar\n";
	cout << "8. Adaugati o activitate itinerarului\n";
	cout << "9. Generarea activitatilor in itinerar\n";
	cout << "10. Export itinerar\n";
	cout << "11. Goliti itinerarul\n";
	cout << "12. Afisati itinerarul\n";
	cout << "13.UNDO\n";
}
void UI::UIadd()
{
	string titlu, descriere, tip;
	int durata;
	cout << "Introduceti titlul activitatii: ";
	cin >> titlu;
	cout << "Introduceti descrierea activitatii: ";
	cin >> descriere;
	cout << "Introduceti tipul activitatii: ";
	cin >> tip;
	cout << "Introduceti durata activitatii: ";
	cin >> durata;
	try {
		service.add(titlu, descriere, tip, durata);
		cout << "Activitatea a fost adaugata cu succes\n";
	}
	catch (const RepoException& e) {
		cout << e.what() << '\n';
	}

}

void UI::UIdelete()
{
	string titlu;
	cout << "Introduceti titlul activitatii pe care doriti sa o stergeti: ";
	cin >> titlu;
	try {
		service.delete_act(titlu);
		cout << "Activitatea a fost stearsa cu succes";
	}
	catch (const RepoException& e) {
		cout << e.what() << '\n';
	}
}

void UI::UImodify() {
	string titlu, new_titlu, new_descriere, new_tip;
	int new_durata;
	cout << "Introduceti titlul activitatii pe care doriti sa o modificati: ";
	cin >> titlu;
	cout << "Introduceti noua descriere a activitatii: ";
	cin >> new_descriere;
	cout << "Introduceti noul tip al activitatii: ";
	cin >> new_tip;
	cout << "Introduceti noua durata a activitatii: ";
	cin >> new_durata;
	try {
		service.modify(titlu,  new_descriere, new_tip, new_durata);
		cout << "Activitatea a fost modificata cu succes\n";
	}
	catch (const RepoException& e) {
		cout << e.what() << '\n';
	}
}
void UI::UIfiltrare() {
	string optiune;
	vector<Activitate> lista;
	cout << "Introduceti optiunea in functie de care se filtreaza(tip/descriere): ";
	cin >> optiune;
	if (optiune == "tip")
	{
		string tip;
		cout << "Introduceti tipul:";
		cin >> tip;
		lista = service.filtrare_tip(tip);
		if (lista.size() == 0) {
			cout << "Nu exista elemente cu acest tip\n";
			return;
		}
		for (const auto& a : lista)
			cout << a.format();
	}
	if (optiune == "descriere")
	{
		string descriere;
		cout << "Introduceti descrierea:";
		cin >> descriere;
		lista = service.filtrare_descriere(descriere);
		if (lista.size() == 0) {
			cout << "Nu exista elemente cu aceasta descriere\n";
			return;
		}
		for (const auto& a : lista)
			cout << a.format();
	}
}
void UI::UIsort() {
	int optiune;
	vector<Activitate> lista;
	cout << "1. Ordonati in functie de titlu\n";
	cout << "2. Ordonati in functie de descriere\n";
	cout << "3. Ordonati in functie de tip si durata\n";
	cin >> optiune;
	if (optiune == 1)
	{
		int ord;
		cout << "In ce ordine sa se ordoneze?(1-crescator, -1-descrescator)";
		cin >> ord;
		if (ord == 1)
		{
			lista = service.ordoneaza_denumire(1);
		}
		else
			lista = service.ordoneaza_denumire(0);

		for (const auto& a : lista)
			cout << a.format();

	}
	if (optiune == 2)
	{
		int ord;
		cout << "In ce ordine sa se ordoneze?(1-crescator, -1-descrescator)";
		cin >> ord;
		if (ord == 1)
		{
			lista = service.ordoneaza_descriere(1);
		}
		else
			lista = service.ordoneaza_descriere(0);

		for (const auto& a : lista)
			cout << a.format();
	}
	if (optiune == 3)
	{
		int ord;
		cout << "In ce ordine sa se ordoneze?(1-crescator, -1-descrescator)";
		cin >> ord;
		if (ord == 1)
		{
			lista = service.ordoneaza_tipuri_si_durata(1);
		}
		else
			lista = service.ordoneaza_tipuri_si_durata(0);

		for (const auto& a : lista)
			cout << a.format();
	}

}
void UI::UIprint()
{
	for (const auto& a : service.get_all())
		cout << a.format();
}
void UI::UIfind()
{
	Activitate activitate;
	string titlu;
	cout << "Introduceti titlul activitatii pe care o cautam: ";
	cin >> titlu;
	activitate = service.cauta_activitate(titlu);
	cout << activitate.format();


}
void UI::itinerar_add() {
	string titlu;
	cout << "Titlul activitatii pe care il adaugati in itinerar: ";
	cin >> titlu;
	service.add_activity(titlu);
	cout << "activitate a fosta adaugata cu succes\n";
}
void UI::generate_itinerar() {
	string numar;
	cout << "Numarul de activitati generate in itinerar: ";
	cin >> numar;
	service.generate_activities(numar);
	cout << "activitatiile au fost adaugate cu succes\n";
}
void UI::export_itinerar() {
	string nume;
	cout << "Numele fisierului: ";
	cin >> nume;
	service.export_activities(nume);
	cout << "exportul s-a realizat cu succes\n";
	
}
void UI::empty_itinerar() {
	service.empty_activities();
	cout << "itinerarul a fost golit";
}
void UI::print_itinerar() {
	for (const auto& act : service.Lista())
		cout << act.format() << endl;
}

void UI::undo() {
	service.undo();
	cout << "Undo successfully completed\n";
}
void UI::run_all() {
	while (true)
	{
		this->print_menu();
		int cmd;
		cout << ">>>";
		cin >> cmd;
		if (cmd == 1)
			this->UIadd();
		else if (cmd == 2)
			this->UIdelete();
		else if (cmd == 3)
			this->UImodify();
		else if (cmd == 4)
			this->UIfiltrare();
		else if (cmd == 5)
			this->UIsort();
		else if (cmd == 6)
			this->UIfind();
		else if (cmd == 0)
			this->UIprint();
		else if (cmd == 7) {
			service.generate_report();
			cout << service.Report().to_str();
		}
		else if (cmd == 8)
			this->itinerar_add();
		else if (cmd == 9)
			this->generate_itinerar();
		else if (cmd == 10)
			this->export_itinerar();
		else if (cmd == 11)
			this->empty_itinerar();
		else if (cmd == 12)
			this->print_itinerar();
		else if (cmd == 13)
			this->undo();
		else {
			cout << "Optiune invalida";
			return;
		}
	}



}
