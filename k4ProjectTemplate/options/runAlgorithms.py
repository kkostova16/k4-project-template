from Gaudi.Configuration import INFO
from Configurables import (
    myProducer,
    myTransformer,
    myConsumer,
)
from k4FWCore import ApplicationMgr
from Configurables import EventDataSvc

producer = myProducer("Producer", OutputCollection=["MCParticle"])

transformer1 = myTransformer("Transformer1", InputCollection=["MCParticle"], OutputCollection=["NewMCParticle1"])
transformer2 = myTransformer("Transformer2", InputCollection=["MCParticle"], OutputCollection=["NewMCParticle2"])

consumer1 = myConsumer("Consumer1", InputCollection=["NewMCParticle1"], Offset=10,)
consumer2 = myConsumer("Consumer2", InputCollection=["NewMCParticle2"], Offset=200,)

ApplicationMgr(
    TopAlg=[producer, transformer1, transformer2, consumer1, consumer2],
    EvtSel="NONE",
    EvtMax=10,
    ExtSvc=[EventDataSvc("EventDataSvc")],
    OutputLevel=INFO,
)

producer.setPDG(111)

print(consumer1.getPDG())
print(consumer2.getPDG())