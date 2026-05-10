#pragma once
#ifndef FINANCE_PAGE_H
#define FINANCE_PAGE_H

#include "Common.h"
#include <vector>

struct FinanceRecord {
    int id;
    std::string period; 
    std::string memberName;
    int amount;
};

class FinancePage {
private:
    std::vector<FinanceRecord> records;
public:
    void display() {
        Theme::header("PAYMENT MANAGEMENT PAGE");

        std::cout << "1. Add Payment Record\n2. View Financial Report\n0. Back\n";
    }
};
#endif