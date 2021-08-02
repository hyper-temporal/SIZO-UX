#ifndef TREESTYLE_H
#define TREESTYLE_H

#include <QColor>
#include <QFont>
#include <QFontMetrics>

struct FontUser{
    int _fontSize,_fontSizeTitre;
    QFont _fontLabel, _fontTitre;
    QFontMetricsF _fmLabel, _fmTitre;
    FontUser()
        :_fontLabel("Helvetica",12)
        ,_fontTitre("Helvetica",24)
        ,_fmLabel(_fontLabel)
        ,_fmTitre(_fontTitre)
    {}
    void  setFontSize(double v){
        if(v<=0.0)return;
        _fontSize = v;
        _fontSizeTitre = 2.0 * v;
        _fontLabel =QFont ("Helvetica");
        _fontTitre =QFont ("Helvetica");
        _fontLabel.setPointSize(_fontSize);
        _fontTitre.setPointSize(_fontSizeTitre);
        _fmLabel = QFontMetrics(_fontLabel);
        _fmTitre = QFontMetrics(_fontTitre);
    }
};

struct TreeStyle{
    Qt::CursorShape
    _crVide,
    _crDeplacement,
    _crGrabInput,
    _crPlugOutput;
    QColor
    _c_fond,
    _c_connection,
    _c_tourBloc,
    _c_centre;

};

static QColor
_clr_backlite(200 ,180,220),
_clr_GrayLine(150 ,150,150),
_clr_Black (0,0,0),
_clr_White (255 ,255,255),
_clr_violet(180 ,0,255),
_clr_Red (255,0,0),
_clr_Orange (200,64,64),
_clr_Blue (128,200,255),
_clr_Green (128,255,200),
_clr_border (150,190,230)
;


#endif // TREESTYLE_H
