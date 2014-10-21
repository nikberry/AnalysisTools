/*********************************************************|                                                                                                                                                                                                                     
 *          TTbarLooseSelectionAnalyser.cpp               |
 *                                                        |
 *                  Author: N.Berry                       |
 *                                                        |
 *********************************************************/

#include "../../interface/Analysers/TTbarLooseSelectionAnalyser.h"
#include "../../interface/BTagWeight.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuLooseReferenceSelection.h"
#include "../../interface/Selections/TopPairEELooseReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuLooseReferenceSelection.h"

namespace BAT {

void TTbarLooseSelectionAnalyser::analyse(const EventPtr event) {
	muMuSignalAnalysis(event);
	eESignalAnalysis(event);
	eMuSignalAnalysis(event);
}

void TTbarLooseSelectionAnalyser::muMuSignalAnalysis(const EventPtr event) {

	if (topMuMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarMuMuLooseReferenceSelection::JustOneGoodPhotonPostSelection)) {
			const JetCollection jets(topMuMuLooseRefSelection_->cleanedJets(event));
			const JetCollection bJets(topMuMuLooseRefSelection_->cleanedBJets(event));
			unsigned int numberOfBjets(bJets.size());
			vector<double> bjetWeights;
			if (event->isRealData()) {
				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
					if (index == numberOfBjets)
						bjetWeights.push_back(1.);
					else
						bjetWeights.push_back(0);
				}
			} else
				bjetWeights = BjetWeights(jets, numberOfBjets);
			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);

			const LeptonPointer signalLepton = topMuMuLooseRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topMuMuLooseRefSelection_->signalPhotons(event);

			    //get dilepton collection
				const ElectronCollection electrons = topMuMuLooseRefSelection_->signalElectrons(event);
				const MuonCollection muons = topMuMuLooseRefSelection_->signalMuons(event);

				for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");

				//met
				metAnalyserMuMuRefSelection_->setScale(bjetWeight);
				metAnalyserMuMuRefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserMuMuRefSelection_->setScale(bjetWeight);
				jetAnalyserMuMuRefSelection_->analyse(event);

				//DiMuon
				diMuonAnalyserMuMuRefSelection_->setScale(bjetWeight);
				diMuonAnalyserMuMuRefSelection_->analyse(event, muons);

			    	//photons
			    	photonAnalyserMuMuRefSelection_->setScale(bjetWeight);
			    	photonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);

			    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");

			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
			    const PhotonCollection photonsMinuspassesPFChargedIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
			    
			    //n-passesDeltaRgammaMuons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaElectrons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");
			    //background shape
			    const PhotonCollection photonBackgroundShape = topMuMuLooseRefSelection_->nMinusOnePhotons(event, "backgroundShape");
			    photonAnalyserMuMuRefSelection_->analyse_NminusOnePhotons(event, photonBackgroundShape, jets, electrons, muons, "backgroundShape");
			
			///////CHECK THIS

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserMuMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}


void TTbarLooseSelectionAnalyser::eESignalAnalysis(const EventPtr event) {

	if (topEELooseRefSelection_->passesSelectionUpToStep(event, TTbarEELooseReferenceSelection::JustOneGoodPhotonPostSelection)) {

			const JetCollection jets(topEELooseRefSelection_->cleanedJets(event));
			const JetCollection bJets(topEELooseRefSelection_->cleanedBJets(event));
			unsigned int numberOfBjets(bJets.size());
			vector<double> bjetWeights;
			if (event->isRealData()) {
				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
					if (index == numberOfBjets)
						bjetWeights.push_back(1.);
					else
						bjetWeights.push_back(0);
				}
			} else
				bjetWeights = BjetWeights(jets, numberOfBjets);
			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);

			//this is for HT in the MET analyser but needs changing
			const LeptonPointer signalLepton = topEELooseRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topEELooseRefSelection_->signalPhotons(event);

			//get dilepton collection
			const ElectronCollection electrons = topEELooseRefSelection_->signalElectrons(event);
			const MuonCollection muons = topEELooseRefSelection_->signalMuons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
				//MET
				metAnalyserEERefSelection_->setScale(bjetWeight);
				metAnalyserEERefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEERefSelection_->setScale(bjetWeight);
				jetAnalyserEERefSelection_->analyse(event);

				//DiElectron
				diElectronAnalyserEERefSelection_->setScale(bjetWeight);
			    diElectronAnalyserEERefSelection_->analyse(event, electrons);

			    //photons
			    photonAnalyserEERefSelection_->setScale(bjetWeight);
			    photonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);

			    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topEELooseRefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");

			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topEELooseRefSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topEELooseRefSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
			    const PhotonCollection photonsMinuspassesPFChargedIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEELooseRefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
			    
			    //n-passesDeltaRgammaMuons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEELooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaElectrons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEELooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
			    photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");

	                     //background shape
                            const PhotonCollection photonBackgroundShape = topEELooseRefSelection_->nMinusOnePhotons(event, "backgroundShape");
                            photonAnalyserEERefSelection_->analyse_NminusOnePhotons(event, photonBackgroundShape, jets, electrons, muons, "backgroundShape");

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEERefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);
			    }

			}
	}
}

