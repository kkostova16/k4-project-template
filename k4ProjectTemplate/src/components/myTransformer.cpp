#include "Gaudi/Property.h"

#include "edm4hep/MCParticleCollection.h"
#include <edm4hep/ReconstructedParticleCollection.h>

#include "edm4hep/MutableReconstructedParticle.h"

#include "k4FWCore/Transformer.h"

#include <string>

struct myTransformer final
    : k4FWCore::Transformer<edm4hep::ReconstructedParticleCollection(const edm4hep::MCParticleCollection&)> {
  myTransformer(const std::string& name, ISvcLocator* svcLoc)
      : Transformer(name, svcLoc, {KeyValues("InputCollection", {"MCParticles"})},
                    {KeyValues("OutputCollection", {"NewMCParticles"})}) {}

  // This is the function that will be called to transform the data
  // Note that the function has to be const, as well as all pointers to collections
  // we get from the input
  edm4hep::ReconstructedParticleCollection operator()(const edm4hep::MCParticleCollection& input) const override {
    info() << "Transforming " << input.size() << " particles" << endmsg;
    auto reco_coll = edm4hep::ReconstructedParticleCollection(); // Define collection
    for (const auto& particle : input) {
      auto new_particle1 = edm4hep::MutableReconstructedParticle();
      new_particle1.setPDG(particle.getPDG() + id_offset[0]);
      reco_coll->push_back(new_particle1);

      auto new_particle2 = edm4hep::MutableReconstructedParticle();
      new_particle2.setPDG(particle.getPDG() + id_offset[1]);
      reco_coll->push_back(new_particle2);
    }
    return reco_coll;
  }

private:
  // integer to add to the dummy values written to the edm
  Gaudi::Property<int> m_offset{this, "Offset", 10, "Integer to add to the dummy values written to the edm"};
  Gaudi::Property<std::vector<int>> id_offset{this, "ID_Offset", {10,200}, "Vector of integers to add to the dummy values written to the PDG"};
};

DECLARE_COMPONENT(myTransformer)