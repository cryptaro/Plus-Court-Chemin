#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void reset();
    void clean();
    void launch();

    void loadImage();

private:
    Ui::MainWindow *ui;

    int nbX,nbY;
};

#endif // MAINWINDOW_H
