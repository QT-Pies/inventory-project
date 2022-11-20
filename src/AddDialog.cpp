#include "AddDialog.hpp"

AddDialog::AddDialog(QWidget *parent) : QDialog(parent)
{
    QFormLayout *lytMain = new QFormLayout(this);

    for (int i = 0; i < 4; ++i)
    {
        QLabel *tLabel = new QLabel(QString("Text_%1:").arg(i), this);
        QLineEdit *tLine = new QLineEdit(this);
        lytMain->addRow(tLabel, tLine);

        fields << tLine;
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &AddDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &AddDialog::reject);
    Q_ASSERT(conn);

    setLayout(lytMain);
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