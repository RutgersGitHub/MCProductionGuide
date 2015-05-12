// -*- C++ -*-
//
// Package:    MultiLeptonFilter
// Class:      MultiLeptonFilter
//
/**\class MultiLeptonFilter MultiLeptonFilter.cc RutgersGenFilter/MultiLeptonFilter/src/MultiLeptonFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Emmanuel Contreras-Campana
//         Created:  Wed Apr 25 17:18:58 EDT 2012
// $Id: MultiLeptonFilter.cc,v 1.2 2013/04/07 16:42:59 ecampana Exp $
//
//

// system include files
#include <memory>
#include <iomanip>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Particle.h"


//
// class declaration
//
class MultiLeptonFilter : public edm::EDFilter
{
  public:
    explicit MultiLeptonFilter( const edm::ParameterSet & );
    ~MultiLeptonFilter();

    static void fillDescriptions( edm::ConfigurationDescriptions & );

  private:
    // ---------- member data ---------------------------
    virtual void beginJob();
    virtual bool filter( edm::Event &, const edm::EventSetup & );
    virtual void endJob();

    virtual bool beginRun( edm::Run &, edm::EventSetup const & );
    virtual bool endRun( edm::Run &, edm::EventSetup const & );
    virtual bool beginLuminosityBlock( edm::LuminosityBlock &, edm::EventSetup const & );
    virtual bool endLuminosityBlock( edm::LuminosityBlock &, edm::EventSetup const & );

    // ---------- member data ---------------------------
    edm::InputTag src_;

    bool m_edfilterOn;
    bool m_multlepFilterOn;
    bool m_mixModeFilterOn;

    int m_nLepton;

    bool m_debug;

    int nTotalEvents;
    int nEventsPassed;
    int nEventsPassedGt2Lep;
    int nEventsPassedGt3Lep;
    int nHZEventsPassed;

    int n0;
    int n1;
    int n2;
    int n3;
    int nGt4;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

MultiLeptonFilter::MultiLeptonFilter( const edm::ParameterSet & iPSet ):
  src_(iPSet.getParameter<edm::InputTag>("src")),
  m_edfilterOn(iPSet.getParameter<bool>("edfilterOn")),
  m_multlepFilterOn(iPSet.getParameter<bool>("multlepFilterOn")),
  m_mixModeFilterOn(iPSet.getParameter<bool>("mixModeFilterOn")),
  m_nLepton(iPSet.getParameter<int>("nLepton")),
  m_debug(iPSet.getParameter<bool>("debug"))
{
   // Now do what ever initialization is needed
   std::cout << "src_: " << src_ << std::endl;
   std::cout << "m_edfilterOn: " << m_edfilterOn << std::endl;
   std::cout << "m_multlepfilterOn: " << m_multlepFilterOn << std::endl;
   std::cout << "m_mixModeFilterOn: " << m_mixModeFilterOn << std::endl;
   std::cout << "m_nLepton: " << m_nLepton << std::endl;
   std::cout << "m_debug: " << m_debug << std::endl;

   nTotalEvents = 0;
   nEventsPassed = 0;
   nEventsPassedGt2Lep = 0;
   nEventsPassedGt3Lep = 0;
   nHZEventsPassed = 0;

   nGt4 = 0;
   n3 = 0;
   n2 = 0;
   n1 = 0;
   n0 = 0;
}

MultiLeptonFilter::~MultiLeptonFilter()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called on each new Event  ------------
bool MultiLeptonFilter::filter( edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  int nLepton = 0;
  int nLepton2 = 0;
  int nHiggs = 0;
  int nZboson = 0;
  int nHZ = 0;

  bool pass = true;

  // Gather information on the reco::GenParticle collection
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(src_, genParticles);

  nTotalEvents++;

  if (m_edfilterOn == true) {

    for (reco::GenParticleCollection::const_iterator iter = genParticles->begin();
         iter != genParticles->end(); ++iter) {

      // Verify whether particle comes from the decay of a Z boson
      try {
        if (iter != genParticles->begin() && iter != genParticles->begin()+1) {
          if ( abs( iter->mother()->pdgId() ) == 23 ) {
            if ( abs( iter->pdgId() ) == 11 || abs( iter->pdgId() ) == 13 || abs( iter->pdgId() ) == 15 ) {
              std::cout << "pdgID: " << iter->pdgId() << " status: " << iter->status()
                        << " mother pdgID: " << abs( iter->mother()->pdgId() )
                        << " mother status: " << iter->mother()->status() << std::endl;

              // Throw exception if the particle that comes from the decay of a Z boson does not have status 3 
              if ( iter->status() != 3 ) {
                throw 1;              
              }
            }
          }
        }
      }

      // Catch exception that have been thrown
      catch (int e) {
        std::cout << "An exception occurred. Found lepton comming from Z boson with status other than 3!!!" << e << std::endl;
      }

      // Search for status 3 particles
      if (iter->status() == 3) {
        // Search for electrons
        if ( abs( iter->pdgId() ) == 11 && iter->pt() > 5.0 ) {
          nLepton++;

          if ( abs( iter->pdgId() ) == 11 && iter->pt() > 10.0 ) {
            nLepton2++;
          }
        }

        // Search for muons
        else if ( abs( iter->pdgId() ) == 13 && iter->pt() > 5.0 ) {
          nLepton++;

          if ( abs( iter->pdgId() ) == 13 && iter->pt() > 10.0 ) {
            nLepton2++;
          }

        }

        // Search for taus
        else if ( abs( iter->pdgId() ) == 15 && iter->pt() > 5.0 ) {
          nLepton++;

          if ( abs( iter->pdgId() ) == 15 && iter->pt() > 10.0 ) {
            nLepton2++;
          }
        }
      } // iter->status() == 3

      // Search for Z bosons coming from neutralino
      if ( abs( iter->pdgId() ) == 23 && abs( iter->mother()->pdgId() ) == 1000023 ) {
        nZboson++;
      }

      // Search for Higgs bosons coming from neutralino
      else if ( abs( iter->pdgId() ) == 25 && abs( iter->mother()->pdgId() ) == 1000023 ) {
        nHiggs++;
      }
    } // end for-loop
  } // m_edfilterOn == true

  // Lepton multiplicity break down
  if (nLepton == 0) {
    n0++;
  }

  if (nLepton == 1) {
    n1++;
  }

  if (nLepton == 2) {
    n2++;
  }

  if (nLepton == 3) {
    n3++;
  }

  if (nLepton >= 4) {
    nGt4++;
  }

  // HZ multiplicity
  if (nHiggs == 1 && nZboson == 1) {
    nHZ++;
  }

  // Only multilepton filter is on
  if (nLepton < m_nLepton && m_multlepFilterOn && !m_mixModeFilterOn) {
    pass = false;

    if (m_debug == true) {
      std::cout << "Only multilepton filter is on!" << std::endl;
    }
  }

  // Only mix mode filter is on
  if (nHiggs != 1 && nZboson != 1 && m_mixModeFilterOn && !m_multlepFilterOn) {
    pass = false;

    if (m_debug == true) {
      std::cout << "Only mix mode filter is on!" << std::endl;
    }
  }

  // Both mulitlepton and mix mode filter is on
  if (nLepton < m_nLepton && m_multlepFilterOn && m_mixModeFilterOn) {
    pass = false;

    if (m_debug == true) {
      std::cout << "Both mulitlepton and mix mode filter is on!" << std::endl;
    }
  }

  else if (nHiggs != 1 && nZboson != 1 && m_multlepFilterOn && m_mixModeFilterOn) {
    pass = false;
  
    if (m_debug == true) {
      std::cout << "Both mulitlepton and mix mode filter is on!" << std::endl;
    }
  }

  if (pass) {
    nEventsPassed++;
  }

  if (nLepton >= 2) {
    nEventsPassedGt2Lep++;
  }

  if (nLepton2 >= 3) {
    nEventsPassedGt3Lep++;
  }

  if (nHZ > 0) {
    nHZEventsPassed++;
  }

  if (m_debug == true) {
    std::cout << "nLepton: " << nLepton << std::endl;
    std::cout << "nHiggs: " << nHiggs << std::endl;
    std::cout << "nZboson: " << nZboson << std::endl;

    if (pass == true) std::cout << "Event passed MultiLeptonFilter" << std::endl;

    if (pass == false) std::cout << "Event failed MultiLeptonFilter" << std::endl;
  }

  //pass = false;
  return pass;
}

// ------------ method called once each job just before starting event loop  ------------
void MultiLeptonFilter::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void MultiLeptonFilter::endJob()
{
  std::cout << "Lepton multiplicity break down" << std::endl;
  std::cout << "nGt4: " << nGt4 << std::endl;
  std::cout << "n3: " << n3 << std::endl;
  std::cout << "n2: " << n2 << std::endl;
  std::cout << "n1: " << n1 << std::endl;
  std::cout << "n0: " << n0 << std::endl;
  std::cout << "nEventsPassedGt2Lep: " << nEventsPassedGt2Lep << std::endl;
  std::cout << "nEventsPassedGt3Lep: " << nEventsPassedGt3Lep << std::endl;
  std::cout << "nHZEventsPassed: " << nHZEventsPassed << std::endl;
  std::cout << "nEventsPassed: " << nEventsPassed << std::endl;
  std::cout << "nTotalEvents: " << nTotalEvents << std::endl;

  std::cout.setf(std::ios::fixed, std:: ios::floatfield);
  std::cout << "EDFilter MultiLepton efficiency: " << std::setprecision(6)
            << (double)nEventsPassed/(double)nTotalEvents << std::endl;
  std::cout.unsetf(std::ios::floatfield);
}

// ------------ method called when starting to processes a run  ------------
bool MultiLeptonFilter::beginRun( edm::Run &iRun, edm::EventSetup const &iSetup )
{
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool MultiLeptonFilter::endRun( edm::Run &iRun, edm::EventSetup const &iSetup )
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool MultiLeptonFilter::beginLuminosityBlock( edm::LuminosityBlock &iLuminosityBlock, edm::EventSetup const &iSetup )
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool MultiLeptonFilter::endLuminosityBlock( edm::LuminosityBlock &iLuminosityBlock, edm::EventSetup const &iSetup )
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MultiLeptonFilter::fillDescriptions( edm::ConfigurationDescriptions &descriptions )
{
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(MultiLeptonFilter);
