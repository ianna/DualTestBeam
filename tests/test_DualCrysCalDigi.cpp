// DualCrysCalDigiTest.cpp
#include "DualCrysCalDigi.h"
#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/EventHeaderCollection.h"
#include "edm4hep/Vector3f.h"
#include <iostream>
#include <chrono>

// Dummy implementations or mocks for services can be added here if needed

int main() {
  // Create dummy event header
  edm4hep::MutableEventHeader header;
  header.setEventNumber(1);
  header.setRunNumber(42);
  edm4hep::EventHeaderCollection headers;
  headers.push_back(header);

  // Create dummy SimCalorimeterHits
  edm4hep::SimCalorimeterHitCollection simHits;

  for (int i = 0; i < 10; ++i) {
    edm4hep::MutableSimCalorimeterHit hit;
    hit.setCellID(i);  // fake cell ID
    hit.setEnergy(0.5f + 0.1f * i);  // variable energy
    hit.setPosition({0.1f * i, 0.2f * i, 0.3f * i});
    simHits.push_back(hit);
  }

  // Create and configure the algorithm
  DualCrysCalDigi algo("TestDigi", nullptr);
  algo.m_calibrCoeffCal = 1.0;
  algo.m_maxHitEnergyCal = 2.0;
  algo.m_thresholdCal = 0.2;

  // Time the execution
  auto start = std::chrono::high_resolution_clock::now();

  auto [calHits, relLinks] = algo(simHits, headers);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Output CalorimeterHits: " << calHits.size() << "\n";
  std::cout << "Output Relations: " << relLinks.size() << "\n";
  std::cout << "Execution time: " << elapsed.count() << " seconds\n";

  return 0;
}