void TTbarLooseSelectionAnalyser::eMuSignalAnalysis(const EventPtr event) {

	if (topEMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarEMuLooseReferenceSelection::JustOneGoodPhotonPostSelection)) {

			const JetCollection jets(topEMuLooseRefSelection_->cleanedJets(event));
			const JetCollection bJets(topEMuLooseRefSelection_->cleanedBJets(event));
			unsigned int numberOfBjets(bJets.size());
			vector<double> bjetWeights;
			if (event->isRealData()) {
				for (unsigned int index = 0; index <= numberOfBjets; ++index) {
					if (index == numberOfBjets)
						bjetWeights.push_back(1.);
					else
						bjetWeights.push_back(0);
				}
			} else
				bjetWeights = BjetWeights(jets, numberOfBjets);

			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);
			const LeptonPointer signalLepton = topEMuLooseRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			//get dilepton collection
			const ElectronCollection electrons = topEMuLooseRefSelection_->signalElectrons(event);
			const MuonCollection muons = topEMuLooseRefSelection_->signalMuons(event);
			const PhotonCollection photons = topEMuLooseRefSelection_->signalPhotons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");

				//met
				metAnalyserEMuRefSelection_->setScale(bjetWeight);
				metAnalyserEMuRefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEMuRefSelection_->setScale(bjetWeight);
				jetAnalyserEMuRefSelection_->analyse(event);

				//DiLepton
				eMuAnalyserEMuRefSelection_->setScale(bjetWeight);
			    eMuAnalyserEMuRefSelection_->analyse(event, electrons, muons);

			    //photon
			    photonAnalyserEMuRefSelection_->setScale(bjetWeight);
			    photonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);

			    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");


			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
			    const PhotonCollection photonsMinuspassesPFChargedIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
		    
			    //n-passesDeltaRgammaMuons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaElectrons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEMuLooseRefSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
			    photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");

		             //background shape
                            const PhotonCollection photonBackgroundShape = topEMuLooseRefSelection_->nMinusOnePhotons(event, "backgroundShape");
                            photonAnalyserEMuRefSelection_->analyse_NminusOnePhotons(event, photonBackgroundShape, jets, electrons, muons, "backgroundShape");

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}

TTbarLooseSelectionAnalyser::TTbarLooseSelectionAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuLooseRefSelection_(new TopPairMuMuLooseReferenceSelection()),
		topEELooseRefSelection_(new TopPairEELooseReferenceSelection()),
		topEMuLooseRefSelection_(new TopPairEMuLooseReferenceSelection()),
		//signal regions MET
		metAnalyserMuMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
		metAnalyserEERefSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
		metAnalyserEMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
		//signal regions MET
		jetAnalyserMuMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Jets")), //
		jetAnalyserEERefSelection_(new JetAnalyser(histMan, histogramFolder + "/EE/Ref selection/Jets")), //
		jetAnalyserEMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Jets")),//
		//signal regions di electron
		diElectronAnalyserEERefSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiLepton")), //
		diMuonAnalyserMuMuRefSelection_(new DiMuonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/DiLepton")), //
		eMuAnalyserEMuRefSelection_(new EMuAnalyser(histMan, histogramFolder + "/EMu/Ref selection/DiLepton")), //
		//signal regions Photons
		photonAnalyserMuMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		photonAnalyserEERefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		photonAnalyserEMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")),//
		//tt photon analyser
		ttphotonAnalyserMuMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		ttphotonAnalyserEERefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		ttphotonAnalyserEMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")) //
		{

}

TTbarLooseSelectionAnalyser::~TTbarLooseSelectionAnalyser() {
}

void TTbarLooseSelectionAnalyser::createHistograms() {

	//signal met
	metAnalyserMuMuRefSelection_->createHistograms();
	metAnalyserEERefSelection_->createHistograms();
	metAnalyserEMuRefSelection_->createHistograms();
	//signal jets
	jetAnalyserMuMuRefSelection_->createHistograms();
	jetAnalyserEERefSelection_->createHistograms();
	jetAnalyserEMuRefSelection_->createHistograms();
	//signal met dielectron
	diElectronAnalyserEERefSelection_->createHistograms();
	diMuonAnalyserMuMuRefSelection_->createHistograms();
	eMuAnalyserEMuRefSelection_->createHistograms();
	//signal photons
	photonAnalyserEERefSelection_->createHistograms();
	photonAnalyserMuMuRefSelection_->createHistograms();
	photonAnalyserEMuRefSelection_->createHistograms();
	//for ttbar
	ttphotonAnalyserMuMuRefSelection_->createHistograms();
	ttphotonAnalyserEERefSelection_->createHistograms();
	ttphotonAnalyserEMuRefSelection_->createHistograms();
}

}
