#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

using namespace std;

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void merge(vector<int> &arr, int start, int middle, int end);
    void mergeSort(vector<int> &arr, int start, int end);

    bool normalSearch(vector<int> v, int num);
    bool binarysearch(int start, int end, int value);

    static int compare(const void* a, const void* b);


private slots:
    void on_nSearch_clicked();

    void on_bSearch_clicked();

    void on_mSort_clicked();

    void on_stlSort_clicked();

    void on_generateData_clicked();

    void on_find_clicked();

private:
    Ui::MainWindow *ui;

    int size;
    vector<int> vect;
    int searchTime;
    int sortTime;
    int x;
    int once = 0;
};
#endif // MAINWINDOW_H
