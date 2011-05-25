#include "SymbianDaemon.h"

SymbianDaemon::SymbianDaemon()
{
  m_daemon=new TrackerDaemon();
  QtConcurrent::run(&m_daemon,TrackerDaemon::run);
}


void SymbianDaemon::start()
{
  m_daemon->startTracking();
}


void SymbianDaemon::stop()
{
  m_daemon->stopTracking();
}


void SymbianDaemon::reload()
{
  m_daemon->reloadSettings();
}


void SymbianDaemon::restart()
{
  m_daemon->reloadSettings();
}


bool SymbianDaemon::isConnected()
{
  return true;
}


bool SymbianDaemon::isStarted()
{
  return m_daemon->isTracking();
}


QPointF SymbianDaemon::getLastCoordinates() const
{
  return m_daemon->getLastCoords();
}
