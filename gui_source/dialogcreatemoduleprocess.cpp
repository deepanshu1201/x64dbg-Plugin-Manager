// Copyright (c) 2019-2023 hors<horsicq@gmail.com>
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
#include "dialogcreatemoduleprocess.h"

#include "ui_dialogcreatemoduleprocess.h"

DialogCreateModuleProcess::DialogCreateModuleProcess(QWidget *pParent, Utils::MDATA *pMData, bool bCreateInfoFile)
    : QDialog(pParent), ui(new Ui::DialogCreateModuleProcess)
{
    ui->setupUi(this);

    this->pMData = pMData;

    pCreateModuleProcess = new CreateModuleProcess;
    pThread = new QThread;

    pCreateModuleProcess->moveToThread(pThread);

    connect(pThread, SIGNAL(started()), pCreateModuleProcess, SLOT(process()));
    connect(pCreateModuleProcess, SIGNAL(completed(qint64)), this, SLOT(onCompleted(qint64)));
    connect(pCreateModuleProcess, SIGNAL(errorMessage(QString)), this, SIGNAL(errorMessage(QString)));

    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    g_pdStructEmpty = XBinary::createPdStruct();

    pCreateModuleProcess->setData(pMData, bCreateInfoFile, &g_pdStructEmpty);

    bIsRun = true;

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);

    pThread->start();
    pTimer->start(1000);  // 1 sec
}

DialogCreateModuleProcess::~DialogCreateModuleProcess()
{
    if (bIsRun) {
        pCreateModuleProcess->stop();
    }

    pTimer->stop();

    pThread->quit();
    pThread->wait();

    delete ui;

    delete pThread;
    delete pCreateModuleProcess;
}

void DialogCreateModuleProcess::on_pushButtonCancel_clicked()
{
    if (bIsRun) {
        pCreateModuleProcess->stop();
        pTimer->stop();
        bIsRun = false;
    }
}

void DialogCreateModuleProcess::onCompleted(qint64 nElapsed)
{
    Q_UNUSED(nElapsed)
    // TODO
    bIsRun = false;
    this->close();
}

void DialogCreateModuleProcess::timerSlot()
{
    Utils::STATS stats = pCreateModuleProcess->getCurrentStats();

    ui->labelInfo->setText(stats.sFile);

    if (stats.nTotalFile) {
        ui->progressBar->setValue((int)((stats.nCurrentFile * 100) / stats.nTotalFile));
    }
}
