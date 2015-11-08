#include "lightcontrolwidget.h"
#include "ui_lightcontrolwidget.h"
#include "hsvpalette.h"
#include <QLinearGradient>
#include <QBrush>
#include <QDebug>
#include <QPicture>

LightControlWidget::LightControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControlWidget)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    //scene = new QGraphicsScene(this);
    //ui->graphicsView->setScene(scene);


    //QPicture *hsvSwatch;

    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->btnSelectPreset,0,0);
    contentLayout->addWidget(ui->lblActivePreset,0,2);

    HSVPalette *hsvSwatch = new HSVPalette(this);
    contentLayout->addWidget(hsvSwatch,1,0,4,4);
    connect(hsvSwatch,SIGNAL(changed()),this,SLOT(updateHSVSelected()));

    /*
    QLinearGradient *lg = new QLinearGradient(0,0,360,0);

    QBrush *brush = new QBrush();

    QPainter hsvSwatchPainter(&hsvSwatch);

    for(float h = 0.1f; h <= 1.0f; h += 0.01f)
        {
           QColor gradient(h,1.0,1.0);
           hsvSwatchPainter.setPen(gradient);
           hsvSwatchPainter.setBrush(gradient);
           QLine *line = new QLine(22,0,22,300);
           hsvSwatchPainter.drawLine(*line);

    }

    hsvSwatchPainter.end();
*/
    /*
    QColor hsvColor[6];
    hsvColor[0].setHsv(0, 255, 255);
    hsvColor[1].setHsv(60, 255, 255);
    hsvColor[2].setHsv(120, 255, 255);
    hsvColor[3].setHsv(180, 255, 255);
    hsvColor[4].setHsv(240, 255, 255);
    hsvColor[5].setHsv(300, 255, 255);
    //qDebug() << gradient.red() << h;
    QString styleH = QString("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0,") +
                     QString("stop:0.000 rgba(%1, %2, %3, 255),").arg( hsvColor[0].red() ).arg( hsvColor[0].green() ).arg( hsvColor[0].blue() ) +
                     QString("stop:0.166 rgba(%1, %2, %3, 255),").arg( hsvColor[1].red() ).arg( hsvColor[1].green() ).arg( hsvColor[1].blue() ) +
                     QString("stop:0.333 rgba(%1, %2, %3, 255),").arg( hsvColor[2].red() ).arg( hsvColor[2].green() ).arg( hsvColor[2].blue() ) +
                     QString("stop:0.500 rgba(%1, %2, %3, 255),").arg( hsvColor[3].red() ).arg( hsvColor[3].green() ).arg( hsvColor[3].blue() ) +
                     QString("stop:0.666 rgba(%1, %2, %3, 255),").arg( hsvColor[4].red() ).arg( hsvColor[4].green() ).arg( hsvColor[4].blue() ) +
                     QString("stop:0.833 rgba(%1, %2, %3, 255),").arg( hsvColor[5].red() ).arg( hsvColor[5].green() ).arg( hsvColor[5].blue() ) +
                     QString("stop:1.000 rgba(%1, %2, %3, 255));").arg( hsvColor[0].red() ).arg( hsvColor[0].green() ).arg( hsvColor[0].blue() );
    ui->graphicsView->setStyleSheet(styleH);

    connect(ui->graphicsView,SIGNAL()

    //lg->setColorAt(1,Qt::white);
    //QLine *line = new QLine(h,0,h,300);
    //colorPalette->setPen(gradient);
    //      }
    //
    //   QRect rec(10,20,200,200);

    //scene->setBackgroundBrush(*lg);
    */
}

LightControlWidget::~LightControlWidget()
{
    delete ui;
}

void LightControlWidget::paintEvent(QPaintEvent *pe)
{

    QPainter painter(this);



}

void LightControlWidget::updateHSVSelected()
{

    qDebug() << "EVENT";
}
