#include "MapsUploadThread.h"
#include "MapsUploader.h"
#include <math.h>
#include <QNetworkReply>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QVector>
#include <QVectorIterator>
#include <QDebug>
#include <QDir>
#include <QBuffer>


MapsUploadThread::MapsUploadThread(QVector<TilePoint> & tiles , QObject *parent) :
    QThread(parent), m_tiles(tiles) 
{
	qDebug() << "Create thread\n";
	QDir home_dir = QDir::home();

	if(!home_dir.exists(".geo2tag/uploaded_maps/"))
		home_dir.mkpath(".geo2tag/uploaded_maps/");
}

void MapsUploadThread::replyError(QNetworkReply::NetworkError code)
{
	qDebug() << "Network error: " << code << "\n";

	this->popNextTile();
}

void MapsUploadThread::handleNetworkData(QNetworkReply *reply)
{
	qDebug() << "Got reply\n";

    QImage img;
    QList<QVariant> data = reply->request().attribute(QNetworkRequest::User).toList();
    QPoint tp = data.front().toPoint();
    int zoom = data.back().toInt();
    QUrl url = reply->url();
    if (!reply->error())
	{
        if (!img.load(reply, 0))
            img = QImage();
	}
	else
	{
	}
    reply->deleteLater();

    if(!img.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img);
		QDir file_store_path = QDir().home();
		if(!file_store_path.exists(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/"))
			file_store_path.mkpath(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/");
		file_store_path.cd(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/");
		QString file_name = file_store_path.path() + "/" + QString::number(tp.x()) + "_" + QString::number(tp.y());// + ".png";
		if(!QFile(file_name).exists())
		{
			qDebug() << file_name << "\n";
			QByteArray bytes;
			QBuffer buffer(&bytes);
			buffer.open(QIODevice::WriteOnly);
			pixmap.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
			bytes = qCompress(bytes,9);
			QFile file(file_name);
			file.open(QIODevice::WriteOnly);
			file.write(bytes);
			file.flush();
			file.close();
			buffer.close();
			//pixmap.save(file_name, 0, 100);
		}
    }

	if(m_tiles.isEmpty())
	{
		quit();
		return;
	}

	this->popNextTile();
}

void MapsUploadThread::downloadTile(int lat, int lg, int zoom)
{
    QPoint grab(lg, lat);

	QDir file_store_path = QDir().home();
	if(!file_store_path.exists(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/"))
		file_store_path.mkpath(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/");
	file_store_path.cd(".geo2tag/uploaded_maps/" + QString::number(zoom) + "/");
	QString file_name = file_store_path.path() + "/" + QString::number(lg) + "_" + QString::number(lat);

	if(QFile::exists(file_name))
	{
		qDebug() << file_name << " already loaded!\n";
		this->popNextTile();
	}
	else
	{
	    QString path = "http://tile.openstreetmap.org/%1/%2/%3.png";
	    m_url = QUrl(path.arg(zoom).arg(lg).arg(lat));
		QNetworkRequest request;
		request.setUrl(m_url);
		qDebug() << m_url << "\n";
    	request.setRawHeader("User-Agent", "OSLL Observer");
	    QList<QVariant> data;
	    data.push_back(QVariant(grab));
	    data.push_back(QVariant(zoom));
	    request.setAttribute(QNetworkRequest::User, QVariant(data));
	    m_manager->get(request);
	}
}


void MapsUploadThread::popNextTile()
{
	if(m_tiles.isEmpty())
	{
		qDebug() << "No more tiles!\n";
		this->quit();
		return;
	}

	TilePoint tp = m_tiles.back();
	m_tiles.pop_back();

	qDebug() << "Call download function. Last " << m_tiles.size() << " tiles.\n";
	QPoint p = tp.first;
	int zoom = tp.second;
	downloadTile(p.x(), p.y(), zoom);
}


void MapsUploadThread::run()
{
	/*BUG: 
	 * without set system variable
	 * export LIBXCB_ALLOW_SLOPPY_LOCK=true
	 * throws exeption
	 * need to figure out what's wrong
	 */
	 
	qDebug() << "Start thread execution\n";

	this->m_manager = new QNetworkAccessManager(this);
    this->connect(this->m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));

	this->popNextTile();

	this->exec();
/*
    for(int i = 0; i < m_tiles.size(); i++)
    {
		if(m_replies_in_work > m_max_number_of_replies)
		{
			i--;
			qDebug() << "Waiting... " << m_replies_in_work  << "\n";
			sleep(1);
			continue;
		}

        TilePoint tp = m_tiles.at(i);

		qDebug() << "Call download function" << m_replies_in_work  << "\n";
        QPoint p = tp.first;
        int zoom = tp.second;
        downloadTile(p.x(), p.y(), zoom);
    }

	qDebug() << "Thread finished!\n";
*/
}
