#include "teste.h"
#include "ReportTest.h"
#include "UI.h"
#include <iostream>
using std::cout;


int main() {
    teste t;
    t.test_all();
    ReportTest::run_all_tests();

    //MemoryRepo m_r;
    //ActivitateService m_s(m_r);
    //UI m_c(m_s);

    // t_r("Activitate.txt");
    //ActivitateService t_s(t_r);
    //UI t_c(t_s);

    
    LabRepo l_r(0.5);
    ActivitateService l_s(l_r);
    UI l_c(l_s);
    
    //t_c.run_all();
    //m_c.run_all();
    l_c.run_all();
    return 0;
}

