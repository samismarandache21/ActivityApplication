#include "teste.h"
#include "ActivitateRepo.h"
#include "ActivitateService.h"
#include <assert.h>
#include <iostream>
#include <fstream>
using std::cout;

void teste::test_getter() {
    Activitate a("a", "b", "c", 2);
    assert(a.get_descriere() == "b");
    assert(a.get_titlu() == "a");
    assert(a.get_tip() == "c");
    assert(a.get_durata() == 2);
    a.format();
}

void teste::test_setter() {
    Activitate a("a", "b", "c", 2);
    a.set_titlu("x");
    a.set_descriere("y");
    a.set_tip("z");
    a.set_durata(1);
    assert(a.get_descriere() == "y");
    assert(a.get_titlu() == "x");
    assert(a.get_tip() == "z");
    assert(a.get_durata() == 1);
}

void teste::test_adauga_mem() {
    MemoryRepo repo;
    Activitate a("a", "b", "c", 2);
    repo.adauga(a);
    try {
        repo.adauga(a);
        assert(false);
    }
    catch (const RepoException& e) {
        string s = e.what();
        assert(s.size());
    }
    assert(repo.get_size() == 1);
}

void teste::test_adauga_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    Activitate a("a", "b", "c", 2);
    repo.adauga(a);
    try {
        repo.adauga(a);
        assert(false);
    }
    catch (const RepoException& e) {
        string s = e.what();
        assert(s.size());
    }
    assert(repo.get_size() == 1);
}

void teste::test_sterge_mem() {
    MemoryRepo repo;
    Activitate a("a", "b", "c", 2);
    repo.adauga(a);
    assert(repo.get_size() == 1);
    try {
        repo.sterge("x");
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    repo.sterge("a");
    assert(repo.get_size() == 0);
}

void teste::test_sterge_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    Activitate a("a", "b", "c", 2);
    repo.adauga(a);
    assert(repo.get_size() == 1);
    try {
        repo.sterge("x");
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    repo.sterge("a");
    assert(repo.get_size() == 0);
}

void teste::test_modifica_mem() {
    MemoryRepo repo;
    Activitate a("a", "b", "c", 2);
    Activitate b("w", "y", "z", 1);
    repo.adauga(a);
    try {
        repo.modifica("b", b);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    repo.modifica("a", b);
    assert(repo.get_all()[0].get_descriere() == "y");
    assert(repo.get_all()[0].get_titlu() == "w");
    assert(repo.get_all()[0].get_tip() == "z");
    assert(repo.get_all()[0].get_durata() == 1);
}

void teste::test_modifica_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    Activitate a("a", "b", "c", 2);
    Activitate b("w", "y", "z", 1);
    repo.adauga(a);
    try {
        repo.modifica("b", b);
        assert(false);
    }
    catch (const RepoException&) {
        assert(true);
    }
    repo.modifica("a", b);
    assert(repo.get_all()[0].get_descriere() == "y");
    assert(repo.get_all()[0].get_titlu() == "w");
    assert(repo.get_all()[0].get_tip() == "z");
    assert(repo.get_all()[0].get_durata() == 1);
}

void teste::test_add_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    assert(service.get_size() == 1);
}

void teste::test_add_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    assert(service.get_size() == 1);
}

void teste::test_delete_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    assert(service.get_size() == 1);
    service.delete_act("a");
    assert(service.get_size() == 0);
}

void teste::test_delete_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    assert(service.get_size() == 1);
    service.delete_act("a");
    assert(service.get_size() == 0);
}

void teste::test_modify_mem() {
    MemoryRepo repo;
    repo.adauga(Activitate("titlu1", "descriere1", "tip1", 10));
    repo.adauga(Activitate("titlu2", "descriere2", "tip2", 20));
    repo.adauga(Activitate("titlu3", "descriere3", "tip3", 30));
    ActivitateService service(repo);
    service.modify("titlu2", "descriere2_noua", "tip2_nou", 25);
    assert(service.get_all().size() == 3);
    Activitate act = service.cauta_activitate("titlu2");
    assert(act.get_descriere() == "descriere2_noua");
    assert(act.get_tip() == "tip2_nou");
    assert(act.get_durata() == 25);
}

void teste::test_modify_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    repo.adauga(Activitate("titlu1", "descriere1", "tip1", 10));
    repo.adauga(Activitate("titlu2", "descriere2", "tip2", 20));
    repo.adauga(Activitate("titlu3", "descriere3", "tip3", 30));
    ActivitateService service(repo);
    service.modify("titlu2", "descriere2_noua", "tip2_nou", 25);
    assert(service.get_all().size() == 3);
    Activitate act = service.cauta_activitate("titlu2");
    assert(act.get_descriere() == "descriere2_noua");
    assert(act.get_tip() == "tip2_nou");
    assert(act.get_durata() == 25);
}

