/*
 * TTbarPhotonAnalyser.cpp
 *
 *  Created on: 10 Aug 2013
 *      Author: Phil
 */

#include "../../interface/Analysers/TTbarPhotonAnalyser.h"
#include "../../interface/BTagWeight.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

void TTbarPhotonAnalyser::analyse(const EventPtr event) {
	muMuSignalAnalysis(event);
	eESignalAnalysis(event);
	eMuSignalAnalysis(event);
}

void TTbarPhotonAnalyser::muMuSignalAnalysis(const EventPtr event) {

	if (topMuMuPhotonSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::JustOneGoodPhoton)) {
			const JetCollection jets(topMuMuPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topMuMuPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topMuMuPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topMuMuPhotonSelection_->signalPhotons(event);

			        //get dilepton collection
			        const ElectronCollection electrons = topMuMuPhotonSelection_->signalElectrons(event);
				const MuonCollection muons = topMuMuPhotonSelection_->signalMuons(event);

				for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");

				//met
				metAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				metAnalyserMuMuPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				jetAnalyserMuMuPhotonSelection_->analyse(event);

				//DiMuon
				diMuonAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				diMuonAnalyserMuMuPhotonSelection_->analyse(event, muons);

			    	//photons
			    	photonAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
			    	photonAnalyserMuMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
				//Vertices
				//vertexAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserMuMuPhotonSelection_->analyse(event);
				

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserMuMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}


void TTbarPhotonAnalyser::eESignalAnalysis(const EventPtr event) {

	if (topEEPhotonSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::JustOneGoodPhoton)) {

			const JetCollection jets(topEEPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topEEPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEEPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topEEPhotonSelection_->signalPhotons(event);

			//get dilepton collection
			const ElectronCollection electrons = topEEPhotonSelection_->signalElectrons(event);
			const MuonCollection muons = topEEPhotonSelection_->signalMuons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
				//MET
				metAnalyserEEPhotonSelection_->setScale(bjetWeight);
				metAnalyserEEPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEEPhotonSelection_->setScale(bjetWeight);
				jetAnalyserEEPhotonSelection_->analyse(event);

				//DiElectron
				diElectronAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    	diElectronAnalyserEEPhotonSelection_->analyse(event, electrons);

			    	//photons
			    	photonAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    	photonAnalyserEEPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
				//Vertices
				//vertexAnalyserEEPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserEEPhotonSelection_->analyse(event);
				

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEERefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}

void TTbarPhotonAnalyser::eMuSignalAnalysis(const EventPtr event) {

	if (topEMuPhotonSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::JustOneGoodPhoton)) {

			const JetCollection jets(topEMuPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topEMuPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEMuPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			//get dilepton collection
			const ElectronCollection electrons = topEMuPhotonSelection_->signalElectrons(event);
			const MuonCollection muons = topEMuPhotonSelection_->signalMuons(event);
			const PhotonCollection photons = topEMuPhotonSelection_->signalPhotons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");

				//met
				metAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				metAnalyserEMuPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				jetAnalyserEMuPhotonSelection_->analyse(event);

				//DiLepton
				eMuAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    	eMuAnalyserEMuPhotonSelection_->analyse(event, electrons, muons);

			    	//photon
			    	photonAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    	photonAnalyserEMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
				//Vertices
				//vertexAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserEMuPhotonSelection_->analyse(event);
				

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}

TTbarPhotonAnalyser::TTbarPhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuPhotonSelection_(new TopPairMuMuReferenceSelection()),
		topEEPhotonSelection_(new TopPairEEReferenceSelection()),
		topEMuPhotonSelection_(new TopPairEMuReferenceSelection()),
		//signal regions MET
		metAnalyserMuMuPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
		metAnalyserEEPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
		metAnalyserEMuPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
		//signal regions MET
		jetAnalyserMuMuPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Jets")), //
		jetAnalyserEEPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/EE/Ref selection/Jets")), //
		jetAnalyserEMuPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Jets")),//
		//signal regions di electron
		diElectronAnalyserEEPhotonSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiElectron")), //
		diMuonAnalyserMuMuPhotonSelection_(new DiMuonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/DiMuon")), //
		eMuAnalyserEMuPhotonSelection_(new EMuAnalyser(histMan, histogramFolder + "/EMu/Ref selection/DiLepton")), //
		//signal regions Photons
		photonAnalyserMuMuPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		photonAnalyserEEPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		photonAnalyserEMuPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")),//
		//tt photon analyser
		ttphotonAnalyserMuMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		ttphotonAnalyserEERefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		ttphotonAnalyserEMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")) //
		//vertices
		//vertexAnalyserMuMuPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Vertex")), //
		//vertexAnalyserEEPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/EE/Ref selection/Vertex")), //
		//vertexAnalyserEMuPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Vertex")),//
		{

}

TTbarPhotonAnalyser::~TTbarPhotonAnalyser() {
}

void TTbarPhotonAnalyser::createHistograms() {

	//signal met
	metAnalyserMuMuPhotonSelection_->createHistograms();
	metAnalyserEEPhotonSelection_->createHistograms();
	metAnalyserEMuPhotonSelection_->createHistograms();
	//signal jets
	jetAnalyserMuMuPhotonSelection_->createHistograms();
	jetAnalyserEEPhotonSelection_->createHistograms();
	jetAnalyserEMuPhotonSelection_->createHistograms();
	//signal met di electron
	diElectronAnalyserEEPhotonSelection_->createHistograms();
	diMuonAnalyserMuMuPhotonSelection_->createHistograms();
	eMuAnalyserEMuPhotonSelection_->createHistograms();
	//signal photons
	photonAnalyserEEPhotonSelection_->createHistograms();
	photonAnalyserMuMuPhotonSelection_->createHistograms();
	photonAnalyserEMuPhotonSelection_->createHistograms();
	//for ttbar
	ttphotonAnalyserMuMuRefSelection_->createHistograms();
	ttphotonAnalyserEERefSelection_->createHistograms();
	ttphotonAnalyserEMuRefSelection_->createHistograms();
	//vertices
//	vertexAnalyserMuMuPhotonSelection_->createHistograms();
//	vertexAnalyserEEPhotonSelection_->createHistograms();
//	vertexAnalyserEMuPhotonSelection_->createHistograms();

}

}
