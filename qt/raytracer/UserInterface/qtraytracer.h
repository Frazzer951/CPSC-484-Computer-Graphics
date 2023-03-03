
#ifndef _QTRAYTRACER_H_
#define _QTRAYTRACER_H_

//#include <wx/wx.h>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include <QPixmap>
#include <QObject>
#include <QResizeEvent>
#include <vector>
#include "oglwidget.h"
#include "World/World.h"


class RenderCanvas;

//============================================================
// RenderPixel
//============================================================
//
struct RenderPixel {
   RenderPixel(int xval, int yval, int redval, int greenval, int blueval)
       : x(xval), y(yval), red(redval), green(greenval), blue(blueval) { }

   int x, y;
   int red, green, blue;
};


//============================================================
// RenderThread
//============================================================
//
class RenderThread : public QThread {
    Q_OBJECT
public:
   RenderThread(RenderCanvas* c, World* w);

   void started();
   void finished();
   void setPixel(int x, int y, int red, int green, int blue);
   void run();

signals:
   void sendRenderResumed();
   void sendRenderCompleted();

protected:
   void resizeEvent(QResizeEvent *event);

private:
   void notifyCanvas(RenderPixel* px);

private:
   World* world;
   RenderCanvas* canvas;
   QElapsedTimer* timer;

   long lastUpdateTime;
};


//============================================================
// RenderCanvas
//============================================================
//
class RenderCanvas: public OglWidget {
    Q_OBJECT

public:
   RenderCanvas(QWindow *parent=nullptr);
   virtual ~RenderCanvas();

   void setPixmap(QPixmap pixmap);
   QPixmap getPixmap();

   void initializeGL() override;
   void paintGL() override;
//   void resize(int w, int h);
   void resizeEvent(QResizeEvent* e) override;
   void paintEvent(QPaintEvent* event) override;
   void customEvent(QEvent* event) override;

//   void newPixel(int x, int y, int red, int green, int blue);
//   void cleanup();

signals:
   void sendNewPixel();

public slots:
   void onRenderStart();
   void onRenderPause();
   void onRenderResume();
   void onRenderCompleted();        // use QEvent& e  ?
   void onTimerUpdate();            // use QTimerEvent& e ?

//   void onNewPixel(const QVector<RenderPixel*>& pixelsUpdate);
//    void onNewPixel();

protected:
   QPixmap pixmap;
   World* w;

private:
   RenderThread* thread;
   QElapsedTimer stopwatchTimer;
   QTimer updateTimer;

   bool running;
   long totalTimeRendering;
   long timeRenderingThisPass;

   long pixelsRendered;
   long pixelsToRender;
};



#endif
