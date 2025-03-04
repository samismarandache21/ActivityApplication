#include "ActivitateRepo.h"


ActivitateRepo::ActivitateRepo() noexcept: Lista_activitati{ vector<Activitate>() } {}

MemoryRepo::MemoryRepo() noexcept : ActivitateRepo() {}


int ActivitateRepo::index_of(const string& title) {
    auto found_at = find_if(Lista_activitati.begin(), Lista_activitati.end(), [&title](const Activitate& a) { return a.get_titlu() == title; });
    if (found_at == Lista_activitati.end())
        throw RepoException("Activitatea nu exista");
    return distance(Lista_activitati.begin(), found_at);
}

void MemoryRepo::adauga(const Activitate& activitate) {
    try {
        int found_at = index_of(activitate.get_titlu());
    }
    catch (const RepoException& e) {
        Lista_activitati.push_back(activitate);
        return;
    }
    throw RepoException("Activitatea exista deja");
}

void MemoryRepo::sterge(const string& titlu) {
    int found_at = index_of(titlu);
    Lista_activitati.erase(Lista_activitati.begin() + found_at);
}

void MemoryRepo::modifica(const string& titlu, const Activitate& activitate) {
    int found_at = index_of(titlu);
    Lista_activitati.at(found_at) = activitate;
}
size_t MemoryRepo::get_size() noexcept {
    return Lista_activitati.size();
}
int MemoryRepo::index_of(const string& title) {
	return ActivitateRepo::index_of(title);
}

FileRepo::FileRepo(const string& file_path) : MemoryRepo(), path{ file_path } {
	read();
}
void FileRepo::read() {
	ifstream fin(path);
	string line{ "" };
	while (getline(fin, line)) {
		if (line != "") {
			const int d{ int(line.length()) };
			int field{ 0 };
			string current{ "" };

			string titlu ="";
			string descriere = "";
			string tip = "";
			int durata = 0;

			for (int i = 0 ; i < d; i++) {
				if (line.at(i) == '|' || i == d - 1) {
					if (i == d - 1)
						current += line.at(i);

					if (field == 0)
						titlu = current;
					else if (field == 1)
						descriere = current;
					else if (field == 2)
						tip = current;
					else
						durata = stoi(current);
					current = "";
					field++;
				}
				else
					current += line.at(i);
			}
			Lista_activitati.push_back(Activitate{ titlu,descriere,tip,durata });
		}
	}
}

void FileRepo::write() const {
	string res{ "" };
	for (const auto& act : Lista_activitati)
		res += act.compressed_str() + "\n";
	ofstream fout(path);
	fout << res;
}

int FileRepo::index_of(const string& titlu) {
	return MemoryRepo::index_of(titlu);
}

void FileRepo::adauga(const Activitate& activitate) {
	MemoryRepo::adauga(activitate);
	write();
}

void FileRepo::sterge(const string& titlu){
	MemoryRepo::sterge(titlu);
	write();
}

void FileRepo::modifica(const string& titlu, const Activitate& activitate) {
	MemoryRepo::modifica(titlu, activitate);
	write();
}
