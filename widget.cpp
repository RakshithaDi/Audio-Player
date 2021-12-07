#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <string>

using std::to_string;
using std::string;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Play List")
                                                            << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);


    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(50);
    //m_playlist->setPlaybackMode(QMediaPlaylist::Loop);


    connect(m_player, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(m_player, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);

   // connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
   // connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
   // connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
   // connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
   // connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);


    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
    });


    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentsong->setText("Now Playing "+m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });

    connect(m_player, &QMediaPlayer::durationChanged, ui->progressbar, &QProgressBar::setMaximum);
    connect(m_player, &QMediaPlayer::positionChanged, ui->progressbar, &QProgressBar::setValue);

}

Widget::~Widget()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}


void Widget::SetTimeLabel()
{
    int seconds = static_cast<int>(m_player->duration()/1000);
    int minutes = 0, hours = 0;
    string stringData;

    if (hours > 9){
        stringData = to_string(hours) + ":";
    }else{
        stringData = to_string(hours) + "0:";
    }

    if((minutes = seconds / 60) > 0){
        seconds -= minutes * 60;
        if((hours = minutes / 60) > 0){
            minutes -= hours * 60;
        }
    }
    if(minutes > 9){
         stringData += to_string(minutes) + ":";
    }else{
        stringData += "0" + to_string(minutes) + ":";
    }
    if(seconds > 9){
         stringData += to_string(seconds);
    }else{
        stringData += "0" + to_string(seconds);
    }
    ui->durationview->setText(QString::fromStdString(stringData));

}

void Widget::on_btn_add_clicked()
{

    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));


    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}



void Widget::on_mute_clicked()
{
    if(ui->mute->text() == "Mute"){
    m_player->setMuted(true);
    ui->mute->setText("Unmute");
    }
    else
    {
        m_player->setMuted(false);
        ui->mute->setText("Mute");
    }
}


void Widget::on_volume_valueChanged(int value)
{

    m_player->setVolume(value);
}


void Widget::on_slider_valueChanged(int value)
{
     qInfo() << "position is " << value ;
    m_player->setPosition(value);

}


void Widget::on_comboBox_activated(int rate)
{
    qreal nowrate = 0;
    switch (rate) {
        case 0:
        {
            nowrate = 1;
            break;
        }
    case 1:
        {
            nowrate = 0.5;
            break;
        }
    case 2:
        {
            nowrate = 2;
            break;
        }
    }
        m_player->setPlaybackRate(nowrate);
}



void Widget::on_btn_play_clicked()
{
    m_player->play();
    this->SetTimeLabel();


}


void Widget::on_btn_pause_clicked()
{
     m_player->pause();
    this->SetTimeLabel();
}


void Widget::on_btn_stop_clicked()
{
     m_player->stop();
    this->SetTimeLabel();
}



void Widget::on_btn_previous_clicked()
{
    m_playlist->previous();
   this->SetTimeLabel();
}


void Widget::on_btn_next_clicked()
{
   m_playlist->next();
   this->SetTimeLabel();
}

