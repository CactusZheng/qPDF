#include "qPDF.h"

#include <QFileDialog>

qPDF::qPDF(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonOpen, SIGNAL(clicked()), this, SLOT(OnOpen()));

    connect(ui.pushButtonFirstPage, SIGNAL(clicked()), this, SLOT(OnFirstPage()));
    connect(ui.pushButtonLastPage, SIGNAL(clicked()), this, SLOT(OnLastPage()));
    connect(ui.pushButtonPreviousPage, SIGNAL(clicked()), this, SLOT(OnPreviousPage()));
    connect(ui.pushButtonNextPage, SIGNAL(clicked()), this, SLOT(OnNextPage()));

    ui.pushButtonFirstPage->setDisabled(true);
    ui.pushButtonPreviousPage->setDisabled(true);
    ui.labelPageCount->setText("0/0");
    ui.pushButtonNextPage->setDisabled(true);
    ui.pushButtonLastPage->setDisabled(true);
}

qPDF::~qPDF()
{
    Clear();
}

int qPDF::OnOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open PDF"), "", tr("PDF Files (*.pdf)"));
    
    if (fileName.isEmpty())
        return 0;

    Clear();

    m_ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);

    fz_try(m_ctx)
        fz_register_document_handlers(m_ctx);
    fz_catch(m_ctx)
    {
        fz_drop_context(m_ctx);
        return EXIT_FAILURE;
    }

    fz_try(m_ctx)
        m_doc = fz_open_document(m_ctx, fileName.toUtf8());
    fz_catch(m_ctx)
    {
        fz_drop_context(m_ctx);
        return EXIT_FAILURE;
    }

    fz_try(m_ctx)
        m_page_count = fz_count_pages(m_ctx, m_doc);
    fz_catch(m_ctx)
    {
        fz_drop_document(m_ctx, m_doc);
        fz_drop_context(m_ctx);
        return EXIT_FAILURE;
    }

    m_current_page_number = 0;

    return UpdatePage();
}

void qPDF::OnFirstPage()
{
    m_current_page_number = 0;
    UpdatePage();
}

void qPDF::OnLastPage()
{
    m_current_page_number = m_page_count - 1;
    UpdatePage();
}

void qPDF::OnPreviousPage()
{
    m_current_page_number--;
    UpdatePage();
}

void qPDF::OnNextPage()
{
    m_current_page_number++;
    UpdatePage();
}

void qPDF::Clear()
{
    if(m_ctx && m_pixmap)
        fz_drop_pixmap(m_ctx, m_pixmap);
    
    if (m_ctx && m_doc)
        fz_drop_document(m_ctx, m_doc);
    
    if (m_ctx)
        fz_drop_context(m_ctx);

    m_page_count = 0;
    m_current_page_number = 0;
}

int qPDF::UpdatePage()
{
    if (!m_ctx || !m_doc || m_page_count <= 0)
    {
        m_current_page_number = 0;
        ui.pushButtonFirstPage->setDisabled(true);
        ui.pushButtonPreviousPage->setDisabled(true);
        ui.labelPageCount->setText("0/0");
        ui.pushButtonNextPage->setDisabled(true);
        ui.pushButtonLastPage->setDisabled(true);
        return EXIT_FAILURE;
    }

    if (m_current_page_number >= m_page_count)
    {
        m_current_page_number = m_page_count - 1;
    }
    else if(m_current_page_number < 0)
    {
        m_current_page_number = 0;
    }

    QString page_text = QString::number(m_current_page_number + 1) + "/" + QString::number(m_page_count);
    ui.labelPageCount->setText(page_text);

    if (m_page_count == 1)
    {
        ui.pushButtonFirstPage->setDisabled(true);
        ui.pushButtonPreviousPage->setDisabled(true);
        ui.pushButtonNextPage->setDisabled(true);
        ui.pushButtonLastPage->setDisabled(true);
    }
    else if (m_current_page_number == 0 )
    {
        ui.pushButtonFirstPage->setDisabled(true);
        ui.pushButtonPreviousPage->setDisabled(true);
        ui.pushButtonNextPage->setDisabled(false);
        ui.pushButtonLastPage->setDisabled(false);
    }
    else if(m_current_page_number == m_page_count - 1)
    {
        ui.pushButtonFirstPage->setDisabled(false);
        ui.pushButtonPreviousPage->setDisabled(false);
        ui.pushButtonNextPage->setDisabled(true);
        ui.pushButtonLastPage->setDisabled(true);
    }
    else
    {
        ui.pushButtonFirstPage->setDisabled(false);
        ui.pushButtonPreviousPage->setDisabled(false);
        ui.pushButtonNextPage->setDisabled(false);
        ui.pushButtonLastPage->setDisabled(false);
    }

    if (m_ctx && m_pixmap)
        fz_drop_pixmap(m_ctx, m_pixmap);

    fz_matrix ctm{ 1, 0, 0, 1, 0, 0 };
    fz_try(m_ctx)
        m_pixmap = fz_new_pixmap_from_page_number(m_ctx, m_doc, m_current_page_number, ctm, fz_device_rgb(m_ctx), 0);
    fz_catch(m_ctx)
    {
        fz_drop_document(m_ctx, m_doc);
        fz_drop_context(m_ctx);
        return EXIT_FAILURE;
    }

    QImage image(m_pixmap->w, m_pixmap->h, QImage::Format_RGB888);
    for (int y = 0; y < m_pixmap->h; ++y)
    {
        unsigned char *p = &m_pixmap->samples[y * m_pixmap->stride];
        for (int x = 0; x < m_pixmap->w; ++x)
        {
            QColor color(p[0], p[1], p[2]);
            image.setPixelColor(x, y, color);
            p += m_pixmap->n;
        }
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    QRect rect(0, 0, m_pixmap->w, m_pixmap->h);
    ui.labelPage->setGeometry(rect);
    ui.labelPage->setPixmap(pixmap);
    ui.labelPage->setScaledContents(true);
}