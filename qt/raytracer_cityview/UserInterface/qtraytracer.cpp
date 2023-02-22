#include <iostream>
#include <cstdio>
#include <QElapsedTimer>
#include <QImage>
#include <QPixmap>
#include <QPen>
#include <QEvent>
#include <QColor>
#include <QThreadStorage>
#include <QPainter>
#include <QOpenGLContext>
#include <QApplication>
#include <QScreen>
#include <QMutexLocker>

#include "Utilities/Matrix.h"
#include "qtraytracer.h"

#include <QMutex>


QColor DARK_GREY_COLOR(43, 44, 50);
QColor GREY_COLOR(143, 144, 150);
QColor RED_COLOR(200, 50, 0);

long long begintime = 0L;
long long endtime = 0L;

QVector<RenderPixel*>* pixels = nullptr;
long rendered = 0;
QMutex mutex;

void print_timer_now(QElapsedTimer& qet) { QMutexLocker locker(&mutex);  qDebug() << "Timer: " << qet.elapsed(); }
void print_pixel(const RenderPixel* px)  {
    QMutexLocker locker(&mutex);
    qDebug() << "Pixel: " << px->x << ", " << px->y << ", " << px->red << ", " << px->green << ", " << px->blue;
}
void pixels_rendered(int pixelsRendered) {
    QMutexLocker locker(&mutex);  qDebug() << "PIXELS RENDERED: " << pixelsRendered;
}

///******************************************************************************/
///********************* RenderThread *******************************************/
///******************************************************************************/

constexpr int renderNewPixelEvent_ID = 1234;
const QEvent::Type renderNewPixelEvent = (QEvent::Type)renderNewPixelEvent_ID;

class RenderNewPixelEvent : public QEvent {
public:
    RenderNewPixelEvent(RenderPixel* px)
    : QEvent((QEvent::Type)renderNewPixelEvent_ID), pixel(px) { }

    RenderPixel* render_pixel() const { return pixel; }
private:
    RenderPixel* pixel;
};
///******************************************************************************/
///********************* RenderThread *******************************************/
///******************************************************************************/
RenderThread::RenderThread(RenderCanvas* c, World* w)
    : world(w), canvas(c), timer(new QElapsedTimer()) {
//    qDebug() << __PRETTY_FUNCTION__;
}
void RenderThread::run() {
    //    qDebug() << __PRETTY_FUNCTION__;
    lastUpdateTime = 0;
    timer->start();
//    print_timer_now(*timer);

    started();
//    emit finished();
}
void RenderThread::started() {
    //    qDebug() << __PRETTY_FUNCTION__;
    timer->start();
//    print_timer_now(*timer);
//    world->render_scene(); //for bare bones ray tracer only
    world->camera_ptr->render_scene(*world);
}
void RenderThread::finished() {
    //    qDebug() << __PRETTY_FUNCTION__;
    notifyCanvas((*pixels)[0]);   // TODO: fix
    sendRenderCompleted();
}
//static int counter = 0;
void RenderThread::setPixel(int x, int y, int red, int green, int blue) {
    //    qDebug() << __PRETTY_FUNCTION__;
    RenderPixel* px = new RenderPixel(x, y, red, green, blue);
    pixels->push_back(px);

    if (++rendered % 10 == 0) {
        notifyCanvas(px);
//        usleep(300);
    }
}
void RenderThread::notifyCanvas(RenderPixel* px) {
    //    qDebug() << __PRETTY_FUNCTION__;
//    QSize oldSize(canvas->size());
//    QSize newSize(400, 400);
//    QResizeEvent* size_event = new QResizeEvent(newSize, oldSize);
//    qDebug() << "rendered: " << rendered;

    RenderNewPixelEvent* rnpe = new RenderNewPixelEvent(px);
    QApplication::postEvent(canvas, rnpe, Qt::HighEventPriority * 1000);

//    QApplication::postEvent(canvas, size_event, Qt::HighEventPriority * 1000);
}
///******************************************************************************/
///********************* RenderCanvas *******************************************/
///******************************************************************************/
RenderCanvas::RenderCanvas(QWindow*)
: w(nullptr), thread(nullptr), running(false), totalTimeRendering(0L),
 updateTimer(new QTimer(this)),
 timeRenderingThisPass(0L)
{
//    qDebug() << __PRETTY_FUNCTION__;
//    connect(&updateTimer, &QTimer::timeout, this, &RenderCanvas::onTimerUpdate);
    pixels = new QVector<RenderPixel*>();
    QVector<RenderPixel*>*& px = pixels;
    pixmap = QPixmap(400, 400);
    if (pixmap.isNull()) { qDebug() << "Pixmap creation failed";  QApplication::exit(); }
    for (int i = 0; i < 10; ++i) { px->push_back(new RenderPixel(50 * i, 399, 255, 255, 0)); }
//    bool success = image.load("maze.png", "PNG");

    update();
//    connect(&updateTimer, SIGNAL(timeout()), SLOT(onSendFoo()));
    updateTimer.setInterval(5000);
    updateTimer.setSingleShot(true);
    updateTimer.start();
    stopwatchTimer.start();

    onRenderStart();
}
RenderCanvas::~RenderCanvas() {
    //    qDebug() << __PRETTY_FUNCTION__;
    if (thread != nullptr)  {
        thread->quit();
        thread->wait();
        delete context;
    }
    if (w != nullptr)  { delete w; }
}
void RenderCanvas::setPixmap(QPixmap qpixmap) {
    //    qDebug() << __PRETTY_FUNCTION__;
    if (!pixmap.isNull()) { pixmap = QPixmap(); }  pixmap = qpixmap;
    update();
}
QPixmap RenderCanvas::getPixmap() {
    //    qDebug() << __PRETTY_FUNCTION__;
    if (!pixmap.isNull()) { return pixmap; }
    return QPixmap();
}
void RenderCanvas::initializeGL() {
    //    qDebug() << __PRETTY_FUNCTION__;
    initializeOpenGLFunctions();
    glClearColor(0.55, 0.55, 0.55, 1);
}

