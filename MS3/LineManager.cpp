#include <iostream>
#include <fstream>
#include "Utilities.h"
#include "LineManager.h"
#include <iomanip>
#include <algorithm>

using namespace std;

namespace sdds {

  LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    if(file.length()!=0) {
      ifstream logFile(file);
      string data;
      Workstation* ws_cur{};
      Workstation* ws_next{};
      Workstation* ws_first{};
      std::vector<string> temp;
      while(getline(logFile, data)) {
        if(data.find('|') != string::npos) {
          string first = data.substr(0, data.find('|'));
          string second = data.substr(data.find('|')+1);
          ws_cur = *find_if(stations.begin(), stations.end(), [&]( Workstation* ws){
            return (ws->getItemName() == first);
          });
          ws_next = *find_if(stations.begin(), stations.end(), [&]( Workstation* ws){
            return (ws->getItemName() == second);
          });
          ws_cur->setNextStation(ws_next);
          m_activeLine.push_back(ws_cur);
          temp.push_back(second);
        }
        else {
          ws_cur = *find_if(stations.begin(), stations.end(), [&]( Workstation* ws){
            return (ws->getItemName() == data);
          });
          m_activeLine.push_back(ws_cur);
        }
      }

      ws_first = *find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
        
        return (find_if(temp.begin(), temp.end(), [&](string &str) {
          return (ws->getItemName() == str);
        }) == temp.end());
        
      });

      m_firstStation = ws_first;
      m_cntCustomerOrder = g_pending.size();

    }
  }
  
  void LineManager::reorderStations() {
    vector<Workstation*> newLine;
    Workstation* ws = m_firstStation;
    while(ws) {
      newLine.push_back(ws);
      ws = ws->getNextStation();
    }
    m_activeLine = newLine;
  }

  bool LineManager::run(std::ostream& os) {
    static int curr = 1;
    os << "Line Manager Iteration: " << curr << endl;
    curr++;
    if(!g_pending.empty()) {
      *m_firstStation += std::move(g_pending.front());
      g_pending.pop_front();
    }

    for(auto i: m_activeLine) {
      i->fill(os);
    }
    for(auto i: m_activeLine) {
      i->attemptToMoveOrder();
    }

    return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
  }

  void LineManager::display(std::ostream& os) const {
    for(auto i: m_activeLine) {
      i->display(os);
    }
  }

}
