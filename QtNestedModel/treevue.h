#ifndef TREEVUE_H
#define TREEVUE_H


#include <QQuickPaintedItem>

class DrTreeVue:
        public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY( Qt::CursorShape  curseurDeplacement     READ    getCrDeplacement    WRITE setCrDeplacement )
    Q_PROPERTY( Qt::CursorShape  curseurGrabInput       READ    getCrGrabInput      WRITE setCrGrabInput   )
    Q_PROPERTY( Qt::CursorShape  curseurPlugOutput      READ    getCrPlugOutput     WRITE setCrPlugOutput  )
    Q_PROPERTY( Qt::CursorShape  curseurVide            READ    getCrVide           WRITE setCrVide        )

    Q_PROPERTY( QColor  c_connection  READ    get_c_connection   WRITE set_c_connection     )
    Q_PROPERTY( QColor  c_fond        READ    get_c_fond         WRITE set_c_fond           )
    Q_PROPERTY( QColor  c_data_tour   READ    get_c_tour_bloc    WRITE set_c_tour_bloc      )
    Q_PROPERTY( QColor  c_centre      READ    get_c_centre       WRITE set_c_centre         )
public:
    DrTreeVue(QQuickItem *p=nullptr);
    virtual Qt::CursorShape getCrVide       ()          =0;
    virtual Qt::CursorShape getCrDeplacement()          =0;
    virtual Qt::CursorShape getCrGrabInput  ()          =0;
    virtual Qt::CursorShape getCrPlugOutput ()          =0;
    virtual void setCrVide       (Qt::CursorShape cu)   =0;
    virtual void setCrDeplacement(Qt::CursorShape cu)   =0;
    virtual void setCrGrabInput  (Qt::CursorShape cu)   =0;
    virtual void setCrPlugOutput (Qt::CursorShape cu)   =0;
    virtual void    set_c_centre        (QColor sty)    =0;
    virtual void    set_c_fond          (QColor sty)    =0;
    virtual void    set_c_tour_bloc     (QColor sty)    =0;
    virtual void    set_c_connection    (QColor sty)    =0;
    virtual QColor  get_c_centre        ()const         =0;
    virtual QColor  get_c_fond          ()const         =0;
    virtual QColor  get_c_tour_bloc     ()const         =0;
    virtual QColor  get_c_connection    ()const         =0;

};


#endif // TREEVUE_H
