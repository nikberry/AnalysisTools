/*
 * EventCountAnalyser.cpp
 *
 *  Created on: 24 Mar 2011
 *      Author: kreczko
 */

#include "../../interface/Analysers/EventCountAnalyser.h"
#include "../../interface/BTagWeight.h"

namespace BAT {

void EventCountAnalyser::analyse(const EventPtr event) {

	//	individualCuts(event);
	
	topMuMuReferenceSelection(event);
	topMuMuReferenceSelectionUnweighted(event);
	
	topEEReferenceSelection(event);
	topEEReferenceSelectionUnweighted(event);
	
	topEMuReferenceSelection(event);
	topEMuReferenceSelectionUnweighted(event);


        topMuMuLooseReferenceSelection(event);
        topMuMuLooseReferenceSelectionUnweighted(event);
        
        topEELooseReferenceSelection(event);
        topEELooseReferenceSelectionUnweighted(event);
        
        topEMuLooseReferenceSelection(event);
        topEMuLooseReferenceSelectionUnweighted(event);
}

void EventCountAnalyser::individualCuts(const EventPtr event) {

	if(topMuMuRefSelection_->passesSelectionUpToStep(event, 1)) {
				cout << "run: " << event->runnumber() << " lumi: " << event->lumiblock() << " evt: " << event->eventnumber() << endl;
/*				if(event->isBeamScraping() || !event->passesHBHENoiseFilter() || !event->passesCSCTightBeamHaloFilter() || !event->passesHCALLaserFilter()
						|| !event->passesECALDeadCellFilter() || !event->passesTrackingFailureFilter() || !event->passesEEBadSCFilter()){

							if(event->isBeamScraping())
								cout << "fail beam scrap" << endl;
							if(!event->passesHBHENoiseFilter())
								cout << "fail HBHE noise filter" << endl;
							if(!event->passesCSCTightBeamHaloFilter())
								cout << "fail CSCTightBeamHaloFilter" << endl;
							if(!event->passesHCALLaserFilter())
								cout << "fail HCALLaserFilter" << endl;
							if(!event->passesECALDeadCellTPFilter())
								cout << "fail ECALDeadCellTPFilter" << endl;
							if(!event->passesTrackingFailureFilter())
								cout << "fail TrackingFailureFilter" << endl;
							if(!event->passesEEBadSCFilter())
								cout << "fail EEBadSCFilter()" << endl;
							if(!event->passesECALLaserCorrFilter())
								cout << "fail ECALLaserCorrFilter()" << endl;
							if(!event->passesTrackingPOGFilters())
								cout << "fail TrackingPOGFilters()" << endl;
				}*/
	}

}

//*************************************Normal Selection**************************************//

void EventCountAnalyser::topMuMuReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	//Trigger SF
	if (!event->isRealData() && topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::EventCleaningAndTrigger)) 
		if(Globals::TriggerSFUp == true)
			scale_ *= 0.977; 
		else if(Globals::TriggerSFDown == true)
			scale_ *= 0.957;
		else
			scale_ *= 0.967;
		
	else 
		scale_ = 1;

	//Muon efficiencies
	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::DiMuonSelection)) { 

		const MuonCollection signalMuons = topMuMuRefSelection_->signalMuons(event);
//		const MuonPointer signalMuon(boost::static_pointer_cast<Muon>(signalMuons));
		const MuonPointer muon1(signalMuons.at(0));
		const MuonPointer muon2(signalMuons.at(1));

		double efficiencyCorrection1 = event->isRealData() ? 1. : muon1->getEfficiencyCorrection();
		double efficiencyCorrection2 = event->isRealData() ? 1. : muon2->getEfficiencyCorrection();
		
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.967; //(1) Muon 1, (2) Muon 2
	}else{
		scale_ =1;
	}

		

 	//use bjet weights in histograms for muons
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

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 		if(weightIndex>0)
 			weight_ge1b += b_weight;
 		}
	
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;

	histMan_->H1D("TTbarMuMuRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
	
		bool passesStep = topMuMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuRefSelection_->passesSelectionUpToStep(event, step);
		
		if(step >= TTbarMuMuReferenceSelection::AtLeastOneBtag){
			weight_ *= weight_ge1b;
			}
		
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topMuMuReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarMuMuRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topMuMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuRefSelection_->passesSelectionUpToStep(event, step);
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

void EventCountAnalyser::topEEReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	
	//Trigger SFs
	if (!event->isRealData() && topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::EventCleaningAndTrigger)) 
             if(Globals::TriggerSFUp == true)
                     scale_ *= 0.986; 
             else if(Globals::TriggerSFDown == true)
                     scale_ *= 0.962;
             else
			scale_ *= 0.974; 
	else 
		scale_ = 1;

	//Electron Efficiencies 
	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::DiElectronSelection)) {

	const ElectronCollection signalElectrons = topEERefSelection_->signalElectrons(event);
//	const ElectronPointer signalMuon(boost::static_pointer_cast<Muon>(signalMuons));
	const ElectronPointer electron1(signalElectrons.at(0));
	const ElectronPointer electron2(signalElectrons.at(1));

	double efficiencyCorrection1 = event->isRealData() ? 1. : electron1->getEfficiencyCorrection();
	double efficiencyCorrection2 = event->isRealData() ? 1. : electron2->getEfficiencyCorrection();
	
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.974;
	}else{
		scale_ =1;
	}


 	//use bjet weights in histograms for muons
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

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}

 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;

	histMan_->H1D("TTbarEERefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEERefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {

		bool passesStep = topEERefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEERefSelection_->passesSelectionUpToStep(event, step);

		if(step >= TTbarEEReferenceSelection::AtLeastOneBtag){
			weight_ *= weight_ge1b;
			}

		if (passesStepUpTo)
			histMan_->H1D("TTbarEERefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEERefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEEReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEERefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEERefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEERefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEERefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEERefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEERefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

 void EventCountAnalyser::topEMuReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	
	//Trigger SF
	if (!event->isRealData() && topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::EventCleaningAndTrigger)) 
             if(Globals::TriggerSFUp == true)
                     scale_ *= 0.964; 
             else if(Globals::TriggerSFDown == true)
                     scale_ *= 0.942;
             else
			scale_ *= 0.953; 
	else 
		scale_ = 1;

	//EMu SF's
 	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::DiLeptonSelection)) {

	const MuonCollection signalMuons = topEMuRefSelection_->signalMuons(event);
	const ElectronCollection signalElectrons = topEMuRefSelection_->signalElectrons(event);
	
	const ElectronPointer electron(signalElectrons.at(0));
	const MuonPointer muon(signalMuons.at(0));

	double efficiencyCorrection1 = event->isRealData() ? 1. : muon->getEfficiencyCorrection();
	double efficiencyCorrection2 = event->isRealData() ? 1. : electron->getEfficiencyCorrection();
	
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.953;
	}else{
		scale_ =1;
	}

	//photon efficiencies - don't need due to the nature of analysis