void RenderCanvas::paintGL() {
//    qDebug() << __PRETTY_FUNCTION__;
//    QPainter painter(this);
//    qDebug() << "rendering the image...";
////    const QRect rect(0, 0, 400, 400);
////    const QPoint pt(0, 0);
////    painter.drawPixmap(pt, *pixmap);
//    painter.end();
//    pixelsRendered = 0;
//    onNewPixel();
//    update();
}
void RenderCanvas::paintEvent(QPaintEvent*) {
//        qDebug() << __PRETTY_FUNCTION__;
    static bool saved = false;
    if (pixelsRendered == pixels->length()) { qDebug() << "nothing to paint";  return; }
//    qDebug() << "paintEvent -- still painting";

    QPainter p(this);
    pixmap.fill(RED_COLOR);
//    qDebug() << "attempting QPaint on pixmap";
//    QPainter p(pixmap);
    if (!p.isActive()) {
        qDebug() << "PAINTER FAILED";
        QApplication::exit();
    }
    for (int i = pixelsRendered; i < pixels->length(); ++i) {
        RenderPixel* px = (*pixels)[i];
        QPen pen = QPen(QColor(px->red, px->green, px->blue));
        p.setPen(pen);
        p.drawPoint(px->x, px->y);
        pixelsRendered++;

//        if (pixelsRendered % 10000 == 0) {
//            qDebug() << "rendered: " << pixelsRendered;
//        }
    }
//    qDebug() << pixelsRendered << " != " << pixelsToRender;
//    if (pixelsRendered >= pixelsToRender && !saved) {
//        qDebug() << "finished rendering pixmap!";
//        QPoint local = mapToGlobal(QPoint(0, 0));
//        QScreen* screen = QGuiApplication::primaryScreen();
//        pixmap = screen->grabWindow(this->winId(), local.x(), local.y(), 400, 400);
//        saved = true;
//        const QPoint pt(400, 200);
//        p.drawPixmap(pt, pixmap);
//    }
    update();
//    pixels->clear();
}
void RenderCanvas::customEvent(QEvent* event) {
    if (event->type() == renderNewPixelEvent_ID) {
        update();
    } else { OglWidget::customEvent(event); }
}
void RenderCanvas::onRenderPause() {
    //    qDebug() << __PRETTY_FUNCTION__;

    if (!updateTimer.isActive()) { qDebug() << "updateTimer is not active... returning...\n"; return; }
    updateTimer.stop();
    timeRenderingThisPass = stopwatchTimer.restart();  // returns elapsed time and restarts the timer
    totalTimeRendering += timeRenderingThisPass;
}
void RenderCanvas::onRenderStart() {
    //    qDebug() << __PRETTY_FUNCTION__;
    w = new World();
    qDebug() << "Status: Building world...";
    w->build();

    pixelsRendered = 0;
    pixelsToRender = w->vp.hres * w->vp.vres;
    updateTimer.start(250);
    stopwatchTimer.start();

    thread = new RenderThread(this, w);
    w->paintArea = thread;
    w->canvas = this;
    connect(thread, &RenderThread::sendRenderResumed,   this, &RenderCanvas::onRenderResume);
    connect(thread, &RenderThread::sendRenderCompleted, this, &RenderCanvas::onRenderCompleted);
    thread->start();
    thread->setPriority(QThread::LowPriority);
}
void RenderCanvas::resizeEvent(QResizeEvent*) {
    qDebug() << __PRETTY_FUNCTION__;
    pixelsRendered = 0;
    update();
}

void RenderCanvas::onRenderResume() {
    //    qDebug() << __PRETTY_FUNCTION__;
    if (thread != nullptr) { thread->start(); }  // Resume
    timeRenderingThisPass = 0L;
    stopwatchTimer.restart();
    updateTimer.start();
}
void RenderCanvas::onRenderCompleted() {
    //    qDebug() << __PRETTY_FUNCTION__;

    thread = nullptr;
    if (w != nullptr) { delete w;  w = nullptr; }
    if (!stopwatchTimer.isValid()) {
        return;
    }
    timeRenderingThisPass = stopwatchTimer.elapsed();
    totalTimeRendering += timeRenderingThisPass;
    stopwatchTimer.invalidate();
}
void RenderCanvas::onTimerUpdate() {
    //    qDebug() << __PRETTY_FUNCTION__;
    if (!stopwatchTimer.isValid()) { return; }
    float completed = (float)pixelsRendered / (float)pixelsToRender;     //percent

    long elapsed = stopwatchTimer.elapsed();
    float remaining = 1.0f - completed;
    long msecRemain = (long)(((double)elapsed / (completed*100)) * 100 * remaining);
    msecRemain = std::max(1L, msecRemain);
}



