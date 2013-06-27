// Default empty project template
#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QUrl>
#include <Qt/qnetworkaccessmanager.h>
#include <Qt/qnetworkreply.h>

#include <bb/cascades/Button>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ScrollView>
#include <bb/cascades/TextArea>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    ~ApplicationUI();

    Q_INVOKABLE void fetch(QString url, QString encoding);
    QString getDecodedString(QByteArray content, QString encoding);

private slots:
	void onPageRequestFinished(QNetworkReply* networkReply);

private:
    bb::cascades::Button* goButton;
    bb::cascades::ActivityIndicator* activityIndicator;
    bb::cascades::ScrollView* contentScrollView;
    bb::cascades::TextArea* headerText;
    bb::cascades::TextArea* contentText;
    QNetworkAccessManager* networkManager;
    QString encoding;
};


#endif /* ApplicationUI_HPP_ */
