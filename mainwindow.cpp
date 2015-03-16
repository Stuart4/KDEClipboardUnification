#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <QtWebSockets>
#include <QClipboard>
#include <unistd.h>
#include <stdlib.h>

using namespace std;


void handleMessages(const std::string & message);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(on_refreshButton_clicked()));

    pid_t pid = fork();
    if (pid == 0) {
        system("nodejs clip.js");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
//on clipboard change
void MainWindow::on_refreshButton_clicked()
{
    ui->clipboardText->setText(QApplication::clipboard()->text());
    ui->toSendText->setText(QApplication::clipboard()->text());

    on_sendButton_clicked();
}

//send selection to the cloud
void MainWindow::on_sendButton_clicked()
{
    QString text = ui->toSendText->text();
    cURLpp::Easy handle;
    list<string> header;
    header.push_back("Authorization: Bearer APIKEY");
    header.push_back("Content-Type: application/json");
    string data = "{\"type\": \"push\", \"push\": {\"type\":\"clip\", \"body\":\"" + text.toStdString() + "\", \"source_device_iden\":\"kdeDesktop\", \"source_user_iden\":\"jake\"}}";
    handle.setOpt(new cURLpp::options::HttpHeader(header));
    handle.setOpt(new cURLpp::Options::Url("https://api.pushbullet.com/v2/ephemerals"));
    handle.setOpt(new cURLpp::options::Post(true));
    handle.setOpt(cURLpp::options::PostFields(data));
    handle.setOpt(cURLpp::options::PostFieldSize(data.length()));


    handle.perform();
}
