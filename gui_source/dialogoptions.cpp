// Copyright (c) 2019-2022 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *pParent, XOptions *pOptions) :
    QDialog(pParent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    this->pOptions=pOptions;

    pOptions->setCheckBox(ui->checkBoxStayOnTop,XOptions::ID_VIEW_STAYONTOP);
    pOptions->setLineEdit(ui->lineEditRootPath,XOptions::ID_ROOTPATH);
    pOptions->setLineEdit(ui->lineEditDataPath,XOptions::ID_DATAPATH);
    pOptions->setLineEdit(ui->lineEditJSONLink,XOptions::ID_JSON);
}

DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::on_pushButtonOK_clicked()
{
    pOptions->getCheckBox(ui->checkBoxStayOnTop,XOptions::ID_VIEW_STAYONTOP);
    pOptions->getLineEdit(ui->lineEditRootPath,XOptions::ID_ROOTPATH);
    pOptions->getLineEdit(ui->lineEditDataPath,XOptions::ID_DATAPATH);
    pOptions->getLineEdit(ui->lineEditJSONLink,XOptions::ID_JSON);

    this->close();
}

void DialogOptions::on_pushButtonCancel_clicked()
{
    this->close();
}

void DialogOptions::on_toolButtonRootPath_clicked()
{
    QString sDirectoryName=QFileDialog::getExistingDirectory(this,tr("Select root directory"),XBinary::convertPathName(ui->lineEditRootPath->text()));

    if(sDirectoryName!="")
    {
        ui->lineEditRootPath->setText(sDirectoryName);
    }
}

void DialogOptions::on_toolButtonDataPath_clicked()
{
    QString sDirectoryName=QFileDialog::getExistingDirectory(this,tr("Select data directory"),XBinary::convertPathName(ui->lineEditDataPath->text()));

    if(sDirectoryName!="")
    {
        ui->lineEditDataPath->setText(sDirectoryName);
    }
}
