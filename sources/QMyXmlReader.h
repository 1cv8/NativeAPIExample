#ifndef __QMYXMLREADER_H__
#define __QMYXMLREADER_H__

#include <QObject>
#include <QIODevice>

class QMyXmlReader : QObject
{
    Q_OBJECT

private:

    QMyXmlReader(QMyXmlReader cp);

public:
    QMyXmlReader();
    ~QMyXmlReader();


    bool OpenFile(QString filename);
    bool Close();
    bool Read();
    void AttributeValue();
    void AttributeName();
    uint AttributeCount();
    void GetAttribute();
    void ReadAttribute();
    void AttributeType();

    Q_PROPERTY(QString Name READ name WRITE setName)
    QString name();
    void setName(QString nameVal);

    Q_PROPERTY(QString NodeType READ nodeType WRITE setNodeType)
    QString nodeType();
    void setNodeType(QString nameVal);

    Q_PROPERTY(QString Value READ value WRITE setValue)
    QString value();
    void setValue(QString nameVal);

private:
    bool fileisopen;

    QIODevice *device;
    bool deleteDevice;



};


#endif //__QMYXMLREADER_H__