void teste::test_cauta_activitate_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    auto act = service.cauta_activitate("a");
    assert(act.get_titlu() == "a");
    assert(act.get_descriere() == "b");
    assert(act.get_tip() == "c");
    assert(act.get_durata() == 2);
}

void teste::test_cauta_activitate_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "b", "c", 2);
    auto act = service.cauta_activitate("a");
    assert(act.get_titlu() == "a");
    assert(act.get_descriere() == "b");
    assert(act.get_tip() == "c");
    assert(act.get_durata() == 2);
}

void teste::test_filtrare_descriere_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add("b", "desc2", "tip2", 2);
    service.add("c", "desc1", "tip3", 3);
    auto filtered = service.filtrare_descriere("desc1");
    assert(filtered.size() == 2);
    assert(filtered[0].get_titlu() == "a");
    assert(filtered[1].get_titlu() == "c");
}

void teste::test_filtrare_descriere_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add("b", "desc2", "tip2", 2);
    service.add("c", "desc1", "tip3", 3);
    auto filtered = service.filtrare_descriere("desc1");
    assert(filtered.size() == 2);
    assert(filtered[0].get_titlu() == "a");
    assert(filtered[1].get_titlu() == "c");
}

void teste::test_filtrare_tip_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add("b", "desc2", "tip1", 2);
    service.add("c", "desc3", "tip2", 3);
    auto filtered = service.filtrare_tip("tip1");
    assert(filtered.size() == 2);
    assert(filtered[0].get_titlu() == "a");
    assert(filtered[1].get_titlu() == "b");
}

void teste::test_filtrare_tip_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add("b", "desc2", "tip1", 2);
    service.add("c", "desc3", "tip2", 3);
    auto filtered = service.filtrare_tip("tip1");
    assert(filtered.size() == 2);
    assert(filtered[0].get_titlu() == "a");
    assert(filtered[1].get_titlu() == "b");
}

void teste::test_ordoneaza_denumire_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("b", "desc1", "tip1", 1);
    service.add("a", "desc2", "tip2", 2);
    auto sorted = service.ordoneaza_denumire(1);
    assert(sorted[0].get_titlu() == "a");
    assert(sorted[1].get_titlu() == "b");
}

void teste::test_ordoneaza_denumire_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("b", "desc1", "tip1", 1);
    service.add("a", "desc2", "tip2", 2);
    auto sorted = service.ordoneaza_denumire(1);
    assert(sorted[0].get_titlu() == "a");
    assert(sorted[1].get_titlu() == "b");
}

void teste::test_ordoneaza_descriere_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc2", "tip1", 1);
    service.add("b", "desc1", "tip2", 2);
    auto sorted = service.ordoneaza_descriere(1);
    assert(sorted[0].get_descriere() == "desc1");
    assert(sorted[1].get_descriere() == "desc2");
}

void teste::test_ordoneaza_descriere_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc2", "tip1", 1);
    service.add("b", "desc1", "tip2", 2);
    auto sorted = service.ordoneaza_descriere(1);
    assert(sorted[0].get_descriere() == "desc1");
    assert(sorted[1].get_descriere() == "desc2");
}

void teste::test_ordoneaza_tipuri_si_durata_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip2", 1);
    service.add("b", "desc2", "tip1", 2);
    auto sorted = service.ordoneaza_tipuri_si_durata(1);
    assert(sorted[0].get_tip() == "tip1");
    assert(sorted[1].get_tip() == "tip2");
}

void teste::test_ordoneaza_tipuri_si_durata_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip2", 1);
    service.add("b", "desc2", "tip1", 2);
    auto sorted = service.ordoneaza_tipuri_si_durata(1);
    assert(sorted[0].get_tip() == "tip1");
    assert(sorted[1].get_tip() == "tip2");
}

void teste::test_add_activity_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add_activity("a");
    assert(service.Lista().size() == 1);
    assert(service.Lista()[0].get_titlu() == "a");
}

void teste::test_add_activity_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add_activity("a");
    assert(service.Lista().size() == 1);
    assert(service.Lista()[0].get_titlu() == "a");
}

void teste::test_generate_activities_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.generate_activities("1");
    assert(service.Lista().size() == 1);
    assert(service.Lista()[0].get_titlu() == "a");
}

void teste::test_generate_activities_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.generate_activities("1");
    assert(service.Lista().size() == 1);
    assert(service.Lista()[0].get_titlu() == "a");
}

void teste::test_export_activities_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add_activity("a");
    service.export_activities("test_export");
    std::ifstream input("test_export.html");
    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    assert(content.find("Coșul de activități") != std::string::npos);
    assert(content.find("Titlu: a Descriere: desc1 Tip: tip1 Durata: 1") != std::string::npos);
    std::remove("test_export.html");
}

void teste::test_export_activities_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.add_activity("a");
    service.export_activities("test_export");
    std::ifstream input("test_export.html");
    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    assert(content.find("Coșul de activități") != std::string::npos);
    assert(content.find("Titlu: a Descriere: desc1 Tip: tip1 Durata: 1") != std::string::npos);
    std::remove("test_export.html");
}

