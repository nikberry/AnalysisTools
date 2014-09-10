/*********************************************************|                                                                                                                                                                                                                     
 *          TTbarLooseSelectionAnalyser.h                 |
 *                                                        |
 *                  Author: N.Berry                       |
 *                                                        |
 *********************************************************/

#ifndef TTBARLOOSESELECTIONANALYSER_H_
#define TTBARLOOSESELECTIONANALYSER_H_

#include "BasicAnalyser.h"
#include "METAnalyser.h"
#include "DiElectronAnalyser.h"
#include "DiMuonAnalyser.h"
#include "EMuAnalyser.h"
#include "ElectronAnalyser.h"
#include "MuonAnalyser.h"
#include "PhotonAnalyser.h"
#include "SignalPhotonAnalyser.h"
#include "VertexAnalyser.h"
#include "JetAnalyser.h"
#include "../Selections/BasicSelection.h"

#include <string>

namespace BAT {

class TTbarLooseSelectionAnalyser: public BAT::BasicAnalyser {
public:
	TTbarLooseSelectionAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "TTbarLooseSelectionAnalysis");
	virtual ~TTbarLooseSelectionAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();

	void muMuSignalAnalysis(const EventPtr);
	void eESignalAnalysis(const EventPtr);
	void eMuSignalAnalysis(const EventPtr);

private:
	//signal selections
	SelectionPointer topMuMuLooseRefSelection_, topEELooseRefSelection_, topEMuLooseRefSelection_;

	//signal region
	METAnalyserLocalPtr metAnalyserMuMuRefSelection_, metAnalyserEERefSelection_, metAnalyserEMuRefSelection_;

	JetAnalyserLocalPtr jetAnalyserMuMuRefSelection_, jetAnalyserEERefSelection_, jetAnalyserEMuRefSelection_;

	DiElectronAnalyserLocalPtr diElectronAnalyserEERefSelection_;
	DiMuonAnalyserLocalPtr diMuonAnalyserMuMuRefSelection_;
	EMuAnalyserLocalPtr eMuAnalyserEMuRefSelection_;

	//photon anlyser
	PhotonAnalyserLocalPtr photonAnalyserMuMuRefSelection_, photonAnalyserEERefSelection_, photonAnalyserEMuRefSelection_;

	//ttphoton anlyser
	SignalPhotonAnalyserLocalPtr ttphotonAnalyserMuMuRefSelection_, ttphotonAnalyserEERefSelection_, ttphotonAnalyserEMuRefSelection_;

};

typedef boost::scoped_ptr<BAT::TTbarLooseSelectionAnalyser> TTbarLooseSelectionAnalyserLocalPtr;
} /* namespace BAT */
#endif /* TTBARLOOSESELECTIONANALYSER_H_ */

