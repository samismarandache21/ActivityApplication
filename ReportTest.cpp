#include "ReportTest.h"
#include "Report.h"
#include <cassert>
#include <iostream>

void ReportTest::test_constructor() {
    Report report;
    assert(report.size() == 0);
}

void ReportTest::test_add() {
    Report report;
    report.add("tip1");
    report.add("tip2");
    report.add("tip1");  

    assert(report.size() == 2);  
}

void ReportTest::test_size() {
    Report report;
    assert(report.size() == 0);
    report.add("tip1");
    assert(report.size() == 1);
    report.add("tip2");
    assert(report.size() == 2);
    report.add("tip1");  
    assert(report.size() == 2);
}

void ReportTest::test_to_str() {
    Report report;
    report.add("tip1");
    report.add("tip2");
    report.add("tip1"); 

    string expected = "tip1 - 2\ntip2 - 1\n";
    assert(report.to_str() == expected);
}

void ReportTest::run_all_tests() {
    test_constructor();
    test_add();
    test_size();
    test_to_str();
}
