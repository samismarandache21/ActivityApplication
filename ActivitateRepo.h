#pragma once
#include "Activitate.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using std::vector;
using std::find_if;
using std::copy_if;
using std::distance;
using std::sort;

using std::ifstream;
using std::ofstream;
using std::getline;
using std::map;

using std::ostream;
using std::endl;
using std::unique_ptr;
using std::make_unique;

class RepoException : public std::exception {
public:
	explicit RepoException(const char* message) : std::exception(message) {}
};
class ActivitateRepo
{
protected:
	vector<Activitate> Lista_activitati;

public:
	virtual const vector<Activitate>& get_all() noexcept { return Lista_activitati; }
	ActivitateRepo() noexcept;
	ActivitateRepo(const ActivitateRepo& other) = delete;


	virtual int index_of(const string& title) = 0;
	virtual void adauga(const Activitate& activitate) = 0;
	virtual void sterge(const string& titlu) = 0;
	virtual void modifica(const string& titlu, const Activitate& activitate) = 0;

	virtual ~ActivitateRepo() = default;

};

class MemoryRepo : public ActivitateRepo {
public:
	MemoryRepo() noexcept;
	~MemoryRepo() override = default;

	int index_of(const string& title) override;
	void operator=(const MemoryRepo& other)noexcept = delete;
	void adauga(const Activitate& activitate) override;
	void sterge(const string& titlu) override;
	void modifica(const string& titlu, const Activitate& activitate) override;
	size_t get_size() noexcept;

};

class FileRepo : public MemoryRepo {
protected:
	string path;

	void read();
	void write() const;
public:
	FileRepo(const string& file_path);
	~FileRepo() override = default;

	int index_of(const string& title);
	void operator=(const FileRepo& other) noexcept = delete;
	inline string Path() const noexcept { return path; }
	void adauga(const Activitate& activitate) override;
	void sterge(const string& titlu) override;
	void modifica(const string& titlu, const Activitate& activitate) override;


};

class LabRepo : public MemoryRepo {
protected:
    map<string, Activitate> act_map;
    double prob;

public:
    LabRepo(const double& probability) noexcept : prob{ probability } {}
    ~LabRepo() override = default;

    void adauga(const Activitate& activitate) override {
        int val = rand() % 2;
        double p = (double)val / 10.0;
        if (p <= prob)
            throw RepoException("Probability");
        if (act_map.find(activitate.get_titlu()) != act_map.end()) {
            throw RepoException("Activitatea există deja");
        }
        act_map[activitate.get_titlu()] = activitate;
    }

    void sterge(const string& titlu) override {
        int val = rand() % 2;
        double p = (double)val / 10.0;
        if (p <= prob)
            throw RepoException("Probability");
        if (act_map.find(titlu) == act_map.end()) {
            throw RepoException("Activitatea nu există");
        }
        act_map.erase(titlu);
    }

    void modifica(const string& titlu, const Activitate& activitate) override {
        int val = rand() % 2;
        double p = (double)val / 10.0;
        if (p <= prob)
            throw RepoException("Probability");
        if (act_map.find(titlu) == act_map.end()) {
            throw RepoException("Activitatea nu există");
        }
        act_map[titlu] = activitate;
    }

    const vector<Activitate>& get_all() noexcept override {
        Lista_activitati.clear();
        for (const auto& pair : act_map) {
            Lista_activitati.push_back(pair.second);
        }
        return Lista_activitati;
    }

    inline double Probability() const noexcept { return prob; }
};
