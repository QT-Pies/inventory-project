#include "../include/SalesComparison.hpp"

SalesComparison::SalesComparison() {}

SalesComparison::SalesComparison(std::shared_ptr<SaleList> sale_list) {
    std::map<unsigned int,
             std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > > >::iterator
        yit;
    std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > >::iterator mit;
    std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > >::iterator dit;
    std::map<int, double>::iterator ait;
    int numYears, totalYears;
    unsigned int month, day;
    time_t current_date;

    // getting current date to check if transactions have been added on the same day
    current_date = time(0);
    tm *ltm = localtime(&current_date);
    curr_y = 1900 + ltm->tm_year;
    curr_m = 1 + ltm->tm_mon;
    curr_d = ltm->tm_mday;

    numYears = 0;
    totalYears = 0;
    salesList = sale_list;
    /* Here we traverse all stored transactions and add their data to the needed maps. */
    for (yit = sale_list->transaction_by_date.begin(); yit != sale_list->transaction_by_date.end(); yit++) {
        numYears++;
        month = 0;
        for (mit = yit->second.begin(); mit != yit->second.end(); mit++) {
            month++;
            day = 1;
            for (dit = mit->second.begin(); dit != mit->second.end(); dit++) {
                if (yit->first == curr_y) {
                    for (long unsigned int i = 0; i < dit->second.size(); i++) {
                        currentYearSales += dit->second[i]->total_price;
                    }
                    if (month == curr_m) {
                        for (long unsigned int i = 0; i < dit->second.size(); i++) {
                            currentMonthSales += dit->second[i]->total_price;
                        }
                        if (day == curr_d) {
                            for (long unsigned int i = 0; i < dit->second.size(); i++) {
                                currentDaySales += dit->second[i]->total_price;
                            }
                        }
                    }
                } else {
                    for (long unsigned int i = 0; i < dit->second.size(); i++) {
                        salesByYear[dit->second[i]->year] += dit->second[i]->total_price;
                        salesByMonth[dit->second[i]->month] += dit->second[i]->total_price;
                    }
                }
                day++;
            }
        }
    }

    /* Now we set average sales. */
    for (ait = salesByYear.begin(); ait != salesByYear.end(); ait++) {
        totalYears += ait->second;
    }
    avgByYear = totalYears / numYears;

    month = 1;
    for (ait = salesByMonth.begin(); ait != salesByMonth.end(); ait++) {
        avgByMonth[month] = ait->second / numYears;
        month++;
    }

    /* Now we set the percent of the year and month that is left. */
    switch (curr_m) {
        case 1:
            if (curr_y % 4 == 0) {
                daysLeftYear = (31 - curr_d + 335) / 366;
            } else {
                daysLeftYear = (31 - curr_d + 334) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 2:
            if (curr_y % 4 == 0) {
                daysLeftYear = (60 - curr_d + 306) / 366;
                daysLeftMonth = (29 - curr_d) / 29;
            } else {
                daysLeftYear = (59 - curr_d + 306) / 365;
                daysLeftMonth = (28 - curr_d) / 28;
            }
            break;
        case 3:
            if (curr_y % 4 == 0) {
                daysLeftYear = (91 - curr_d + 275) / 366;
            } else {
                daysLeftYear = (90 - curr_d + 275) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 4:
            if (curr_y % 4 == 0) {
                daysLeftYear = (121 - curr_d + 245) / 366;
            } else {
                daysLeftYear = (120 - curr_d + 245) / 365;
            }
            daysLeftMonth = (30 - curr_d) / 30;
            break;
        case 5:
            if (curr_y % 4 == 0) {
                daysLeftYear = (152 - curr_d + 214) / 366;
            } else {
                daysLeftYear = (151 - curr_d + 214) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 6:
            if (curr_y % 4 == 0) {
                daysLeftYear = (182 - curr_d + 184) / 366;
            } else {
                daysLeftYear = (181 - curr_d + 184) / 365;
            }
            daysLeftMonth = (30 - curr_d) / 30;
            break;
        case 7:
            if (curr_y % 4 == 0) {
                daysLeftYear = (213 - curr_d + 153) / 366;
            } else {
                daysLeftYear = (212 - curr_d + 153) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 8:
            if (curr_y % 4 == 0) {
                daysLeftYear = (244 - curr_d + 122) / 366;
            } else {
                daysLeftYear = (243 - curr_d + 122) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 9:
            if (curr_y % 4 == 0) {
                daysLeftYear = (274 - curr_d + 92) / 366;
            } else {
                daysLeftYear = (273 - curr_d + 92) / 365;
            }
            daysLeftMonth = (30 - curr_d) / 30;
            break;
        case 10:
            if (curr_y % 4 == 0) {
                daysLeftYear = (305 - curr_d + 61) / 366;
            } else {
                daysLeftYear = (304 - curr_d + 61) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
        case 11:
            if (curr_y % 4 == 0) {
                daysLeftYear = (335 - curr_d + 31) / 366;
            } else {
                daysLeftYear = (334 - curr_d + 31) / 365;
            }
            daysLeftMonth = (30 - curr_d) / 30;
            break;
        case 12:
            if (curr_y % 4 == 0) {
                daysLeftYear = (366 - curr_d) / 366;
            } else {
                daysLeftYear = (365 - curr_d) / 365;
            }
            daysLeftMonth = (31 - curr_d) / 31;
            break;
    }

    /* Lastly set how many days are in a month. */
    if (curr_y % 4 == 0) {
        daysInMonth = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    } else {
        daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    }
}

void SalesComparison::printComparison(std::string function, int x) {
    double result;

    if (function == "ByYear") {
        result = compareByYear();
        fprintf(stdout, "Average sales per year : %.2f\nSales so far this year : %.2f\n%% Difference : %.2f\n",
                avgByYear, currentYearSales, result);
    } else if (function == "ByMonth") {
        result = compareByMonth();
        fprintf(stdout, "Average sales per month %d : %.2f\nSales so far this year : %.2f\n%% Difference : %.2f\n",
                curr_m, avgByMonth[curr_m], currentMonthSales, result);
    } else if (function == "LastXYears") {
        result = compareLastXYears(x);
        fprintf(stdout, "Sales so far this year compared to the average over the past 10 years : %.2f\n", result);
    } else if (function == "LastMonth") {
        result = compareLastMonth();
        fprintf(stdout, "Sales so far this month compared to last month so far : %.2f\n", result);
    } else if (function == "Last7Days") {
        result = compareLast7Days();
        fprintf(stdout,
                "Sales over the past 7 days compared to today : %.2f\nThis number will be lower"
                " earlier in the day and only shows an accurate comparison at the end of the day.\n",
                result);
    } else if (function == "Yesterday") {
        result = compareYesterday();
        fprintf(stdout,
                "Yesterdays sales compared to today : %.2f\nThis number will be lower"
                " earlier in the day and only shows an accurate comparison at the end of the day.\n",
                result);
    } else {
        fprintf(stderr, "Invalid function %s passed to SalesComparison::printComparison(std::string)\n",
                function.c_str());
        return;
    }
}

void SalesComparison::printAllComparisons() {
    double result;

    result = compareByYear();
    fprintf(stdout, "Average sales per year : %.2f\nSales so far this year : %.2f\n%% Difference : %.2f\n", avgByYear,
            currentYearSales, result);

    result = compareByMonth();
    fprintf(stdout, "Average sales per month %d : %.2f\nSales so far this year : %.2f\n%% Difference : %.2f\n", curr_m,
            avgByMonth[curr_m], currentMonthSales, result);

    result = compareLastMonth();
    fprintf(stdout, "Sales so far this month compared to last month so far : %.2f\n", result);

    result = compareLast7Days();
    fprintf(stdout,
            "Sales over the past 7 days compared to today : %.2f\nThis number will be lower"
            " earlier in the day and only shows an accurate comparison at the end of the day.\n",
            result);

    result = compareYesterday();
    fprintf(stdout,
            "Yesterdays sales compared to today : %.2f\nThis number will be lower"
            " earlier in the day and only shows an accurate comparison at the end of the day.\n",
            result);
}

double SalesComparison::compareByYear() {
    /* Compare the sales from the current year to the past years up to this point in the year. */
    return currentYearSales / (avgByYear * (1 - daysLeftYear));
}

double SalesComparison::compareByMonth() {
    /* Compare the sales from the current month to the past months up to this point in the month. */
    return currentMonthSales / (avgByMonth[curr_m] * (1 - daysLeftMonth));
}

double SalesComparison::compareLastXYears(int x) {
    int num_years, first_year;
    double total;
    std::map<unsigned int,
             std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > > >::iterator
        yit;
    std::map<int, double>::iterator mit;

    /* This function will compare up to 10 years in the past, however if there are not 10 years to compare it will
     *  tell you how many years are being compared. */
    num_years = 0;
    for (yit = salesList->transaction_by_date.end(); num_years < x || yit != salesList->transaction_by_date.begin();
         yit--) {
        num_years++;
    }
    // if (num_years != x) num_years++;
    first_year = yit->first;

    if (num_years < x) {
        fprintf(stdout, "Only %d years to compare with.\n", num_years);
    }

    total = 0;
    for (mit = salesByYear.begin(); mit->first != first_year; mit++)
        ;
    for (mit = mit; mit != salesByYear.end(); mit++) {
        total += mit->second;
    }
    return currentYearSales / ((total / num_years) * (1 - daysLeftYear));
}

double SalesComparison::compareLastMonth() {
    double last_month = 0;
    std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > >::iterator dit;

    if (curr_m == 1) {
        if (salesList->transaction_by_date.find(curr_y - 1) != salesList->transaction_by_date.end()) {
            if (salesList->transaction_by_date[curr_y - 1].find(12) !=
                salesList->transaction_by_date[curr_y - 1].end()) {
                for (dit = salesList->transaction_by_date[curr_y - 1][12].begin();
                     dit != salesList->transaction_by_date[curr_y - 1][12].end(); dit++) {
                    for (long unsigned int i = 0; i < dit->second.size(); i++) {
                        last_month += dit->second[i]->total_price;
                    }
                }
                return currentMonthSales / (last_month * (1 - daysLeftMonth));
            }
        }
        fprintf(stderr, "No sales made in the last month to compare to.\n");
        return 0;
    } else {
        if (salesList->transaction_by_date.find(curr_y) != salesList->transaction_by_date.end()) {
            if (salesList->transaction_by_date[curr_y].find(curr_m - 1) !=
                salesList->transaction_by_date[curr_y].end()) {
                for (dit = salesList->transaction_by_date[curr_y][curr_m - 1].begin();
                     dit != salesList->transaction_by_date[curr_y][curr_m - 1].end(); dit++) {
                    for (long unsigned int i = 0; i < dit->second.size(); i++) {
                        last_month += dit->second[i]->total_price;
                    }
                }
                return currentMonthSales / (last_month * (1 - daysLeftMonth));
            }
        }
        fprintf(stderr, "No sales made in the last month to compare to.\n");
        return 0;
    }
}

double SalesComparison::compareLast7Days() {
    double last_week;
    int days_in_last_month, days;
    std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > >::iterator dit;

    last_week = 0;
    if (curr_d < 7) {
        days_in_last_month = 7 - curr_d;
        if (curr_m == 1) {
            if (salesList->transaction_by_date.find(curr_y - 1) != salesList->transaction_by_date.end()) {
                if (salesList->transaction_by_date[curr_y - 1].find(12) !=
                    salesList->transaction_by_date[curr_y - 1].end()) {
                    dit = salesList->transaction_by_date[curr_y][12].end();
                    dit--;
                    days = 0;
                    for (dit = dit; days != days_in_last_month; dit--) {
                        for (long unsigned int i = 0; i < dit->second.size(); i++) {
                            last_week += dit->second[i]->total_price;
                        }
                        days++;
                    }
                    return currentDaySales / ((last_week + currentMonthSales - currentDaySales) / 7);
                }
            }
            fprintf(stderr, "No sales made in the last week to compare to.\n");
            return 0;
        } else {
            if (salesList->transaction_by_date.find(curr_y) != salesList->transaction_by_date.end()) {
                if (salesList->transaction_by_date[curr_y].find(curr_m - 1) !=
                    salesList->transaction_by_date[curr_y].end()) {
                    dit = salesList->transaction_by_date[curr_y][curr_m - 1].end();
                    dit--;
                    days = 0;
                    for (dit = dit; days != days_in_last_month; dit--) {
                        for (long unsigned int i = 0; i < dit->second.size(); i++) {
                            last_week += dit->second[i]->total_price;
                        }
                        days++;
                    }
                    return currentDaySales / ((last_week + currentMonthSales - currentDaySales) / 7);
                }
            }
            fprintf(stderr, "No sales made in the last week to compare to.\n");
            return 0;
        }
    } else {
        if (salesList->transaction_by_date.find(curr_y) != salesList->transaction_by_date.end()) {
            if (salesList->transaction_by_date[curr_y].find(curr_m) != salesList->transaction_by_date[curr_y].end()) {
                for (dit = salesList->transaction_by_date[curr_y][curr_m].begin(); dit->first < curr_d - 7; dit++)
                    ;
                for (dit = dit; dit->first != curr_d; dit++) {
                    for (long unsigned int i = 0; i < dit->second.size(); i++) {
                        last_week += dit->second[i]->total_price;
                    }
                }
                return currentDaySales / (last_week / 7);
            }
        }
        fprintf(stderr, "No sales made in the last week to compare to.\n");
        return 0;
    }
}

double SalesComparison::compareYesterday() {
    double yesterday_sales = 0;

    if (curr_d == 1) {
        if (curr_m == 1) {
            if (salesList->transaction_by_date.find(curr_y - 1) != salesList->transaction_by_date.end()) {
                if (salesList->transaction_by_date[curr_y - 1].find(12) !=
                    salesList->transaction_by_date[curr_y - 1].end()) {
                    if (salesList->transaction_by_date[curr_y - 1][12].find(31) !=
                        salesList->transaction_by_date[curr_y - 1][12].end()) {
                        for (long unsigned int i = 0; i < salesList->transaction_by_date[curr_y - 1][12][31].size();
                             i++) {
                            yesterday_sales += salesList->transaction_by_date[curr_y - 1][12][31][i]->total_price;
                        }
                        return currentDaySales / yesterday_sales;
                    }
                }
            }
            fprintf(stderr, "No sales made yesterday to compare to.\n");
            return 0;
        } else {
            if (salesList->transaction_by_date.find(curr_y) != salesList->transaction_by_date.end()) {
                if (salesList->transaction_by_date[curr_y].find(curr_m - 1) !=
                    salesList->transaction_by_date[curr_y].end()) {
                    if (salesList->transaction_by_date[curr_y][curr_m - 1].find(daysInMonth[curr_m]) !=
                        salesList->transaction_by_date[curr_y][curr_m - 1].end()) {
                        for (long unsigned int i = 0;
                             i < salesList->transaction_by_date[curr_y][curr_m - 1][daysInMonth[curr_m - 1]].size();
                             i++) {
                            yesterday_sales +=
                                salesList->transaction_by_date[curr_y][curr_m - 1][daysInMonth[curr_m - 1]][i]
                                    ->total_price;
                        }
                        return currentDaySales / yesterday_sales;
                    }
                }
            }
            fprintf(stderr, "No sales made yesterday to compare to.\n");
            return 0;
        }
    } else {
        if (salesList->transaction_by_date.find(curr_y) != salesList->transaction_by_date.end()) {
            if (salesList->transaction_by_date[curr_y].find(curr_m) != salesList->transaction_by_date[curr_y].end()) {
                if (salesList->transaction_by_date[curr_y][curr_m].find(curr_d - 1) !=
                    salesList->transaction_by_date[curr_y][curr_m].end()) {
                    for (long unsigned int i = 0; i < salesList->transaction_by_date[curr_y][curr_m][curr_d - 1].size();
                         i++) {
                        yesterday_sales += salesList->transaction_by_date[curr_y][curr_m][curr_d - 1][i]->total_price;
                    }
                    return currentDaySales / yesterday_sales;
                }
            }
        }
        fprintf(stderr, "No sales made yesterday to compare to.\n");
        return 0;
    }
}