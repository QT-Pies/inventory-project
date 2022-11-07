#ifndef SALES_COMPARISON_HPP
#define SALES_COMPARISON_HPP

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
     * @param int number of years to compare
     * @return %difference of current / past.
     */
    double compareLastXYears(int);
    double compareLastMonth();
    double compareLast7Days();
    double compareYesterday();

    std::shared_ptr<SaleList> salesList;
    std::map<int, double> salesByYear;   // This will store all past sales totals based on the year.
    double avgByYear;                    // This will store the average of all past sales totals based on the year.
    std::map<int, double> salesByMonth;  // This will store all past sales totals based on the month of the year.
    std::map<int, double> avgByMonth;    // This will store the average of all past sales totals based on the month.
    double currentYearSales;             // This will store the running sales total of the current year.
    double currentMonthSales;            // This will store the running sales total of the current month.
    double currentDaySales;              // This will store the running sales total of the day.
    unsigned int curr_y, curr_m, curr_d;
    double daysLeftYear;
    double daysLeftMonth;
    std::vector<int> daysInMonth;
};

#endif /* SALES_COMPARISON_HPP */