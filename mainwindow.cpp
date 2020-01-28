/*  mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer * ptimer = new QTimer(this);

    connect(ptimer, SIGNAL(timeout()), SLOT(calculate()));

    ptimer->start(100);

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            u[x][y] = 0;
            u1[x][y] = 0;
            u2[x][y] = 0;
        }
}

bool MainWindow::border(int x, int y)
{
    return x == N - 10;

    return (y == 40 && x < N - 10) || (x == N - 11 && y > 40 && y < N - 10);
}

void MainWindow::calculate()
{
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
        {
            float f = 0;

            if (border(x, y)) continue;

            if (x == 20 && y >= 15 + iter && y <= 17 + iter && iter < 20)
                f = -40;
            n_u2[x][y] = (k * (GetDUbyDX(2, x, y) + GetDUbyDY(2, x, y)) - f) / p;
        }

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
        {
            if (border(x, y)) continue;

            u2[x][y] = n_u2[x][y];
            u1[x][y] += u2[x][y] * timestep;
            u[x][y] += u1[x][y] * timestep;
        }

    repaint();

    iter++;
}

float MainWindow::GetDUbyDT(int derivative, int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= N) return 0;

     if (derivative == 0) return u[x][y];
     if (derivative == 1) return u1[x][y];
     else return u2[x][y];

}

float MainWindow::GetDUbyDX(int derivative, int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= N) return 0;

    if (derivative == 2)
    {
        float x1 = GetDUbyDT(0, x - 1, y);
        float x2 = GetDUbyDT(0, x, y);
        float x3 = GetDUbyDT(0, x + 1, y);

        float x4 = (x2 - x1) / scale;
        float x5 = (x3 - x2) / scale;

        return (x5 - x4) / scale;
    }
    else if (derivative == 1)
    {
        float x1 = GetDUbyDT(0, x - 1, y);
        float x2 = GetDUbyDT(0, x + 1, y);

        return (x2 - x1) / 2 / scale;
    }
    else return GetDUbyDT(0, x, y);
}

float MainWindow::GetDUbyDY(int derivative, int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= N) return 0;

    if (derivative == 2)
    {
        float y1 = GetDUbyDT(0, x, y - 1);
        float y2 = GetDUbyDT(0, x, y);
        float y3 = GetDUbyDT(0, x, y + 1);

        float y4 = (y2 - y1) / scale;
        float y5 = (y3 - y2) / scale;

        return (y5 - y4) / scale;
    }
    else if (derivative == 1)
    {
        float y1 = GetDUbyDT(0, x, y - 1);
        float y2 = GetDUbyDT(0, x, y + 1);

        return (y2 - y1) / 2 / scale;
    }
    else return GetDUbyDT(0, x, y);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p;
    float umax = 1;

    p.begin(this);

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
        {
            float m = abs(u[x][y]);
            if (m > umax) umax = m;
        }

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
        {
            if (!border(x, y))
            {
                int c = 128 + 100 * u[x][y] / umax;
                p.setPen(QPen(QColor(c, c, c), 6));
            }
            else p.setPen(QPen(QColor(255, 0, 0), 3));
            p.drawPoint(x * 6 + 10, y * 6 + 10);
        }

    p.end();
}

MainWindow::~MainWindow()
{
    delete ui;
}
