#ifndef SALES_COMPARISON_HPP
#define SALES_COMPARISON_HPP

#include <set>

#include "Sales.hpp"

class SalesComparison {
   public:
    /*
     * @brief The default constructor should not be called.
     */
    SalesComparison();

    /*
     * @brief This constructor must be called after your sales data has been loaded for the past. It
     *   will parse the sales data into total sales by year and by month.
     * @param SaleList - the current sales list that is being used by the inventory manager.
     */
    void setup(std::shared_ptr<SaleList>);

    /*
     * @brief This will call the comparison function given and print it's return in an organized way.
     * @param std::string - name of function to call.
     * @param int - used number of years to compare.
     */
    void printComparison(std::string, int);

    /*
     * @brief This will call all comparison functions and print their returns in an organized way.
     */
    void printAllComparisons();

    /*
     * @brief The suggestSale function will compare all items sold this month compared to the average sales of
     *  that item in that month and offer a suggested sale if one of them is below a certain threshold.
     *  @return string - suggested item id and name
     */
    void suggestSale();

   private:
    /*
     * @brief The compareBy functions will compare sales from your current year or month with data from all
     *  previous ones.
     * @return %difference of current / (past * % days past) .
     */
    double compareByYear();
    double compareByMonth();

    /*
     * @brief The compareLast functions will compare sales from your current year, month, or day with data from the
     * past 10 years, 5 years, month, 7days, or just yesterday.
     * @param int - number of years to compare
     * @return %difference of current / past
     */
    double compareLastXYears(int);
    double compareLastMonth();
    double compareLast7Days();
    double compareYesterday();

    std::shared_ptr<SaleList> sales_list;
    std::set<unsigned long> years;         // This holds the years that have sales stored.
    std::map<int, double> sales_by_year;   // This will store all past sales totals based on the year.
    double avg_by_year;                    // This will store the average of all past sales totals based on the year.
    std::map<int, double> sales_by_month;  // This will store all past sales totals based on the month of the year.
    std::map<int, std::map<unsigned long, double> > item_ids_by_month;  // This stores item totals averaged by month.
    std::map<unsigned long, double> current_month_item_ids;             // This stores this month's total items by id.
    std::map<int, double> avg_by_month;  // This will store the average of all past sales totals based on the month.
    double current_year_sales = 0;       // This will store the running sales total of the current year.
    double current_month_sales = 0;      // This will store the running sales total of the current month.
    double current_day_sales = 0;        // This will store the running sales total of the day.
    unsigned int curr_y, curr_m, curr_d;
    double days_left_year;
    double days_left_month;
    std::vector<int> days_in_month;
};

#endif /* SALES_COMPARISON_HPP */