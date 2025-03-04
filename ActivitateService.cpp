#include "ActivitateService.h"
#include <iostream>
#include <fstream>
#include<string>

using std::ifstream;
using std::ofstream;


ActivitateService::ActivitateService(ActivitateRepo& given_repo) noexcept : repo{ given_repo } {}

const vector<Activitate>& ActivitateService::Lista() const noexcept {
    return activities;
}
void ActivitateService::add_activity(const string& titlu) {
    auto it = find_if(repo.get_all().begin(), repo.get_all().end(), [&](const Activitate& activity) {
        return activity.get_titlu() == titlu;
        });

    if (it != repo.get_all().end()) {
        
        activities.push_back(*it);
    }
    
}

void ActivitateService::generate_activities(const string& numar) {

    if (activities.empty() != 0) {
    }
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<Activitate> copy = repo.get_all();
    std::shuffle(copy.begin(), copy.end(), std::default_random_engine(unsigned int(seed)));
    int diff{ int(copy.size()) - stoi(numar) };
    while (diff--) { copy.pop_back(); }
    activities = static_cast<vector<Activitate>&&>(copy);
       
}
void ActivitateService::export_activities(const string& where) const {

    ofstream output;
    const string file_name{ where + ".html" };
    output.open(file_name);

    output << "<!DOCTYPE html><html><head><title>Coșul de activități</title></head><body>";
    output << "<h1>Coșul de activități</h1>";
    for (const auto& act : activities) {
        output << "<p>" << act.format() << "</p>";
    }
    output << "</body></html>";

    output.close();
}


void ActivitateService::empty_activities() noexcept {
    activities.clear();
}

void ActivitateService::add(string titlu, string descriere, string tip, int durata) {
    Activitate act{ titlu, descriere, tip, durata };
    repo.adauga(act);
    undo_list.push_back(make_unique<AddUndo>(repo, act));
}

void ActivitateService::delete_act(string titlu) {

    repo.sterge(titlu);
    Activitate aux;
    for (auto const act : repo.get_all())
        if (act.get_titlu() == titlu)
            aux = act;
    undo_list.push_back(make_unique<RemoveUndo>(repo, aux));
}

void ActivitateService::modify(string titlu, string descriere_noua, string tip_nou, int durata_noua) {

    Activitate act{ titlu, descriere_noua, tip_nou, durata_noua };
    repo.modifica(titlu, act);
    undo_list.push_back(make_unique<UpdateUndo>(repo, act));

}
Activitate ActivitateService::cauta_activitate(string denumire) {
    int pos = repo.index_of(denumire);
    return repo.get_all().at(pos);
}

vector<Activitate> ActivitateService::filtrare_descriere(const string& descriere) {
    vector<Activitate> filter(repo.get_all().size());
    auto res = copy_if(repo.get_all().begin(), repo.get_all().end(), filter.begin(), 
        [&descriere](const Activitate& a) { return a.get_descriere() == descriere; });
    filter.resize(distance(filter.begin(), res));
    return filter;
}

vector<Activitate> ActivitateService::filtrare_tip(const string& tip) {
    vector<Activitate> filter(repo.get_all().size());
    auto res = copy_if(repo.get_all().begin(), repo.get_all().end(), filter.begin(),
        [&tip](const Activitate& a) { return a.get_tip() == tip; });
    filter.resize(distance(filter.begin(), res));
    return filter;
}

vector<Activitate> ActivitateService::ordoneaza_denumire(int ordine) {
    vector<Activitate> sorted = repo.get_all();
    if (ordine == 1) {
        sort(sorted.begin(), sorted.end(), cmp_title_asc);
    }
    else {
        sort(sorted.begin(), sorted.end(), cmp_title_desc);
    }
    return sorted;
}

vector<Activitate> ActivitateService::ordoneaza_descriere(int ordine) {
    vector<Activitate> sorted = repo.get_all();
    if (ordine == 1) {
        sort(sorted.begin(), sorted.end(), cmp_desc_asc);
    }
    else {
        sort(sorted.begin(), sorted.end(), cmp_desc_desc);
    }
    return sorted;
}

vector<Activitate> ActivitateService::ordoneaza_tipuri_si_durata(int ordine) {
    vector<Activitate> sorted = repo.get_all();
    if (ordine == 1) {
        sort(sorted.begin(), sorted.end(), cmp_type_dur_asc);
    }
    else {
        sort(sorted.begin(), sorted.end(), cmp_type_dur_desc);
    }
    return sorted;
}

const vector<Activitate>& ActivitateService::get_all() {
    return repo.get_all();
}

size_t ActivitateService::get_size() {
    return repo.get_all().size();
}

const Report& ActivitateService::Report() const noexcept {
    return tipuri_raportate;
}

void ActivitateService::generate_report() {
    for (const auto& act : repo.get_all())
        tipuri_raportate.add(act.get_tip());
}

void ActivitateService::undo() {
    
    undo_list.back()->doUndo();
    undo_list.pop_back();
    
}