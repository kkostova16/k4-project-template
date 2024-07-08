from Gaudi.Configuration import INFO
from Configurables import (
    myProducer,
    myTransformer,
    myConsumer,
)
from k4FWCore import ApplicationMgr
from Configurables import EventDataSvc

producer = myProducer("Producer", OutputCollection=["MCParticles"])

transformer = myTransformer("Transformer", InputCollection=["MCParticles"], 
                                OutputCollection=["RecoParticles"])

consumer = myConsumer("Consumer", MCInputCollection=["MCParticles"],
                                RecoInputCollection = ["RecoParticles"], Offset=10)

ApplicationMgr(
    TopAlg=[producer, transformer, consumer],
    EvtSel="NONE",
    EvtMax=10,
    ExtSvc=[EventDataSvc("EventDataSvc")],
    OutputLevel=INFO,
)