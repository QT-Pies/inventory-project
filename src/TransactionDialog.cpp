#include "TransactionDialog.hpp"

TransactionDialog::TransactionDialog(QWidget *parent) : QDialog(parent)
{
    auto layout = new QFormLayout(this);

    auto name = new QLabel("Name:", this);
    auto name_edit = new QLineEdit(this);
    layout->addRow(name, name_edit);

    auto id = new QLabel("ID:", this);
    auto id_edit = new QLineEdit(this);
    layout->addRow(id, id_edit);

    auto quantity = new QLabel("Quantity:", this);
    auto quantity_edit = new QLineEdit(this);
    layout->addRow(quantity, quantity_edit);

    fields << name_edit << id_edit << quantity_edit;

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    layout->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &TransactionDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &TransactionDialog::reject);
    Q_ASSERT(conn);

    setLayout(layout);
}

QStringList TransactionDialog::getStrings(QWidget *parent, bool *ok)
{
    TransactionDialog *dialog = new TransactionDialog(parent);

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