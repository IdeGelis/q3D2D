#ifndef Q3D2DDLG_H
#define Q3D2DDLG_H

#include <QDialog>

namespace Ui {
class q3D2DDlg;
}

class q3D2DDlg : public QDialog
{
    Q_OBJECT

public:
    explicit q3D2DDlg(QWidget *parent = 0);
    ~q3D2DDlg();

private:
    Ui::q3D2DDlg *ui;
};

#endif // Q3D2DDLG_H
