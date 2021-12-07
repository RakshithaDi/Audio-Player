#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <string>
#include <sstream>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void SetTimeLabel();

private slots:
    void on_btn_add_clicked();

    void on_volume_valueChanged(int value);

    void on_mute_clicked();

    void on_slider_valueChanged(int value);

    void on_comboBox_activated(int rate);


    void on_btn_play_clicked();

    void on_btn_pause_clicked();

    void on_btn_stop_clicked();


    void on_btn_previous_clicked();

    void on_btn_next_clicked();

private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;
    QMediaPlayer        *m_player;
    QMediaPlaylist      *m_playlist;

};

#endif // WIDGET_H
