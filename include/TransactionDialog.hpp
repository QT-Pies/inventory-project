#ifndef TRANSACTION_DIALOG_HPP
#define TRANSACTION_DIALOG_HPP

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

class QLineEdit;
class QLabel;

class TransactionDialog : public QDialog
{
public:
    explicit TransactionDialog(QWidget *parent = nullptr);

    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

    virtual ~TransactionDialog() {};
private:
    QList<QLineEdit*> fields;
};

#endif // TRANSACTION_DIALOG_HPP