//         if(topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::AtLeastOnePhotonPostSelection)) {
//         
//                 const PhotonCollection signalPhotons = topEMuRefSelection_->signalPhotons(event);
//                 
//                 for(unsigned int i = 0; i<signalPhotons.size(); i++){
//                 
//                         const PhotonPointer photon(signalPhotons[i]);
//                         
//                         double efficiencyCorrection = event->isRealData() ? 1 : photon->getEfficiencyCorrection();
//                         
//                         scale_ = efficiencyCorrection;
//                 }                                                                                                                                                                                                                                                        
//                 
//                 //scale_ = efficiencyCorrection;
//         } else {
//                 scale_ = 1;
//         }

 	//use bjet weights in histograms for muons
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


 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;
	

	histMan_->H1D("TTbarEMuRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
	
		bool passesStep = topEMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEMuRefSelection_->passesSelectionUpToStep(event, step);
		
		if(step >= TTbarEMuReferenceSelection::AtLeastOneBtag){
			weight_ *= weight_ge1b;
			}
		
		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEMuReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEMuRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEMuRefSelection_->passesSelectionStep(event, step);

		bool passesStepUpTo = topEMuRefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

//*********************************Loose selection*****************************************//

void EventCountAnalyser::topMuMuLooseReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	//Trigger SF
	if (!event->isRealData() && topMuMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarMuMuLooseReferenceSelection::EventCleaningAndTrigger)) 
		if(Globals::TriggerSFUp == true)
			scale_ *= 0.977; 
		else if(Globals::TriggerSFDown == true)
			scale_ *= 0.957;
		else
			scale_ *= 0.967;
		
	else 
		scale_ = 1;

	//Muon efficiencies
	if (topMuMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarMuMuLooseReferenceSelection::DiMuonSelection)) { 

		const MuonCollection signalMuons = topMuMuLooseRefSelection_->signalMuons(event);
//		const MuonPointer signalMuon(boost::static_pointer_cast<Muon>(signalMuons));
		const MuonPointer muon1(signalMuons.at(0));
		const MuonPointer muon2(signalMuons.at(1));

		double efficiencyCorrection1 = event->isRealData() ? 1. : muon1->getEfficiencyCorrection();
		double efficiencyCorrection2 = event->isRealData() ? 1. : muon2->getEfficiencyCorrection();
		
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.967; //(1) Muon 1, (2) Muon 2
	}else{
		scale_ =1;
	}

		

 	//use bjet weights in histograms for muons
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

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 		if(weightIndex>0)
 			weight_ge1b += b_weight;
 		}
	
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;

	histMan_->H1D("TTbarMuMuLooseRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuLooseRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
	
		bool passesStep = topMuMuLooseRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuLooseRefSelection_->passesSelectionUpToStep(event, step);
		
		
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuLooseRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuLooseRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topMuMuLooseReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarMuMuLooseRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuLooseRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topMuMuLooseRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuLooseRefSelection_->passesSelectionUpToStep(event, step);
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuLooseRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuLooseRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

void EventCountAnalyser::topEELooseReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	
	//Trigger SFs
	if (!event->isRealData() && topEELooseRefSelection_->passesSelectionUpToStep(event, TTbarEELooseReferenceSelection::EventCleaningAndTrigger)) 
             if(Globals::TriggerSFUp == true)
                     scale_ *= 0.986; 
             else if(Globals::TriggerSFDown == true)
                     scale_ *= 0.962;
             else
			scale_ *= 0.974; 
	else 
		scale_ = 1;

	//Electron Efficiencies 
	if (topEELooseRefSelection_->passesSelectionUpToStep(event, TTbarEELooseReferenceSelection::DiElectronSelection)) {

	const ElectronCollection signalElectrons = topEELooseRefSelection_->signalElectrons(event);
//	const ElectronPointer signalMuon(boost::static_pointer_cast<Muon>(signalMuons));
	const ElectronPointer electron1(signalElectrons.at(0));
	const ElectronPointer electron2(signalElectrons.at(1));

	double efficiencyCorrection1 = event->isRealData() ? 1. : electron1->getEfficiencyCorrection();
	double efficiencyCorrection2 = event->isRealData() ? 1. : electron2->getEfficiencyCorrection();
	
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.974;
	}else{
		scale_ =1;
	}


 	//use bjet weights in histograms for muons
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

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}

 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;

	histMan_->H1D("TTbarEELooseRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEELooseRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {

		bool passesStep = topEELooseRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEELooseRefSelection_->passesSelectionUpToStep(event, step);

	
		if (passesStepUpTo)
			histMan_->H1D("TTbarEELooseRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEELooseRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEELooseReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEELooseRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEELooseRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEELooseRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEELooseRefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEELooseRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEELooseRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

 void EventCountAnalyser::topEMuLooseReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	
	//Trigger SF
	if (!event->isRealData() && topEMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarEMuLooseReferenceSelection::EventCleaningAndTrigger)) 
             if(Globals::TriggerSFUp == true)
                     scale_ *= 0.964; 
             else if(Globals::TriggerSFDown == true)
                     scale_ *= 0.942;
             else
			scale_ *= 0.953; 
	else 
		scale_ = 1;

	//EMu SF's
 	if (topEMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarEMuLooseReferenceSelection::DiLeptonSelection)) {

	const MuonCollection signalMuons = topEMuLooseRefSelection_->signalMuons(event);
	const ElectronCollection signalElectrons = topEMuLooseRefSelection_->signalElectrons(event);
	
	const ElectronPointer electron(signalElectrons.at(0));
	const MuonPointer muon(signalMuons.at(0));

	double efficiencyCorrection1 = event->isRealData() ? 1. : muon->getEfficiencyCorrection();
	double efficiencyCorrection2 = event->isRealData() ? 1. : electron->getEfficiencyCorrection();
	
	 	scale_ = efficiencyCorrection1*efficiencyCorrection2;//*0.953;
	}else{
		scale_ =1;
	}

	//photon efficiencies - don't need due to the nature of analysis
