#include <QDebug>
#include <QBitmap>
#include <QColor>
#include <QDir>
#include <QFile>
#include <QFontMetrics>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QTextStream>

#include "skinfcitx.h"

SkinFcitx::SkinFcitx() : SkinBase()
{

}

SkinFcitx::~SkinFcitx()
{

}

bool SkinFcitx::loadSkin(const QString skinPath)
{
    QFile fcitxSkinConfFile(skinPath + "fcitx_skin.conf");
    if (!fcitxSkinConfFile.exists())
        return false;

    if (!fcitxSkinConfFile.open(QIODevice::ReadOnly))
        return false;

    QString line;
    QString key, value;
    bool skinfont = false;
    bool skininputbar = false;
    QTextStream textStream(fcitxSkinConfFile.readAll());

    do {
        line = textStream.readLine();

        if (line.isEmpty() || line.at(0) == '#')
            continue;

        if (line.at(0) == '[') {
            skinfont = (line == "[SkinFont]");
            skininputbar = (line == "[SkinInputBar]");
            continue;
        }

        if (!line.contains('='))
            continue;

        key = line.split('=').at(0);
        value = line.split('=').at(1);

        if (value.isEmpty())
            continue;

        if (skininputbar) {
            if (key == "BackImg") {
                setInputBackImg("file:/" + skinPath + value);

            } else if (key == "MarginLeft") {
                setMarginLeft(value.toInt());

            } else if (key == "MarginTop") {
                setMarginTop(value.toInt());

            } else if (key == "MarginRight") {
                setMarginRight(value.toInt());

            } else if (key == "MarginBottom") {
                setMarginBottom(value.toInt());

            } else if (key == "BackArrow") {
                setBackArrowImg("file:/" + skinPath + value);

            } else if (key == "ForwardArrow") {
                setForwardArrowImg("file:/" + skinPath + value);

            }
        }
    } while (!line.isNull());

    fcitxSkinConfFile.close();
    return true;
}

