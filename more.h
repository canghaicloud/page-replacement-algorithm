#ifndef MORE_H
#define MORE_H

#include <QWidget>

namespace Ui {
class more;
}

class more : public QWidget
{
    Q_OBJECT

public:
    explicit more(QWidget *parent = nullptr, QString lfu_result = "", QString clock_result = "");
    ~more();

private:
    Ui::more *ui;
    QString lfu_result;
};

#endif // MORE_H
