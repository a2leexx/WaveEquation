/*  mainwindow.h
 *
 *  Numerical simulation of wave propagation
 *
 *  Copyright (C) 2020 Alexander Zuev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>

namespace Ui {
class MainWindow;
}

const int N = 80;
const float timestep = 0.1f;
const float scale = 0.1f;
const float k = 0.2f;
const float p = 1;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void calculate();



protected:
    void paintEvent(QPaintEvent *event);


private:
    bool border(int, int);
    float GetDUbyDT(int, int, int);
    float GetDUbyDX(int, int, int);
    float GetDUbyDY(int, int, int);

    Ui::MainWindow *ui;
    int iter = 0;
    float u[N][N];
    float u1[N][N];
    float u2[N][N];
    float n_u2[N][N];
};

#endif // MAINWINDOW_H
