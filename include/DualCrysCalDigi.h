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
#ifndef DUALCRYSCALDIGI_H
#define DUALCRYSCALDIGI_H

#include "Gaudi/Property.h"
#include "edm4hep/CaloHitContributionCollection.h"
#include "edm4hep/CaloHitSimCaloHitLinkCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/EventHeaderCollection.h"
#include "edm4hep/SimCalorimeterHitCollection.h"

#include "CalorimeterHitType.h"
#include "DualCrysCalorimeterHit.h"
#include "DDRec/SurfaceManager.h"
#include "k4FWCore/Transformer.h"
#include "k4Interface/IGeoSvc.h"
#include "k4Interface/IUniqueIDGenSvc.h"

#include <random>
#include <string>
#include <vector>

/**
 * @brief Digitization algorithm for Dual Crystal Calorimeter.
 *
 * Converts SimCalorimeterHitCollection into CalorimeterHitCollection
 * and CaloHitSimCaloHitLinkCollection using calibration parameters.
 *
 * @author (Your Name)
 */
struct DualCrysCalDigi final
    : k4FWCore::MultiTransformer<
          std::tuple<edm4hep::CalorimeterHitCollection, edm4hep::CaloHitSimCaloHitLinkCollection>(
              const edm4hep::SimCalorimeterHitCollection&, const edm4hep::EventHeaderCollection&)> {

  DualCrysCalDigi(const std::string& name, ISvcLocator* svcLoc);

  StatusCode initialize() override;

  std::tuple<edm4hep::CalorimeterHitCollection, edm4hep::CaloHitSimCaloHitLinkCollection> operator()(
      const edm4hep::SimCalorimeterHitCollection& simCaloHits,
      const edm4hep::EventHeaderCollection&       headers) const override;

private:
  // Input and output collection names
  Gaudi::Property<std::string> m_CalCollections{this, "calCollections", "DRCNoSegment",
                                                "The input collection of calorimeter hits"};
  Gaudi::Property<std::string> outputRelCollection{this, "outputRelCollection", "outputRelCollection",
                                                   "The output collection of relations"};
  Gaudi::Property<std::string> outputCalCollection{this, "outputCalCollection", "outputCalCollection",
                                                   "The output collection of calorimeter hits"};

  // Geometry and cellID handling
  Gaudi::Property<std::string> m_encodingStringVariable{
      this, "EncodingStringParameterName", "GlobalTrackerReadoutID",
      "The name of the DD4hep constant containing the encoding string"};

  // Calibration and thresholds
  Gaudi::Property<float> m_thresholdCal{this, "CalThreshold", 0.025f, "Energy threshold for calorimeter hits"};
  Gaudi::Property<float> m_calibrCoeffCal{this, "calibrationCoeffcal", 120000.0f,
                                          "Calibration coefficient for calorimeter"};
  Gaudi::Property<float> m_maxHitEnergyCal{this, "maxCalHitEnergy", 2.0f,
                                           "Maximum energy considered for a calorimeter hit"};

  // Detector names
  Gaudi::Property<std::string> m_detectorNameEcal{this, "detectornameEcal", "DRCrystal",
                                                  "Name of the ECAL detector"};
  Gaudi::Property<std::string> m_detectorNameHcal{this, "detectornameHcal", "DRFtubeFiber",
                                                  "Name of the HCAL detector"};

  // Internal variables
  std::string m_collName;

  SmartIF<IGeoSvc> m_geoSvc;
  SmartIF<IUniqueIDGenSvc> m_uidSvc;
};

DECLARE_COMPONENT(DualCrysCalDigi)

#endif // DUALCRYSCALDIGI_H
