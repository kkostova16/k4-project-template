#include "Gaudi/Property.h"

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/MutableMCParticle.h"

#include "k4FWCore/Transformer.h"

#include <string>

struct myTransformer final
    : k4FWCore::Transformer<edm4hep::MCParticleCollection(const edm4hep::MCParticleCollection&)> {
  myTransformer(const std::string& name, ISvcLocator* svcLoc)
      : Transformer(name, svcLoc, {KeyValues("InputCollection", {"MCParticles"})},
                    {KeyValues("OutputCollection", {"NewMCParticles"})}) {}

  // This is the function that will be called to transform the data
  // Note that the function has to be const, as well as all pointers to collections
  // we get from the input
  edm4hep::MCParticleCollection operator()(const edm4hep::MCParticleCollection& input) const override {
    info() << "Transforming " << input.size() << " particles" << endmsg;
    auto coll_out = edm4hep::MCParticleCollection();
    for (const auto& particle : input) {
      auto new_particle = edm4hep::MutableMCParticle();
      new_particle.setPDG(particle.getPDG() + m_offset);
      new_particle.setGeneratorStatus(particle.getGeneratorStatus() + m_offset);
      new_particle.setSimulatorStatus(particle.getSimulatorStatus() + m_offset);
      new_particle.setCharge(particle.getCharge() + m_offset);
      new_particle.setTime(particle.getTime() + m_offset);
      new_particle.setMass(particle.getMass() + m_offset);
      coll_out->push_back(new_particle);
    }
    return coll_out;
  }

private:
  // integer to add to the dummy values written to the edm
  Gaudi::Property<int> m_offset{this, "Offset", 10, "Integer to add to the dummy values written to the edm"};
};

DECLARE_COMPONENT(myTransformer)