#include "Gaudi/Property.h"

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/ReconstructedParticleCollection.h"

#include "k4FWCore/Consumer.h"

#include <stdexcept>
#include <string>

struct myConsumer final 
  : k4FWCore::Consumer<void(const edm4hep::MCParticleCollection&, const edm4hep::ReconstructedParticleCollection&)> {
  // The pair in KeyValue can be changed from python and it corresponds
  // to the name of the input collection
  myConsumer(const std::string& name, ISvcLocator* svcLoc)
      : Consumer(name, svcLoc, {KeyValues("MCInputCollection", {"MCParticles"}), 
                           KeyValues("RecoInputCollection", {"RecoParticles"})}) {}

  // This is the function that will be called to transform the data
  // Note that the function has to be const, as well as the collections
  // we get from the input
  void operator()(
    const edm4hep::MCParticleCollection& MC_input, const edm4hep::ReconstructedParticleCollection& reco_input) const override {
    debug() << "Received MCParticle collection with " << MC_input.size() << " elements" << endmsg;
    debug() << "Received ReconstructedParticle collection with " << reco_input.size() << " elements" << endmsg;
    if (MC_input.size() != 1) {
      fatal() << "Wrong size of MCParticle collection, expected 1 got " << MC_input.size() << endmsg;
      throw std::runtime_error("Wrong size of MCParticle collection");
    }
    int i = 0;
    for (const auto& particle : reco_input) {
      if ((particle.getPDG() != MC_input[0].getPDG() + id_offset[i])) {
        std::stringstream error;
        error << "Wrong data in MCParticle collection, expected PGD " << MC_input[0].getPDG() + id_offset[i] << 
              " got " << particle.getPDG();
        throw std::runtime_error(error.str());
      }
      else {
        info() << "ReconstructedParticle PDG " << particle.getPDG() << " matches the expected PDG " << MC_input[0].getPDG() + id_offset[i] << endmsg;
      }
      i++;
    }
  }

  Gaudi::Property<int> m_offset{this, "Offset", 10, "Integer to add to the dummy values written to the edm"};
  Gaudi::Property<std::vector<int>> id_offset{this, "ID_Offset", {10,200}, "Vector of integers to add to the dummy values written to the PDG"};
};

DECLARE_COMPONENT(myConsumer)