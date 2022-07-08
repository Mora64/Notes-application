#ifndef CUSTOMCOLORPLACEHOLDERLINEEDIT_H
#define CUSTOMCOLORPLACEHOLDERLINEEDIT_H
#include<QLineEdit>
#include <QPainter>
class CustomColorPlaceholderLineEdit : public QLineEdit
{
public:
    CustomColorPlaceholderLineEdit(QWidget * parent = 0) : QLineEdit(parent) { color = QColor(0,0,0,128); }
    void setCustomPlaceholderText(const QString &text) { this->mText = text; }
    const QString &customPlaceholderText() const { return mText; }
    void setCustomPlaceholderColor(const QColor &color) { this->color = color; }
    const QColor &customPlaceholderColor() const { return color; }
    void paintEvent(QPaintEvent *event) {
        QLineEdit::paintEvent(event);
        if (!hasFocus() && text().isEmpty() && !mText.isEmpty()) {
            // QLineEdit's own placeholder clashes with ours.
            Q_ASSERT(placeholderText().isEmpty());
            QPainter p(this);
            p.setPen(color);
            QFontMetrics fm = fontMetrics();
            int minLB = qMax(0, -fm.minLeftBearing());
            QRect lineRect = this->rect();
            QRect ph = lineRect.adjusted(minLB + 3, 0, 0, 0);
            QString elidedText = fm.elidedText(mText, Qt::ElideRight, ph.width());
            p.drawText(ph, Qt::AlignVCenter, elidedText);
        }
    }
private:
    QString mText;
    QColor color;
};
#endif // CUSTOMCOLORPLACEHOLDERLINEEDIT_H
