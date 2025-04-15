//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================
#ifndef EXAMPLES_DDDUALCRYS_SRC_DUALCRYSCALORIMETERHIT_H
#define EXAMPLES_DDDUALCRYS_SRC_DUALCRYSCALORIMETERHIT_H

/// Framework include files
#include "DDG4/Geant4Data.h"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"

#include <array>
#include <vector>

#include "Math/Vector3D.h"

typedef ROOT::Math::XYZVector Position;
typedef ROOT::Math::XYZVector Direction;

namespace CalVision {

  /// Constants for binning
  static constexpr int finenbin = 40;
  static constexpr int coarsenbin = 4;

  /// This is the hit definition.
  /**
   * Based on the Geant4Tracker class in DDG4/Geant4Data.h.
   *
   * ⚠️ Note:
   * If MC truth handling is required, the standard Geant4Output2ROOT
   * event action won't work. Custom output writing is required.
   *
   * \author  M.Frank
   * \version 1.0
   * \ingroup DD4HEP_SIMULATION
   */
  class DualCrysCalorimeterHit : public dd4hep::sim::Geant4Calorimeter::Hit {

  public:
    // Photon and energy data
    int n_inelastic = 0;
    int ncerenkov = 0;
    int nscintillator = 0;
    float edeprelativistic = 0.0f;
    float edepepgam = 0.0f;

    // Wavelength and time window
    float wavelenmin = 300.0f;
    float wavelenmax = 1000.0f;
    float timemin = 0.0f;
    float timemax = 400.0f;
    float timemaxz = 40.0f;

    // Fine time binning
    std::array<int, finenbin> ncertime{};
    std::array<int, finenbin> nscinttime{};
    std::array<int, finenbin> ncertimez{};
    std::array<int, finenbin> nscinttimez{};
    std::array<float, finenbin> edeptime{};
    std::array<float, finenbin> ereldeptime{};

    // Hit position space
    float xmax = 10.0f, ymax = 10.0f;
    float xmin = -10.0f, ymin = -10.0f;

    // Coarse binning — placeholder for future use
    int ncoarsebin = coarsenbin;

    // MC truth contribution vectors
    std::vector<float> contribBeta;
    std::vector<float> contribCharge;

  public:
    /// Default constructor
    DualCrysCalorimeterHit() = default;

    /// Constructor with position
    explicit DualCrysCalorimeterHit(const Position& cell_pos)
        : dd4hep::sim::Geant4Calorimeter::Hit(cell_pos) {
      ncertime.fill(0);
      nscinttime.fill(0);
      ncertimez.fill(0);
      nscinttimez.fill(0);
      edeptime.fill(0.0f);
      ereldeptime.fill(0.0f);
    }

    /// Default destructor
    virtual ~DualCrysCalorimeterHit() = default;

    // Defaulted copy/move operations
    DualCrysCalorimeterHit(const DualCrysCalorimeterHit&) = default;
    DualCrysCalorimeterHit& operator=(const DualCrysCalorimeterHit&) = default;
    DualCrysCalorimeterHit(DualCrysCalorimeterHit&&) = default;
    DualCrysCalorimeterHit& operator=(DualCrysCalorimeterHit&&) = default;
  };


  /// Helper class for ROOT data dumping
  class Dump {
  public:
    /// Dump data from a ROOT file
    static int DualCrysCalorimeterdumpData(int num_evts, const char* file_name);
  };

} // namespace CalVision

// CINT/ROOTCLING dictionary configuration
#if defined(__CINT__) || defined(__MAKECINT__) || defined(__CLING__) || defined(__ROOTCLING__)
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace dd4hep;
#pragma link C++ namespace dd4hep::sim;
#pragma link C++ namespace CalVision;
#pragma link C++ class CalVision::DualCrysCalorimeterHit+;
#pragma link C++ class CalVision::Dump+;
#endif

#endif // EXAMPLES_DDDUALCRYS_SRC_DUALCRYSCALORIMETERHIT_H
