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
#include <QtDebug>

#include <cmath>
#include "main_widget.h"

#define OFFSET 6.0
#define RADIUS 20
#define CUBES  30

MainWidget::MainWidget() : QOpenGLWidget() {
  qDebug() << "constructing " << CUBES << " texture cubes...";
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes.push_back( new TextureCube( 0, 0 ) ); }
}

MainWidget::~MainWidget() {
  qDebug() << "destroying " << CUBES << " texture cubes...";
  for ( int i = 0; i < CUBES; i++ ) { delete texture_cubes[i]; }
}

void MainWidget::mousePressEvent( QMouseEvent *e ) {
  // Save mouse press position
  mousePressPosition = QVector2D( e->position() );
}

void MainWidget::mouseReleaseEvent( QMouseEvent *e ) {
  // Mouse release position - mouse press position
  QVector2D diff = QVector2D( e->position() ) - mousePressPosition;

  // Rotation axis is perpendicular
  //     to the mouse position difference vector
  QVector3D n = QVector3D( diff.y(), diff.x(), 0.0 ).normalized();

  // Accelerate angular speed relative
  //     to the length of the mouse sweep
  qreal acc = diff.length() / 100.0;

  // Calculate new rotation axis as weighted sum
  rotationAxis = ( rotationAxis * angularSpeed + n * acc ).normalized();
  angularSpeed += acc;    // Increase angular speed
}

void MainWidget::timerEvent( QTimerEvent * ) {
  // Decrease angular speed (friction)
  // angularSpeed *= 0.99;

  static bool accel = true;

  if ( ( accel && angularSpeed > 10.0 ) || ( !accel && angularSpeed < 0.5 ) ) {
    accel = !accel;
  } else if ( accel ) {
    angularSpeed *= 1.01;
  } else {
    angularSpeed *= 0.99;
  }

  // Stop rotation when speed goes below threshold
  if ( angularSpeed < 0.01 ) {
    angularSpeed = 0.0;
  } else {
    qDebug() << "angularSpeed: " << angularSpeed;
  }

  rotation = QQuaternion::fromAxisAndAngle( rotationAxis, angularSpeed ) * rotation;
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes[i]->set_rotation( rotation ); }

  update();
}

void MainWidget::initializeGL() {
  double theta = ( 2 * M_PI ) / (double) CUBES;

  for ( int i = 0; i < CUBES; i++ ) {
    // x = r cos(theta) and y = r sin(theta)
    double x = RADIUS * std::cos( i * theta );
    double y = RADIUS * std::sin( i * theta );
    texture_cubes[i]->set_xy( x, y );
    texture_cubes[i]->initializeGL();
  }

  timer.start( 12, this );
}

void MainWidget::initShaders() {
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes[i]->initShaders(); }
}

void MainWidget::initTextures() {
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes[i]->initTextures(); }
}

void MainWidget::resizeGL( int w, int h ) {
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes[i]->resizeGL( w, h ); }
}

void MainWidget::paintGL() {
  //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for ( int i = 0; i < CUBES; i++ ) { texture_cubes[i]->paintGL(); }
}
