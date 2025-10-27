#include "widget.h"
#include "ui_widget.h"
#include "fftwstuff.h"
#include "rec_arr_tool.h"
#include "filewriter.h"
#include <QAudioDevice>
#include <QAudioSource>
#include <QtEndian>
#include <math.h>
#include <stdlib.h>

AudioInfo::AudioInfo(const QAudioFormat &format) : m_format(format)
{

}

void AudioInfo::start()
{
    open(QIODevice::WriteOnly);
}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char * /* data */, qint64 /* maxlen */)
{
    return 0;
}

qreal AudioInfo::calculateLevel(const char *data, qint64 len)
{
    const int channelBytes = m_format.bytesPerSample();
    const int sampleBytes = m_format.bytesPerFrame();
    const int numSamples = len / sampleBytes;

    float maxValue = 0;
    auto *ptr = reinterpret_cast<const signed char *>(data);

    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < m_format.channelCount(); ++j) {
            float value = m_format.normalizedSampleValue(ptr);

            rec_arr[rec_arr_cnt] = value;

            maxValue = qMax(value, maxValue);
            ptr += channelBytes;
            if (rec_arr_cnt == 1000)
                qDebug() << "  " <<  i << "  " << value;
            rec_arr_cnt++;
        }
    }
    frame_cnt++;
    return maxValue;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    m_level = calculateLevel(data, len);

    emit levelChanged(m_level);

    return len;
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeWindow()
{
    const QAudioDevice &defaultDeviceInfo = QMediaDevices::defaultAudioInput();
}

void Widget::initializeAudio(const QAudioDevice &deviceInfo)
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    m_audioInfo.reset(new AudioInfo(format));
    m_audioSource.reset(new QAudioSource(deviceInfo, format));
    m_audioInfo->start();
    restartAudioStream();
}

void Widget::restartAudioStream()
{
    m_audioSource->stop();

    // pull mode: QAudioSource provides a QIODevice to pull from
    auto *io = m_audioSource->start();
    if (!io)
        return;

    Rec_Arr_Tool::zero_rec_arr();
    Rec_Arr_Tool::make_sin(440.0,0,1024);
    Rec_Arr_Tool::look_rec_arr(80,100);

    connect(io, &QIODevice::readyRead, [this, io]() {
        static const qint64 BufferSize = 4096;
        const qint64 len = qMin(m_audioSource->bytesAvailable(), BufferSize);

        QByteArray buffer(len, 0);
        qint64 l = io->read(buffer.data(), len);
        if (l > 0) {
            const qreal level = m_audioInfo->calculateLevel(buffer.constData(), l);
            qDebug() << level;
            QString temp2;
            temp2.setNum(rec_arr_cnt);
            ui->cboFrameEnds->addItem(temp2);

            if (m_audioInfo->frame_cnt > 100){
                int frame_length = 100;
                int start = 10 * frame_length;
                fftwStuff::DoIt(start, frame_length);
                m_audioInfo->stop();
                m_audioSource->stop();

                filewriter::WriteData();
            }
        }
    });    
}

void Widget::on_btnDataInput_clicked()
{
    initializeWindow();
    initializeAudio(QMediaDevices::defaultAudioInput());
}

void Widget::on_cboFrameEnds_currentTextChanged(const QString &arg1)
{
    int beginframe = arg1.toInt();
    qDebug() << beginframe;
    Rec_Arr_Tool::look_rec_arr(beginframe, beginframe + 20);
}

