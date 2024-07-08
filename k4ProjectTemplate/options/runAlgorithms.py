from Gaudi.Configuration import INFO
from Configurables import (
    myProducer,
    myTransformer,
    myConsumer,
)
from k4FWCore import ApplicationMgr
from Configurables import EventDataSvc
from k4FWCore import IOSvc

producer = myProducer("Producer", OutputCollection=["MCParticles"])

transformer = myTransformer("Transformer", InputCollection=["MCParticles"], 
                                OutputCollection=["RecoParticles"])

consumer = myConsumer("Consumer", MCInputCollection=["MCParticles"],
                                RecoInputCollection = ["RecoParticles"], Offset=10)

iosvc = IOSvc("IOSvc")
iosvc.output = "output_k4test_runAlgoritms.root"
iosvc.outputCommands = ["keep *"]

ApplicationMgr(
    TopAlg=[producer, transformer, consumer],
    EvtSel="NONE",
    EvtMax=10,
    ExtSvc=[EventDataSvc("EventDataSvc")],
    OutputLevel=INFO,
)