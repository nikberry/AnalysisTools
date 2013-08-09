/*
 * TTbarDiLeptonAnalyser.cpp
 *
 *  Created on: 8 Jul 2013
 *      Author: Phil
 */
#include "../../interface/Analysers/TTbarDiLeptonAnalyser.h"
#include "../../interface/BTagWeight.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

void TTbarDiLeptonAnalyser::analyse(const EventPtr event) {
	muMuSignalAnalysis(event);
	eESignalAnalysis(event);
	eMuSignalAnalysis(event);
}

void TTbarDiLeptonAnalyser::muMuSignalAnalysis(const EventPtr event) {

	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::MetCut)) {
			const JetCollection jets(topMuMuRefSelection_->cleanedJets(event));
			const JetCollection bJets(topMuMuRefSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topMuMuRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");

				metAnalyserMuMuRefSelection_->setScale(bjetWeight);
				metAnalyserMuMuRefSelection_->analyse(event, signalLepton);

			}
	}
}


void TTbarDiLeptonAnalyser::eESignalAnalysis(const EventPtr event) {

	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::MetCut)) {
			const JetCollection jets(topEERefSelection_->cleanedJets(event));
			const JetCollection bJets(topEERefSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEERefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			//get dilepton collection
			const ElectronCollection electrons = topEERefSelection_->signalElectrons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
				//MET
				metAnalyserEERefSelection_->setScale(bjetWeight);
				metAnalyserEERefSelection_->analyse(event, signalLepton);
				//DiElectron
				diElectronAnalyserEERefSelection_->setScale(bjetWeight);
			    //diElectronAnalyserEERefSelection_->analyse(event, electrons);
				diElectronAnalyserEERefSelection_->analyse(event);
			}
	}
}

void TTbarDiLeptonAnalyser::eMuSignalAnalysis(const EventPtr event) {

	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::AtLeastTwoGoodJets)) {
			const JetCollection jets(topEMuRefSelection_->cleanedJets(event));
			const JetCollection bJets(topEMuRefSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEMuRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");

				metAnalyserEMuRefSelection_->setScale(bjetWeight);
				metAnalyserEMuRefSelection_->analyse(event, signalLepton);

			}
	}
}

TTbarDiLeptonAnalyser::TTbarDiLeptonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuRefSelection_(new TopPairMuMuReferenceSelection()),
		topEERefSelection_(new TopPairEEReferenceSelection()),
		topEMuRefSelection_(new TopPairEMuReferenceSelection()),
		//signal regions MET
		metAnalyserMuMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
		metAnalyserEERefSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
		metAnalyserEMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
		//signal regions di electron
		diElectronAnalyserEERefSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiElectron")) //
		{

}

TTbarDiLeptonAnalyser::~TTbarDiLeptonAnalyser() {
}

void TTbarDiLeptonAnalyser::createHistograms() {

	//signal met
	metAnalyserMuMuRefSelection_->createHistograms();
	metAnalyserEERefSelection_->createHistograms();
	metAnalyserEMuRefSelection_->createHistograms();
	//signal met di electron
	diElectronAnalyserEERefSelection_->createHistograms();

}

}
