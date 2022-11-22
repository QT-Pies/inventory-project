#include "SalesComparison.hpp"

SalesComparison::SalesComparison() {}

void SalesComparison::setup(std::shared_ptr<SaleList> sale_list) {
    std::map<unsigned int,
             std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > > >::iterator
        mit;
    std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > >::iterator dit;
    std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > >::iterator yit;
    std::map<int, double>::iterator ait;
    std::map<int, std::map<unsigned long, double> >::iterator it;
    std::map<unsigned long, double>::iterator idIt;
    double numYears, totalYears;
    unsigned int month;
    time_t current_date;

    // getting current date to check if transactions have been added on the same day
    current_date = time(0);
    tm *ltm = localtime(&current_date);
    curr_y = 1900 + ltm->tm_year;
    curr_m = 1 + ltm->tm_mon;
    curr_d = ltm->tm_mday;

    numYears = 0;
    totalYears = 0;
    sales_list = sale_list;
    /* Here we traverse all stored transactions and add their data to the needed maps. */
    for (mit = sale_list->transaction_by_date.begin(); mit != sale_list->transaction_by_date.end(); mit++) {
        for (dit = mit->second.begin(); dit != mit->second.end(); dit++) {
            for (yit = dit->second.begin(); yit != dit->second.end(); yit++) {
                years.insert(yit->first);
                if (yit->first == curr_y) {
                    if (mit->first <= curr_m) {
                        for (long unsigned int i = 0; i < yit->second.size(); i++) {
                            if (mit->first < curr_m || dit->first <= curr_d) {
                                current_year_sales += yit->second[i]->total_price;
                            } else {
                                sales_by_year[yit->second[i]->year] += yit->second[i]->total_price;
                            }
                        }
                        if (mit->first == curr_m && dit->first <= curr_d) {
                            for (long unsigned int i = 0; i < yit->second.size(); i++) {
                                current_month_sales += yit->second[i]->total_price;
                                for (long unsigned int j = 0; j < yit->second[i]->sales.size(); j++) {
                                    current_month_item_ids[yit->second[i]->sales[j]->item_id] +=
                                        yit->second[i]->sales[j]->sale_price * yit->second[i]->sales[j]->num_sold;
                                }
                            }
                            if (dit->first == curr_d) {
                                for (long unsigned int i = 0; i < yit->second.size(); i++) {
                                    current_day_sales += yit->second[i]->total_price;
                                }
                            }
                        }
                    }
                }
                for (long unsigned int i = 0; i < yit->second.size(); i++) {
                    sales_by_year[yit->second[i]->year] += yit->second[i]->total_price;
                    sales_by_month[yit->second[i]->month] += yit->second[i]->total_price;
                    for (long unsigned int j = 0; j < yit->second[i]->sales.size(); j++) {
                        item_ids_by_month[yit->second[i]->month][yit->second[i]->sales[j]->item_id] +=
                            yit->second[i]->sales[j]->sale_price * yit->second[i]->sales[j]->num_sold;
                    }
                }
            }
        }
    }

    numYears = years.size();

    /* Now we set average sales. */
    for (ait = sales_by_year.begin(); ait != sales_by_year.end(); ait++) {
        totalYears += ait->second;
    }
    avg_by_year = totalYears / numYears;

    month = 1;
    for (ait = sales_by_month.begin(); ait != sales_by_month.end(); ait++) {
        avg_by_month[month] = ait->second / numYears;
        month++;
    }

    for (it = item_ids_by_month.begin(); it != item_ids_by_month.end(); it++) {
        for (idIt = it->second.begin(); idIt != it->second.end(); idIt++) {
            idIt->second /= numYears;
        }
    }

    /* Now we set the percent of the year and month that is left. */
    switch (curr_m) {
        case 1:
            if (curr_y % 4 == 0) {
                days_left_year = (31 - curr_d + 335) / 366.0;
            } else {
                days_left_year = (31 - curr_d + 334) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 2:
            if (curr_y % 4 == 0) {
                days_left_year = (60 - curr_d + 306) / 366.0;
                days_left_month = (29 - curr_d) / 29.0;
            } else {
                days_left_year = (59 - curr_d + 306) / 365.0;
                days_left_month = (28 - curr_d) / 28.0;
            }
            break;
        case 3:
            if (curr_y % 4 == 0) {
                days_left_year = (91 - curr_d + 275) / 366.0;
            } else {
                days_left_year = (90 - curr_d + 275) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 4:
            if (curr_y % 4 == 0) {
                days_left_year = (121 - curr_d + 245) / 366.0;
            } else {
                days_left_year = (120 - curr_d + 245) / 365.0;
            }
            days_left_month = (30 - curr_d) / 30.0;
            break;
        case 5:
            if (curr_y % 4 == 0) {
                days_left_year = (152 - curr_d + 214) / 366.0;
            } else {
                days_left_year = (151 - curr_d + 214) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 6:
            if (curr_y % 4 == 0) {
                days_left_year = (182 - curr_d + 184) / 366.0;
            } else {
                days_left_year = (181 - curr_d + 184) / 365.0;
            }
            days_left_month = (30 - curr_d) / 30.0;
            break;
        case 7:
            if (curr_y % 4 == 0) {
                days_left_year = (213 - curr_d + 153) / 366.0;
            } else {
                days_left_year = (212 - curr_d + 153) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 8:
            if (curr_y % 4 == 0) {
                days_left_year = (244 - curr_d + 122) / 366.0;
            } else {
                days_left_year = (243 - curr_d + 122) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 9:
            if (curr_y % 4 == 0) {
                days_left_year = (274 - curr_d + 92) / 366.0;
            } else {
                days_left_year = (273 - curr_d + 92) / 365.0;
            }
            days_left_month = (30 - curr_d) / 30.0;
            break;
        case 10:
            if (curr_y % 4 == 0) {
                days_left_year = (305 - curr_d + 61) / 366.0;
            } else {
                days_left_year = (304 - curr_d + 61) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
        case 11:
            if (curr_y % 4 == 0) {
                days_left_year = (335 - curr_d + 31) / 366.0;
            } else {
                days_left_year = (334 - curr_d + 31) / 365.0;
            }
            days_left_month = (30 - curr_d) / 30.0;
            break;
        case 12:
            if (curr_y % 4 == 0) {
                days_left_year = (366 - curr_d) / 366.0;
            } else {
                days_left_year = (365 - curr_d) / 365.0;
            }
            days_left_month = (31 - curr_d) / 31.0;
            break;
    }

    /* Lastly set how many days are in a month. */
    if (curr_y % 4 == 0) {
        days_in_month = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    } else {
        days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    }
}

void SalesComparison::printComparison(std::string function, int x) {
    double result;

    if (function == "ByYear") {
        result = compareByYear();
        fprintf(stdout,
                "Average sales per year : $%.2f\n"
                "Sales so far this year : $%.2f\n"
                "%% Gain this year vs avg : %.2f\n\n",
                avg_by_year, current_year_sales, result - 100);
    } else if (function == "ByMonth") {
        result = compareByMonth();
        fprintf(stdout,
                "Average sales per month %d  : $%.2f\n"
                "Sales so far this month     : $%.2f\n"
                "%% Gain this month vs avg    : %.2f\n\n",
                curr_m, avg_by_month[curr_m] * (1 - days_left_month), current_month_sales, result - 100);
    } else if (function == "LastXYears") {
        result = compareLastXYears(x);
        fprintf(stdout, "%% Sales so far this year compared to the average over the past %d years : %.2f\n", x,
                result - 100);
    } else if (function == "LastMonth") {
        result = compareLastMonth();
        fprintf(stdout, "%% Sales so far this month compared to last month so far : %.2f\n", result - 100);
    } else if (function == "Last7Days") {
        result = compareLast7Days();
        fprintf(stdout,
                "%% Sales over the past 7 days compared to today : %.2f\n"
                "***This number will be lower earlier in the day and only\n"
                " shows an accurate comparison at the end of the day.***\n",
                result - 100);
    } else if (function == "Yesterday") {
        result = compareYesterday();
        fprintf(stdout,
                "%% Yesterdays sales compared to today : %.2f\n"
                "***This number will be lower earlier in the day and only\n"
                " shows an accurate comparison at the end of the day.***\n",
                result - 100);
    } else {
        fprintf(stderr, "Invalid function %s passed to SalesComparison::printComparison(std::string)\n",
                function.c_str());
        return;
    }
}

void SalesComparison::printAllComparisons() {
    double result;

    result = compareByYear();
    fprintf(stdout,
            "Average sales per year  : $%.2f\n"
            "Sales so far this year  : $%.2f\n"
            "%% Gain this year vs avg : %.2f\n\n",
            avg_by_year, current_year_sales, result - 100);

    result = compareByMonth();
    fprintf(stdout,
            "Average sales per month %d : $%.2f\n"
            "Sales so far this month    : $%.2f\n"
            "%% Gain this month vs avg   : %.2f\n\n",
            curr_m, avg_by_month[curr_m] * (1 - days_left_month), current_month_sales, result - 100);

    result = compareLastMonth();
    fprintf(stdout, "%% Sales so far this month compared to last month so far : %.2f\n\n", result - 100);

    result = compareLast7Days();
    fprintf(stdout,
            "%% Sales over the past 7 days compared to today : %.2f\n"
            "***This number will be lower earlier in the day and only\n"
            " shows an accurate comparison at the end of the day.***\n\n",
            result - 100);

    result = compareYesterday();
    fprintf(stdout,
            "%% Yesterdays sales compared to today : %.2f\n"
            "***This number will be lower earlier in the day and only\n"
            " shows an accurate comparison at the end of the day.***\n\n",
            result - 100);
}

double SalesComparison::compareByYear() {
    /* Compare the sales from the current year to the past years up to this point in the year. */
    return 100.0 * (current_year_sales / (avg_by_year * days_left_year));
}

double SalesComparison::compareByMonth() {
    /* Compare the sales from the current month to the past months up to this point in the month. */
    return 100.0 * (current_month_sales / (avg_by_month[curr_m] * (1 - days_left_month)));
}

double SalesComparison::compareLastXYears(int x) {
    int num_years, first_year;
    double total;
    std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > >::iterator yit;
    std::map<int, double>::iterator it;

    /* This function will compare up to 10 years in the past, however if there are not 10 years to compare it will
     *  tell you how many years are being compared. */
    num_years = 0;
    for (yit = sales_list->transaction_by_date[curr_m][curr_d].end(); yit->first != curr_y - 1; yit--)
        ;
    for (; yit != sales_list->transaction_by_date[curr_m][curr_d].end(); yit--) {
        num_years++;
        if (num_years == x) break;
    }

    first_year = yit->first;

    if (num_years < x) {
        fprintf(stdout, "Only %d year(s) to compare with.\n", num_years);
    }

    total = 0;
    for (it = sales_by_year.begin(); it->first < first_year; it++)
        ;
    for (; it != sales_by_year.end(); it++) {
        total += it->second;
    }
    return 100.0 * (current_year_sales / ((total / num_years) * days_left_year));
}

double SalesComparison::compareLastMonth() {
    double last_month = 0;
    std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > >::iterator dit;

    if (curr_m == 1) {
        if (years.find(curr_y - 1) != years.end()) {
            for (dit = sales_list->transaction_by_date[12].begin(); dit != sales_list->transaction_by_date[12].end();
                 dit++) {
                for (long unsigned int i = 0; i < dit->second[curr_y - 1].size(); i++) {
                    last_month += dit->second[curr_y - 1][i]->total_price;
                }
            }
            return 100.0 * (current_month_sales / (last_month * (1 - days_left_month)));
        }
        fprintf(stderr, "No sales made in the last month to compare to.\n");
        return 0;
    } else {
        if (years.find(curr_y - 1) != years.end()) {
            for (dit = sales_list->transaction_by_date[curr_m - 1].begin();
                 dit != sales_list->transaction_by_date[curr_m - 1].end(); dit++) {
                for (long unsigned int i = 0; i < dit->second[curr_y].size(); i++) {
                    last_month += dit->second[curr_y][i]->total_price;
                }
            }
            return 100.0 * (current_month_sales / (last_month * (1 - days_left_month)));
        }
        fprintf(stderr, "No sales made in the last month to compare to.\n");
        return 0;
    }
}

double SalesComparison::compareLast7Days() {
    double last_week;
    int days_in_last_month;
    std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > >::iterator dit;

    last_week = 0;
    if (curr_d < 7) {
        days_in_last_month = 7 - curr_d;
        if (curr_m == 1) {
            if (years.find(curr_y - 1) != years.end()) {
                if (sales_list->transaction_by_date[12][days_in_month[11] - days_in_last_month].find(curr_y - 1) !=
                    sales_list->transaction_by_date[12][days_in_month[11] - days_in_last_month].end()) {
                    dit = sales_list->transaction_by_date[12].find(days_in_month[11] - days_in_last_month);
                    for (int j = 0; j < days_in_last_month; j++) {
                        for (long unsigned int i = 0; i < dit->second[curr_y - 1].size(); i++) {
                            last_week += dit->second[curr_y - 1][i]->total_price;
                        }
                        dit++;
                    }
                    return 100.0 * (current_day_sales / ((last_week + current_month_sales - current_day_sales) / 7));
                }
            }
            fprintf(stderr, "No sales made in the last week to compare to.\n");
            return 0;
        } else {
            if (years.find(curr_y) != years.end()) {
                if (sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2] - days_in_last_month].find(
                        curr_y) !=
                    sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2] - days_in_last_month].end()) {
                    dit = sales_list->transaction_by_date[curr_m - 1].find(days_in_month[curr_m - 2] -
                                                                           days_in_last_month);
                    for (int j = 0; j < days_in_last_month; j++) {
                        for (long unsigned int i = 0; i < dit->second[curr_y].size(); i++) {
                            last_week += dit->second[curr_y][i]->total_price;
                        }
                        dit++;
                    }
                    return 100.0 * (current_day_sales / ((last_week + current_month_sales - current_day_sales) / 7));
                }
            }
            fprintf(stderr, "No sales made in the last week to compare to.\n");
            return 0;
        }
    } else {
        if (years.find(curr_y) != years.end()) {
            if (sales_list->transaction_by_date[curr_m][curr_d - 7].find(curr_y) !=
                sales_list->transaction_by_date[curr_m][curr_d - 7].end()) {
                dit = sales_list->transaction_by_date[curr_m].find(curr_d - 7);
                for (int j = 0; j < 7; j++) {
                    for (long unsigned int i = 0; i < dit->second[curr_y].size(); i++) {
                        last_week += dit->second[curr_y][i]->total_price;
                    }
                    dit++;
                }
                return 100.0 * (current_day_sales / (last_week / 7));
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
            if (years.find(curr_y - 1) != years.end()) {
                if (sales_list->transaction_by_date[12].find(days_in_month[11]) !=
                    sales_list->transaction_by_date[12].end()) {
                    if (sales_list->transaction_by_date[12][days_in_month[11]].find(curr_y - 1) !=
                        sales_list->transaction_by_date[12][days_in_month[11]].end()) {
                        for (long unsigned int i = 0;
                             i < sales_list->transaction_by_date[12][days_in_month[11]][curr_y - 1].size(); i++) {
                            yesterday_sales +=
                                sales_list->transaction_by_date[12][days_in_month[11]][curr_y - 1][i]->total_price;
                        }
                        return 100.0 * (current_day_sales / yesterday_sales);
                    }
                }
            }
            fprintf(stderr, "No sales made yesterday to compare to.\n");
            return 0;
        } else {
            if (years.find(curr_y) != years.end()) {
                if (sales_list->transaction_by_date[curr_m - 1].find(days_in_month[curr_m - 2]) !=
                    sales_list->transaction_by_date[curr_m - 1].end()) {
                    if (sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2]].find(curr_y) !=
                        sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2]].end()) {
                        for (long unsigned int i = 0;
                             i < sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2]][curr_y].size();
                             i++) {
                            yesterday_sales +=
                                sales_list->transaction_by_date[curr_m - 1][days_in_month[curr_m - 2]][curr_y][i]
                                    ->total_price;
                        }
                        return 100.0 * (current_day_sales / yesterday_sales);
                    }
                }
            }
            fprintf(stderr, "No sales made yesterday to compare to.\n");
            return 0;
        }
    } else {
        if (years.find(curr_y) != years.end()) {
            if (sales_list->transaction_by_date[curr_m].find(curr_d - 1) !=
                sales_list->transaction_by_date[curr_m].end()) {
                if (sales_list->transaction_by_date[curr_m][curr_d - 1].find(curr_y) !=
                    sales_list->transaction_by_date[curr_m][curr_d - 1].end()) {
                    for (long unsigned int i = 0;
                         i < sales_list->transaction_by_date[curr_m][curr_d - 1][curr_y].size(); i++) {
                        yesterday_sales += sales_list->transaction_by_date[curr_m][curr_d - 1][curr_y][i]->total_price;
                    }
                    return 100.0 * (current_day_sales / yesterday_sales);
                }
            }
        }
        fprintf(stderr, "No sales made yesterday to compare to.\n");
        return 0;
    }
}

