#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qPDF.h"

#include <mupdf/fitz.h>

class qPDF : public QMainWindow
{
    Q_OBJECT

public:
    qPDF(QWidget *parent = Q_NULLPTR);
    ~qPDF();

public slots:
    int OnOpen();
    void OnFirstPage();
    void OnLastPage();
    void OnPreviousPage();
    void OnNextPage();

private:
    void Clear();
    int UpdatePage();
    
    Ui::qPDFClass ui;

    fz_context *m_ctx = nullptr;
    fz_document *m_doc = nullptr;
    fz_pixmap *m_pixmap = nullptr;
    int m_page_count = 0;
    int m_current_page_number = 0;
};
