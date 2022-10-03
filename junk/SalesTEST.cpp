#include <string>
#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

class Sale
{
friend class SaleList;
public:
    void add(unsigned intid,  unsigned int sn,  string& d,  unsigned int as, unsigned int p,  string& b,  string& sell);
protected:
    unsigned int sale_number;
    unsigned int identification;
    //Date date;
    string date;
    unsigned int amount_sold;
    unsigned int price;
    std::string buyer;
    std::string seller;
};

void Sale::add( unsigned int id,  unsigned int sn,  string& d,  unsigned int as,  unsigned int p,  string& b,  string& sell){
    identification = id;
    sale_number = sn;
    date = d;
    amount_sold = as;
    price = p;
    buyer = b;
    seller = sell;
}

class SaleList
{
public:
    vector<Sale> sales;
    void save();
};

void SaleList::save()
{
    ofstream fout;
    fout.open("junk.txt");
    fout << "ID, Sale Number, Date, Amount Sold, Price, Buyer, Seller"
    for(int i = 0; i < sales.size(); i++){
        fout << sales[i].identification << ", " << sales[i].sale_number << ", " << sales[i].date << ", " <<  sales[i].amount_sold << ", " <<  sales[i].price << ", " <<  sales[i].buyer << ", " <<  sales[i].seller << endl;
    }
    fout.close();
}

int main()
{
    string line;

    SaleList sl;
    Sale s;

    unsigned int ID;
    unsigned int SN;
    string date;
    unsigned int AS;
    unsigned int price;
    string buyer;
    string seller;

    int additions;
    int i;

    ofstream fout;
    cout << " INPUT AMOUNT OF SALES BEING ADDED: ";
    cin >> additions;
    cout << "INPUT: ITEM_ID SALE_NUMBER DATE AMOUNT_SOLD PRICE BUYER SELLER" << endl;

    for(i = 0; i < additions; i++){
        // change to fscanf
        cin >> ID >> SN >> date >> AS >> price >> buyer >> seller;

        s.add(ID, SN, date, AS, price, buyer, seller);
        sl.sales.push_back(s);
    }
    

    fout.open("junk.txt");

    sl.save();
    
    fout.close();

    return 0;
}