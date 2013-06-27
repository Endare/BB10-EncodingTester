// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_app", this);

    AbstractPane *root = qml->createRootObject<AbstractPane>();
	//Link the variables
	goButton = root->findChild<Button*>("goButton");
	activityIndicator = root->findChild<ActivityIndicator*>("activityIndicator");
	contentScrollView = root->findChild<ScrollView*>("contentScrollView");
	headerText = root->findChild<TextArea*>("headerText");
	contentText = root->findChild<TextArea*>("contentText");
    app->setScene(root);

    //Create the network manager
    networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPageRequestFinished(QNetworkReply*)));
}

ApplicationUI::~ApplicationUI()
{
	delete networkManager;
}

Q_INVOKABLE void ApplicationUI::fetch(QString url, QString encoding)
{
	contentScrollView->setVisible(false);
	this->encoding = encoding;
	QUrl serviceUrl = QUrl(url);
	networkManager->get(QNetworkRequest(serviceUrl));
}

void ApplicationUI::onPageRequestFinished(QNetworkReply* networkReply)
{
	qDebug() << "ApplicationUI:: onPageRequestFinished";
	//Process the header
	QString contentTypeHeader = networkReply->header(QNetworkRequest::ContentTypeHeader).toString();
	int statusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	headerText->setText(QString("Content type: ") + contentTypeHeader + QString("\nStatus code: ") + QString::number(statusCode));
	//Process the content
	QByteArray content = networkReply->readAll();
	qDebug() << "Size of content is " << content.size();
	QString dataString = getDecodedString(content, encoding);
	contentText->setText(dataString);
	//Reset UI
	goButton->setVisible(true);
	activityIndicator->setVisible(false);
	contentScrollView->setVisible(true);
}

QString ApplicationUI::getDecodedString(QByteArray content, QString encoding)
{
	QString dataString;
	if(encoding.compare(QString("UTF8")) == 0)
	{
		qDebug() << "Assuming UTF8 encoding";
		dataString = QString::fromUtf8(content.data(), content.size());
	}
	else if(encoding.compare(QString("ASCII")) == 0)
	{
		qDebug() << "Assuming ASCII encoding";
		dataString = QString::fromAscii(content.data(), content.size());
	}
	else if(encoding.compare(QString("UCS4")) == 0)
	{
		qDebug() << "Assuming UCS4 encoding";
		dataString = QString::fromUcs4((uint *)content.data(), content.size()/4);
	}
	else if(encoding.compare(QString("UTF16")) == 0)
	{
		qDebug() << "Assuming UTF16 encoding";
		dataString = QString::fromUtf16((ushort *)content.data(), content.size()/2);
	}
	else if(encoding.compare(QString("Latin1")) == 0)
	{
		qDebug() << "Assuming Latin encoding";
		dataString = QString::fromAscii(content.data(), content.size());
	}
	else
	{
		qDebug() << "Assuming Local 8bit encoding";
		dataString = QString::fromLocal8Bit(content.data(), content.size());
	}
	return dataString;
}
