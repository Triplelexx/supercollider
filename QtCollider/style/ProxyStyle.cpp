#include "ProxyStyle.hpp"

#include <QWebView>
#include <QStyleOptionSlider>
#include <QPainter>

using namespace QtCollider;

#ifdef Q_OS_MAC
void ProxyStyle::drawComplexControl ( ComplexControl ctrl, const QStyleOptionComplex *opt,
                                      QPainter *p, const QWidget * w) const
{
  // FIXME: this is a workaround for the WebKit bug #104116 (or a variation on it).
  if( ctrl == QStyle::CC_ScrollBar
      && qobject_cast<const QWebView*>(w) != 0
      && opt->type == QStyleOption::SO_Slider )
  {
    // WebKit tries to hide scrollbars, but mistakenly hides QWebView - NULL-ify styleObject to prevent.
    const QStyleOptionSlider *optSlider = static_cast<const QStyleOptionSlider*>(opt);
    QStyleOptionSlider opt2( *optSlider );
    opt2.styleObject = NULL;

    QProxyStyle::drawComplexControl( ctrl, &opt2, p, w );

    return;
  }

  QProxyStyle::drawComplexControl( ctrl, opt, p, w );
}
#endif

int ProxyStyle::styleHint ( StyleHint hint, const QStyleOption * option,
                            const QWidget * widget, QStyleHintReturn * returnData ) const
{
  switch( hint ) {
    case QStyle::SH_Slider_AbsoluteSetButtons:
      return Qt::LeftButton;
    case QStyle::SH_Slider_PageSetButtons:
      return Qt::NoButton;
    case QStyle::SH_ScrollBar_Transient:
      return 1;
    default:
      return QProxyStyle::styleHint( hint, option, widget, returnData );
  }
}
