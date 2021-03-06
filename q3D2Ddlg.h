#ifndef Q3D2DDLG_H
#define Q3D2DDLG_H

//Qt
#include <QDialog>

//3D2D
#include "ccWorkSite.h"
#include "ccPoint.h"

//qCC
#include <ccGLWindow.h>
#include "ccMainAppInterface.h"
#include "ccPickingListener.h"


namespace Ui {
class q3D2DDlg;
}

class q3D2DDlg : public QDialog, public ccPickingListener
{
    Q_OBJECT

public:
    explicit q3D2DDlg(QWidget *parent = 0);
    ~q3D2DDlg();
    ccGLWindow* win;
    ccMainAppInterface* m_app;



private:
    Ui::q3D2DDlg *ui;
    ccWorkSite *currentWorkSite;
    ccPoint *currentPoint;
    ccPickingHub* m_pickingHub;


public slots:
    void load();
    void reproj();
    void displayImg();
    void selectPt();

protected slots:
    //inherited from ccPickingListener
    virtual void onItemPicked(const ccPickingListener::PickedItem& pi);

    //picked point callback (called by the above function)
    void pointPicked(ccHObject* entity, unsigned itemIdx, int x, int y, const CCVector3& P, CCVector3 N);

};

#endif // Q3D2DDLG_H