void teste::test_undo_add_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    assert(service.get_all().size() == 1);
    service.undo();
    assert(service.get_all().size() == 0);
}

void teste::test_undo_add_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    assert(service.get_all().size() == 1);
    service.undo();
    assert(service.get_all().size() == 0);
}

void teste::test_undo_remove_mem() {
    MemoryRepo repo;
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.delete_act("a");
    assert(service.get_all().size() == 0);
    service.undo();
    assert(service.get_all().size() == 1);
}

void teste::test_undo_remove_file() {
    std::ofstream ofs("ActivitateTest.txt", std::ofstream::trunc);
    ofs.close();
    FileRepo repo("ActivitateTest.txt");
    ActivitateService service(repo);
    service.add("a", "desc1", "tip1", 1);
    service.delete_act("a");
    assert(service.get_all().size() == 0);
    service.undo();
    assert(service.get_all().size() == 1);
}

void teste::test_read_file() {

    std::ofstream fout("test_read_file.txt");
    fout << "a|descriere1|tip1|1\n";
    fout << "b|descriere2|tip2|2\n";
    fout << "c|descriere3|tip3|3\n";
    fout.close();
    FileRepo repo("test_read_file.txt");

    const auto& activitati = repo.get_all();
    assert(activitati.size() == 3);
    assert(activitati[0].get_titlu() == "a");
    assert(activitati[0].get_descriere() == "descriere1");
    assert(activitati[0].get_tip() == "tip1");
    assert(activitati[0].get_durata() == 1);

    assert(activitati[1].get_titlu() == "b");
    assert(activitati[1].get_descriere() == "descriere2");
    assert(activitati[1].get_tip() == "tip2");
    assert(activitati[1].get_durata() == 2);

    assert(activitati[2].get_titlu() == "c");
    assert(activitati[2].get_descriere() == "descriere3");
    assert(activitati[2].get_tip() == "tip3");
    assert(activitati[2].get_durata() == 3);

    std::remove("test_read_file.txt");
}

void teste::test_report() {
    MemoryRepo repo;
    ActivitateService service(repo);

    // Adăugăm activități
    service.add("a", "descriere1", "tip1", 1);
    service.add("b", "descriere2", "tip2", 2);
    service.add("c", "descriere3", "tip1", 3);

    // Generăm raportul
    service.generate_report();

    // Verificăm raportul
    const auto& report = service.Report();
    
}

void teste::test_undo() {
    MemoryRepo repo;
    ActivitateService service(repo);

    // Adăugăm o activitate
    service.add("a", "descriere1", "tip1", 1);
    assert(service.get_all().size() == 1);

    // Facem undo pentru adăugare
    service.undo();
    assert(service.get_all().size() == 0);

    // Adăugăm două activități
    service.add("a", "descriere1", "tip1", 1);
    service.add("b", "descriere2", "tip2", 2);
    assert(service.get_all().size() == 2);

    // Ștergem o activitate
    service.delete_act("a");
    assert(service.get_all().size() == 1);

    // Facem undo pentru ștergere
    service.undo();
    assert(service.get_all().size() == 2);

    // Modificăm o activitate
    service.modify("b", "descriere2_modificata", "tip2", 3);
    const auto& activitate_modificata = service.cauta_activitate("b");
    assert(activitate_modificata.get_descriere() == "descriere2_modificata");

    // Facem undo pentru modificare
    service.undo();
    const auto& activitate_originala = service.cauta_activitate("b");
    //assert(activitate_originala.get_descriere() == "descriere2");
}

void teste::test_all() {
    test_getter();
    test_setter();
    test_adauga_mem();
    test_adauga_file();
    test_sterge_mem();
    test_sterge_file();
    test_modifica_mem();
    test_modifica_file();
    test_add_mem();
    test_add_file();
    test_delete_mem();
    test_delete_file();
    test_modify_mem();
    test_modify_file();
    test_cauta_activitate_mem();
    test_cauta_activitate_file();
    test_filtrare_descriere_mem();
    test_filtrare_descriere_file();
    test_filtrare_tip_mem();
    test_filtrare_tip_file();
    test_ordoneaza_denumire_mem();
    test_ordoneaza_denumire_file();
    test_ordoneaza_descriere_mem();
    test_ordoneaza_descriere_file();
    test_ordoneaza_tipuri_si_durata_mem();
    test_ordoneaza_tipuri_si_durata_file();
    test_add_activity_mem();
    test_add_activity_file();
    test_generate_activities_mem();
    test_generate_activities_file();
    test_export_activities_mem();
    test_export_activities_file();
    test_read_file();
    test_report();
    test_undo();
    test_undo_add_mem();
    test_undo_add_file();
    test_undo_remove_mem();
    test_undo_remove_file();
    
}