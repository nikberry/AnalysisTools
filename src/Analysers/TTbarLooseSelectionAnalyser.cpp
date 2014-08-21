// /*********************************************************|                                                                                                                                                                                                                     
//  *          TTbarLooseSelectionAnalyser.cpp               |
//  *                                                        |
//  *                  Author: N.Berry                       |
//  *                                                        |
//  *********************************************************/
// 
// #include "../../interface/Analysers/TTbarLooseSelectionAnalyser.h"
// #include "../../interface/GlobalVariables.h"
// #include "../../interface/BTagWeight.h"
// #include "../../interface/Selections/TopPairMuMuLooseReferenceSelection.h"
// #include "../../interface/Selections/TopPairEELooseReferenceSelection.h"
// #include "../../interface/Selections/TopPairEMuLooseReferenceSelection.h"
// 
// namespace BAT {
// 
// void TTbarLooseSelectionAnalyser::analyse(const EventPtr event) {
// 	muMuSignalAnalysis(event);
// 	eESignalAnalysis(event);
// 	eMuSignalAnalysis(event);
// }
// 
// void TTbarLooseSelectionAnalyser::muMuSignalAnalysis(const EventPtr event) {
// 
// 	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuLooseReferenceSelection:JustOneGoodPhotonPostSelection)) {
// 			const JetCollection jets(topMuMuRefSelection_->cleanedJets(event));
// 			const JetCollection bJets(topMuMuRefSelection_->cleanedBJets(event));
// 			unsigned int numberOfBjets(bJets.size());
// 			vector<double> bjetWeights;
// 			if (event->isRealData()) {
// 				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
// 					if (index == numberOfBjets)
// 						bjetWeights.push_back(1.);
// 					else
// 						bjetWeights.push_back(0);
// 				}
// 			} else
// 				bjetWeights = BjetWeights(jets, numberOfBjets);
// 			histMan_->setCurrentJetBin(jets.size());
// 			histMan_->setCurrentBJetBin(numberOfBjets);
// 
// 			const LeptonPointer signalLepton = topMuMuRefSelection_->signalLepton(event);
// 			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
// 			const PhotonCollection photons = topMuMuRefSelection_->signalPhotons(event);
// 
// 			    //get dilepton collection
// 				const ElectronCollection electrons = topMuMuRefSelection_->signalElectrons(event);
// 				const MuonCollection muons = topMuMuRefSelection_->signalMuons(event);
// 
// 				for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
// 
// 				double bjetWeight = bjetWeights.at(weightIndex);
// 				histMan_->setCurrentBJetBin(weightIndex);
// 				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");
// 
// 				//met
// 				metAnalyserMuMuRefSelection_->setScale(bjetWeight);
// 				metAnalyserMuMuRefSelection_->analyse(event, signalLepton);
// 
// 				//jets
// 				jetAnalyserMuMuRefSelection_->setScale(bjetWeight);
// 				jetAnalyserMuMuRefSelection_->analyse(event);
// 
// 				//DiMuon
// 				diMuonAnalyserMuMuRefSelection_->setScale(bjetWeight);
// 				diMuonAnalyserMuMuRefSelection_->analyse(event, muons);
// 
// 			    	//photons
// 			    	photonAnalyserMuMuRefSelection_->setScale(bjetWeight);
// 			    	photonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);
// 
// 			    //n-EtAndEta photons
// 			    const PhotonCollection photonsMinusEtAndEta = topMuMuRefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");
// 
// 			    //n-passesHOverE photons
// 			    const PhotonCollection photonsMinusHOverE = topMuMuRefSelection_->nMinusOnePhotons(event, "passesHOverE");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");
// 
// 			    //n-passesShowerShape photons
// 			    const PhotonCollection photonsMinuspassesShowerShape = topMuMuRefSelection_->nMinusOnePhotons(event, "passesShowerShape");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");
// 
// 			    //n-passesPFChargedIso photons
// 			    const PhotonCollection photonsMinuspassesPFChargedIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");
// 
// 			    //n-passesPFNeutralIso photons
// 			    const PhotonCollection photonsMinuspassesPFNeutralIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");
// 
// 			    //n-passesPFPhotonIso photons
// 			    const PhotonCollection photonsMinuspassesPFPhotonIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
// 			    
// 			    //n-passesphoSCChIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCChIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");
// 
// 			    //n-passesphoSCNuIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCNuIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");
// 
// 			    //n-passesphoSCPhIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCPhIso = topMuMuRefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
// 			    
// 			    //n-passesDeltaRgammaMuons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topMuMuRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
// 			    
// 			    //n-passesDeltaRgammaElectrons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topMuMuRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
// 			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");
// 
// 			    if(event->getDataType() == DataType::TTJets){
// 			    ttphotonAnalyserMuMuRefSelection_->setScale(bjetWeight);
// 			    ttphotonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);
// 			    }
// 			}
// 	}
// }
// 
// 
// void TTbarLooseSelectionAnalyser::eESignalAnalysis(const EventPtr event) {
// 
// 	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEELooseReferenceSelection::JustOneGoodPhotonPostSelection)) {
// 
// 			const JetCollection jets(topEERefSelection_->cleanedJets(event));
// 			const JetCollection bJets(topEERefSelection_->cleanedBJets(event));
// 			unsigned int numberOfBjets(bJets.size());
// 			vector<double> bjetWeights;
// 			if (event->isRealData()) {
// 				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
// 					if (index == numberOfBjets)
// 						bjetWeights.push_back(1.);
// 					else
// 						bjetWeights.push_back(0);
// 				}
// 			} else
// 				bjetWeights = BjetWeights(jets, numberOfBjets);
// 			histMan_->setCurrentJetBin(jets.size());
// 			histMan_->setCurrentBJetBin(numberOfBjets);
// 
// 			//this is for HT in the MET analyser but needs changing
// 			const LeptonPointer signalLepton = topEERefSelection_->signalLepton(event);
// 			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
// 			const PhotonCollection photons = topEERefSelection_->signalPhotons(event);
// 
// 			//get dilepton collection
// 			const ElectronCollection electrons = topEERefSelection_->signalElectrons(event);
// 			const MuonCollection muons = topEERefSelection_->signalMuons(event);
// 
// 			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
// 
// 				double bjetWeight = bjetWeights.at(weightIndex);
// 				histMan_->setCurrentBJetBin(weightIndex);
// 				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
// 				//MET
// 				metAnalyserEERefSelection_->setScale(bjetWeight);
// 				metAnalyserEERefSelection_->analyse(event, signalLepton);
// 
// 				//jets
// 				jetAnalyserEERefSelection_->setScale(bjetWeight);
// 				jetAnalyserEERefSelection_->analyse(event);
// 
// 				//DiElectron
// 				diElectronAnalyserEERefSelection_->setScale(bjetWeight);
// 			    diElectronAnalyserEERefSelection_->analyse(event, electrons);
// 
// 			    //photons
// 			    photonAnalyserEERefSelection_->setScale(bjetWeight);
// 			    photonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);
// 
// 			    //n-EtAndEta photons
// 			    const PhotonCollection photonsMinusEtAndEta = topEERefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");
// 
// 			    //n-passesHOverE photons
// 			    const PhotonCollection photonsMinusHOverE = topEERefSelection_->nMinusOnePhotons(event, "passesHOverE");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");
// 
// 			    //n-passesShowerShape photons
// 			    const PhotonCollection photonsMinuspassesShowerShape = topEERefSelection_->nMinusOnePhotons(event, "passesShowerShape");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");
// 
// 			    //n-passesPFChargedIso photons
// 			    const PhotonCollection photonsMinuspassesPFChargedIso = topEERefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");
// 
// 			    //n-passesPFNeutralIso photons
// 			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEERefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");
// 
// 			    //n-passesPFPhotonIso photons
// 			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEERefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
// 			    
// 			    //n-passesphoSCChIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCChIso = topEERefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");
// 
// 			    //n-passesphoSCNuIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEERefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");
// 
// 			    //n-passesphoSCPhIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEERefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
// 			    
// 			    //n-passesDeltaRgammaMuons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEERefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
// 			    
// 			    //n-passesDeltaRgammaElectrons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEERefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
// 			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");
// 
// 
// 			    if(event->getDataType() == DataType::TTJets){
// 			    ttphotonAnalyserEERefSelection_->setScale(bjetWeight);
// 			    ttphotonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);
// 			    }
// 
// 			}
// 	}
// }
// 
// void TTbarLooseSelectionAnalyser::eMuSignalAnalysis(const EventPtr event) {
// 
// 	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuLooseReferenceSelection::AJustOneGoodPhotonPostSelection)) {
// 
// 			const JetCollection jets(topEMuRefSelection_->cleanedJets(event));
// 			const JetCollection bJets(topEMuRefSelection_->cleanedBJets(event));
// 			unsigned int numberOfBjets(bJets.size());
// 			vector<double> bjetWeights;
// 			if (event->isRealData()) {
// 				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
// 					if (index == numberOfBjets)
// 						bjetWeights.push_back(1.);
// 					else
// 						bjetWeights.push_back(0);
// 				}
// 			} else
// 				bjetWeights = BjetWeights(jets, numberOfBjets);
// 
// 			histMan_->setCurrentJetBin(jets.size());
// 			histMan_->setCurrentBJetBin(numberOfBjets);
// 			const LeptonPointer signalLepton = topEMuRefSelection_->signalLepton(event);
// 			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
// 
// 			//get dilepton collection
// 			const ElectronCollection electrons = topEMuRefSelection_->signalElectrons(event);
// 			const MuonCollection muons = topEMuRefSelection_->signalMuons(event);
// 			const PhotonCollection photons = topEMuRefSelection_->signalPhotons(event);
// 
// 			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
// 
// 				double bjetWeight = bjetWeights.at(weightIndex);
// 				histMan_->setCurrentBJetBin(weightIndex);
// 				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");
// 
// 				//met
// 				metAnalyserEMuRefSelection_->setScale(bjetWeight);
// 				metAnalyserEMuRefSelection_->analyse(event, signalLepton);
// 
// 				//jets
// 				jetAnalyserEMuRefSelection_->setScale(bjetWeight);
// 				jetAnalyserEMuRefSelection_->analyse(event);
// 
// 				//DiLepton
// 				eMuAnalyserEMuRefSelection_->setScale(bjetWeight);
// 			    eMuAnalyserEMuRefSelection_->analyse(event, electrons, muons);
// 
// 			    //photon
// 			    photonAnalyserEMuRefSelection_->setScale(bjetWeight);
// 			    photonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);
// 
// 			    //n-EtAndEta photons
// 			    const PhotonCollection photonsMinusEtAndEta = topEMuRefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");
// 
// 
// 			    //n-passesHOverE photons
// 			    const PhotonCollection photonsMinusHOverE = topEMuRefSelection_->nMinusOnePhotons(event, "passesHOverE");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");
// 
// 			    //n-passesShowerShape photons
// 			    const PhotonCollection photonsMinuspassesShowerShape = topEMuRefSelection_->nMinusOnePhotons(event, "passesShowerShape");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");
// 
// 			    //n-passesPFChargedIso photons
// 			    const PhotonCollection photonsMinuspassesPFChargedIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");
// 
// 			    //n-passesPFNeutralIso photons
// 			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");
// 
// 			    //n-passesPFPhotonIso photons
// 			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
// 			    
// 			    //n-passesphoSCChIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCChIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");
// 
// 			    //n-passesphoSCNuIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");
// 
// 			    //n-passesphoSCPhIso photons
// 			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEMuRefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
// 		    
// 			    //n-passesDeltaRgammaMuons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEMuRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
// 			    
// 			    //n-passesDeltaRgammaElectrons photons
// 			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEMuRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
// 			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");
// 
// 
// 			    if(event->getDataType() == DataType::TTJets){
// 			    ttphotonAnalyserEMuRefSelection_->setScale(bjetWeight);
// 			    ttphotonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);
// 			    }
// 			}
// 	}
// }
// 
// TTbarLooseSelectionAnalyser::TTbarLooseSelectionAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
// 		BasicAnalyser(histMan, histogramFolder), //
// 		topMuMuRefSelection_(new TopPairMuMuLooseReferenceSelection()),
// 		topEERefSelection_(new TopPairEELooseReferenceSelection()),
// 		topEMuRefSelection_(new TopPairEMuLooseReferenceSelection()),
// 		//signal regions MET
// 		metAnalyserMuMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
// 		metAnalyserEERefSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
// 		metAnalyserEMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
// 		//signal regions MET
// 		jetAnalyserMuMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Jets")), //
// 		jetAnalyserEERefSelection_(new JetAnalyser(histMan, histogramFolder + "/EE/Ref selection/Jets")), //
// 		jetAnalyserEMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Jets")),//
// 		//signal regions di electron
// 		diElectronAnalyserEERefSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiLepton")), //
// 		diMuonAnalyserMuMuRefSelection_(new DiMuonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/DiLepton")), //
// 		eMuAnalyserEMuRefSelection_(new EMuAnalyser(histMan, histogramFolder + "/EMu/Ref selection/DiLepton")), //
// 		//signal regions Photons
// 		photonAnalyserMuMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
// 		photonAnalyserEERefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
// 		photonAnalyserEMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")),//
// 		//tt photon analyser
// 		ttphotonAnalyserMuMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
// 		ttphotonAnalyserEERefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
// 		ttphotonAnalyserEMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")) //
// 		{
// 
// }
// 
// TTbarLooseSelectionAnalyser::~TTbarLooseSelectionAnalyser() {
// }
// 
// void TTbarLooseSelectionAnalyser::createHistograms() {
// 
// 	//signal met
// 	metAnalyserMuMuRefSelection_->createHistograms();
// 	metAnalyserEERefSelection_->createHistograms();
// 	metAnalyserEMuRefSelection_->createHistograms();
// 	//signal jets
// 	jetAnalyserMuMuRefSelection_->createHistograms();
// 	jetAnalyserEERefSelection_->createHistograms();
// 	jetAnalyserEMuRefSelection_->createHistograms();
// 	//signal met di electron
// 	diElectronAnalyserEERefSelection_->createHistograms();
// 	diMuonAnalyserMuMuRefSelection_->createHistograms();
// 	eMuAnalyserEMuRefSelection_->createHistograms();
// 	//signal photons
// 	photonAnalyserEERefSelection_->createHistograms();
// 	photonAnalyserMuMuRefSelection_->createHistograms();
// 	photonAnalyserEMuRefSelection_->createHistograms();
// 	//for ttbar
// 	ttphotonAnalyserMuMuRefSelection_->createHistograms();
// 	ttphotonAnalyserEERefSelection_->createHistograms();
// 	ttphotonAnalyserEMuRefSelection_->createHistograms();
// }
// 
// }
