#include "Gaudi/Property.h"

#include "edm4hep/MCParticleCollection.h"

#include "k4FWCore/Consumer.h"

#include <stdexcept>
#include <string>

struct myConsumer final : k4FWCore::Consumer<void(const edm4hep::MCParticleCollection& input)> {
  // The pair in KeyValue can be changed from python and it corresponds
  // to the name of the input collection
  myConsumer(const std::string& name, ISvcLocator* svcLoc)
      : Consumer(name, svcLoc, KeyValues("InputCollection", {"MCParticles"})) {}

  // This is the function that will be called to transform the data
  // Note that the function has to be const, as well as the collections
  // we get from the input
  void operator()(const edm4hep::MCParticleCollection& input) const override {
    debug() << "Received MCParticle collection with " << input.size() << " elements" << endmsg;
    if (input.size() != 2) {
      fatal() << "Wrong size of MCParticle collection, expected 2 got " << input.size() << endmsg;
      throw std::runtime_error("Wrong size of MCParticle collection");
    }
    int i = 0;
    for (const auto& particle : input) {
      if ((particle.getPDG() != 1 + i + m_offset) || (particle.getGeneratorStatus() != 2 + i + m_offset) ||
          (particle.getSimulatorStatus() != 3 + i + m_offset) || (particle.getCharge() != 4 + i + m_offset) ||
          (particle.getTime() != 5 + i + m_offset) || (particle.getMass() != 6 + i + m_offset)) {
        std::stringstream error;
        error << "Wrong data in MCParticle collection, expected " << 1 + i + m_offset << ", " << 2 + i + m_offset
              << ", " << 3 + i + m_offset << ", " << 4 + i + m_offset << ", " << 5 + i + m_offset << ", "
              << 6 + i + m_offset << " got " << particle.getPDG() << ", " << particle.getGeneratorStatus() << ", "
              << particle.getSimulatorStatus() << ", " << particle.getCharge() << ", " << particle.getTime() << ", "
              << particle.getMass();
        throw std::runtime_error(error.str());
      }
      i++;
    }
  }

  Gaudi::Property<int> m_offset{this, "Offset", 10, "Integer to add to the dummy values written to the edm"};
};

DECLARE_COMPONENT(myConsumer)