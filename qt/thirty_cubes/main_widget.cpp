/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QMouseEvent>

#include <cmath>
#include "main_widget.h"

#include <QtDebug>

#define OFFSET   6
#define RADIUS   20

#define CUBES    30

MainWidget::MainWidget() : QOpenGLWidget(), texture_cubes() {
    qDebug() << "constructing " << CUBES << " texture_cubes...";
    for (int i = 0; i < CUBES; ++i) {
        texture_cubes.push_back(new TextureCube(0, 0));
    }
    qDebug() << "vector.size() is: " << texture_cubes.size();
}

MainWidget::~MainWidget() {
    qDebug() << "destroying " << texture_cubes.size() << " texture_cubes...";
    for (auto p : texture_cubes) {
        delete p;
    }
}

void MainWidget::mousePressEvent(QMouseEvent* e) {
            // Save mouse press position
    mousePressPosition = QVector2D(e->position());
}

void MainWidget::mouseReleaseEvent(QMouseEvent* e) {
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

            // Rotation axis is perpendicular
            //     to the mouse position difference vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

            // Accelerate angular speed relative
            //     to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

            // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    angularSpeed += acc;    // Increase angular speed
}

void MainWidget::timerEvent(QTimerEvent*) {
    // Decrease angular speed (friction)
    static bool accel = true;

    if (accel && angularSpeed > 10.0) { accel = !accel;
    } else if (accel) { angularSpeed *= 1.01;
    } else if (!accel && angularSpeed < 0.5) { accel = !accel;
    } else {
            angularSpeed *= 0.99;
    }

    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    for (auto p : texture_cubes) {
        p->set_rotation(rotation);
    }

    update();
}

void MainWidget::initializeGL() {
    for (int i = 0; i < CUBES; ++i) {
        double x = RADIUS * cos(i * 2.0 * M_PI / CUBES);
        double y = RADIUS * sin(i * 2.0 * M_PI / CUBES);

        auto p = texture_cubes[i];
        p->set_xy(x, y);
        p->initializeGL();
    }


    timer.start(12, this);
}

void MainWidget::initShaders() {
    for (auto p : texture_cubes) {
        p->initShaders();
    }
}

void MainWidget::initTextures() {
    for (auto p : texture_cubes) {
        p->initTextures();
    }
}

void MainWidget::resizeGL(int w, int h) {
    w /= 4;
    h /= 4;

    for (auto p : texture_cubes) {
        p->resizeGL(w, h);
    }
}


void MainWidget::paintGL() {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto p : texture_cubes) {
        p->paintGL();
    }
}