//         if(topEMuLooseRefSelection_->passesSelectionUpToStep(event, TTbarEMuLooseReferenceSelection::AtLeastOnePhotonPostSelection)) {
//         
//                 const PhotonCollection signalPhotons = topEMuLooseRefSelection_->signalPhotons(event);
//                 
//                 for(unsigned int i = 0; i<signalPhotons.size(); i++){
//                 
//                         const PhotonPointer photon(signalPhotons[i]);
//                         
//                         double efficiencyCorrection = event->isRealData() ? 1 : photon->getEfficiencyCorrection();
//                         
//                         scale_ = efficiencyCorrection;
//                 }                                                                                                                                                                                                                                                        
//                 
//                 //scale_ = efficiencyCorrection;
//         } else {
//                 scale_ = 1;
//         }

 	//use bjet weights in histograms for muons
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


 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ ;
	

	histMan_->H1D("TTbarEMuLooseRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuLooseRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
	
		bool passesStep = topEMuLooseRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEMuLooseRefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuLooseRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuLooseRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEMuLooseReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEMuLooseRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuLooseRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEMuLooseRefSelection_->passesSelectionStep(event, step);

		bool passesStepUpTo = topEMuLooseRefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuLooseRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuLooseRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

void EventCountAnalyser::createHistograms() {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	const boost::array<string, 1> refSelections_dimuon = { {"TTbarMuMu"} };
	for (unsigned int index = 0; index < refSelections_dimuon.size(); ++index) {
		string selection = refSelections_dimuon.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
	const boost::array<string, 1> refSelections_dielectron = { {"TTbarEE"} };
	for (unsigned int index = 0; index < refSelections_dielectron.size(); ++index) {
		string selection = refSelections_dielectron.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
 	const boost::array<string, 1> refSelections_dilepton = { {"TTbarEMu"} };
	for (unsigned int index = 0; index < refSelections_dilepton.size(); ++index) {
		string selection = refSelections_dilepton.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
	const boost::array<string, 1> refSelections_dimuon_loose = { {"TTbarMuMuLoose"} };
	for (unsigned int index = 0; index < refSelections_dimuon_loose.size(); ++index) {
		string selection = refSelections_dimuon_loose.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
	const boost::array<string, 1> refSelections_dielectron_loose = { {"TTbarEELoose"} };
	for (unsigned int index = 0; index < refSelections_dielectron_loose.size(); ++index) {
		string selection = refSelections_dielectron_loose.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEELooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
 	const boost::array<string, 1> refSelections_dilepton_loose = { {"TTbarEMuLoose"} };
	for (unsigned int index = 0; index < refSelections_dilepton_loose.size(); ++index) {
		string selection = refSelections_dilepton_loose.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
}

void EventCountAnalyser::setHistogramLabels() {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	for (unsigned int index = 0; index < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++index) {
		unsigned int bin(index + 1);
		string binLabel = TTbarMuMuReferenceSelection::StringSteps[index];

		histMan_->H1D("TTbarMuMuRefSelection")->GetXaxis()->SetBinLabel(bin, binLabel.c_str());
		histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->GetXaxis()->SetBinLabel(bin, binLabel.c_str());

	}
}

EventCountAnalyser::EventCountAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //

		//dilepton signal selections
		topMuMuRefSelection_(new TopPairMuMuReferenceSelection()), 
		topEERefSelection_(new TopPairEEReferenceSelection()), 
		topEMuRefSelection_(new TopPairEMuReferenceSelection()),
		topMuMuLooseRefSelection_(new TopPairMuMuLooseReferenceSelection()), 
		topEELooseRefSelection_(new TopPairEELooseReferenceSelection()), 
		topEMuLooseRefSelection_(new TopPairEMuLooseReferenceSelection()){ 
		
}

EventCountAnalyser::~EventCountAnalyser() {
}

} /* namespace BAT */
