#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Sale
{
friend class SaleList;
public:
    Sale(Item*, const unsigned int, const std::string&, const unsinged int, const std::string&, const std::string&);
    virtual ~Sale() = default;
    virtual void print() = 0;
    void save();
protected:
    Item * item;
    unsigned int sale_number;
    Date date;
    unsigned_int amount_sold;
    std::string buyer;
    std::string seller;
};

class SaleList
{
public:
    vector<Sale> sales;
};

int main(){
    char read;
    vector<

    cout << "READ FROM FILE y/n\n";
    cin >> read;

    if(read == y){

    }
}