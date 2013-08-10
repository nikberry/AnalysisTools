/*
 * TTbarDiLeptonAnalyser.h
 *
 *  Created on: 22 Mar 2012
 *      Author: phil
 */

#ifndef TTBARPLUSMETANALYSER_H_
#define TTBARPLUSMETANALYSER_H_

#include "BasicAnalyser.h"
#include "METAnalyser.h"
#include "DiElectronAnalyser.h"
#include "DiMuonAnalyser.h"
#include "EMuAnalyser.h"
#include "ElectronAnalyser.h"
#include "MuonAnalyser.h"
#include "PhotonAnalyser.h"
#include "VertexAnalyser.h"
#include "JetAnalyser.h"
#include "../Selections/BasicSelection.h"

#include <string>

namespace BAT {

class TTbarDiLeptonAnalyser: public BAT::BasicAnalyser {
public:
	TTbarDiLeptonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "TTbarDiLeptonAnalysis");
	virtual ~TTbarDiLeptonAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();
	void muMuSignalAnalysis(const EventPtr);
	void eESignalAnalysis(const EventPtr);
	void eMuSignalAnalysis(const EventPtr);

private:
	//signal selections
	SelectionPointer topMuMuRefSelection_, topEERefSelection_, topEMuRefSelection_;

	//signal region
	METAnalyserLocalPtr metAnalyserMuMuRefSelection_, metAnalyserEERefSelection_, metAnalyserEMuRefSelection_;

	JetAnalyserLocalPtr jetAnalyserMuMuRefSelection_, jetAnalyserEERefSelection_, jetAnalyserEMuRefSelection_;

	DiElectronAnalyserLocalPtr diElectronAnalyserEERefSelection_;
	DiMuonAnalyserLocalPtr diMuonAnalyserMuMuRefSelection_;
	EMuAnalyserLocalPtr eMuAnalyserEMuRefSelection_;

	//photon anlyser
	PhotonAnalyserLocalPtr photonAnalyserMuMuRefSelection_, photonAnalyserEERefSelection_, photonAnalyserEMuRefSelection_;


};

typedef boost::scoped_ptr<BAT::TTbarDiLeptonAnalyser> TTbarDiLeptonAnalyserLocalPtr;
} /* namespace BAT */
#endif /* TTBARPLUSMETANALYSER_H_ */
