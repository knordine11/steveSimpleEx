#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioSource>
#include <QMediaDevices>
#include <QPixmap>
#include <QPainter>

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format);

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

    qreal calculateLevel(const char *data, qint64 len);
    static void zero_rec_arr();
    int frame_cnt = 0;


signals:
    void levelChanged(qreal level);

private:
    const QAudioFormat m_format;
    qreal m_level = 0.0; // 0.0 <= m_level <= 1.0

};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnDataInput_clicked();

private:
    Ui::Widget *ui;

private:
    void initializeWindow();
    void initializeAudio(const QAudioDevice &deviceInfo);
    void restartAudioStream();

private:
    // Owned by layout
    QMediaDevices *m_devices = nullptr;
    std::unique_ptr<AudioInfo> m_audioInfo;
    std::unique_ptr<QAudioSource> m_audioSource;
    bool m_pullMode = true;
    int frame_length = 0;
    int frame_start = 0;
};
#endif // WIDGET_H
