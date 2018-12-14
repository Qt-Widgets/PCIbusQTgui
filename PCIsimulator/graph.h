#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QString>
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = 0);
    ~graph();
    int NumberofPoints(QString signal);
    QChart* chartsetup(int numberofClockCycles);
    QLineSeries* GetPoints(QString signal,int SignalIndex);
    void DrawSignals(QVector<QString> signal,int NumberOfCycles);

private:
    Ui::graph *ui;
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
};

#endif // GRAPH_H
