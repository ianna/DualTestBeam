/*
 * Copyright (c) 2020-2024 Key4hep-Project.
 *
 * This file is part of Key4hep.
 * See https://key4hep.github.io/key4hep-doc/ for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cctype>
#include <cstdlib>  // for std::abs

#include "DD4hep/DD4hepUnits.h"
#include "DD4hep/Detector.h"
#include "DDRec/DetectorData.h"
#include "GaudiKernel/MsgStream.h"

#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/Constants.h"
#include "edm4hep/SimCalorimeterHit.h"

#include "DualCrysCalDigi.h"
#include "DualCrysCalorimeterHit.h"

DECLARE_COMPONENT(DualCrysCalDigi)

DualCrysCalDigi::DualCrysCalDigi(const std::string& aName, ISvcLocator* aSvcLoc)
    : MultiTransformer(
          aName, aSvcLoc,
          {
              KeyValues("CALCollection", {"ECalEcalCollection"}),
              KeyValues("HeaderName", {"EventHeader"}),
          },
          {
              KeyValues("CALOutputCollections", {"CalorimeterHit"}),
              KeyValues("RelationOutputCollection", {"RelationCalHit"})
          }) {
  m_uidSvc = service<IUniqueIDGenSvc>("UniqueIDGenSvc", true);
  if (!m_uidSvc) {
    error() << "Unable to get UniqueIDGenSvc" << endmsg;
  }

  m_geoSvc = serviceLocator()->service("GeoSvc");
  if (!m_geoSvc) {
    error() << "Unable to locate GeoSvc" << endmsg;
  }
}

StatusCode DualCrysCalDigi::initialize() {
  return StatusCode::SUCCESS;
}

std::tuple<edm4hep::CalorimeterHitCollection, edm4hep::CaloHitSimCaloHitLinkCollection>
DualCrysCalDigi::operator()(const edm4hep::SimCalorimeterHitCollection& simCaloHits,
                            const edm4hep::EventHeaderCollection&       headers) const {
  debug() << "Processing event: " << headers[0].getEventNumber()
          << " - run: " << headers[0].getRunNumber() << endmsg;

  edm4hep::CalorimeterHitCollection calHits;
  edm4hep::CaloHitSimCaloHitLinkCollection relLinks;

  std::string colName = m_CalCollections.value();
  CHT::Layout caloLayout = layoutFromString(colName);

  std::string encodingString = m_geoSvc->constantAsString(m_encodingStringVariable.value());
  dd4hep::DDSegmentation::BitFieldCoder bitFieldCoder(encodingString);

  for (const auto& simHit : simCaloHits) {
    const int cellID = simHit.getCellID();
    const float energy = simHit.getEnergy();

    unsigned int layer = bitFieldCoder.get(cellID, "layer");

    if (!useLayer(caloLayout, layer)) {
      continue;
    }

    float calibratedEnergy = m_calibrCoeffCal.value() * energy;
    if (calibratedEnergy > m_maxHitEnergyCal.value()) {
      calibratedEnergy = m_maxHitEnergyCal.value();
    }

    if (calibratedEnergy > m_thresholdCal.value()) {
      edm4hep::MutableCalorimeterHit calHit = calHits.create();
      calHit.setCellID(cellID);
      calHit.setEnergy(calibratedEnergy);
      calHit.setPosition(simHit.getPosition());
      calHit.setType(CHT(CHT::muon, CHT::yoke, caloLayout, layer));

      auto link = relLinks.create();
      link.setFrom(calHit);
      link.setTo(simHit);
    }
  }

  return std::make_tuple(std::move(calHits), std::move(relLinks));
}

// StatusCode DualCrysCalDigi::finalize() { return StatusCode::SUCCESS; }

bool DualCrysCalDigi::useLayer(CHT::Layout caloLayout, unsigned int layer) const {
  switch (caloLayout) {
    case CHT::ecal:
      if (m_useLayersEcalVec.empty() || layer >= m_useLayersEcalVec.size()) {
        return true;
      }
      return m_useLayersEcalVec[layer];

    case CHT::hcal:
      if (m_useLayersHcalVec.empty() || layer >= m_useLayersHcalVec.size()) {
        return true;
      }
      return m_useLayersHcalVec[layer];

    default:
      return true;
  }
}
