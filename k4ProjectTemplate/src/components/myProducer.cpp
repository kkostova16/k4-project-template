#include "Gaudi/Property.h"

#include "edm4hep/MCParticleCollection.h"

#include "k4FWCore/Producer.h"

#include <string>

struct myProducer final : k4FWCore::Producer<edm4hep::MCParticleCollection()> {
  // The pair in KeyValue can be changed from python and it corresponds
  // to the name of the output collection
  myProducer(const std::string& name, ISvcLocator* svcLoc)
      : Producer(name, svcLoc, {}, KeyValues("OutputCollection", {"MCParticles"})) {}

  // This is the function that will be called to produce the data
  edm4hep::MCParticleCollection operator()() const override {
    auto coll = edm4hep::MCParticleCollection();
    coll.create(1, 2, 3, 4., 5., 6.);
    coll.create(2, 3, 4, 5., 6., 7.);
    // We have to return whatever collection type we specified in the
    // template argument
    return coll;
  }

private:
  // We can define any property we want that can be set from python
  // and use it inside operator()
  Gaudi::Property<int> m_exampleInt{this, "ExampleInt", 3, "Example int that can be used in the algorithm"};
};

DECLARE_COMPONENT(myProducer)