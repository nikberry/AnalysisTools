/*********************************************************|                                                                                                                                                                                                                     
 *          TopPairEMuLooseReferenceSelection.h           |
 *                                                        |
 *                  Author: N.Berry                       |
 *                                                        |
 *********************************************************/

#ifndef TopPairEMuLooseReferenceSelection_H_
#define TopPairEMuLooseReferenceSelection_H_

#include "BasicSelection.h"

namespace BAT {

namespace TTbarEMuLooseReferenceSelection {
enum Step {
	EventCleaningAndTrigger,
	DiLeptonSelection,
	AtLeastOneGoodJets,
	AtLeastOnePhotonPreSelection,
	AtLeastOnePhotonPostSelection,
	JustOneGoodPhotonPostSelection,
	NUMBER_OF_SELECTION_STEPS
};

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = { //
		"Event cleaning and High Level Trigger", //
				"di lepton selection", //
				">= 1 jets",
				">=1 Photon Presel",
				">=1 Photon Postsel",
				"==1 Photon Postsel"
		};
}

class TopPairEMuLooseReferenceSelection: public BAT::BasicSelection {
public:
	TopPairEMuLooseReferenceSelection(unsigned int numberOfSelectionSteps =
			TTbarEMuLooseReferenceSelection::NUMBER_OF_SELECTION_STEPS);
	virtual ~TopPairEMuLooseReferenceSelection();

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
	virtual bool isIsolatedElectron(const LeptonPointer lepton) const;
	virtual bool isIsolatedMuon(const LeptonPointer lepton) const;
	
	virtual bool passesSelectionStep(const EventPtr event, unsigned int selectionStep) const;

	virtual bool passesEventCleaning(const EventPtr event) const;
	virtual bool passesTriggerSelection(const EventPtr event) const;
	virtual bool passesDiLeptonSelection(const EventPtr event) const;
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
//	virtual void signalLeptons(const EventPtr event);
	virtual const PhotonCollection signalPhotons(const EventPtr event) const;
	virtual const PhotonCollection nMinusOnePhotons(const EventPtr event, TString cut) const;
	virtual const JetCollection cleanedJets(const EventPtr event) const;
        virtual const JetCollection cleanedBJets(const EventPtr event) const;
};

typedef boost::shared_ptr<TopPairEMuLooseReferenceSelection> TopPairEMuLooseReferenceSelectionPointer;

} /* namespace BAT */
#endif /* TopPairEMuLooseReferenceSelection_H_ */
