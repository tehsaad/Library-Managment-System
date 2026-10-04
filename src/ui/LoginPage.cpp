#include "LoginPage.h"
#include "Theme.h"
#include "core/Library.h"

#include <QCheckBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>


LoginPage::LoginPage(Library &library, QWidget *parent)
    : QWidget(parent)
    , m_library(library)
    , m_role(Role::Student)
{
    setObjectName("loginPage");

    auto *back = Theme::button("←  Back", "link");
    connect(back, &QPushButton::clicked, this, &LoginPage::backRequested);

    m_eyebrow = Theme::label("", "eyebrow");
    m_hint = Theme::label("", "muted");

    m_username = new QLineEdit;
    m_username->setPlaceholderText("Username");

    m_password = new QLineEdit;
    m_password->setPlaceholderText("Password");
    m_password->setEchoMode(QLineEdit::Password);

    m_showPassword = new QCheckBox("Show password");
    connect(m_showPassword, &QCheckBox::toggled, this, [this](bool checked) {
        m_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    });

    m_error = Theme::label("", "error");
    m_error->hide();

    auto *signIn = Theme::button("Sign in", "primary");
    signIn->setMinimumHeight(40);

    connect(signIn, &QPushButton::clicked, this, &LoginPage::attemptLogin);
    connect(m_username, &QLineEdit::returnPressed, m_password, qOverload<>(&QLineEdit::setFocus));
    connect(m_password, &QLineEdit::returnPressed, this, &LoginPage::attemptLogin);

    // ---- the white card in the middle ----
    auto *card = new QFrame;
    card->setProperty("card", true);
    card->setFixedWidth(420);

    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(32, 28, 32, 32);
    cardLayout->setSpacing(10);
    cardLayout->addWidget(m_eyebrow);
    cardLayout->addWidget(Theme::label("Sign in", "title"));
    cardLayout->addWidget(m_hint);
    cardLayout->addSpacing(12);
    cardLayout->addWidget(Theme::label("Username", "small"));
    cardLayout->addWidget(m_username);
    cardLayout->addSpacing(4);
    cardLayout->addWidget(Theme::label("Password", "small"));
    cardLayout->addWidget(m_password);
    cardLayout->addWidget(m_showPassword);
    cardLayout->addWidget(m_error);
    cardLayout->addSpacing(8);
    cardLayout->addWidget(signIn);

    auto *column = new QVBoxLayout;
    column->setSpacing(12);
    column->addWidget(back, 0, Qt::AlignLeft);
    column->addWidget(card);

    // Centre the card with stretches (not alignment flags: Qt then
    // ignores the extra height a wrapped error message needs)
    auto *row = new QHBoxLayout;
    row->addStretch();
    row->addLayout(column);
    row->addStretch();

    auto *layout = new QVBoxLayout(this);
    layout->addStretch(2);
    layout->addLayout(row);
    layout->addStretch(3);
}

void LoginPage::setRole(Role role)
{
    m_role = role;

    switch (role)
    {
    case Role::Student:
        m_eyebrow->setText("STUDENT");
        m_hint->setText("Use the username and password from the library desk.");
        break;
    case Role::Faculty:
        m_eyebrow->setText("FACULTY");
        m_hint->setText("Staff account for managing books and loans.");
        break;
    case Role::Admin:
        m_eyebrow->setText("ADMINISTRATOR");
        m_hint->setText("Full access to members, volunteers and the catalog.");
        break;
    }

    m_username->clear();
    m_password->clear();
    m_showPassword->setChecked(false);
    m_error->hide();
    m_username->setFocus();
}

void LoginPage::attemptLogin()
{
    const std::string username = Theme::str(m_username->text());
    const std::string password = m_password->text().toStdString();   // passwords are not trimmed

    if (username.empty() || password.empty())
    {
        m_error->setText("Please enter your username and password.");
        m_error->show();
        return;
    }

    try
    {
        Person *user = m_library.login(username, password, m_role);

        if (user == nullptr)
        {
            m_error->setText("That username and password do not match a " +
                             Theme::qs(EnumText::toString(m_role)).toLower() + " account.");
            m_error->show();
            m_password->selectAll();
            m_password->setFocus();
            return;
        }

        emit loggedIn(user);
    }
    catch (const std::exception &e)
    {
        // e.g. the History file could not be written
        m_error->setText(e.what());
        m_error->show();
    }
}
