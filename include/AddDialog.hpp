#ifndef ADD_DIALOG_HPP
#define ADD_DIALOG_HPP

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

class QLineEdit;
class QLabel;

class AddDialog : public QDialog
{
public:
    explicit AddDialog(QWidget *parent = nullptr);

    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

    virtual ~AddDialog() {};
private:
    QList<QLineEdit*> fields;
};

#endif // ADD_DIALOG_HPP