void SalesComparison::suggestSale() {
    double worst_perc;
    unsigned long worst_id;
    std::string ret;
    std::map<unsigned long, double>::iterator it;
    std::vector<std::pair<unsigned long, double> > worst_vector;

    worst_perc = 1000000000000000000000.0;
    worst_id = -1;
    for (it = current_month_item_ids.begin(); it != current_month_item_ids.end(); it++) {
        if (it->second / (item_ids_by_month[curr_m][it->first] * (1 - days_left_month)) < worst_perc) {
            worst_perc = it->second / (item_ids_by_month[curr_m][it->first] * (1 - days_left_month));
            worst_id = it->first;
            if (worst_perc <= 0.85) worst_vector.push_back(std::make_pair(worst_id, worst_perc));
        }
    }

    if (worst_vector.size() != 0) {
        for (size_t i = 0; i < worst_vector.size(); i++) {
            printf(
                "We suggest a sale on item id %lu.\n"
                "Yours sales this month are %.2f%% of the average from this month in previous years.\n",
                worst_vector[i].first, worst_vector[i].second);
        }
    } else {
        printf("All items are selling well.\nNo sale suggested.\n");
    }
}

void SalesComparison::suggestSaleGUI() {
    double worst_perc;
    unsigned long worst_id;
    std::string ret;
    std::map<unsigned long, double>::iterator it;
    std::vector<std::pair<unsigned long, double> > worst_vector;

    worst_perc = 1000000000000000000000.0;
    worst_id = -1;
    for (it = current_month_item_ids.begin(); it != current_month_item_ids.end(); it++) {
        if (it->second / (item_ids_by_month[curr_m][it->first] * (1 - days_left_month)) < worst_perc) {
            worst_perc = it->second / (item_ids_by_month[curr_m][it->first] * (1 - days_left_month));
            worst_id = it->first;
            if (worst_perc <= 0.85) worst_vector.push_back(std::make_pair(worst_id, worst_perc));
        }
    }

    if (worst_vector.size() != 0) {
        any_ss = true;
        ss1_avg = -1;
        ss2_avg = -1;
        ss3_avg = -1;
        if(worst_vector.size() >= 1) {
            ss1 = worst_vector[0].first;
            ss1_avg = worst_vector[0].second;
        }
        if(worst_vector.size() >= 2) {
            ss2 = worst_vector[1].first;
            ss2_avg = worst_vector[1].second;
        }
        if(worst_vector.size() >= 3) {
            ss3 = worst_vector[2].first;
            ss3_avg = worst_vector[2].second;
        }
        //for (size_t i = 0; i < worst_vector.size(); i++) {
            // printf(
            //     "We suggest a sale on item id %lu.\n"
            //     "Yours sales this month are %.2f%% of the average from this month in previous years.\n",
            //     worst_vector[i].first, worst_vector[i].second);
        // }
    } else {
        any_ss = false;
        // printf("All items are selling well.\nNo sale suggested.\n");
    }
}