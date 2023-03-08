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

#define OFFSET 2.0

MainWidget::~MainWidget() {}

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

#include <QtDebug>

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
  ulA.set_rotation( rotation );
  urA.set_rotation( rotation );
  blA.set_rotation( rotation );
  brA.set_rotation( rotation );

  ulB.set_rotation( rotation );
  urB.set_rotation( rotation );
  blB.set_rotation( rotation );
  brB.set_rotation( rotation );

  update();
}

void MainWidget::initializeGL() {
  double divisor = 2.5;
  ulA.set_xy( -OFFSET / divisor, OFFSET );
  urA.set_xy( OFFSET / divisor, OFFSET );
  blA.set_xy( -OFFSET / divisor, -OFFSET );
  brA.set_xy( OFFSET / divisor, -OFFSET );

  ulB.set_xy( -OFFSET, OFFSET / divisor );
  urB.set_xy( OFFSET, OFFSET / divisor );
  blB.set_xy( -OFFSET, -OFFSET / divisor );
  brB.set_xy( OFFSET, -OFFSET / divisor );

  ulA.initializeGL();
  urA.initializeGL();
  blA.initializeGL();
  brA.initializeGL();

  ulB.initializeGL();
  urB.initializeGL();
  blB.initializeGL();
  brB.initializeGL();

  timer.start( 12, this );
}

void MainWidget::initShaders() {
  ulA.initShaders();
  urA.initShaders();
  blA.initShaders();
  brA.initShaders();

  ulB.initShaders();
  urB.initShaders();
  blB.initShaders();
  brB.initShaders();
}

void MainWidget::initTextures() {
  ulA.initTextures();
  urA.initTextures();
  blA.initTextures();
  brA.initTextures();

  ulB.initTextures();
  urB.initTextures();
  blB.initTextures();
  brB.initTextures();
}

void MainWidget::resizeGL( int w, int h ) {
  ulA.resizeGL( w, h );
  urA.resizeGL( w, h );
  blA.resizeGL( w, h );
  brA.resizeGL( w, h );

  ulB.resizeGL( w, h );
  urB.resizeGL( w, h );
  blB.resizeGL( w, h );
  brB.resizeGL( w, h );
}

void MainWidget::paintGL() {
  //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ulA.paintGL();
  urA.paintGL();
  blA.paintGL();
  brA.paintGL();

  ulB.paintGL();
  urB.paintGL();
  blB.paintGL();
  brB.paintGL();
}
