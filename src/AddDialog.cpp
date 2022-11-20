#include "AddDialog.hpp"

AddDialog::AddDialog(QWidget *parent) : QDialog(parent)
{
    auto layout = new QFormLayout(this);

    auto name = new QLabel("Name:", this);
    auto name_edit = new QLineEdit(this);
    layout->addRow(name, name_edit);

    auto id = new QLabel("ID:", this);
    auto id_edit = new QLineEdit(this);
    layout->addRow(id, id_edit);

    auto category = new QLabel("Category:", this);
    auto cat_edit = new QLineEdit(this);
    layout->addRow(category, cat_edit);

    auto sub_category = new QLabel("Sub Category:", this);
    auto sub_edit = new QLineEdit(this);
    layout->addRow(sub_category, sub_edit);

    auto location = new QLabel("Location:", this);
    auto location_edit = new QLineEdit(this);
    layout->addRow(location, location_edit);

    auto quantity = new QLabel("Quantity:", this);
    auto quantity_edit = new QLineEdit(this);
    layout->addRow(quantity, quantity_edit);

    auto backorder = new QLabel("Backorder:", this);
    auto backorder_edit = new QLineEdit(this);
    layout->addRow(backorder, backorder_edit);

    auto sale_price = new QLabel("Sale Price:", this);
    auto sale_price_edit = new QLineEdit(this);
    layout->addRow(sale_price, sale_price_edit);

    auto tax = new QLabel("Tax:", this);
    auto tax_edit = new QLineEdit(this);
    layout->addRow(tax, tax_edit);

    auto buy_cost = new QLabel("Purchase Cost:", this);
    auto buy_cost_edit = new QLineEdit(this);
    layout->addRow(buy_cost, buy_cost_edit);

    auto expiration_date = new QLabel("Expiration Date:", this);
    auto exp_date_edit = new QLineEdit(this);
    layout->addRow(expiration_date, exp_date_edit);

    fields << name_edit << id_edit << cat_edit << sub_edit << location_edit << quantity_edit << backorder_edit << sale_price_edit << tax_edit << buy_cost_edit << exp_date_edit;

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    layout->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &AddDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &AddDialog::reject);
    Q_ASSERT(conn);

    setLayout(layout);
}

QStringList AddDialog::getStrings(QWidget *parent, bool *ok)
{
    AddDialog *dialog = new AddDialog(parent);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            list << field->text();
        }
    }

    dialog->deleteLater();

    return list;
}