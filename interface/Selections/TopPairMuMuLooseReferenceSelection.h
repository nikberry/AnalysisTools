/*********************************************************|
 * 	    TopPairMuMuLooseReferenceSelection.h	  |
 *							  |
 *  		    Author: N.Berry			  |
 *     							  |
 *********************************************************/

#ifndef TOPPAIRMUMULOOSEREFERENCESELECTION_H_
#define TOPPAIRMUMULOOSEREFERENCESELECTION_H_

#include "BasicSelection.h"

namespace BAT {

namespace TTbarMuMuLooseReferenceSelection {
enum Step {
	EventCleaningAndTrigger,
	DiMuonSelection,
	ZmassVeto,
	AtLeastOneGoodJets,
	MetCut,
	AtLeastOnePhotonPreSelection,
	AtLeastOnePhotonPostSelection,
	JustOneGoodPhotonPostSelection,
	NUMBER_OF_SELECTION_STEPS
};

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = { //
		"Event cleaning and High Level Trigger", //
		"di muon selection", //
		"z mass veto", //
		">= 1 jets",
		"met cut",
		">=1 Photon Presel",
		">=1 Photon Postsel",
		"==1 Photon Postsel"
		};
}

class TopPairMuMuLooseReferenceSelection: public BAT::BasicSelection {
public:
	TopPairMuMuLooseReferenceSelection(unsigned int numberOfSelectionSteps =
			TTbarMuMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS);
	virtual ~TopPairMuMuLooseReferenceSelection();

	virtual bool isGoodJet(const JetPointer jet) const;
        virtual bool isBJet(const JetPointer jet) const;
	virtual bool isGoodMuon(const MuonPointer muon) const;
	virtual bool isGoodElectron(const ElectronPointer electron) const;
	virtual bool isGoodPhoton(const PhotonPointer photon, const EventPtr event) const;
	virtual bool isNminusOnePhoton(const PhotonPointer photon, const EventPtr event, TString cut) const;
	
	//definitions of loose objects
	virtual bool isLooseElectron(const ElectronPointer electron) const;
	virtual bool isLooseMuon(const MuonPointer electron) const;
	
	//isolation definitions
	virtual bool isIsolated(const LeptonPointer lepton) const;

	virtual bool passesSelectionStep(const EventPtr event, unsigned int selectionStep) const;

	virtual bool passesEventCleaning(const EventPtr event) const;
	virtual bool passesTriggerSelection(const EventPtr event) const;
	virtual bool passesDiMuonSelection(const EventPtr event) const;
	virtual bool passesZmassVeto(const EventPtr event) const;
	virtual bool hasAtLeastNGoodJets(const EventPtr event, int Njets) const;
	virtual bool passesMetCut(const EventPtr event) const;
	virtual bool hasAtLeastOnePhotonPreSelection(const EventPtr event) const;
	virtual bool hasAtLeastOneGoodPhotonPostSelection(const EventPtr event) const;
	virtual bool hasJustOneGoodPhotonPostSelection(const EventPtr event) const;

	virtual const PhotonCollection AllPhotonsPreSelection(const EventPtr event) const;
	virtual const LeptonPointer signalLepton(const EventPtr event) const;
	virtual const ElectronCollection goodElectrons(const EventPtr event) const;
	virtual const MuonCollection goodMuons(const EventPtr event) const;
	virtual const ElectronCollection signalElectrons(const EventPtr event) const;
	virtual const MuonCollection signalMuons(const EventPtr event) const;
	virtual const PhotonCollection signalPhotons(const EventPtr event) const;
	virtual const PhotonCollection nMinusOnePhotons(const EventPtr event, TString cut) const;
	virtual const JetCollection cleanedJets(const EventPtr event) const;
	virtual const JetCollection cleanedBJets(const EventPtr event) const;
};

typedef boost::shared_ptr<TopPairMuMuLooseReferenceSelection> TopPairMuMuLooseReferenceSelectionPointer;

} /* namespace BAT */
#endif /* TOPPAIRMUMULOOSEREFERENCESELECTION_H_ */
