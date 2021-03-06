#include "tracker.h"
#include "trackerlist.h"

constexpr auto NAME{ "Name" };

Tracker::Tracker(QObject *parent) : PostProcess(parent) {
  m_baseTracker = new Trackers::None{};
}

void Tracker::configure(QJsonObject const &a_config) {
  //Logger->trace("Tracker::configure()");
  auto const NAME_STRING{a_config[NAME].toString()};
  //Logger->trace("Tracker type: {}", NAME_STRING.toStdString());
  delete m_baseTracker;
  m_timer.reset();

  if (NAME_STRING == "OpenCVTrackers") {
    m_baseTracker = new Trackers::Trackers{a_config};
  } else if (NAME_STRING == "None") {
    m_baseTracker = {new Trackers::None{}};
  } else {
    //spdlog::error("Unsupported filter type: {}", NAME_STRING.toStdString());
  }
}

void Tracker::process(std::vector<_postData> &_data)
{
  //Logger->trace("Tracker::process(a_image)");
  m_timer.start();
  m_baseTracker->process(_data);
  m_timer.stop();
}
double Tracker::getElapsedTime() { return m_timer.getTimeMilli(); }

void Tracker::endProcess(std::vector<_postData> &_data) {}