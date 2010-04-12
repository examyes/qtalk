#include "LoginWidget.h"
#include "ui_LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    QRegExp rx(".+@.+\\..+");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->jidLineEdit->setValidator(validator);

    ui->portSpinBox->setValue(5222);
    connect(ui->loginButton, SIGNAL(clicked()),
            SLOT(clickedLogin()));
    connect(ui->jidLineEdit, SIGNAL(editingFinished()),
            this, SLOT(getHost()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString LoginWidget::jid() const
{
    return ui->jidLineEdit->text();
}

QString LoginWidget::password() const
{
    return ui->passwordLineEdit->text();
}

QString LoginWidget::host() const
{
    return ui->hostLineEdit->text();
}

int LoginWidget::port() const
{
    return ui->portSpinBox->value();
}

bool LoginWidget::isRemember() const
{
    return ui->rememberCheckBox->isChecked();
}

void LoginWidget::lock()
{
    ui->tabWidget->setEnabled(false);
}

void LoginWidget::unlock()
{
    ui->tabWidget->setEnabled(true);
}

void LoginWidget::showState(QString str)
{
    ui->stateLabel->setText(str);;
}

void LoginWidget::clickedLogin()
{
    if (ui->jidLineEdit->hasAcceptableInput()) {
        emit login();
    } else {
        showState("<b>Notice !</b> Jabber ID is looks like 'username@domain.com'");
    }
}

void LoginWidget::getHost()
{
    if (!ui->advanceCheckBox->isChecked()) {
        const int pos = jid().indexOf(QChar('@'));
        if (pos < 0)
            return;
        ui->hostLineEdit->setText(jid().mid(pos + 1));
    }
}
