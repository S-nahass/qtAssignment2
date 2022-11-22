#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <algorithm>
#include "QMessageBox"
#include <QElapsedTimer>

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nSearch_clicked()
{
    ui->searchType->setText("using normal-search");
}

void MainWindow::on_bSearch_clicked()
{
    ui->searchType->setText("using binary-search");
}


void MainWindow::on_mSort_clicked()
{
    ui->sortType->setText("sorting using merge-sort");
    ui->sortStatus->setText("sorted array");

    ui->list->clear();

    QElapsedTimer mTimer;
    mTimer.start();

    mergeSort(vect, 0, vect.size() - 1);

    sortTime = mTimer.nsecsElapsed();

    for (auto i = vect.begin(); i != vect.end(); i++) {

        ui->list->addItem(QString::number(*i));

    }
}


void MainWindow::on_stlSort_clicked()
{
    ui->sortType->setText("sorting using STL quick-sort");
    ui->sortStatus->setText("sorted array");

    ui->list->clear();

    QElapsedTimer qsTimer;
    qsTimer.start();

    qsort(vect.data(),vect.size(),sizeof(int),compare);

    sortTime = qsTimer.nsecsElapsed();

    for (auto i = vect.begin(); i != vect.end(); i++) {

        ui->list->addItem(QString::number(*i));

    }

}



void MainWindow::on_generateData_clicked()
{
    size = ui->sizeInp->text().toInt();


    if (ui->sizeInp->isModified() && size > 0) {
        ui->datasetSize->setText("the dataset size is " + ui->sizeInp->text());

        vect.clear();
        ui->list->clear();

        for (int i = 0; i < size; i++) {

            vect.push_back(rand() % size);
        }

        for (auto i = vect.begin(); i != vect.end(); i++) {

            ui->list->addItem(QString::number(*i));
        }
    }
}

void MainWindow::on_find_clicked()
{

    QElapsedTimer timer;
    timer.start();

    x = ui->findInp->text().toInt();

    if (ui->sortStatus->text() == "sorted array") {

        if (binary_search(vect.begin(), vect.end(), x) == true) {
            if (ui->searchType->text() == "using binary-search") {

            searchTime = timer.nsecsElapsed();

                QMessageBox msg;
                msg.setWindowTitle("using binary-search");
                msg.setText(QString("the item exist & the time taken to find it in nano-seconds is = ")
                    .append(QVariant(searchTime).toString())+QString(" s"));
                msg.setInformativeText(QString("sorting time is = ")
                    .append(QVariant(sortTime).toString())+QString(" s"));
                msg.exec();

            }

        }
        else {

            QMessageBox msg;
            msg.setWindowTitle("using binary-search");
            msg.setText(QString("the item does not exist."));

        }



        if (normalSearch(vect, x) == true) {
            if (ui->searchType->text() == "using normal-search") {

                searchTime = timer.nsecsElapsed();

                QMessageBox msg;
                msg.setWindowTitle("using normal-search");
                msg.setText(QString("the item exists & the time taken to find it in nano-seconds is = ")
                    .append(QVariant(searchTime).toString())+QString(" s"));
                msg.setInformativeText(QString("sorting time is = ")
                    .append(QVariant(sortTime).toString())+QString(" s"));

                msg.exec();

            }

        }
        else {

            QMessageBox::information(this, "using normal-search", "the item does not exist.");

        }

    }
}



bool MainWindow::normalSearch(vector<int> v, int num) {

    for (int i = 0; i < v.size(); i++) {

        if (v[i] == num) { return true; }
    }
}



void MainWindow::merge(vector<int>& arr, int start, int middle, int end) {

    vector<int> leftArray(middle - start + 1);
    vector<int> rightArray(end - middle);

    for (int i = 0; i < leftArray.size(); ++i)
        leftArray[i] = arr[start + i];

    for (int i = 0; i < rightArray.size(); ++i)
        rightArray[i] = arr[middle + 1 + i];


    int leftIndex = 0, rightIndex = 0;

    int currentIndex = start;

    while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {

        if (leftArray[leftIndex] <= rightArray[rightIndex]) {

            arr[currentIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else {

            arr[currentIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        currentIndex++;
    }
    while (leftIndex < leftArray.size()) arr[currentIndex++] = leftArray[leftIndex++];
    while (rightIndex < rightArray.size()) arr[currentIndex++] = rightArray[rightIndex++];
}

void MainWindow::mergeSort(vector<int>& arr, int start, int end) {

    if (start < end) {

        int middle = (start + end) / 2;

        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);

        merge(arr, start, middle, end);
    }
}

int MainWindow::compare(const void* a, const void* b)
{
    const int* x = (int*) a;
    const int* y = (int*) b;

    if (*x > *y)
        return 1;
    else if (*x < *y)
        return -1;

    return 0;
}
